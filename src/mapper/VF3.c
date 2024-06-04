#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"
#include "dfg.h"
#include "CGRA.h"
#include "VF3.h"
#include "operation.h"
#include "bitmatrix.h"

static struct Graph* dfg = NULL; 
static struct CGRA* cgra = NULL;

//=========================================================================================
// Sorting dfg node
//=========================================================================================
#pragma region Sorting dfg node
#define EQUAL_PROP 0
#define HIGER_PROP 1
#define LOWER_PROP 2
struct Sorted_Nodes {
    int num;
    int* nodes;
};
static int* n_sorted = NULL;
static struct Sorted_Nodes sort_res = {
    .num = 0,
    .nodes = NULL
};

int compare_PE_num(int n_1, int n_2)
{
    // compare nums of PE support node's operation
    int pe_cnt_1 = cgra->sup_op_PE_cnt[dfg->nodes[n_1].op];
    int pe_cnt_2 = cgra->sup_op_PE_cnt[dfg->nodes[n_2].op];
    if (pe_cnt_1 > pe_cnt_2) {
        return HIGER_PROP;
    } else if (pe_cnt_1 < pe_cnt_2) {
        return LOWER_PROP;
    }
    return EQUAL_PROP;
}

int compare_conn(int n_1, int n_2)
{
    // compare number of connections with nodes already sorted
    // compare the total node degree without const
    int i;
    int conn_1 = 0, conn_2 = 0, tmp_n;
    int degree_1 = 0, degree_2 = 0;
    // calc out deg
    for (i = 0; i < dfg->nodes[n_1].out_degree; i++) {
        if (is_dfg_edge(dfg->nodes[n_1].outs[i].attr)) {
            degree_1++;
            tmp_n = dfg->nodes[n_1].outs[i].node;
            if (n_sorted[tmp_n]) { // in sorted nodes
                conn_1++;
            }
        }
    }
    for (i = 0; i < dfg->nodes[n_2].out_degree; i++) {
        if (is_dfg_edge(dfg->nodes[n_2].outs[i].attr)) {
            degree_2++;
            tmp_n = dfg->nodes[n_2].outs[i].node;
            if (n_sorted[tmp_n]) {
                conn_2++;
            }
        }
    }

    // calc in deg
    for (i = 0; i < dfg->nodes[n_1].in_degree; i++) {
        if (is_dfg_edge(dfg->nodes[n_1].ins[i].attr)) {
            degree_1++;
            tmp_n = dfg->nodes[n_1].ins[i].node;
            if (n_sorted[tmp_n]) {
                conn_1++;
            }
        }
    }
    for (i = 0; i < dfg->nodes[n_2].in_degree; i++) {
        if (is_dfg_edge(dfg->nodes[n_2].ins[i].attr)) {
            degree_2++;
            tmp_n = dfg->nodes[n_2].ins[i].node;
            if (n_sorted[tmp_n]) {
                conn_2++;
            }
        }
    }
    
    if (conn_1 < conn_2) {
        return HIGER_PROP;
    } else if (conn_1 > conn_2) {
        return LOWER_PROP;
    }

    if (degree_1 < degree_2) {
        return HIGER_PROP;
    } else if (degree_1 > degree_2) {
        return LOWER_PROP;
    }
    return EQUAL_PROP;
}


int compare_prob(int n_1, int n_2) 
{
    if (n_1 == IN_VALID) {
        return 1;
    }

    int res = -1; 
    
    res = compare_PE_num(n_1, n_2);
    if (res ==  HIGER_PROP) {
        return 1;
    } else if (res == LOWER_PROP) {
        return 0;
    }

    res = compare_conn(n_1, n_2);
    if (res ==  HIGER_PROP) {
        return 1;
    } else if (res == LOWER_PROP) {
        return 0;
    }

    // rout can be mapped on gr, which has low rejection probability
    if (dfg->nodes[n_1].op == ID_ROUT && dfg->nodes[n_2].op != ID_ROUT) {
        return 1;
    } else if (dfg->nodes[n_1].op != ID_ROUT && dfg->nodes[n_2].op == ID_ROUT) {
        return 0;
    }

    // 
    // if (dfg->nodes[n_1].schedule > dfg->nodes[n_2].schedule) {
    //     return 1;
    // } else {
    //     return 0;
    // }

    return 0;
}

