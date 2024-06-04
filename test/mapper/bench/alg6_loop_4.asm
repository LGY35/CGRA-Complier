PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout8"*/
//iteration_cycle=5971968|start_cycle=3|II=1|out=20/*gr[7]*/
%rout gr[3]

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout3"*/
//iteration_cycle=5971968|start_cycle=6|II=1|out=17/*gr[4]*/
%rout pe_down

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=5971968|start_cycle=3|II=1|out=5/*pe_right*/
%sra gr[3],imm_reg[0]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=5971968|start_cycle=4|II=1|out=5/*pe_right*/|out=6/*pe_down*/
%smul pe_left,imm_reg[0]

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @d3_2_dst,imm_reg[0]
//iteration_cycle=5971968|start_cycle=5|II=1|out=6/*pe_down*/
%sadd imm_reg[0],pe_left

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "sel2"*/
//iteration_cycle=5971968|start_cycle=8|II=1|out=5/*pe_right*/
%if a==1,gr[4],gr[0],pe_down

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load0"*/
//iteration_cycle=5971968|start_cycle=9|II=1|out=5/*pe_right*/
%load pe_left

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store0"*/
//iteration_cycle=5971968|start_cycle=10|II=1
%store pe_left,pe_down

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout11"*/
//iteration_cycle=5971968|start_cycle=6|II=1|out=19/*gr[6]*/
%rout pe_down

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout2"*/
//iteration_cycle=5971968|start_cycle=5|II=1|out=8/*pe_up*/
%rout gr[5]

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @d3_3_dst,imm_reg[0]
//iteration_cycle=5971968|start_cycle=5|II=1|out=5/*pe_right*/
%sadd imm_reg[0],pe_up

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "sel0"*/
//iteration_cycle=5971968|start_cycle=6|II=1|out=5/*pe_right*/
%if a==1,gr[1],pe_left,pe_up

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "sel1"*/
//iteration_cycle=5971968|start_cycle=7|II=1|out=8/*pe_up*/
%if a==1,pe_down,pe_right,pe_left

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @d3_1_dst,imm_reg[0]
//iteration_cycle=5971968|start_cycle=6|II=1|out=7/*pe_left*/|out=3/*gr[0]*/
%sadd imm_reg[0],pe_down

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add6"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %0,imm_reg[0]
//iteration_cycle=5971968|start_cycle=9|II=1|out=8/*pe_up*/
%sadd imm_reg[0],pe_down

PE[16]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout10"*/
//iteration_cycle=5971968|start_cycle=5|II=1|out=8/*pe_up*/
%rout gr[7]

PE[18]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=5971968|start_cycle=3|II=1|out=5/*pe_right*/|out=18/*gr[5]*/
%if a==b,pe_down,imm_reg[0]

PE[19]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "or0"*/
//iteration_cycle=5971968|start_cycle=4|II=1|out=5/*pe_right*/
%or pe_down,pe_left

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "or1"*/
//iteration_cycle=5971968|start_cycle=5|II=1|out=5/*pe_right*/
%or pe_left,pe_down

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not0"*/
//iteration_cycle=5971968|start_cycle=6|II=1|out=8/*pe_up*/
%not pe_left

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=5971968|start_cycle=5|II=1|out=8/*pe_up*/
%smul pe_down,imm_reg[0]

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=5971968|start_cycle=8|II=1|out=8/*pe_up*/
%smul gr[6],imm_reg[0]

PE[25]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add8"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=5/*pe_right*/|out=16/*gr[3]*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=5971967|start_cycle=2|II=1|out=5/*pe_right*/|out=16/*gr[3]*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[26]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 3,imm_reg[0]
//iteration_cycle=5971968|start_cycle=2|II=1|out=5/*pe_right*/|out=8/*pe_up*/|out=15/*gr[2]*/
%and pe_left,imm_reg[0]

PE[27]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=5971968|start_cycle=3|II=1|out=8/*pe_up*/
%if a==b,pe_left,imm_reg[0]

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=5971968|start_cycle=4|II=1|out=8/*pe_up*/|out=14/*gr[1]*/
%if a==b,gr[2],imm_reg[0]

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm -1,imm_reg[0]
//iteration_cycle=5971968|start_cycle=3|II=1|out=5/*pe_right*/
%sadd gr[3],imm_reg[0]

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=5971968|start_cycle=4|II=1|out=8/*pe_up*/
%sra pe_left,imm_reg[0]

