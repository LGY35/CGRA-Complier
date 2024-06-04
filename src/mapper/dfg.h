#include "utils.h"


struct In_Conn {
    int             node;
    enum Edge_Attr  attr;
    int             operand;
};

struct Out_Conn {
    int             node;
    enum Edge_Attr  attr;
};

struct Node {
    char*               name;
    int                 schedule;
    enum OP_ID          op;
    int                 in_degree;
    int                 out_degree;
    int                 val;
    char*               llvm_name;
    struct In_Conn*     ins;
    struct Out_Conn*    outs;
};

struct Graph {
    int             max_schedule;
    // TODO: support loop and node add/remove operation
    int             loop_len;
    int             node_num;
    int             const_num;
    struct Node*    nodes;
};

int handle_dfg(struct Graph* dfg);
struct Graph* init_dfg(int node_num, int const_num);
int is_dfg_edge(enum Edge_Attr attr);
int is_schedule_edge(enum Edge_Attr attr);
void dfg_in_degree(struct Graph* dfg, int node, int* r_deg, int* non_r_deg);
void dfg_out_degree(struct Graph* dfg, int node, int* r_deg, int* non_r_deg);
void clear_dfg(struct Graph* dfg);
int const_in_degree(struct Graph* dfg, int node);
int const_base_in_degree(struct Graph* dfg, int node);
int is_const_edge(enum Edge_Attr attr);