int get_first_sort_node()
{
    int n, candi_n = IN_VALID;
    for (n = 0; n < dfg->node_num; n++) {
        // rout node should be only mapped from a connected node
        if (!is_const(dfg->nodes[n].op) && dfg->nodes[n].op != ID_ROUT && !n_sorted[n]) {
            if (compare_prob(candi_n, n)) {
                candi_n = n;
            }
        }
    }
    if (candi_n != IN_VALID) {
        n_sorted[candi_n] = 1;
    }
    return candi_n;
}

int get_next_sort_node()
{
    int i, j, tmp_n, conn_n, candi_n = -1;
    for (i = 0; i < sort_res.num; i++) {
        if (sort_res.nodes[i] != IN_VALID) {
            tmp_n = sort_res.nodes[i];
            for (j = 0; j < dfg->nodes[tmp_n].in_degree; j++) {
                if (is_dfg_edge(dfg->nodes[tmp_n].ins[j].attr)) {
                    conn_n = dfg->nodes[tmp_n].ins[j].node;
                    if (!n_sorted[conn_n] && compare_prob(candi_n, conn_n)) {
                        candi_n = conn_n;
                    }
                }
            }
            for (j = 0; j < dfg->nodes[tmp_n].out_degree; j++) {
                if (is_dfg_edge(dfg->nodes[tmp_n].outs[j].attr)) {
                    conn_n = dfg->nodes[tmp_n].outs[j].node;
                    if (!n_sorted[conn_n] && compare_prob(candi_n, conn_n)) {
                        candi_n = conn_n;
                    }
                }
            }
        } else {
            break;
        }
    }
    if (candi_n == IN_VALID) {
        candi_n = get_first_sort_node();
    }
    if (candi_n != IN_VALID) {
        n_sorted[candi_n] = 1;
    }
    return candi_n;
}

void sort_dfg()
{
    int sorted_node = get_first_sort_node();
    int i = 1;

    sort_res.nodes[0] = sorted_node;
    for (i = 1; i < sort_res.num; i++) {
        sort_res.nodes[i] = get_next_sort_node();
        assert(sort_res.nodes[i] != IN_VALID);
    }
    // for (i = 0; i < sort_res.num; i++) {
    //     printf("%d: %s\n", i, dfg->nodes[sort_res.nodes[i]].name);
    // }
}
#pragma endregion
//=========================================================================================
// VF3 state operation
//=========================================================================================
#pragma region VF3 state operation
enum edge_type {
    dir_in, 
    dir_out
};
struct Pred {
    int node;
    enum edge_type e_type;
};
struct Core_2 {
    struct Bit_Matrix* g_regs;
    struct Bit_Matrix* l_regs;
    int* const_regs;
    int* PE_ts;
};
struct State {
    int core_len;
    struct Tec_Pos* core_1;
    struct Core_2 core_2;
    struct Pred* predecessors;  // one that connected node already matched
};

static struct State s = {
    .core_len = 0,
    .core_1 = NULL,
    .core_2 = {
        .g_regs = NULL,
        .const_regs = NULL,
        .l_regs = NULL,
        .PE_ts = NULL
    },
    .predecessors = NULL
};

int find_free_l_reg(int PE_pos, int t)
{
    for (int l_pos = 0; l_pos < cgra->PEs[PE_pos].l_reg; l_pos++) {
        if (!get_bit(s.core_2.l_regs, get_PE_t_pos(cgra, t, PE_pos), l_pos)) {
            return l_pos;
        }
    }
    return IN_VALID;
}

void init_state()
{
    int i, j, k, tmp_n, conn_n;
    for (i = 0; i < sort_res.num; i++) {
        tmp_n = sort_res.nodes[i];
        for (j = 0; j < dfg->nodes[tmp_n].out_degree; j++) {
            if (is_dfg_edge(dfg->nodes[tmp_n].outs[j].attr)) {
                conn_n = dfg->nodes[tmp_n].outs[j].node;
                for (k = i + 1; k < sort_res.num; k++) {
                    if(sort_res.nodes[k] == conn_n) {
                        if (
                            s.predecessors[k].node == IN_VALID ||
                            (dfg->nodes[s.predecessors[k].node].op == ID_ROUT && dfg->nodes[tmp_n].op != ID_ROUT)
                        ) {
                            s.predecessors[k].node = tmp_n;
                            s.predecessors[k].e_type = dir_out;
                        }
                    }
                }
            }
        }
        for (j = 0; j < dfg->nodes[tmp_n].in_degree; j++) {
            if (is_dfg_edge(dfg->nodes[tmp_n].ins[j].attr)) {
                conn_n = dfg->nodes[tmp_n].ins[j].node;
                for (k = i + 1; k < sort_res.num; k++) {
                    if(sort_res.nodes[k] == conn_n && s.predecessors[k].node == IN_VALID) {
                        if (
                            s.predecessors[k].node == IN_VALID ||
                            (dfg->nodes[s.predecessors[k].node].op == ID_ROUT && dfg->nodes[tmp_n].op != ID_ROUT)
                        ) {
                            s.predecessors[k].node = tmp_n;
                            s.predecessors[k].e_type = dir_in;
                        }
                    }
                }
            }
        }
    }
}

