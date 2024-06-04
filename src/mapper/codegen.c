#include "CGRA.h"
#include "dfg.h"
#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"
#include "operation.h"
#include "codegen.h"

struct PE_Index {
    int instr_count;
    int immi_cnt;
};

static struct Graph* dfg = NULL;
static struct Tec_Pos* mapping = NULL;
static struct CGRA* cgra = NULL;
static FILE* fp = NULL;
static struct PE_Index* PEs = NULL;
static int loop_num = 0;
static char* INPUT_SRC[22] = {
    "pe_left",  //0
    "pe_up",    //1
    "pe_right",
    "pe_down",
    "left_LSU",
    "up_LSU",
    "right_LSU",
    "down_LSU",
    "lr[0]",
    "lr[1]",
    "lr[2]",
    "imm_reg[0]",
    "imm_reg[1]",  
    "imm_reg[2]",
    "gr[0]",    //14
    "gr[1]",
    "gr[2]",
    "gr[3]",
    "gr[4]",
    "gr[5]",
    "gr[6]",
    "gr[7]",    //21
};
static char* OUTPUT_SRC[21] = {
    "lr[0]",
    "lr[1]",
    "lr[2]",
    "gr[0]",
    "fifo",
    "pe_right", //5
    "pe_down",  //6
    "pe_left",  //7
    "pe_up",    //8
    "LSU_store_data",
    "LSU_load_address",
    "imm_reg[0]",   //11
    "imm_reg[1]",   //12
    "imm_reg[2]",   //13
    "gr[1]",    //14
    "gr[2]",    //15
    "gr[3]",    //16
    "gr[4]",    //17
    "gr[5]",    //18
    "gr[6]",    //19
    "gr[7]",    //20
};
static char* OP_CODE[NUMS_OF_OP] = {
    // arithmetic IDeration
    "%sadd",
    "%ssub",
    "%sabs",
    "%sneg",
    "%smul",
    "%smod",
    "%smac",
    // compare
    "%if",
    "%if",
    "%if",
    // logic IDeration
    "%and",
    "%or",
    "%not",
    "%xor",
    "%if",
    // shift
    "%sra",
    "%srl",
    "%sll",
    // rout
    "%rout",
    // mem
    "%load",
    "%store"
};

int get_output(struct Tec_Pos* PE_curr, struct Tec_Pos* PE_next);

int gen_const(int n, int i)
{
    int val = dfg->nodes[dfg->nodes[n].ins[i].node].val;
    // 11 = immi_reg[0], 12 = immi_reg[1], 13 = immi_reg[2]
    int res = 11 + PEs[mapping[n].pos].immi_cnt;
    PEs[mapping[n].pos].immi_cnt++;
    fprintf(fp, "//iteration_cycle=1|start_cycle=0|II=0|out=%d\n", res);
    if (dfg->nodes[dfg->nodes[n].ins[i].node].llvm_name) {
        if (val == IN_VALID) {
            fprintf(fp, "%%imm %s,%s\n", dfg->nodes[dfg->nodes[n].ins[i].node].llvm_name, INPUT_SRC[res]);
        } else {
            fprintf(fp, "%%imm %d,%s/*%s*/\n", val, INPUT_SRC[res], dfg->nodes[dfg->nodes[n].ins[i].node].llvm_name);
        }
    } else {
        fprintf(fp, "%%imm %d,%s\n", val, INPUT_SRC[res]);
    }

    if (dfg->nodes[n].ins[i].attr == ATTR_CONST_BASE) {
        int lr = mapping[n].const_base_l_pos;
        fprintf(fp, "//iteration_cycle=1|start_cycle=%d|II=0", dfg->nodes[n].schedule + 1);
        for (i = 0; i < dfg->nodes[n].out_degree; i++) {
            if (is_dfg_edge(dfg->nodes[n].outs[i].attr)) {
                int index = get_output(&mapping[n], &mapping[dfg->nodes[n].outs[i].node]);
                fprintf(fp, "|out=%d/*%s*/", index, OUTPUT_SRC[index]);
            }
        }
        fprintf(fp, "|out=%d/*%s*/\n", lr, OUTPUT_SRC[lr]);
        fprintf(fp, "%%rout %s\n", INPUT_SRC[res]);
        return lr + 8;
    }
    return res;
}

