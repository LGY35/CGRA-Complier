PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=2|out=5/*pe_right*/|out=16/*gr[3]*/
%smod pe_down,imm_reg[0]

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "eq5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=3|II=2|out=5/*pe_right*/
%if a==b,pe_left,imm_reg[0]
/*generating asm for node name "rout17"*/
//iteration_cycle=11943936|start_cycle=4|II=2|out=15/*gr[2]*/
%rout gr[3]

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and3"*/
//iteration_cycle=11943936|start_cycle=4|II=2|out=5/*pe_right*/
%and pe_down,pe_left

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "loop_add37"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=5|II=0|out=5/*pe_right*/|out=16/*gr[3]*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=11943935|start_cycle=7|II=2|out=5/*pe_right*/|out=16/*gr[3]*/|out=0/*lr[0]*/
%sadd lr[0],pe_left

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=6|II=2|out=5/*pe_right*/
%sra pe_left,imm_reg[0]

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "mul14"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=2|out=6/*pe_down*/|out=14/*gr[1]*/
%smul pe_left,imm_reg[0]
/*generating asm for node name "add34"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 4,imm_reg[1]
//iteration_cycle=11943936|start_cycle=10|II=2|out=6/*pe_down*/
%sadd gr[1],imm_reg[1]

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "mul15"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=2|out=6/*pe_down*/|out=3/*gr[0]*/
%smul pe_right,imm_reg[0]
/*generating asm for node name "rout21"*/
//iteration_cycle=11943936|start_cycle=11|II=2|out=6/*pe_down*/
%rout gr[0]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=2|out=7/*pe_left*/
%sra gr[2],imm_reg[0]

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add38"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=8/*pe_up*/|out=5/*pe_right*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=11943935|start_cycle=3|II=2|out=8/*pe_up*/|out=5/*pe_right*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq6"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=2|out=5/*pe_right*/
%if a==b,pe_left,imm_reg[0]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not2"*/
//iteration_cycle=11943936|start_cycle=3|II=2|out=8/*pe_up*/
%not pe_left

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=2|out=6/*pe_down*/
%and gr[3],imm_reg[0]

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add22"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %3,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=2|out=5/*pe_right*/
%sadd imm_reg[0],pe_up
/*generating asm for node name "add35"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=11943936|start_cycle=11|II=2|out=5/*pe_right*/
%sadd imm_reg[1],pe_up

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "add23"*/
//iteration_cycle=11943936|start_cycle=9|II=2|out=5/*pe_right*/
%sadd pe_left,pe_up
/*generating asm for node name "sel6"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @dump,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=2|out=5/*pe_right*/
%if a==1,pe_up,pe_left,imm_reg[0]

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "load4"*/
//iteration_cycle=11943936|start_cycle=10|II=2|out=6/*pe_down*/
%load pe_left
/*generating asm for node name "store5"*/
//iteration_cycle=11943936|start_cycle=13|II=2
%store pe_down,pe_left

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq7"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=2|out=5/*pe_right*/
%if a==b,pe_up,imm_reg[0]

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "xor0"*/
//iteration_cycle=11943936|start_cycle=9|II=2|out=5/*pe_right*/|out=3/*gr[0]*/
%xor pe_down,pe_left
/*generating asm for node name "rout25"*/
//iteration_cycle=11943936|start_cycle=10|II=2|out=5/*pe_right*/
%rout gr[0]

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "add32"*/
//iteration_cycle=11943936|start_cycle=11|II=2|out=5/*pe_right*/
%sadd pe_down,pe_left
/*generating asm for node name "sel4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @dump,imm_reg[0]
//iteration_cycle=11943936|start_cycle=10|II=2|out=5/*pe_right*/
%if a==1,pe_left,pe_down,imm_reg[0]

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "store3"*/
//iteration_cycle=11943936|start_cycle=11|II=2
%store pe_up,pe_left
/*generating asm for node name "load6"*/
//iteration_cycle=11943936|start_cycle=12|II=2|out=8/*pe_up*/
%load pe_left

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=2|out=5/*pe_right*/
%and gr[2],imm_reg[0]

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "eq8"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=2|out=8/*pe_up*/
%if a==b,pe_left,imm_reg[0]
/*generating asm for node name "rout23"*/
//iteration_cycle=11943936|start_cycle=9|II=2|out=5/*pe_right*/
%rout gr[1]

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "add25"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=9|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_down
/*generating asm for node name "add31"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %5,imm_reg[1]
//iteration_cycle=11943936|start_cycle=10|II=2|out=8/*pe_up*/
%sadd imm_reg[1],pe_left

PE[37]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul17"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 6,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=2|out=5/*pe_right*/
%smul gr[2],imm_reg[0]

PE[38]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add24"*/
//iteration_cycle=11943936|start_cycle=8|II=2|out=8/*pe_up*/|out=5/*pe_right*/|out=14/*gr[1]*/
%sadd pe_down,pe_left

PE[39]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add29"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=11943936|start_cycle=9|II=2|out=6/*pe_down*/
%sadd pe_left,imm_reg[0]

PE[46]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul16"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 27648,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=2|out=8/*pe_up*/
%smul gr[3],imm_reg[0]

PE[47]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add30"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=10|II=2|out=6/*pe_down*/
%sadd imm_reg[0],pe_up

PE[53]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add26"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %4,imm_reg[0]
//iteration_cycle=11943936|start_cycle=9|II=2|out=5/*pe_right*/
%sadd imm_reg[0],gr[1]

PE[54]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add27"*/
//iteration_cycle=11943936|start_cycle=10|II=2|out=6/*pe_down*/
%sadd pe_left,gr[0]

PE[55]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @dump,imm_reg[0]
//iteration_cycle=11943936|start_cycle=11|II=2|out=6/*pe_down*/
%if a==1,gr[0],pe_up,imm_reg[0]

PE[62]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load5"*/
//iteration_cycle=11943936|start_cycle=11|II=2|out=5/*pe_right*/
%load pe_up

PE[63]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store4"*/
//iteration_cycle=11943936|start_cycle=12|II=2
%store pe_left,pe_up

