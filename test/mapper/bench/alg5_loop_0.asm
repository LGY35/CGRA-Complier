PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout73"*/
//iteration_cycle=11943936|start_cycle=10|II=1|out=3/*gr[0]*/
%rout pe_down

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout70"*/
//iteration_cycle=11943936|start_cycle=7|II=1|out=20/*gr[7]*/
%rout gr[2]

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr10"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=11|II=1|out=5/*pe_right*/
%sra gr[1],imm_reg[0]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul46"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=5/*pe_right*/
%smul pe_left,imm_reg[0]

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add71"*/
//iteration_cycle=11943936|start_cycle=13|II=1|out=5/*pe_right*/
%sadd pe_down,pe_left

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add72"*/
//iteration_cycle=11943936|start_cycle=14|II=1|out=5/*pe_right*/
%sadd pe_left,pe_down

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel18"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @dump,imm_reg[0]
//iteration_cycle=11943936|start_cycle=15|II=1|out=5/*pe_right*/
%if a==1,pe_down,pe_left,imm_reg[0]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store10"*/
//iteration_cycle=11943936|start_cycle=16|II=1
%store pe_down,pe_left

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout72"*/
//iteration_cycle=11943936|start_cycle=9|II=1|out=8/*pe_up*/
%rout gr[7]

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel15"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=9|II=1|out=5/*pe_right*/|out=19/*gr[6]*/
%if a==1,gr[3],pe_down,imm_reg[0]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not10"*/
//iteration_cycle=11943936|start_cycle=10|II=1|out=5/*pe_right*/
%not pe_left

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and18"*/
//iteration_cycle=11943936|start_cycle=11|II=1|out=5/*pe_right*/|out=18/*gr[5]*/
%and pe_left,pe_down

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "sel17"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %3,imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %4,imm_reg[1]
//iteration_cycle=11943936|start_cycle=12|II=1|out=8/*pe_up*/
%if a==1,pe_left,imm_reg[1],imm_reg[0]

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul47"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=11943936|start_cycle=13|II=1|out=8/*pe_up*/
%smul pe_down,imm_reg[0]

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "or1"*/
//iteration_cycle=11943936|start_cycle=14|II=1|out=8/*pe_up*/
%or pe_down,gr[4]

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load12"*/
//iteration_cycle=11943936|start_cycle=15|II=1|out=8/*pe_up*/
%load pe_down

PE[16]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and16"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=1|out=5/*pe_right*/
%and gr[2],imm_reg[0]

PE[17]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq23"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=1|out=8/*pe_up*/|out=5/*pe_right*/
%if a==b,pe_left,imm_reg[0]

PE[18]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel16"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=9|II=1|out=5/*pe_right*/
%if a==1,pe_down,imm_reg[0],pe_left

PE[19]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not11"*/
//iteration_cycle=11943936|start_cycle=10|II=1|out=8/*pe_up*/
%not pe_left

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout68"*/
//iteration_cycle=11943936|start_cycle=5|II=1|out=15/*gr[2]*/
%rout pe_down

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr11"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=8/*pe_up*/
%sra gr[0],imm_reg[0]

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout81"*/
//iteration_cycle=11943936|start_cycle=13|II=1|out=8/*pe_up*/
%rout gr[5]

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add70"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=14|II=1|out=8/*pe_up*/
%sadd imm_reg[0],pe_down

PE[24]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and15"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=6|II=1|out=5/*pe_right*/
%and pe_down,imm_reg[0]

PE[25]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq22"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=1|out=5/*pe_right*/|out=16/*gr[3]*/
%if a==b,pe_left,imm_reg[0]

PE[26]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "xor2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=1|out=8/*pe_up*/
%xor pe_left,imm_reg[0]

PE[27]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout66"*/
//iteration_cycle=11943936|start_cycle=3|II=1|out=5/*pe_right*/
%rout pe_down

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout67"*/
//iteration_cycle=11943936|start_cycle=4|II=1|out=8/*pe_up*/
%rout pe_left

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout78"*/
//iteration_cycle=11943936|start_cycle=12|II=1|out=17/*gr[4]*/
%rout pe_down

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul45"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=5/*pe_right*/
%smul gr[0],imm_reg[0]

PE[31]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add69"*/
//iteration_cycle=11943936|start_cycle=13|II=1|out=8/*pe_up*/
%sadd pe_down,pe_left

PE[32]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "loop_add74"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=5|II=0|out=8/*pe_up*/|out=6/*pe_down*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=11943935|start_cycle=6|II=1|out=8/*pe_up*/|out=6/*pe_down*/|out=0/*lr[0]*/
%sadd lr[0],pe_right

PE[33]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and14"*/
//iteration_cycle=11943936|start_cycle=4|II=1|out=7/*pe_left*/
%and pe_down,pe_right

PE[34]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq20"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=3|II=1|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[35]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=1|out=7/*pe_left*/|out=8/*pe_up*/
%smod pe_down,imm_reg[0]

PE[37]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout77"*/
//iteration_cycle=11943936|start_cycle=11|II=1|out=8/*pe_up*/
%rout gr[6]

PE[38]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout87"*/
//iteration_cycle=11943936|start_cycle=11|II=1|out=5/*pe_right*/
%rout gr[1]

PE[39]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul44"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 9216,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=8/*pe_up*/
%smul pe_left,imm_reg[0]

PE[40]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout82"*/
//iteration_cycle=11943936|start_cycle=6|II=1|out=6/*pe_down*/
%rout pe_up

PE[41]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not9"*/
//iteration_cycle=11943936|start_cycle=3|II=1|out=8/*pe_up*/
%not pe_right

PE[42]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq21"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=1|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[43]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add75"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=8/*pe_up*/|out=7/*pe_left*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=11943935|start_cycle=2|II=1|out=8/*pe_up*/|out=7/*pe_left*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[48]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout83"*/
//iteration_cycle=11943936|start_cycle=7|II=1|out=5/*pe_right*/
%rout pe_up

PE[49]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout84"*/
//iteration_cycle=11943936|start_cycle=8|II=1|out=5/*pe_right*/
%rout pe_left

PE[50]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout85"*/
//iteration_cycle=11943936|start_cycle=9|II=1|out=14/*gr[1]*/
%rout pe_left

