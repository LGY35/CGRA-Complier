PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=6
/*generating asm for node name "eq0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=3|II=3|out=5/*pe_right*/
%if a==b,pe_down,imm_reg[0]
/*generating asm for node name "or0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=2985984|start_cycle=7|II=3|out=5/*pe_right*/|out=3/*gr[0]*/
%or pe_right,imm_reg[1]
/*generating asm for node name "loop_add19"*/
//iteration_cycle=1|start_cycle=0|II=0|out=13
%imm 0,imm_reg[2]
//iteration_cycle=1|start_cycle=5|II=0|out=5/*pe_right*/|out=14/*gr[1]*/|out=0/*lr[0]*/
%rout imm_reg[2]
//iteration_cycle=2985983|start_cycle=8|II=3|out=5/*pe_right*/|out=14/*gr[1]*/|out=0/*lr[0]*/
%sadd lr[0],pe_right

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "and0"*/
//iteration_cycle=2985984|start_cycle=4|II=3|out=7/*pe_left*/
%and pe_down,pe_left
/*generating asm for node name "shl0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=2985984|start_cycle=6|II=3|out=7/*pe_left*/|out=5/*pe_right*/
%sll pe_left,imm_reg[0]
/*generating asm for node name "lt0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 2591,imm_reg[1]
//iteration_cycle=2985984|start_cycle=8|II=3|out=5/*pe_right*/
%if a<b,imm_reg[1],pe_left

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "sel0"*/
//iteration_cycle=2985984|start_cycle=9|II=3|out=5/*pe_right*/
%if a==1,pe_left,gr[1],gr[0]
/*generating asm for node name "rout5"*/
//iteration_cycle=2985984|start_cycle=8|II=3|out=16/*gr[3]*/
%rout gr[0]
/*generating asm for node name "rout8"*/
//iteration_cycle=2985984|start_cycle=7|II=3|out=14/*gr[1]*/
%rout pe_left

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "shl1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=2985984|start_cycle=8|II=3|out=5/*pe_right*/
%sll gr[0],imm_reg[0]
/*generating asm for node name "mul0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 27648,imm_reg[1]
//iteration_cycle=2985984|start_cycle=10|II=3|out=5/*pe_right*/
%smul pe_left,imm_reg[1]
/*generating asm for node name "rout3"*/
//iteration_cycle=2985984|start_cycle=6|II=3|out=3/*gr[0]*/
%rout gr[3]

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "or1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=2985984|start_cycle=9|II=3|out=5/*pe_right*/
%or pe_left,imm_reg[0]
/*generating asm for node name "add1"*/
//iteration_cycle=2985984|start_cycle=11|II=3|out=5/*pe_right*/|out=6/*pe_down*/|out=3/*gr[0]*/
%sadd pe_left,pe_right
/*generating asm for node name "rout14"*/
//iteration_cycle=2985984|start_cycle=7|II=3|out=15/*gr[2]*/
%rout gr[1]

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "mul1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 6,imm_reg[0]
//iteration_cycle=2985984|start_cycle=10|II=3|out=7/*pe_left*/
%smul pe_left,imm_reg[0]
/*generating asm for node name "add2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=2985984|start_cycle=12|II=3|out=5/*pe_right*/
%sadd imm_reg[1],pe_left

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "load0"*/
//iteration_cycle=2985984|start_cycle=13|II=3|out=5/*pe_right*/
%load pe_left
/*generating asm for node name "mul2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 13824,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=3|out=6/*pe_down*/
%smul gr[2],imm_reg[0]
/*generating asm for node name "rout16"*/
//iteration_cycle=2985984|start_cycle=9|II=3|out=15/*gr[2]*/
%rout gr[2]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "store0"*/
//iteration_cycle=2985984|start_cycle=14|II=3
%store pe_left,pe_down
/*generating asm for node name "rout1"*/
//iteration_cycle=2985984|start_cycle=4|II=3|out=16/*gr[3]*/
%rout gr[2]

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2304,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=3|out=8/*pe_up*/|out=15/*gr[2]*/
%smod pe_right,imm_reg[0]

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "not0"*/
//iteration_cycle=2985984|start_cycle=3|II=3|out=8/*pe_up*/
%not pe_right
/*generating asm for node name "loop_add18"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=7/*pe_left*/|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=2985983|start_cycle=4|II=3|out=7/*pe_left*/|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=3|out=7/*pe_left*/
%if a==b,pe_left,imm_reg[0]

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add6"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=12|II=3|out=5/*pe_right*/
%sadd pe_up,imm_reg[0]

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "mul3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 6,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=3|out=5/*pe_right*/
%smul gr[3],imm_reg[0]
/*generating asm for node name "add7"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=2985984|start_cycle=13|II=3|out=5/*pe_right*/
%sadd imm_reg[1],pe_left

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add3"*/
//iteration_cycle=2985984|start_cycle=12|II=3|out=5/*pe_right*/|out=6/*pe_down*/|out=14/*gr[1]*/
%sadd pe_up,pe_left
/*generating asm for node name "load1"*/
//iteration_cycle=2985984|start_cycle=14|II=3|out=5/*pe_right*/
%load pe_left
/*generating asm for node name "add12"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4,imm_reg[0]
//iteration_cycle=2985984|start_cycle=13|II=3|out=6/*pe_down*/
%sadd gr[0],imm_reg[0]

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "add4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=13|II=3|out=8/*pe_up*/
%sadd imm_reg[0],pe_left
/*generating asm for node name "store1"*/
//iteration_cycle=2985984|start_cycle=15|II=3
%store pe_left,pe_down
/*generating asm for node name "add15"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 4,imm_reg[1]
//iteration_cycle=2985984|start_cycle=14|II=3|out=6/*pe_down*/
%sadd gr[1],imm_reg[1]

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add9"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=13|II=3|out=5/*pe_right*/
%sadd pe_up,imm_reg[0]
/*generating asm for node name "add13"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=2985984|start_cycle=14|II=3|out=6/*pe_down*/
%sadd imm_reg[1],pe_up

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add10"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=14|II=3|out=8/*pe_up*/
%sadd imm_reg[0],pe_left
/*generating asm for node name "add16"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %0,imm_reg[1]
//iteration_cycle=2985984|start_cycle=15|II=3|out=6/*pe_down*/
%sadd imm_reg[1],pe_up

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load2"*/
//iteration_cycle=2985984|start_cycle=15|II=3|out=5/*pe_right*/
%load pe_up

PE[31]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store2"*/
//iteration_cycle=2985984|start_cycle=16|II=3
%store pe_left,pe_up