void add_pair(int node, struct Tec_Pos* PE_t)
{
    s.core_1[node].t = PE_t->t;
    s.core_1[node].pos = PE_t->pos;
    s.core_1[node].type = PE_t->type;
    s.core_1[node].l_pos = PE_t->l_pos;
    switch (PE_t->type) {
        case POS_PE: {
            s.core_2.PE_ts[get_PE_t_pos(cgra, PE_t->t, PE_t->pos)] = node;
            s.core_2.const_regs[PE_t->pos] += const_in_degree(dfg, node);
            break;
        }
        case POS_G_REG: {
            set_bit(s.core_2.g_regs, PE_t->t, PE_t->pos);
            break;
        }
        case POS_L_REG: {
            set_bit(s.core_2.l_regs, get_PE_t_pos(cgra, PE_t->t, PE_t->pos), PE_t->l_pos);
            break;
        }
        default: {
            printf("unrecognized position type %d", PE_t->type);
            exit(1);
        }  
    }
    // special handle for loop add const, has to save it in the lr register
    if (const_base_in_degree(dfg, node)) {
        s.core_1[node].const_base_l_pos = find_free_l_reg(PE_t->pos, PE_t->t);
        set_bit(s.core_2.l_regs, get_PE_t_pos(cgra, PE_t->t, PE_t->pos), s.core_1[node].const_base_l_pos);
    }
    s.core_len++;
    // if (cgra->II == 2) {
    //     switch (PE_t->type) {
    //         case POS_PE : {
    //             int x,y;
    //             get_dim_by_pos(cgra, PE_t->pos, &x, &y);
    //             printf("%s\tt: %d\tx: %d\ty: %d\n", dfg->nodes[node].name, PE_t->t, x, y);
    //             break;
    //         }
    //         case POS_G_REG : {
    //             printf("%s\tt: %d\tgr(%d)\n", dfg->nodes[node].name, PE_t->t, PE_t->pos);
    //             break;
    //         }
    //         case POS_L_REG: {
    //             int x, y;
    //             get_dim_by_pos(cgra, PE_t->pos, &x, &y);
    //             printf("%s\tt: %d\tx: %d\tx: %d lr(%d)\n", dfg->nodes[node].name, PE_t->t, x, y, s.core_1[node].l_pos);
    //             break;
    //         }
    //     }
    // };
}

void rm_pair(int node)
{
    switch (s.core_1[node].type) {
        case POS_PE: {
            s.core_2.PE_ts[get_PE_t_pos(cgra, s.core_1[node].t, s.core_1[node].pos)] = IN_VALID;
            s.core_2.const_regs[s.core_1[node].pos] -= const_in_degree(dfg, node);
            break;
        }
        case POS_G_REG: {
            rec_bit(s.core_2.g_regs, s.core_1[node].t, s.core_1[node].pos);
            break;
        }
        case POS_L_REG: {
            rec_bit(s.core_2.l_regs, get_PE_t_pos(cgra, s.core_1[node].t, s.core_1[node].pos), s.core_1[node].l_pos);
            break;
        }
        default: {
            printf("unrecognized position type %d", s.core_1[node].type);
            exit(1);
        }  
    }
    // special handle for loop add const, has to save it in the lr register
    if (const_base_in_degree(dfg, node)) {
        rec_bit(s.core_2.l_regs, get_PE_t_pos(cgra, s.core_1[node].t, s.core_1[node].pos), s.core_1[node].const_base_l_pos);
    }
    s.core_1[node].t = IN_VALID;
    s.core_1[node].pos = IN_VALID;
    s.core_1[node].type = IN_VALID;
    s.core_1[node].l_pos = IN_VALID;
    s.core_len--;
    // printf("rm node map: %s->(time: %d, x: %d, y:%d)\n",
    //     dfg->nodes[node].name,
    //     PE_t->t,
    //     PE_t->x,
    //     PE_t->y
    // );
}
#pragma endregion
//=========================================================================================
// matching dfg to cgra-tec
//=========================================================================================
#pragma region matching dfg to cgra-tec
int unmapped_and_valid_PE(struct Tec_Pos* PE_t, enum OP_ID curr_op)
{
    return PE_sup_op(cgra, PE_t->pos, curr_op) &&
            s.core_2.PE_ts[get_PE_t_pos(cgra, PE_t->t, PE_t->pos)] == IN_VALID;
}

