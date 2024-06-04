#include "utils.h"
#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"
#include "dfg.h"
#include "readdot.h"
#include "CGRA.h"
#include "VF3.h"
#include "operation.h"
#include "codegen.h"
#include <time.h>
#include "bitmatrix.h"
#include "../../submodules/argparse/argparse.h"

static const char *const usages[] = {
    "basic [options] [[--] args]",
    "basic [options]",
    NULL,
};

int main(int argc, const char** argv) 
{
    char* dot_input_filename = NULL;
    char* asm_outpu_filename = NULL;
    char* rout_added_filename = NULL;
    char* cgra_design_filename = NULL;
    int loop_times = 0;
    int scheduled = 0;
    int g_reg_num = IN_VALID;
    
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('s', "scheduled", &scheduled, "dot file is scheduled", NULL, 0, 0),
        OPT_STRING('d', "dot", &dot_input_filename, "path to read dot file", NULL, 0, 0),
        OPT_STRING('a', "asm", &asm_outpu_filename, "path to output asm file", NULL, 0, 0),
        OPT_STRING('r', "rout", &rout_added_filename, "path to output rout added dot file", NULL, 0, 0),
        OPT_STRING('c', "cgra", &cgra_design_filename, "path to cgra design file", NULL, 0, 0),
        OPT_INTEGER('l', "looptimes", &loop_times, "time of loops", NULL, 0, 0),
        OPT_INTEGER('g', "gregs", &g_reg_num, "force the number of CGRA's global registers", NULL, 0, 0),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usages, 0);
    argc = argparse_parse(&argparse, argc, argv);

    if (!dot_input_filename) {
        printf("no input .dot file");
        exit(1);
    }

    clock_t start = clock(), end, tmp;
    struct Tec_Pos* matched = NULL;
    rpmalloc_initialize();
    // test_bit_matrix();
    // construct dfg
    struct Graph* dfg = read_dot(dot_input_filename, scheduled);
    if (!scheduled && handle_dfg(dfg) && rout_added_filename) {
        output_dot(dfg, rout_added_filename);
    }
    // construct cgra
    struct CGRA* cgra = CGRA_init(8, 8);
    set_special_sup_op(cgra);
    if (g_reg_num != IN_VALID) {
        cgra->g_reg_num = g_reg_num;
    }
    cgra->II = calc_II(dfg->node_num, 0, cgra);
    calc_sup_op(cgra);
    
    // mapping
    tmp = clock();
    while (cgra->II < MAX_II) {
        printf("start for for cgra->II = %d\n", cgra->II);
        matched = VF3_mapping(dfg, cgra);
        end = clock();
        printf("time cost %f sec for cgra->II = %d\n", ((double)(end - tmp)) / (double)(CLOCKS_PER_SEC), cgra->II);
        tmp = end;
        if (matched) {
            break;
        }
        cgra->II++;
    }

    end = clock();
    printf("tot time: %f\n", ((double)(end - start)) / (double)(CLOCKS_PER_SEC));

    if (cgra->II == MAX_II) {
        printf("cannot find match within %d tries\n", MAX_II);
        exit(1);
    }

    // print info
    for (int t = 0; t < dfg->max_schedule + 1; t++) {
        printf("schedule time = %d: ", t);
        for(int i = 0; i < dfg->node_num; i++) {
            if(!is_const(dfg->nodes[i].op) && dfg->nodes[i].schedule == t) {
                printf("%s,", dfg->nodes[i].name);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < dfg->node_num; i++) {
        if (!is_const(dfg->nodes[i].op)) {
            switch (matched[i].type) {
                case POS_PE : {
                    int x, y;
                    get_dim_by_pos(cgra, matched[i].pos, &x, &y);
                    printf("%s: %d %d %d\n", dfg->nodes[i].name, matched[i].t, x, y);
                    break;
                }
                case POS_G_REG : {
                    printf("%s: %d gr(%d)\n", dfg->nodes[i].name, matched[i].t, matched[i].pos);
                    break;
                }
                case POS_L_REG : {
                    int x, y;
                    get_dim_by_pos(cgra, matched[i].pos, &x, &y);
                    printf("%s: %d %d %d lr(%d)\n", dfg->nodes[i].name, matched[i].t, x, y, matched[i].l_pos);
                    break;
                }
                default: {
                    printf("unrecognized position type %d", matched[i].type);
                    exit(1);
                }   
            }
        }
    }

    // print asm
    if (asm_outpu_filename) {
        code_gen(dfg, matched, cgra, loop_times, asm_outpu_filename);
    }
    
    // free all allocated
    clear_dfg(dfg);
    clear_CGRA(cgra);
    if (matched) {
        rpfree(matched);
    }
    clear_dot();
    rpmalloc_finalize();
    
    return 0;
}