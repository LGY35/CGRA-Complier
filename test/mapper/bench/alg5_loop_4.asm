PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout8"*/
//iteration_cycle=11943936|start_cycle=9|II=3|out=15/*gr[2]*/
%rout gr[2]

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "loop_add20"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=5/*pe_right*/|out=6/*pe_down*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=11943935|start_cycle=4|II=3|out=5/*pe_right*/|out=6/*pe_down*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]
/*generating asm for node name "rout0"*/
//iteration_cycle=11943936|start_cycle=3|II=3|out=14/*gr[1]*/
%rout pe_right

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=3|out=5/*pe_right*/|out=7/*pe_left*/
%smod pe_left,imm_reg[0]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "eq0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=3|II=3|out=6/*pe_down*/
%if a==b,pe_left,imm_reg[0]
/*generating asm for node name "eq2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 0,imm_reg[1]
//iteration_cycle=11943936|start_cycle=7|II=3|out=5/*pe_right*/
%if a==b,pe_down,imm_reg[1]

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "and2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=6|II=3|out=5/*pe_right*/
%and gr[1],imm_reg[0]
/*generating asm for node name "sel0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=11943936|start_cycle=8|II=3|out=5/*pe_right*/
%if a==1,pe_left,imm_reg[1],pe_right

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "eq3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=3|out=7/*pe_left*/
%if a==b,pe_left,imm_reg[0]
/*generating asm for node name "not1"*/
//iteration_cycle=11943936|start_cycle=9|II=3|out=5/*pe_right*/|out=3/*gr[0]*/
%not pe_left

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "add3"*/
//iteration_cycle=11943936|start_cycle=8|II=3|out=5/*pe_right*/|out=3/*gr[0]*/
%sadd pe_down,pe_right
/*generating asm for node name "sel1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @dump,imm_reg[0]
//iteration_cycle=11943936|start_cycle=10|II=3|out=5/*pe_right*/
%if a==1,pe_left,pe_right,imm_reg[0]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "mul3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 6,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=3|out=7/*pe_left*/
%smul gr[1],imm_reg[0]
/*generating asm for node name "add4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=11943936|start_cycle=9|II=3|out=7/*pe_left*/
%sadd imm_reg[1],pe_left
/*generating asm for node name "store0"*/
//iteration_cycle=11943936|start_cycle=11|II=3
%store pe_down,pe_left

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=3|out=5/*pe_right*/
%if a==b,pe_up,imm_reg[0]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not0"*/
//iteration_cycle=11943936|start_cycle=3|II=3|out=5/*pe_right*/
%not pe_left

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "and0"*/
//iteration_cycle=11943936|start_cycle=4|II=3|out=5/*pe_right*/
%and pe_left,pe_up
/*generating asm for node name "and1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=6|II=3|out=8/*pe_up*/
%and pe_right,imm_reg[0]

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "shr0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=3|out=5/*pe_right*/
%sra gr[1],imm_reg[0]
/*generating asm for node name "add6"*/
//iteration_cycle=11943936|start_cycle=9|II=3|out=5/*pe_right*/
%sadd pe_down,pe_right
/*generating asm for node name "loop_add19"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 0,imm_reg[1]
//iteration_cycle=1|start_cycle=5|II=0|out=7/*pe_left*/|out=5/*pe_right*/|out=15/*gr[2]*/|out=0/*lr[0]*/
%rout imm_reg[1]
//iteration_cycle=11943935|start_cycle=8|II=3|out=7/*pe_left*/|out=5/*pe_right*/|out=15/*gr[2]*/|out=0/*lr[0]*/
%sadd lr[0],pe_left

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "shr1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=6|II=3|out=6/*pe_down*/
%sra pe_left,imm_reg[0]
/*generating asm for node name "mul1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 2,imm_reg[1]
//iteration_cycle=11943936|start_cycle=8|II=3|out=5/*pe_right*/|out=7/*pe_left*/|out=6/*pe_down*/|out=16/*gr[3]*/
%smul pe_left,imm_reg[1]
/*generating asm for node name "load1"*/
//iteration_cycle=11943936|start_cycle=10|II=3|out=5/*pe_right*/
%load pe_left

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add2"*/
//iteration_cycle=11943936|start_cycle=9|II=3|out=5/*pe_right*/
%sadd pe_down,pe_left
/*generating asm for node name "mul2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 27648,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=3|out=8/*pe_up*/
%smul gr[2],imm_reg[0]
/*generating asm for node name "add9"*/
//iteration_cycle=11943936|start_cycle=11|II=3|out=5/*pe_right*/
%sadd pe_down,pe_left

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "load0"*/
//iteration_cycle=11943936|start_cycle=10|II=3|out=8/*pe_up*/
%load pe_left
/*generating asm for node name "shr2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=3|out=6/*pe_down*/
%sra pe_left,imm_reg[0]

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %4,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=3|out=8/*pe_up*/
%sadd imm_reg[0],pe_right
/*generating asm for node name "add11"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 2,imm_reg[1]
//iteration_cycle=11943936|start_cycle=10|II=3|out=5/*pe_right*/
%sadd gr[0],imm_reg[1]

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "mul0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=3|out=5/*pe_right*/|out=7/*pe_left*/|out=6/*pe_down*/|out=15/*gr[2]*/
%smul pe_up,imm_reg[0]
/*generating asm for node name "add8"*/
//iteration_cycle=11943936|start_cycle=9|II=3|out=5/*pe_right*/
%sadd pe_down,pe_up
/*generating asm for node name "add12"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=11943936|start_cycle=11|II=3|out=5/*pe_right*/
%sadd imm_reg[1],pe_left

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=5
/*generating asm for node name "add1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %3,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=3|out=8/*pe_up*/
%sadd imm_reg[0],pe_left
/*generating asm for node name "load2"*/
//iteration_cycle=11943936|start_cycle=10|II=3|out=8/*pe_up*/
%load pe_left
/*generating asm for node name "sel2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm @dump,imm_reg[1]
//iteration_cycle=11943936|start_cycle=12|II=3|out=5/*pe_right*/
%if a==1,gr[0],pe_left,imm_reg[1]

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store1"*/
//iteration_cycle=11943936|start_cycle=13|II=3
%store pe_up,pe_left

