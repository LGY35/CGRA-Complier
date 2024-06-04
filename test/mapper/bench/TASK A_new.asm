PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=8|II=0|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=9|II=1|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load8"*/
//iteration_cycle=1512|start_cycle=9|II=1|out=5/*pe_right*/
%load pe_left

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "lt2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=1512|start_cycle=10|II=1|out=5/*pe_right*/
%if a<b,imm_reg[0],pe_left

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "select2"*/
//iteration_cycle=1512|start_cycle=11|II=1|out=5/*pe_right*/
%if a==1,pe_left,pe_down,gr[0]

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=1512|start_cycle=12|II=1|out=5/*pe_right*/
%smod pe_left,imm_reg[0]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store0"*/
//iteration_cycle=1512|start_cycle=13|II=1
%store pe_down,pe_left

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sub2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=5|II=1|out=5/*pe_right*/
%ssub pe_down,imm_reg[0]

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=6|II=1|out=5/*pe_right*/
%smul pe_left,imm_reg[0]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1512|start_cycle=7|II=1|out=5/*pe_right*/
%sadd pe_left,imm_reg[0]

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout1"*/
//iteration_cycle=1512|start_cycle=8|II=1|out=5/*pe_right*/
%rout pe_left

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load7"*/
//iteration_cycle=1512|start_cycle=9|II=1|out=5/*pe_right*/
%load pe_left

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add6"*/
//iteration_cycle=1512|start_cycle=10|II=1|out=8/*pe_up*/
%sadd pe_down,pe_left

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=12|II=0|out=8/*pe_up*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=13|II=1|out=8/*pe_up*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[16]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load6"*/
//iteration_cycle=1512|start_cycle=4|II=1|out=8/*pe_up*/
%load pe_down

PE[17]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=5|II=1|out=5/*pe_right*/
%smul pe_down,imm_reg[0]

PE[18]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1512|start_cycle=6|II=1|out=5/*pe_right*/
%sadd pe_left

PE[19]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load4"*/
//iteration_cycle=1512|start_cycle=7|II=1|out=5/*pe_right*/
%load pe_left

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add5"*/
//iteration_cycle=1512|start_cycle=8|II=1|out=5/*pe_right*/
%sadd pe_down,pe_left

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "select1"*/
//iteration_cycle=1512|start_cycle=9|II=1|out=8/*pe_up*/|out=3/*gr[0]*/
%if a==1,pe_right,pe_left,pe_down

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "lt1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=8|II=1|out=7/*pe_left*/
%if a<b,imm_reg[0],pe_right

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load9"*/
//iteration_cycle=1512|start_cycle=7|II=1|out=7/*pe_left*/
%load pe_down

PE[24]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=3|II=1|out=8/*pe_up*/
%sadd pe_down,imm_reg[0]

PE[25]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sub1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=4|II=1|out=8/*pe_up*/
%ssub pe_down,imm_reg[0]

PE[26]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1512|start_cycle=5|II=1|out=5/*pe_right*/
%sadd pe_down

PE[27]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load3"*/
//iteration_cycle=1512|start_cycle=6|II=1|out=5/*pe_right*/
%load pe_left

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "select0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1512|start_cycle=7|II=1|out=8/*pe_up*/|out=5/*pe_right*/
%if a==1,pe_down,pe_left,imm_reg[0]

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout2"*/
//iteration_cycle=1512|start_cycle=8|II=1|out=8/*pe_up*/
%rout pe_left

PE[31]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=6|II=0|out=8/*pe_up*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=7|II=1|out=8/*pe_up*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[32]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=2|II=1|out=5/*pe_right*/|out=8/*pe_up*/
%sadd pe_down,imm_reg[0]

PE[33]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load5"*/
//iteration_cycle=1512|start_cycle=3|II=1|out=8/*pe_up*/
%load pe_left

PE[34]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=4|II=1|out=8/*pe_up*/
%smul pe_down,imm_reg[0]

PE[35]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load0"*/
//iteration_cycle=1512|start_cycle=5|II=1|out=5/*pe_right*/
%load pe_down

PE[36]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "lt0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1512|start_cycle=6|II=1|out=8/*pe_up*/
%if a<b,imm_reg[0],pe_left

PE[40]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=8/*pe_up*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 3,imm_reg[1]
//iteration_cycle=1511|start_cycle=2|II=1|out=8/*pe_up*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[41]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load10"*/
//iteration_cycle=1512|start_cycle=2|II=1|out=5/*pe_right*/
%load pe_down

PE[42]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sub0"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=1512|start_cycle=3|II=1|out=8/*pe_up*/
%ssub pe_left,imm_reg[0]

PE[43]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=4|II=0|out=8/*pe_up*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=1511|start_cycle=5|II=1|out=8/*pe_up*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[49]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=8/*pe_up*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 3,imm_reg[1]
//iteration_cycle=1511|start_cycle=2|II=1|out=8/*pe_up*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

