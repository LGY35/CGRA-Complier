PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=6/*pe_down*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=2|II=1|out=6/*pe_down*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=4|II=0|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=5|II=1|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load1"*/
//iteration_cycle=1512|start_cycle=5|II=1|out=5/*pe_right*/
%load pe_left

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store0"*/
//iteration_cycle=1512|start_cycle=6|II=1
%store pe_down,pe_left

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load0"*/
//iteration_cycle=1512|start_cycle=2|II=1|out=5/*pe_right*/
%load pe_up

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 359,imm_reg[0]
//iteration_cycle=1512|start_cycle=3|II=1|out=5/*pe_right*/
%sadd imm_reg[0],pe_left

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=4|II=1|out=5/*pe_right*/
%smul pe_left,imm_reg[0]

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1512|start_cycle=5|II=1|out=8/*pe_up*/
%sadd pe_left,imm_reg[0]

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=6|II=0|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=7|II=1|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load2"*/
//iteration_cycle=1512|start_cycle=7|II=1|out=6/*pe_down*/
%load pe_left

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=8|II=0|out=6/*pe_down*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=9|II=1|out=6/*pe_down*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=6|II=0|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=7|II=1|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load3"*/
//iteration_cycle=1512|start_cycle=7|II=1|out=5/*pe_right*/
%load pe_left

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "select0"*/
//iteration_cycle=1512|start_cycle=8|II=1|out=5/*pe_right*/
%if a==1,pe_down,pe_left,pe_up

PE[31]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store1"*/
//iteration_cycle=1512|start_cycle=9|II=1
%store pe_up,pe_left

PE[37]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 0,imm_reg[1]
//iteration_cycle=1|start_cycle=6|II=0|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[1]
//iteration_cycle=1511|start_cycle=7|II=1|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[0]

PE[38]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "lt0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 360,imm_reg[0]
//iteration_cycle=1512|start_cycle=7|II=1|out=8/*pe_up*/
%if a<b,pe_left,imm_reg[0]

