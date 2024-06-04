#include "dfg.h"
#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"
#include "operation.h"

#pragma region edge
int is_const_edge(enum Edge_Attr attr)
{
    return attr == ATTR_CONST || attr == ATTR_CONST_BASE;
}

int is_dfg_edge(enum Edge_Attr attr)
{
    return attr == ATTR_IN_VALID;
}

void dfg_in_degree(struct Graph* dfg, int node, int* r_deg, int* non_r_deg)
{
    int i;
    for (i = 0; i < dfg->nodes[node].in_degree; i++) {
        if (is_dfg_edge(dfg->nodes[node].ins[i].attr)) {
            int in_node = dfg->nodes[node].ins[i].node;
            if (dfg->nodes[in_node].op == ID_ROUT) {
                (*r_deg)++;
            } else {
                (*non_r_deg)++;
            }
        }
    }
}

void dfg_out_degree(struct Graph* dfg, int node, int* r_deg, int* non_r_deg)
{
    int i, deg = 0;
    for (i = 0; i < dfg->nodes[node].out_degree; i++) {
        if (is_dfg_edge(dfg->nodes[node].outs[i].attr)) {
            int out_node = dfg->nodes[node].outs[i].node;
            if (dfg->nodes[out_node].op == ID_ROUT) {
                (*r_deg)++;
            } else {
                (*non_r_deg)++;
            }
        }
    }
}

int is_schedule_edge(enum Edge_Attr attr)
{
    return attr == ATTR_IN_VALID || attr == ATTR_ORDER;
}
#pragma endregion

#pragma region degree
int schedule_out_degree(struct Graph* dfg, int node)
{
    int in_degree = 0;
    for (int i = 0; i < dfg->nodes[node].out_degree; i++) {
        if (is_schedule_edge(dfg->nodes[node].outs[i].attr)) {
            in_degree++;
        }
    }
    return in_degree;
}

int schedule_in_degree(struct Graph* dfg, int node)
{
    int in_degree = 0;
    for (int i = 0; i < dfg->nodes[node].in_degree; i++) {
        if (is_schedule_edge(dfg->nodes[node].ins[i].attr)) {
            in_degree++;
        }
    }
    return in_degree;
}

int const_in_degree(struct Graph* dfg, int node)
{
    int in_degree = 0;
    for (int i = 0; i < dfg->nodes[node].in_degree; i++) {
        if (is_const_edge(dfg->nodes[node].ins[i].attr)) {
            in_degree++;
        }
    }
    return in_degree;
}

int const_base_in_degree(struct Graph* dfg, int node)
{
    int in_degree = 0;
    for (int i = 0; i < dfg->nodes[node].in_degree; i++) {
        if (dfg->nodes[node].ins[i].attr == ATTR_CONST_BASE) {
            in_degree++;
        }
    }
    return in_degree;
}
#pragma endregion

#pragma region Schedule
void Schedule_ALAP(struct Graph* dfg)
{
    int i, j, node, in_node, out_node;
    STK_stack stack = STK_init();
    // index[i][0] if 1 the node still in graph, 0 then has removed (in degree is 0) 
    // index[i][1] is the in degree of i'th node (dfg->nodes[i])
    int(*index)[2] = rpmalloc(sizeof(int) * dfg->node_num * 2);
    
    // 拓扑排序
    for(i = 0; i < dfg->node_num; i++) {
        if (!is_const(dfg->nodes[i].op)) {
            index[i][0] = 1;
            index[i][1] = schedule_out_degree(dfg, i);
            if (index[i][1] == 0) {
                index[i][0] = 0;
                dfg->nodes[i].schedule = 0;
                STK_push(&stack, i);
            }
        }
    }

    while (stack->top) {
        node = STK_pop(&stack);
        for (i = 0; i < dfg->nodes[node].in_degree; i++) {
            if (is_schedule_edge(dfg->nodes[node].ins[i].attr)) {
                in_node = dfg->nodes[node].ins[i].node;
                if (dfg->nodes[in_node].schedule > dfg->nodes[node].schedule - 1) {
                    dfg->nodes[in_node].schedule = dfg->nodes[node].schedule - 1;
                }
                if (index[in_node][0]) {
                    index[in_node][1]--;
                    if (index[in_node][1] == 0) {
                        index[in_node][0] = 0;
                        STK_push(&stack, in_node);
                        if (dfg->nodes[in_node].schedule < dfg->max_schedule) {
                            dfg->max_schedule = dfg->nodes[in_node].schedule;
                        }
                    }
                }
            }
        }
    }
    // check
    for (i = 0; i < dfg->node_num; i++) {
        if (!is_const(dfg->nodes[i].op) && index[i][0]) {
            printf("Topology sort un-successful, there may be circle in the graph without reverse edge!");
            exit(1);
        }
    }
    dfg->max_schedule = -dfg->max_schedule;
    for (i = 0; i < dfg->node_num; i++) {
        if (!is_const(dfg->nodes[i].op)) {
            dfg->nodes[i].schedule += dfg->max_schedule;
        }
    }
    rpfree(index);
    STK_clear(stack);
}
#pragma endregion