int next_conn_PE(struct Tec_Pos* PE_t, struct M_Pos* m_pos, int curr_n, enum OP_ID curr_op, int mapped_pos, enum edge_type e_type)
{
    struct Bit_Matrix* matrix = NULL;

    if (e_type == dir_in) {
        matrix = cgra->conn_in;
    } else if (e_type == dir_out) {
        matrix = cgra->conn_out;
    }
    
    PE_t->pos = get_next_set_column(matrix, mapped_pos, m_pos);

    if (PE_t->pos != IN_VALID) {
        if (m_pos->mode == MODE_FIRST) {
            m_pos->mode = MODE_CONT;
        }
    } else {
        return 0;
    }

    while (PE_t->pos != IN_VALID) {
        if (unmapped_and_valid_PE(PE_t, curr_op)) {
            PE_t->type = POS_PE;
            return 1;
        }
        PE_t->pos = get_next_set_column(matrix, mapped_pos, m_pos);
    }
    return 0;
}

int next_not_conn_PE(struct Tec_Pos* PE_t, struct M_Pos* m_pos, int curr_n, enum OP_ID curr_op)
{
    if (m_pos->mode == MODE_FIRST) {
        m_pos->mode = MODE_CONT;
        PE_t->pos = 0;
    } else {
        PE_t->pos++;
    }
    while (PE_t->pos < cgra->x_dim * cgra->y_dim) {
        if (unmapped_and_valid_PE(PE_t, curr_op)) {
            PE_t->type = POS_PE;
            return 1; 
        }
        PE_t->pos++;
    }
    return 0;
}

int find_reg_conn(int curr_n, enum Pos_Type type)
{
    assert(type == POS_G_REG || type == POS_L_REG);
    int ret_n = IN_VALID, n, conn_n;
    for (n = 0; n < dfg->nodes[curr_n].in_degree; n++) {
        conn_n = dfg->nodes[curr_n].ins[n].node;
        if (s.core_1[conn_n].t != IN_VALID && s.core_1[conn_n].type == type) {
            if (ret_n == IN_VALID) {
                ret_n = conn_n;
            } else if (ret_n != conn_n) {
                return -2; // connecting to 2 register in different position
            }
        }
    }
    for (n = 0; n < dfg->nodes[curr_n].out_degree; n++) {
        conn_n = dfg->nodes[curr_n].outs[n].node;
        if (s.core_1[conn_n].t != IN_VALID && s.core_1[conn_n].type == type) {
            if (ret_n == IN_VALID) {
                ret_n = conn_n;
            } else if (ret_n != conn_n) {
                return -2; // connecting to 2 register in different position
            }
        }
    }
    return ret_n;
}

int next_with_conn_l(struct Tec_Pos* PE_t, enum OP_ID curr_op, int reg_n)
{
    PE_t->pos = s.core_1[reg_n].pos;
    if (curr_op == ID_ROUT && !get_bit(s.core_2.l_regs, get_PE_t_pos(cgra, PE_t->t, PE_t->pos), s.core_1[reg_n].l_pos)) {
        PE_t->l_pos = s.core_1[reg_n].l_pos;
        if (PE_t->type == POS_IN_VALID) {
            PE_t->type = POS_L_REG;
            return 1;
        } else if (PE_t->type == POS_L_REG && unmapped_and_valid_PE(PE_t, curr_op)) {
            PE_t->type = POS_PE;
            return 1;
        }
    } else {
        if (PE_t->type == POS_IN_VALID && unmapped_and_valid_PE(PE_t, curr_op)) {
            PE_t->type = POS_PE;
            return 1;
        }
    }
    return 0;
}