PE[27]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout14"*/
//iteration_cycle=11943936|start_cycle=10|II=3|out=5/*pe_right*/
%rout gr[0]

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add16"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4,imm_reg[0]
//iteration_cycle=11943936|start_cycle=11|II=3|out=5/*pe_right*/
%sadd pe_left,imm_reg[0]

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add7"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %5,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=3|out=8/*pe_up*/
%sadd imm_reg[0],pe_up
/*generating asm for node name "add17"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=11943936|start_cycle=12|II=3|out=5/*pe_right*/
%sadd imm_reg[1],pe_left

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add13"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %6,imm_reg[0]
//iteration_cycle=11943936|start_cycle=11|II=3|out=6/*pe_down*/
%sadd imm_reg[0],gr[2]
/*generating asm for node name "sel3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm @dump,imm_reg[1]
//iteration_cycle=11943936|start_cycle=13|II=3|out=5/*pe_right*/
%if a==1,pe_right,pe_left,imm_reg[1]

PE[31]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "store2"*/
//iteration_cycle=11943936|start_cycle=14|II=3
%store pe_down,pe_left
/*generating asm for node name "rout6"*/
//iteration_cycle=11943936|start_cycle=12|II=3|out=7/*pe_left*/
%rout gr[0]

PE[38]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add14"*/
//iteration_cycle=11943936|start_cycle=12|II=3|out=5/*pe_right*/
%sadd pe_up,gr[3]

PE[39]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load3"*/
//iteration_cycle=11943936|start_cycle=13|II=3|out=8/*pe_up*/
%load pe_left

