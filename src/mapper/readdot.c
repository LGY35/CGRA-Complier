#include <graphviz/gvc.h>
#include "readdot.h"
#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"
#include "dfg.h"
#include "operation.h"

int find_node(struct Graph* dfg, char* name)
{
    for (int i = 0; i < dfg->node_num; i++) {
        if (name == dfg->nodes[i].name) {
            return i;
        }
    }
    return -1;
}

void add_nodes(Agraph_t *g, struct Graph* dfg, int scheduled)
{
    Agnode_t *n;
    int node_id = 0, const_id = 0;
    int in_degree,out_degree;
    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
        in_degree = agdegree(g, n, TRUE, FALSE);
        out_degree = agdegree(g, n, FALSE, TRUE);
        dfg->nodes[node_id].name = agnameof(n);
        dfg->nodes[node_id].op = get_op(agget(n, "opcode"));
        if (is_const(dfg->nodes[node_id].op)) {
            char* val_str = agget(n, "val");
            if (val_str && val_str[0]) {
                dfg->nodes[node_id].val = atoi(val_str);
            } else {
                dfg->nodes[node_id].val = IN_VALID;
            }
            val_str = agget(n, "llvm");
            if (val_str && val_str[0]) {
                dfg->nodes[node_id].llvm_name = val_str;
            } else {
                dfg->nodes[node_id].llvm_name = NULL;
            }
        }
        if (scheduled) {
            dfg->nodes[node_id].schedule = atoi(agget(n, "schedule"));
            if (dfg->nodes[node_id].schedule > dfg->max_schedule) {
                dfg->max_schedule = dfg->nodes[node_id].schedule;
            }
        } else {
            dfg->nodes[node_id].schedule = 0;
        }
        dfg->nodes[node_id].ins = rpmalloc(sizeof(struct In_Conn) * in_degree);
        dfg->nodes[node_id].outs = rpmalloc(sizeof(struct Out_Conn) * out_degree);
        memset(dfg->nodes[node_id].ins, IN_VALID, sizeof(struct In_Conn) * in_degree);
        memset(dfg->nodes[node_id].outs, IN_VALID, sizeof(struct Out_Conn) * out_degree);
        node_id++;
    }
}

void add_edges(Agraph_t *g, struct Graph* dfg)
{
    Agnode_t *n;
    Agedge_t *e;
    int in_node, out_node, operand, in_pos, out_pos;
    char* attr;
    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
        for (e = agfstout(g, n); e; e = agnxtout(g, e)) {
            in_node = find_node(dfg, agnameof(aghead(e)));
            out_node = find_node(dfg, agnameof(agtail(e)));
            in_pos = dfg->nodes[in_node].in_degree;
            out_pos = dfg->nodes[out_node].out_degree;
            operand = atoi(agget(e, "operand"));

            dfg->nodes[in_node].ins[in_pos].node = out_node;
            dfg->nodes[in_node].ins[in_pos].operand = operand;
            dfg->nodes[out_node].outs[out_pos].node = in_node;
            
            if (is_const(dfg->nodes[out_node].op)) {
                dfg->nodes[in_node].ins[in_pos].attr = ATTR_CONST;
            }

            attr = agget(e, "type");
            if (attr && attr[0]) {
                if (!strcmp(attr, "rev")) {
                    printf("reverse edge will be supported in future");
                    exit(1);
                    dfg->nodes[in_node].ins[in_pos].attr = ATTR_REV;
                    dfg->nodes[out_node].outs[out_pos].attr = ATTR_REV;
                } else if (!strcmp(attr, "order")) {
                    dfg->nodes[in_node].ins[in_pos].operand = -1;
                    dfg->nodes[in_node].ins[in_pos].attr = ATTR_ORDER;
                    dfg->nodes[out_node].outs[out_pos].attr = ATTR_ORDER;
                } else if (!strcmp(attr, "const_base")) {
                    dfg->nodes[in_node].ins[in_pos].attr = ATTR_CONST_BASE;
                    dfg->nodes[out_node].outs[out_pos].attr = ATTR_CONST_BASE;
                } else {
                    printf("un-recognized edge attribute: %s", attr);
                    exit(1);
                }
            } 

            dfg->nodes[in_node].in_degree++;
            dfg->nodes[out_node].out_degree++;
        }
    }
}

static FILE* fp;
static Agraph_t *g;
static GVC_t *gvc;

struct Graph* read_dot(char* filename, int scheduled) 
{
    Agnode_t *n;

    fp = fopen(filename,"r");
    if (!fp) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    gvc = gvContext();
    g = agread(fp, 0);

    int const_num = 0, node_num = 0;
    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
        if(!strcmp(agget(n, "opcode"), "const")) {
            const_num++;
            node_num++;
        } else {
            node_num++;
        }
    }
    struct Graph* dfg = init_dfg(node_num, const_num);

    add_nodes(g, dfg, scheduled);
    add_edges(g, dfg);
    
    return dfg;
}

char* get_edge_attr_name(enum Edge_Attr attr)
{
    if (attr == ATTR_IN_VALID) {
        return "";
    } else if (attr == ATTR_CONST) {
        return "";
    } else if (attr == ATTR_CONST_BASE) {
        return "const_base";
    } else if (attr == ATTR_ORDER) {
        return "order";
    } else if (attr == ATTR_REV) {
        return "rev";
    }
    printf("unrecognized edge attribute");
    exit(1);
    return NULL;
}

void output_dot(struct Graph* dfg, char* filename) 
{
    GVC_t *gvc;
    Agraph_t *g;
    Agnode_t *n;
    Agedge_t *e;

    gvc = gvContext();
    g = agopen("G", Agdirected, NULL);

    // Output nodes
    for (int i = 0; i < dfg->node_num; i++) {
        n = agnode(g, dfg->nodes[i].name, 1);
        agsafeset(n, "opcode", get_op_name(dfg->nodes[i].op), "");
        if (is_const(dfg->nodes[i].op)) {
            char val_str[16];
            sprintf(val_str, "%d", dfg->nodes[i].val);
            agsafeset(n, "val", val_str, "");
        }
    }

    // Output edges
    int in_node, out_node;
    for (int i = 0; i < dfg->node_num; i++) {
        for (int j = 0; j < dfg->nodes[i].in_degree; j++) {
            out_node = dfg->nodes[i].ins[j].node;
            in_node = i;
            n = agnode(g, dfg->nodes[out_node].name, 0);
            Agnode_t *head = agnode(g, dfg->nodes[in_node].name, 0);
            e = agedge(g, n, head, NULL, 1);
            char *operand_str = rpmalloc(16);
            sprintf(operand_str, "%d", dfg->nodes[in_node].ins[j].operand);
            agsafeset(e, "operand", operand_str, "");

            if (dfg->nodes[in_node].ins[j].attr != ATTR_IN_VALID) {
                agsafeset(e, "type", get_edge_attr_name(dfg->nodes[in_node].ins[j].attr), "");
            }
        }
    }

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "dot", filename);

    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}

void clear_dot()
{
    agclose(g);
    gvFreeContext(gvc);
    fclose(fp);
}