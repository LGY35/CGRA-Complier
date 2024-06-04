#include "operation.h"
#include "CGRA.h"
#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"
#include "../../submodules/cJSON/cJSON.h"
#include "dfg.h"
#include "bitmatrix.h"
#include "VF3.h"

#pragma region PE position/dimension convert functions
int get_PE_t_pos(struct CGRA* cgra, int t, int pos)
{
    assert(t >= 0 && t  < cgra->II);
    assert(pos >= 0 && pos < cgra->x_dim * cgra->y_dim);
    return t * (cgra->x_dim * cgra->y_dim) + pos;
}

int get_G_reg_t_Pos(struct CGRA* cgra, int t, int pos)
{
    assert(t >= 0 && t  < cgra->II);
    assert(pos >= 0 && pos < cgra->g_reg_num);
    return t * cgra->g_reg_num + pos;
}

void get_dim_by_pos(struct CGRA* cgra, int pos, int* x, int* y)
{
    *y = pos / cgra->y_dim;
    *x = pos - ((*y) * cgra->y_dim);

    assert(*x >= 0 && *x < cgra->x_dim);
    assert(*y >= 0 && *y < cgra->y_dim);
}

int get_PE_pos_by_dim(struct CGRA* cgra, int x, int y)
{
    assert(x >= 0 && x < cgra->x_dim);
    assert(y >= 0 && y < cgra->y_dim);

    return cgra->y_dim * y + x;
}
#pragma endregion

#pragma region PE connections
int has_out_edge(struct Tec_Pos* PE_t_1, struct Tec_Pos* PE_t_2, struct CGRA* cgra)
{
    assert(PE_t_1->t >= 0 && PE_t_1->t < cgra->II);
    assert(PE_t_1->pos >= 0 && PE_t_1->pos < cgra->x_dim * cgra->y_dim);
    assert(PE_t_2->t >= 0 && PE_t_2->t < cgra->II);
    assert(PE_t_2->pos >= 0 && PE_t_2->pos < cgra->x_dim * cgra->y_dim);
    if (PE_t_2->t - PE_t_1->t == 1 || ((PE_t_1->t == cgra->II - 1) && (PE_t_2->t == 0))) {
        // has global register
        if (PE_t_1->type == POS_G_REG) {
            switch (PE_t_2->type) {
                case POS_PE:
                    return 1;
                case POS_G_REG:
                    return PE_t_1->pos == PE_t_2->pos;
                case POS_L_REG:
                    return 0;
                default:
                    printf("unrecognized position type %d", PE_t_2->type);
                    exit(1);
            }
        }
        if (PE_t_2->type == POS_G_REG) {
            switch (PE_t_1->type) {
                case POS_PE:
                    return 1;
                case POS_G_REG:
                    return PE_t_1->pos == PE_t_2->pos;
                case POS_L_REG:
                    return 0;
                default:
                    printf("unrecognized position type %d", PE_t_2->type);
                    exit(1);
            }
        }
        if (PE_t_1->type == POS_L_REG || PE_t_2->type == POS_L_REG) {
            return PE_t_1->pos == PE_t_2->pos;
        }
        return get_bit(cgra->conn_out, PE_t_1->pos, PE_t_2->pos);
    }
    assert(0);
    return IN_VALID;
}

void get_PE_free_deg(struct CGRA* cgra, struct Tec_Pos* PE_t, int* PE_ts, struct Deg_Pack* deg_pac,int t_prev, int t_next)
{
    int PE_pos;

    struct M_Pos m_pos = {
        .mode = MODE_FIRST
    };
    // conn in
    PE_pos = get_next_set_column(cgra->conn_in, PE_t->pos, &m_pos);
    m_pos.mode = MODE_CONT;

    while (PE_pos != IN_VALID) {
        if (PE_ts[get_PE_t_pos(cgra, t_prev, PE_pos)] == IN_VALID) {
            deg_pac->free_PE_in++;
        }
        PE_pos = get_next_set_column(cgra->conn_in, PE_t->pos, &m_pos);
    }
    m_pos.mode = MODE_FIRST;
    PE_pos = get_next_set_column(cgra->conn_out, PE_t->pos, &m_pos);
    m_pos.mode = MODE_CONT;

    while (PE_pos != IN_VALID) {
        if (PE_ts[get_PE_t_pos(cgra, t_next, PE_pos)] == IN_VALID) {
            deg_pac->free_PE_out++;
            if(t_next == t_prev && get_bit(cgra->conn_in, PE_t->pos, PE_pos)) {
                deg_pac->intersect_PE++;
            }
        }
        PE_pos = get_next_set_column(cgra->conn_out, PE_t->pos, &m_pos);
    }
}
#pragma endregion