int next_g_reg(struct Tec_Pos* PE_t, enum OP_ID curr_op, int curr_n)
{
    int reg_n = find_reg_conn(curr_n, POS_G_REG);
    if (reg_n == IN_VALID) { // no connected register
        for (PE_t->pos = 0; PE_t->pos < cgra->g_reg_num; PE_t->pos++) {
            if (!get_bit(s.core_2.g_regs, PE_t->t, PE_t->pos)) {
                PE_t->type = POS_G_REG;
                return 1; // successfully found a g_reg
            }
        }
        return 0; // no g_reg available, no connected node mapped to g_reg
                  // can map to local reg
    } else { // has connected register
        if (reg_n != -2) { // only one connected g_reg
            assert(reg_n >= 0 && reg_n <= dfg->node_num);
            if (!get_bit(s.core_2.g_regs, PE_t->t, s.core_1[reg_n].pos)) {
                PE_t->type = POS_G_REG;
                PE_t->pos = s.core_1[reg_n].pos;
                return 1; // successfully found a g_reg
            }
        }
        return 2; // no g_reg available, but has connected node mapped to g_reg
                  // cannot map to local reg
    }
}

int next_l_reg(struct Tec_Pos* PE_t, int curr_n, enum OP_ID curr_op)
{
    int in_node = IN_VALID;
    if (dfg->nodes[curr_n].in_degree != 0) {
        in_node = dfg->nodes[curr_n].ins[0].node;
    }
    int out_node = IN_VALID;
    if (dfg->nodes[curr_n].out_degree != 0) {
        out_node = dfg->nodes[curr_n].outs[0].node;
    }

    if (
        // If has both out and in, PE->LR->PE has to be on the same position, thus II >= 3
        (out_node != IN_VALID && in_node != IN_VALID && cgra->II < 3) || 
        // LR can only be store and read from one PE, thus the in degree and out degree must be 1
        (
            (in_node != IN_VALID && dfg->nodes[curr_n].in_degree != 1) ||
            (out_node != IN_VALID && dfg->nodes[curr_n].out_degree != 1)
        ) ||
        // LR/PE->LR->PE/LR all should be happened on the same PE
        // Thus if mapped, in_node and out_node should be on the same PE
        (
            in_node != IN_VALID && s.core_1[in_node].t != IN_VALID &&
            out_node != IN_VALID && s.core_1[out_node].t != IN_VALID &&
            s.core_1[in_node].pos != s.core_1[out_node].pos
        )
    ) {
        return 0;
    }

    assert(!((in_node == IN_VALID || s.core_1[in_node].t == IN_VALID) && (out_node == IN_VALID || s.core_1[out_node].t == IN_VALID)));

    if (in_node != IN_VALID && s.core_1[in_node].t != IN_VALID) {
        // If have available local reg, try to map to local reg first
        int l_pos = find_free_l_reg(s.core_1[in_node].pos, PE_t->t);
        if (l_pos != IN_VALID) {
            PE_t->type = POS_L_REG;
            PE_t->pos = s.core_1[in_node].pos;
            PE_t->l_pos = l_pos;
            return 1;
        }
    }

    if (out_node != IN_VALID && s.core_1[out_node].t != IN_VALID) {
        // If have available local reg, try to map to local reg first
        int l_pos = find_free_l_reg(s.core_1[out_node].pos, PE_t->t);
        if (l_pos != IN_VALID) {
            PE_t->type = POS_L_REG;
            PE_t->pos = s.core_1[out_node].pos;
            PE_t->l_pos = l_pos;
            return 1;
        }
    }
    return 0;   // rout must connected to some node else
}

int next_PE(struct Tec_Pos* PE_t, struct M_Pos* m_pos, int curr_n, enum OP_ID curr_op)
{
    if (s.predecessors[s.core_len].node != IN_VALID && s.core_1[s.predecessors[s.core_len].node].type == POS_PE) {
        return next_conn_PE(PE_t, m_pos, curr_n, curr_op, 
            s.core_1[s.predecessors[s.core_len].node].pos, 
            s.predecessors[s.core_len].e_type);
    } else {
        return next_not_conn_PE(PE_t, m_pos, curr_n, curr_op);
    }
}