#pragma region transform
int cnt = 0, cnt_2 = 0;
void insert_rout(int prev, int out_pos, int next, int in_pos, struct Graph* dfg)
{
    cnt++;
    dfg->nodes[prev].outs[out_pos].node = dfg->node_num;
    dfg->nodes[next].ins[in_pos].node = dfg->node_num;


    dfg->nodes[dfg->node_num].name = rpmalloc(16);
    sprintf(dfg->nodes[dfg->node_num].name, "rout%d", dfg->node_num);
    dfg->nodes[dfg->node_num].op = ID_ROUT;
    dfg->nodes[dfg->node_num].val = IN_VALID;
    dfg->nodes[dfg->node_num].in_degree = 1;
    dfg->nodes[dfg->node_num].out_degree = 1;

    dfg->nodes[dfg->node_num].ins = rpmalloc(sizeof(struct In_Conn));
    dfg->nodes[dfg->node_num].outs = rpmalloc(sizeof(struct Out_Conn));

    dfg->nodes[dfg->node_num].ins->node = prev;
    dfg->nodes[dfg->node_num].ins->attr = dfg->nodes[prev].outs[out_pos].attr;
    dfg->nodes[dfg->node_num].ins->operand = 0;
    dfg->nodes[dfg->node_num].outs->node = next;
    dfg->nodes[dfg->node_num].outs->attr = dfg->nodes[next].ins[in_pos].attr;
    dfg->nodes[dfg->node_num].schedule = dfg->nodes[prev].schedule + 1;

    dfg->node_num++;
}

int get_min_sche(struct Graph* dfg, int n)
{
    int max_in_sche = -1, tmp_n;
    if (schedule_in_degree(dfg, n) > 0) {
        for (int i = 0; i < dfg->nodes[n].in_degree; i++) {
            if (is_schedule_edge(dfg->nodes[n].ins[i].attr)) {
                tmp_n = dfg->nodes[n].ins[i].node;
                if (dfg->nodes[tmp_n].schedule > max_in_sche) {
                    max_in_sche = dfg->nodes[tmp_n].schedule;
                }
            }
        }
        return max_in_sche + 1;
    }
    return dfg->nodes[n].schedule;
}

void indent_schedule(struct Graph* dfg)
{
    int i, min_sche, n, out_of_n;
    STK_stack stack = STK_init();
    
    for(i = 0; i < dfg->node_num; i++) {
        if (!is_const(dfg->nodes[i].op) && dfg->nodes[i].in_degree > 0) {
            min_sche = get_min_sche(dfg, i);
            assert(dfg->nodes[i].schedule >= min_sche);
            if (dfg->nodes[i].schedule > min_sche) {
                STK_push(&stack, i);
            }
        }
    }

    while (stack->top) {
        n = STK_pop(&stack);
        min_sche = get_min_sche(dfg, n);
        dfg->nodes[n].schedule = get_min_sche(dfg, n);        
        // Calc possible out node of n that changed
        for (i = 0; i < dfg->nodes[n].out_degree; i++) {
            out_of_n = dfg->nodes[n].outs[i].node;
            min_sche = get_min_sche(dfg, out_of_n);
            assert(dfg->nodes[out_of_n].schedule >= min_sche);
            if (dfg->nodes[out_of_n].schedule > min_sche) {
                STK_push(&stack, out_of_n);
            }
        }
    }
    STK_clear(stack);
}

