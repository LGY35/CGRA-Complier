#include "utils.h"

struct Deg_Pack {
    int dfg_in_non_rout_deg;
    int dfg_in_rout_deg;
    int dfg_out_non_rout_deg;
    int dfg_out_rout_deg;
    int free_PE_in;
    int free_PE_out;
    int intersect_PE;
};

struct Tec_Pos* VF3_mapping(struct Graph* _dfg, struct CGRA* _cgra);