int get_input(struct Tec_Pos* PE_curr, struct Tec_Pos* PE_prev)
{
   
    switch (PE_prev->type) {
        case POS_PE : {
            int prev_x, prev_y, curr_x, curr_y;
            get_dim_by_pos(cgra, PE_prev->pos, &prev_x, &prev_y);
            get_dim_by_pos(cgra, PE_curr->pos, &curr_x, &curr_y);
            
            assert((abs(prev_x - curr_x) + abs(prev_y - curr_y)) == 1);
            assert((PE_curr->t - PE_prev->t == 1) || (PE_curr->t == 0 && PE_prev->t == cgra->II - 1));
            if (curr_x - prev_x == 1) {
                return 0; //pe_left
            } 

            if (curr_y - prev_y == 1) {
                return 1; //pe_up
            }
            
            if (prev_x - curr_x == 1) {
                return 2; //pe_right
            }

            if (prev_y - curr_y == 1) {
                return 3; //pe_down
            }
            break;
        }
        case POS_G_REG : {
            return 14 + PE_prev->pos; //gr
            break;
        }
        case POS_L_REG : {
            return 8 + PE_prev->l_pos;
            break;
        }
        default: {
            printf("unrecognized position type %d", PE_prev->type);
            exit(1);
        }  
    }
}

int get_output(struct Tec_Pos* PE_curr, struct Tec_Pos* PE_next)
{
    switch (PE_next->type) {
        case POS_PE : {
            int next_x, next_y, curr_x, curr_y;
            get_dim_by_pos(cgra, PE_next->pos, &next_x, &next_y);
            get_dim_by_pos(cgra, PE_curr->pos, &curr_x, &curr_y);
            
            assert((abs(next_x - curr_x) + abs(next_y - curr_y)) == 1);
            assert((PE_next->t - PE_curr->t == 1) ||(PE_next->t == 0 && PE_curr->t == cgra->II - 1));
            if (curr_x - next_x == 1) {
                return 7; //pe_left
            } 

            if (curr_y - next_y == 1) {
                return 8; //pe_up
            }
            
            if (next_x - curr_x == 1) {
                return 5; //pe_right
            }

            if (next_y - curr_y == 1) {
                return 6; //pe_down
            }
            break;
        }
        case POS_G_REG : {
            if (PE_next->pos == 0) {
                return 3; //gr[0]
            } else {
                return 14 + PE_next->pos - 1; //gr[1] ~ gr[7]
            }
            break;
        }
        case POS_L_REG : {
            return PE_next->l_pos;
            break;
        }
        default: {
            printf("unrecognized position type %d", PE_next->type);
            exit(1);
        }  
    }
}

void gen_OP_code(enum OP_ID op, int operand[3])
{
    fprintf(fp, "%s ", OP_CODE[op]);
    int i = 0;
    switch (op)
    {
        case ID_LT:
            fprintf(fp, "a<b,");
            break;
        case ID_LE:
            fprintf(fp, "a<=b,");
            break;
        case ID_EQ:
            fprintf(fp, "a==b,");
            break;
        case ID_SEL:
            fprintf(fp, "a==1,");
            break;    
        default:
            break;
    }
    fprintf(fp, "%s", INPUT_SRC[operand[i]]);
    i++;
    while(operand[i] != IN_VALID && i < 3) {
        fprintf(fp, ",%s", INPUT_SRC[operand[i]]);
        i++;
    }
}