int calc_num_rout_needed(struct Graph* dfg)
{
    int num = 0;
    int i, j, prev, next, in_pos, out_pos, k, node_num = dfg->node_num;
    for (i = 0; i < node_num; i++) {
        if (!is_const(dfg->nodes[i].op)) {
            for (j = 0; j < dfg->nodes[i].out_degree; j++) {
                if (is_dfg_edge(dfg->nodes[i].outs[j].attr)) {
                    next = dfg->nodes[i].outs[j].node;                 
                    prev = i;
                    out_pos = j;
                    num += dfg->nodes[next].schedule - dfg->nodes[prev].schedule - 1;
                }
            }
        }
    }
    return num;
}

void trans_dfg(struct Graph* dfg, int num_rout)
{
    int i, j, prev, next, in_pos, out_pos, k, node_num = dfg->node_num, insert_num;
    dfg->nodes = rprealloc(dfg->nodes, (num_rout + dfg->node_num) * sizeof(struct Node));
    for (i = 0; i < node_num; i++) {
        if (!is_const(dfg->nodes[i].op)) {
            for (j = 0; j < dfg->nodes[i].out_degree; j++) {
                if (is_dfg_edge(dfg->nodes[i].outs[j].attr)) {
                    next = dfg->nodes[i].outs[j].node;
                    // find in_pos
                    for (in_pos = 0; in_pos < dfg->nodes[next].in_degree; in_pos++) {
                        if (dfg->nodes[next].ins[in_pos].node == i) {
                            break;
                        }
                    }
                    assert(in_pos < dfg->nodes[next].in_degree);
                    
                    prev = i;
                    out_pos = j;
                    insert_num = dfg->nodes[next].schedule - dfg->nodes[prev].schedule - 1;
                    for (k = 0; k < insert_num; k++) {
                        cnt_2++;
                        insert_rout(prev, out_pos, next, in_pos, dfg);
                        prev = dfg->node_num - 1;
                        out_pos = 0;
                    }
                }
            }
        }
    }
}
#pragma endregion

int handle_dfg(struct Graph* dfg)
{
    Schedule_ALAP(dfg);
    // ALAP will schecdule order edge as late as possible, but they can be stored earlier instead of add a rout node
    // example as follow
    /*
        add->store0
        add->neg0
        add->abs0
        abs->store1
        store0->store1[order edge]

        by order edge, store1 must be saved before store1
        ALAP will schedule store1 at time 3, and store1 at time 2, add at time 0
        If this is followed, there had to be an rout between add and store
        indent will indent store0 back to time 1, and avoid adding the rout node
    */
    indent_schedule(dfg);
    int num_rout = calc_num_rout_needed(dfg);
    if (num_rout) {
        trans_dfg(dfg, num_rout);
    }
    return num_rout;
}

struct Graph* init_dfg(int node_num, int const_num)
{
    struct Graph* dfg = (struct Graph*)rpmalloc(sizeof(struct Graph));
    dfg->max_schedule = 0;
    dfg->loop_len = 0;
    dfg->node_num = node_num;
    dfg->const_num = const_num;
    dfg->nodes = (struct Node*)rpmalloc(sizeof(struct Node) * node_num);
    return dfg;
}

void clear_dfg(struct Graph* dfg)
{
    for (int i = 0; i < dfg->node_num; i++) {
        rpfree(dfg->nodes[i].ins);
        rpfree(dfg->nodes[i].outs);
    }
    rpfree(dfg->nodes);
    rpfree(dfg);
}