void set_PE_op(struct CGRA* cgra, int x, int y, int sup_op)
{
    cgra->PEs[get_PE_pos_by_dim(cgra, x, y)].sup_op = sup_op;
}

int PE_sup_op(struct CGRA* cgra, int pos, enum OP_ID op)
{
    return cgra->PEs[pos].sup_op & (1 << op);
}

struct CGRA* CGRA_init(int x_dim, int y_dim)
{
    struct CGRA* cgra = rpmalloc(sizeof(struct CGRA));
    cgra->II = 0;
    cgra->x_dim = x_dim;
    cgra->y_dim = y_dim;
    cgra->g_reg_num = IN_VALID;
    cgra->max_l_reg_num = IN_VALID;
    cgra->PEs = rpmalloc(sizeof(struct PE) * x_dim * y_dim);
    memset(cgra->PEs, 0, sizeof(struct PE) * x_dim * y_dim);
    cgra->conn_out = create_bit_matrix(cgra->y_dim * cgra->x_dim, cgra->y_dim * cgra->x_dim);
    cgra->conn_in = create_bit_matrix(cgra->y_dim * cgra->x_dim, cgra->y_dim * cgra->x_dim);
    return cgra;
}

void clear_CGRA(struct CGRA* cgra)
{
    rpfree(cgra->conn_out);
    rpfree(cgra->conn_in);
    rpfree(cgra->PEs);
    rpfree(cgra);
}

void set_special_sup_op(struct CGRA* cgra)
{
    for (int x = 0; x < cgra->x_dim; x++) {
        for (int y = 0; y < cgra->y_dim; y++) {
            int curr_PE = get_PE_pos_by_dim(cgra, x, y);
            if (x - 1 >= 0) {
                set_bit(cgra->conn_out, curr_PE, get_PE_pos_by_dim(cgra, x - 1, y));
            }
            if (y - 1 >= 0) {
                set_bit(cgra->conn_out, curr_PE, get_PE_pos_by_dim(cgra, x, y - 1));
            }
            if (x + 1 < cgra->x_dim) {
                set_bit(cgra->conn_out, curr_PE, get_PE_pos_by_dim(cgra, x + 1, y));
            }
            if (y + 1 < cgra->y_dim) {
                set_bit(cgra->conn_out, curr_PE, get_PE_pos_by_dim(cgra, x, y + 1));
            }
            if (x == cgra->x_dim - 1) {
                set_PE_op(cgra, x, y, SUP_ALL_OP);
            } else {
                set_PE_op(cgra, x, y, SUP_ALL_BUT_STORE_OP);
            }
            cgra->PEs[curr_PE].const_reg = 3;
            cgra->PEs[curr_PE].l_reg = 3;
        }
    }
    transpos_matrix(cgra->conn_out, cgra->conn_in);
    cgra->g_reg_num = 8; // 根据谷老师提供
}

int calc_II (int dfg_nodes_num, int loop_len, struct CGRA* cgra) 
{
    int res_MII = 0, rec_MII = 0;
    for (int x = 0; x < cgra->x_dim; x++) {
        for (int y = 0; y < cgra->y_dim; y++) {
            int curr_PE = get_PE_pos_by_dim(cgra, x, y);
            if (cgra->PEs[curr_PE].l_reg > cgra->max_l_reg_num) {
                cgra->max_l_reg_num = cgra->PEs[curr_PE].l_reg;
            }
        }
    }
    res_MII = dfg_nodes_num / (cgra->x_dim * cgra->x_dim) + 1;
    rec_MII = loop_len / 2;
    if (rec_MII > res_MII) {
        return rec_MII;
    } else {
        return res_MII;
    }
}

void calc_sup_op(struct CGRA* cgra)
{
    for (int x = 0; x < cgra->x_dim; x++) {
        for (int y = 0; y < cgra->y_dim; y++) {
            for (int op = 0; op < NUMS_OF_OP; op++) {
                if(PE_sup_op(cgra, get_PE_pos_by_dim(cgra, x, y), op)) {
                    cgra->sup_op_PE_cnt[op]++;
                }
            }
        }
    }
}

#pragma region load CGRA design file
struct CGRA* load_CGRA(char* cgra_design_filename)
{
    char* json_str = read_file(cgra_design_filename);
    if (!json_str) {
        printf("cannot open file %s", cgra_design_filename);
        exit(1);
    }
    cJSON *json = cJSON_Parse(json_str);

    return NULL;
}

#pragma endregion