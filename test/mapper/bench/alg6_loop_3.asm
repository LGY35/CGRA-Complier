PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=2985984|start_cycle=6|II=1|out=5/*pe_right*/
%and pe_down,imm_reg[0]

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq6"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=7|II=1|out=5/*pe_right*/|out=16/*gr[3]*/
%if a==b,pe_left,imm_reg[0]

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "sel3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @d3_2,imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm @d3_3,imm_reg[1]
//iteration_cycle=2985984|start_cycle=8|II=1|out=5/*pe_right*/
%if a==1,pe_left,imm_reg[0],imm_reg[1]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add12"*/
//iteration_cycle=2985984|start_cycle=9|II=1|out=5/*pe_right*/
%sadd pe_left,pe_down

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load1"*/
//iteration_cycle=2985984|start_cycle=10|II=1|out=5/*pe_right*/|out=3/*gr[0]*/
%load pe_left

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "le0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1023,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=1|out=5/*pe_right*/
%if a<=b,pe_left,imm_reg[0]

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1023,imm_reg[0]
//iteration_cycle=2985984|start_cycle=12|II=1|out=5/*pe_right*/
%if a==1,pe_left,gr[0],imm_reg[0]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store1"*/
//iteration_cycle=2985984|start_cycle=13|II=1
%store pe_left,pe_down

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout15"*/
//iteration_cycle=2985984|start_cycle=5|II=1|out=8/*pe_up*/|out=14/*gr[1]*/
%rout pe_down

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2304,imm_reg[0]
//iteration_cycle=2985984|start_cycle=6|II=1|out=5/*pe_right*/
%smul pe_down,imm_reg[0]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add10"*/
//iteration_cycle=2985984|start_cycle=7|II=1|out=5/*pe_right*/
%sadd pe_left,gr[1]

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul7"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=8|II=1|out=8/*pe_up*/
%smul pe_left,imm_reg[0]

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout20"*/
//iteration_cycle=2985984|start_cycle=9|II=1|out=15/*gr[2]*/
%rout gr[3]

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout17"*/
//iteration_cycle=2985984|start_cycle=7|II=1|out=17/*gr[4]*/
%rout gr[1]

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "sel4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @d3_2_dst,imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm @d3_3_dst,imm_reg[1]
//iteration_cycle=2985984|start_cycle=11|II=1|out=5/*pe_right*/
%if a==1,gr[2],imm_reg[0],imm_reg[1]

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add13"*/
//iteration_cycle=2985984|start_cycle=12|II=1|out=8/*pe_up*/
%sadd pe_left,pe_down

PE[16]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout14"*/
//iteration_cycle=2985984|start_cycle=4|II=1|out=8/*pe_up*/
%rout gr[5]

PE[17]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "loop_add16"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=5|II=0|out=8/*pe_up*/|out=20/*gr[7]*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=2985983|start_cycle=6|II=1|out=8/*pe_up*/|out=20/*gr[7]*/|out=0/*lr[0]*/
%sadd lr[0],pe_right

PE[18]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and1"*/
//iteration_cycle=2985984|start_cycle=4|II=1|out=7/*pe_left*/
%and pe_down,pe_right

PE[19]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=3|II=1|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2304,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=1|out=7/*pe_left*/|out=18/*gr[5]*/
%smod pe_down,imm_reg[0]

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul6"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1152,imm_reg[0]
//iteration_cycle=2985984|start_cycle=9|II=1|out=5/*pe_right*/
%smul gr[6],imm_reg[0]

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add11"*/
//iteration_cycle=2985984|start_cycle=10|II=1|out=5/*pe_right*/
%sadd pe_left,pe_down

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul8"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=1|out=8/*pe_up*/
%smul pe_left,imm_reg[0]

PE[24]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout24"*/
//iteration_cycle=2985984|start_cycle=7|II=1|out=19/*gr[6]*/
%rout gr[7]

PE[26]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not1"*/
//iteration_cycle=2985984|start_cycle=3|II=1|out=8/*pe_up*/
%not pe_right

PE[27]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=1|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add15"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=8/*pe_up*/|out=7/*pe_left*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=2985983|start_cycle=2|II=1|out=8/*pe_up*/|out=7/*pe_left*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=2985984|start_cycle=9|II=1|out=8/*pe_up*/
%sra gr[4],imm_reg[0]

