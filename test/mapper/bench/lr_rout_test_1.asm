PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "add0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1512|start_cycle=1|II=2|out=5/*pe_right*/|out=3/*gr[0]*/|out=0/*lr[0]*/|out=1/*lr[1]*/|out=2/*lr[2]*/|out=6/*pe_down*/
%sadd imm_reg[0],imm_reg[1]

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not0"*/
//iteration_cycle=1512|start_cycle=2|II=2
%not pe_left

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout4"*/
//iteration_cycle=1512|start_cycle=2|II=2
%rout pe_up