int next_pair(struct Tec_Pos* PE_t, struct M_Pos* m_pos)
{
    int curr_n = sort_res.nodes[s.core_len];
    enum OP_ID curr_op = dfg->nodes[curr_n].op;

    assert((PE_t->t == IN_VALID && PE_t->pos == IN_VALID && PE_t->type == POS_IN_VALID) || 
        (PE_t->t != IN_VALID && PE_t->pos != IN_VALID && PE_t->type != POS_IN_VALID));

    if (PE_t->t == IN_VALID) {
        PE_t->t = dfg->nodes[curr_n].schedule % cgra->II;
    }

    // if has connected lr mapping, curr_n has to be mapped on the same pos
    int reg_n = find_reg_conn(curr_n, POS_L_REG);
    if (reg_n == -2) {
        return 0;
    } else if (reg_n != IN_VALID) {
        return next_with_conn_l(PE_t, curr_op, reg_n);
    }

    if (curr_op == ID_ROUT) {
        int ret = IN_VALID;
        if (PE_t->match_layer == 0) {
            PE_t->match_layer++;
            ret = next_g_reg(PE_t, curr_op, curr_n);
            if (ret == 1) {
                return 1;
            }
        } 
        
        if (PE_t->match_layer == 1) {
            PE_t->match_layer++;
            if (ret != 2 /*ret == 2 means has connected g_reg*/ && 
                next_l_reg(PE_t, curr_n, curr_op)) {
                return 1;
            }
        }
    }

    return next_PE(PE_t, m_pos, curr_n, curr_op);
}

int is_feasible_conn(int node, struct Tec_Pos* PE_t, struct Deg_Pack* deg_pac)
{
    int i,j,k, conn_n;
    for (i = 0; i < dfg->nodes[node].in_degree; i++) {
        if (is_dfg_edge(dfg->nodes[node].ins[i].attr)) {
            conn_n = dfg->nodes[node].ins[i].node;
            if(s.core_1[conn_n].t != IN_VALID) {
                if (!has_out_edge(&s.core_1[conn_n], PE_t, cgra)) {
                    return 0;
                }
                if (dfg->nodes[conn_n].op == ID_ROUT) {
                    deg_pac->dfg_in_rout_deg--;
                } else {
                    deg_pac->dfg_in_non_rout_deg--;
                }
            }
        }
    }
    for (i = 0; i < dfg->nodes[node].out_degree; i++) {
        if (is_dfg_edge(dfg->nodes[node].outs[i].attr)) {
            conn_n = dfg->nodes[node].outs[i].node;
            if(s.core_1[conn_n].t != IN_VALID) {
                if (!has_out_edge(PE_t, &s.core_1[conn_n], cgra)) {
                    return 0;
                }
                if (dfg->nodes[conn_n].op == ID_ROUT) {
                    deg_pac->dfg_out_rout_deg--;
                } else {
                    deg_pac->dfg_out_non_rout_deg--;
                }
            }
        }
    }
    return 1;
}

int is_feasible_avail_1(struct Tec_Pos* PE_t, struct Deg_Pack* deg_pack, int t)
{
    int tot_free_r = cgra->g_reg_num -  get_tot_set_column(s.core_2.g_regs, t);

    if (t != PE_t->t) {
        // Free lr for target PE
        tot_free_r += cgra->PEs[PE_t->pos].l_reg - get_tot_set_column(s.core_2.l_regs, get_PE_t_pos(cgra, t, PE_t->pos));
    }
    deg_pack->free_PE_in -= deg_pack->intersect_PE;
    deg_pack->free_PE_out -= deg_pack->intersect_PE;

    deg_pack->dfg_in_non_rout_deg -= deg_pack->free_PE_in;
    if (deg_pack->dfg_in_non_rout_deg < 0) {
        deg_pack->dfg_in_rout_deg += deg_pack->dfg_in_non_rout_deg;
        if (deg_pack->dfg_in_rout_deg < 0) {
            deg_pack->dfg_in_rout_deg = 0;
        }
        deg_pack->dfg_in_non_rout_deg = 0;
    }

    deg_pack->dfg_out_non_rout_deg -= deg_pack->free_PE_out;
    if (deg_pack->dfg_out_non_rout_deg < 0) {
        deg_pack->dfg_out_rout_deg += deg_pack->dfg_out_non_rout_deg;
        if (deg_pack->dfg_out_rout_deg < 0) {
            deg_pack->dfg_out_rout_deg = 0;
        }
        deg_pack->dfg_out_non_rout_deg = 0;
    }

    deg_pack->intersect_PE -= deg_pack->dfg_in_non_rout_deg + deg_pack->dfg_out_non_rout_deg;
    if (deg_pack->intersect_PE < 0) {
        return 0;
    }
    if (tot_free_r + deg_pack->intersect_PE < deg_pack->dfg_in_rout_deg + deg_pack->dfg_out_rout_deg) {
        return 0;
    }

    return 1;
}

