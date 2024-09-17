#include "utils.h"

#define MAX_II 10
#define SUP_ALL_OP OP_ADD | \
    OP_SUB   | \
    OP_ABS   | \
    OP_NEG   | \
    OP_MUL   | \
    OP_UDIV   | \
    OP_SDIV   | \
    OP_MOD   | \
    OP_LT    | \
    OP_LE    | \
    OP_EQ    | \
    OP_AND   | \
    OP_OR    | \
    OP_NOT   | \
    OP_XOR   | \
    OP_SHR   | \
    OP_ASHR  | \
    OP_SHL   | \
    OP_ROUT  | \
    OP_LOAD  | \
    OP_STORE | \
    OP_MAC   | \
    OP_SEL
#define SUP_ALL_BUT_STORE_OP OP_ADD | \
    OP_SUB  | \
    OP_ABS  | \
    OP_NEG  | \
    OP_MUL  | \
    OP_UDIV  | \
    OP_SDIV  | \
    OP_MOD  | \
    OP_LT   | \
    OP_LE   | \
    OP_EQ   | \
    OP_AND  | \
    OP_OR   | \
    OP_NOT  | \
    OP_XOR  | \
    OP_SHR  | \
    OP_ASHR | \
    OP_SHL  | \
    OP_ROUT | \
    OP_LOAD | \
    OP_MAC  | \
    OP_SEL

struct PE {
    int sup_op;
    int const_reg;
    int l_reg;
};

struct CGRA {
    int II;
    int x_dim;
    int y_dim;
    int g_reg_num;
    int max_l_reg_num;
    int sup_op_PE_cnt[NUMS_OF_OP];
    struct PE* PEs;
    struct Bit_Matrix* conn_out;
    struct Bit_Matrix* conn_in;
};
enum Pos_Type {
    POS_IN_VALID = -1,
    POS_G_REG,
    POS_L_REG,
    POS_S_REG,
    POS_PE
};
struct Tec_Pos {
    int t;      //time
    enum Pos_Type type;
    int pos;    //position (x,y)
    int l_pos;
    int match_layer;
    // special handle for const base attribute, since it takes one lr
    int const_base_l_pos;
};

int get_PE_t_pos(struct CGRA* cgra, int t, int pos);
int get_G_reg_t_Pos(struct CGRA* cgra, int t, int pos);
int get_PE_pos(struct CGRA* cgra, struct Tec_Pos* PE_t);
void get_PE_free_deg(struct CGRA* cgra, struct Tec_Pos* PE_t, int* PE_ts, struct Deg_Pack* deg_pac,int t_prev, int t_next);
void set_PE_op(struct CGRA* cgra, int x, int y, int sup_op);
int PE_sup_op(struct CGRA* cgra, int pos, enum OP_ID op);
struct CGRA* CGRA_init(int x_dim, int y_dim);
void set_special_sup_op(struct CGRA* cgra);
int calc_II (int dfg_nodes_num, int loop_len, struct CGRA* cgra);
void calc_sup_op(struct CGRA* cgra);
int has_out_edge(struct Tec_Pos* PE_t_1, struct Tec_Pos* PE_t_2, struct CGRA* cgra);
void clear_CGRA(struct CGRA* cgra);
struct CGRA* load_CGRA(char* cgra_design_filename);
void get_dim_by_pos(struct CGRA* cgra, int pos, int* x, int* y);
int get_PE_pos_by_dim(struct CGRA* cgra, int x, int y);