void gen_PE_code(int n)
{
    int i, operand[3] = {IN_VALID, IN_VALID, IN_VALID}, extra_lr = IN_VALID;
    int index;
    if (mapping[n].type == POS_G_REG || mapping[n].type == POS_L_REG) {
        return;
    }
    fprintf(fp,"/*generating asm for node name \"%s\"*/\n", dfg->nodes[n].name);
    
    for (i = 0; i < dfg->nodes[n].in_degree; i++) {
        assert(dfg->nodes[n].ins[i].operand < 3);
        if (is_const_edge(dfg->nodes[n].ins[i].attr)) {
            operand[dfg->nodes[n].ins[i].operand] = gen_const(n, i);
            if (dfg->nodes[n].ins[i].attr == ATTR_CONST_BASE) {
                assert(extra_lr == IN_VALID);
                extra_lr = operand[dfg->nodes[n].ins[i].operand];
            }
        } else if (is_dfg_edge(dfg->nodes[n].ins[i].attr)){
            operand[dfg->nodes[n].ins[i].operand] = get_input(&mapping[n], &mapping[dfg->nodes[n].ins[i].node]);
        }
    }
    if (extra_lr != IN_VALID) {
        if (loop_num == 0) {
            fprintf(fp, "//iteration_cycle=$(loop_num_min_1)|start_cycle=%d|II=%d", dfg->nodes[n].schedule + 1 + cgra->II, cgra->II);
        } else {
            fprintf(fp, "//iteration_cycle=%d|start_cycle=%d|II=%d", loop_num - 1, dfg->nodes[n].schedule + 1 + cgra->II, cgra->II);
        }
    } else {
        if (loop_num == 0) {
            fprintf(fp, "//iteration_cycle=$(loop_num)|start_cycle=%d|II=%d", dfg->nodes[n].schedule + 1, cgra->II);
        } else {
            fprintf(fp, "//iteration_cycle=%d|start_cycle=%d|II=%d", loop_num, dfg->nodes[n].schedule + 1, cgra->II);
        }
    }

    for (i = 0; i < dfg->nodes[n].out_degree; i++) {
        if (is_dfg_edge(dfg->nodes[n].outs[i].attr)) {
            index = get_output(&mapping[n], &mapping[dfg->nodes[n].outs[i].node]);
            fprintf(fp, "|out=%d/*%s*/", index, OUTPUT_SRC[index]);
        }
    }
    if (extra_lr != IN_VALID) {
        fprintf(fp, "|out=%d/*%s*/", extra_lr - 8, OUTPUT_SRC[extra_lr - 8]);
    }
    fprintf(fp, "\n");
    gen_OP_code(dfg->nodes[n].op, operand);
    fprintf(fp, "\n");
}

void code_gen_init(struct Graph* _dfg, struct Tec_Pos* _mapping, struct CGRA* _cgra, int _loop_num, char* filename)
{
    dfg = _dfg;
    mapping = _mapping;
    cgra = _cgra;
    loop_num = _loop_num;
    fp = fopen(filename, "wr");
    if (!fp) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    PEs = rpmalloc(sizeof(struct PE_Index) * cgra->x_dim * cgra->y_dim);
    memset(PEs, 0, sizeof(struct PE_Index) * cgra->x_dim * cgra->y_dim);
}

void code_gen_clear()
{
    dfg = NULL;
    mapping = NULL;
    cgra = NULL;
    loop_num = IN_VALID;
    fclose(fp);
    fp = NULL;
    rpfree(PEs);
    PEs = NULL;
}

int code_gen(struct Graph* _dfg, struct Tec_Pos* _mapping, struct CGRA* _cgra, int _loop_num, char* filename)
{
    int n, i;
    
    code_gen_init(_dfg, _mapping, _cgra, _loop_num, filename);
    
    for (n = 0; n < dfg->node_num; n++) {
        if (!is_const(dfg->nodes[n].op)) {
            if (mapping[n].type == POS_PE) {
                PEs[mapping[n].pos].instr_count++;
                for (i = 0; i < dfg->nodes[n].in_degree; i++) {
                    if (is_const_edge(dfg->nodes[n].ins[i].attr)) {
                        PEs[mapping[n].pos].instr_count++;
                    }
                }
            }
        }
    }
    for (i = 0; i < cgra->x_dim * cgra->y_dim; i++) {
        if (PEs[i].instr_count) {
            fprintf(fp, "PE[%d]\n%%TOP CP_index_=x|CP_num=x|Instruction_num=%d\n", i, PEs[i].instr_count);
            for (n = 0; n < dfg->node_num; n++) {
                if (!is_const(dfg->nodes[n].op)) {
                    if (mapping[n].pos == i) {
                        gen_PE_code(n);
                    }
                }
            }
            fprintf(fp, "\n");
        }
    }
    
    code_gen_clear();

    return 0;
}