int is_feasible_avail_2(struct Deg_Pack* deg_pack, struct Tec_Pos* PE_t, int t_prev, int t_next)
{
    int prev_reg = cgra->g_reg_num - get_tot_set_column(s.core_2.g_regs, t_prev) + 
        (cgra->PEs[PE_t->pos].l_reg - get_tot_set_column(s.core_2.l_regs, get_PE_t_pos(cgra, t_prev, PE_t->pos)));

    int next_reg = cgra->g_reg_num - get_tot_set_column(s.core_2.g_regs, t_next) + 
        (cgra->PEs[PE_t->pos].l_reg - get_tot_set_column(s.core_2.l_regs, get_PE_t_pos(cgra, t_next, PE_t->pos)));

    deg_pack->dfg_in_non_rout_deg -= deg_pack->free_PE_in;
    if (deg_pack->dfg_in_non_rout_deg > 0) {
        return 0;
    }
    if (deg_pack->dfg_in_non_rout_deg < 0) {
        deg_pack->dfg_in_rout_deg += deg_pack->dfg_in_non_rout_deg;
        if (deg_pack->dfg_in_rout_deg < 0) {
            deg_pack->dfg_in_rout_deg = 0;
        }
        deg_pack->dfg_in_non_rout_deg = 0;
    }

    deg_pack->dfg_out_non_rout_deg -= deg_pack->free_PE_out;
    if (deg_pack->dfg_out_non_rout_deg > 0) {
        return 0;
    }
    if (deg_pack->dfg_out_non_rout_deg < 0) {
        deg_pack->dfg_out_rout_deg += deg_pack->dfg_out_non_rout_deg;
        if (deg_pack->dfg_out_rout_deg < 0) {
            deg_pack->dfg_out_rout_deg = 0;
        }
        deg_pack->dfg_out_non_rout_deg = 0;
    }
    if (deg_pack->dfg_in_rout_deg > prev_reg) {
        return 0;
    }
    if (deg_pack->dfg_out_rout_deg > next_reg) {
        return 0;
    }
    return 1;
}

int is_feasible_avail(int node, struct Tec_Pos* PE_t, struct Deg_Pack* deg_pack)
{
    int t_prev, t_next;

    t_prev = PE_t->t - 1;
    if (t_prev < 0) {
        t_prev = cgra->II - 1;
    }
    t_next = PE_t->t + 1;
    if (t_next >= cgra->II) {
        t_next = 0;
    }
    get_PE_free_deg(cgra, PE_t, s.core_2.PE_ts, deg_pack, t_prev, t_next);

    if (t_prev == t_next) {
        return is_feasible_avail_1(PE_t, deg_pack, t_prev);
    } else {
        return is_feasible_avail_2(deg_pack, PE_t, t_prev, t_next);
    }
}

int is_feasible_reg(int node, struct Tec_Pos* PE_t)
{
    if (s.core_2.const_regs[PE_t->pos] + const_in_degree(dfg, node) > cgra->PEs[PE_t->pos].const_reg) {
        return 0;
    }

    if (
        cgra->PEs[PE_t->pos].l_reg - 
        get_tot_set_column(s.core_2.l_regs, get_PE_t_pos(cgra, PE_t->t, PE_t->pos)) -
        const_base_in_degree(dfg, node) 
        < 0
    ) {
        return 0;
    }
    return 1;
}

int is_feasible(int node, struct Tec_Pos* PE_t)
{
    // global reg
    if (PE_t->type == POS_G_REG) {
        assert(dfg->nodes[node].op == ID_ROUT);
        return 1;
    }

    // PE
    if (!is_feasible_reg(node, PE_t)) {
        return 0;
    }

    // local reg, have to check the availability of const_base, since it uses one lr
    if (PE_t->type == POS_L_REG) {
        assert(dfg->nodes[node].op == ID_ROUT);
        return 1;
    }

    struct Deg_Pack deg_pack = {0};

    dfg_in_degree(dfg, node, &deg_pack.dfg_in_rout_deg, &deg_pack.dfg_in_non_rout_deg);
    dfg_out_degree(dfg, node, &deg_pack.dfg_out_rout_deg, &deg_pack.dfg_out_non_rout_deg);

    if (!is_feasible_conn(node, PE_t, &deg_pack)) {
        return 0;
    }
    if (!is_feasible_avail(node, PE_t, &deg_pack)) {
        return 0;
    }
    return 1;
}

