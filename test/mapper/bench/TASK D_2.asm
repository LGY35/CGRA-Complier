PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=2|II=1|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load3"*/
//iteration_cycle=1512|start_cycle=2|II=1|out=5/*pe_right*/
%load pe_left

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store1"*/
//iteration_cycle=1512|start_cycle=3|II=1
%store pe_down,pe_left

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=2|II=0|out=8/*pe_up*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=3|II=1|out=8/*pe_up*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

