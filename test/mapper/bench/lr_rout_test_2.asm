PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add2"*/
//iteration_cycle=1512|start_cycle=3|II=3
%sadd gr[0],pe_down

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "not0"*/
//iteration_cycle=1512|start_cycle=2|II=3|out=6/*pe_down*/
%not pe_down
/*generating asm for node name "not4"*/
//iteration_cycle=1512|start_cycle=3|II=3
%not gr[0]

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not5"*/
//iteration_cycle=1512|start_cycle=3|II=3
%not gr[0]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not6"*/
//iteration_cycle=1512|start_cycle=3|II=3
%not gr[0]

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout2"*/
//iteration_cycle=1512|start_cycle=2|II=3|out=8/*pe_up*/
%rout pe_right

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1512|start_cycle=1|II=3|out=8/*pe_up*/|out=5/*pe_right*/|out=6/*pe_down*/|out=3/*gr[0]*/|out=0/*lr[0]*/|out=7/*pe_left*/
%sadd imm_reg[0],imm_reg[1]
/*generating asm for node name "add1"*/
//iteration_cycle=1512|start_cycle=3|II=3
%sadd lr[0]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not1"*/
//iteration_cycle=1512|start_cycle=2|II=3
%not pe_left

PE[17]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not2"*/
//iteration_cycle=1512|start_cycle=2|II=3
%not pe_up