int find_one_match()
{
    if (s.core_len == sort_res.num) {
        return 1;
    }

    int node = sort_res.nodes[s.core_len];
    struct Tec_Pos PE_t = { 
        .t = IN_VALID,
        .type = POS_IN_VALID,
        .pos = IN_VALID,
        .l_pos = IN_VALID,
        .const_base_l_pos = IN_VALID,
        .match_layer = 0
    };
    struct M_Pos m_pos = {
        .mode = MODE_FIRST
    };

    while (next_pair(&PE_t, &m_pos)) {
        if (is_feasible(node, &PE_t)) {
            add_pair(node, &PE_t);
            if (find_one_match()) {
                return 1;
            }
            rm_pair(node);
        }
    }

    return 0;
}
#pragma endregion
//=========================================================================================
// entry functions
//=========================================================================================
void init_core_2()
{
    s.core_2.g_regs = create_bit_matrix(cgra->II, cgra->g_reg_num);
    s.core_2.l_regs = create_bit_matrix(cgra->x_dim * cgra->y_dim * cgra->II, cgra->max_l_reg_num);
    s.core_2.const_regs = rpmalloc(sizeof(int) * cgra->x_dim * cgra->y_dim);
    s.core_2.PE_ts = rpmalloc(sizeof(int) * cgra->x_dim * cgra->y_dim * cgra->II);
    memset(s.core_2.const_regs, 0, sizeof(int) * cgra->x_dim * cgra->y_dim);
    memset(s.core_2.PE_ts, IN_VALID, sizeof(int) * cgra->x_dim * cgra->y_dim * cgra->II);
}

void clear_core_2()
{
    rm_bit_matrix(s.core_2.g_regs);
    rm_bit_matrix(s.core_2.l_regs);
    rpfree(s.core_2.const_regs);
    rpfree(s.core_2.PE_ts);
    s.core_2.g_regs = NULL;
    s.core_2.const_regs = NULL;
    s.core_2.l_regs = NULL;
    s.core_2.PE_ts = NULL;
}

void VF3_init(struct Graph* _dfg, struct CGRA* _cgra)
{
    dfg = _dfg;
    cgra = _cgra;

    n_sorted = rpmalloc(sizeof(int) * dfg->node_num);
    memset(n_sorted, 0, sizeof(int) * dfg->node_num);
    sort_res.num = dfg->node_num - dfg->const_num;
    sort_res.nodes = rpmalloc(sizeof(int) * sort_res.num);
    memset(sort_res.nodes, IN_VALID, sizeof(int) * sort_res.num);

    s.core_len = 0;
    if (s.core_1) {
        rpfree(s.core_1);
        s.core_1 = NULL;
    }
    s.core_1 = rpmalloc(sizeof(struct Tec_Pos) * dfg->node_num);
    s.predecessors = rpmalloc(sizeof(struct Pred) * sort_res.num);
    memset(s.core_1, IN_VALID, sizeof(struct Tec_Pos) * dfg->node_num);
    memset(s.predecessors, IN_VALID, sizeof(struct Pred) * sort_res.num);

    init_core_2();
}

void VF3_clear(int res)
{
    dfg = NULL;
    cgra = NULL;

    sort_res.num = 0;
    rpfree(sort_res.nodes);
    rpfree(n_sorted);
    n_sorted = NULL;
    sort_res.nodes = NULL;

    s.core_len = 0;
    // core_1 is the matching result
    if (!res)  {
        rpfree(s.core_1);
        s.core_1 = NULL;
    }
    clear_core_2();
    rpfree(s.predecessors);
    s.predecessors = NULL;
}

struct Tec_Pos* VF3_mapping(struct Graph* _dfg, struct CGRA* _cgra)
{
    int res = 0;
    
    VF3_init(_dfg, _cgra);
    sort_dfg();
    init_state();
    res = find_one_match();
    VF3_clear(res);
    
    return s.core_1;
}