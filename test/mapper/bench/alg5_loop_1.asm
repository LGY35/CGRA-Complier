PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout51"*/
//iteration_cycle=11943936|start_cycle=10|II=1|out=3/*gr[0]*/
%rout pe_right

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout50"*/
//iteration_cycle=11943936|start_cycle=9|II=1|out=7/*pe_left*/
%rout gr[7]

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr8"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=11|II=1|out=5/*pe_right*/
%sra gr[1],imm_reg[0]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul42"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=5/*pe_right*/
%smul pe_left,imm_reg[0]

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add63"*/
//iteration_cycle=11943936|start_cycle=13|II=1|out=5/*pe_right*/
%sadd pe_down,pe_left

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add64"*/
//iteration_cycle=11943936|start_cycle=14|II=1|out=5/*pe_right*/
%sadd pe_left,pe_down

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel14"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @dump,imm_reg[0]
//iteration_cycle=11943936|start_cycle=15|II=1|out=5/*pe_right*/
%if a==1,pe_down,pe_left,imm_reg[0]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "store9"*/
//iteration_cycle=11943936|start_cycle=16|II=1
%store pe_down,pe_left

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "xor1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=1|out=5/*pe_right*/
%xor pe_down,imm_reg[0]

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel11"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=9|II=1|out=5/*pe_right*/|out=19/*gr[6]*/
%if a==1,pe_left,pe_down,imm_reg[0]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not7"*/
//iteration_cycle=11943936|start_cycle=10|II=1|out=5/*pe_right*/
%not pe_left

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and13"*/
//iteration_cycle=11943936|start_cycle=11|II=1|out=5/*pe_right*/|out=18/*gr[5]*/
%and pe_left,pe_down

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "sel13"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %5,imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %6,imm_reg[1]
//iteration_cycle=11943936|start_cycle=12|II=1|out=8/*pe_up*/
%if a==1,pe_left,imm_reg[1],imm_reg[0]

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul43"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=11943936|start_cycle=13|II=1|out=8/*pe_up*/
%smul pe_down,imm_reg[0]

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "or0"*/
//iteration_cycle=11943936|start_cycle=14|II=1|out=8/*pe_up*/
%or pe_down,gr[4]

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load11"*/
//iteration_cycle=11943936|start_cycle=15|II=1|out=8/*pe_up*/
%load pe_down

PE[16]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq17"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=1|out=8/*pe_up*/|out=15/*gr[2]*/
%if a==b,pe_down,imm_reg[0]

PE[17]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq18"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=8|II=1|out=8/*pe_up*/|out=5/*pe_right*/
%if a==b,pe_down,imm_reg[0]

PE[18]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "sel12"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=9|II=1|out=5/*pe_right*/
%if a==1,gr[2],imm_reg[0],pe_left

PE[19]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not8"*/
//iteration_cycle=11943936|start_cycle=10|II=1|out=8/*pe_up*/
%not pe_left

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout46"*/
//iteration_cycle=11943936|start_cycle=5|II=1|out=16/*gr[3]*/
%rout pe_down

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shr9"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=8/*pe_up*/
%sra gr[0],imm_reg[0]

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout59"*/
//iteration_cycle=11943936|start_cycle=13|II=1|out=8/*pe_up*/
%rout gr[5]

PE[23]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add62"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=14|II=1|out=8/*pe_up*/
%sadd imm_reg[0],pe_down

PE[24]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and10"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=6|II=1|out=8/*pe_up*/
%and pe_down,imm_reg[0]

PE[25]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "and11"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1,imm_reg[0]
//iteration_cycle=11943936|start_cycle=7|II=1|out=8/*pe_up*/
%and gr[3],imm_reg[0]

PE[26]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout48"*/
//iteration_cycle=11943936|start_cycle=7|II=1|out=20/*gr[7]*/
%rout gr[3]

PE[27]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout44"*/
//iteration_cycle=11943936|start_cycle=3|II=1|out=5/*pe_right*/
%rout pe_down

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout45"*/
//iteration_cycle=11943936|start_cycle=4|II=1|out=8/*pe_up*/
%rout pe_left

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout56"*/
//iteration_cycle=11943936|start_cycle=12|II=1|out=17/*gr[4]*/
%rout pe_down

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul41"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=5/*pe_right*/
%smul gr[0],imm_reg[0]

PE[31]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add61"*/
//iteration_cycle=11943936|start_cycle=13|II=1|out=8/*pe_up*/
%sadd pe_down,pe_left

PE[32]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "loop_add66"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=5|II=0|out=8/*pe_up*/|out=6/*pe_down*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=11943935|start_cycle=6|II=1|out=8/*pe_up*/|out=6/*pe_down*/|out=0/*lr[0]*/
%sadd lr[0],pe_right

PE[33]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and9"*/
//iteration_cycle=11943936|start_cycle=4|II=1|out=7/*pe_left*/
%and pe_down,pe_right

PE[34]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq15"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=3|II=1|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[35]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4608,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=1|out=7/*pe_left*/|out=8/*pe_up*/
%smod pe_down,imm_reg[0]

PE[37]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout55"*/
//iteration_cycle=11943936|start_cycle=11|II=1|out=8/*pe_up*/
%rout gr[6]

PE[38]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout65"*/
//iteration_cycle=11943936|start_cycle=11|II=1|out=5/*pe_right*/
%rout gr[1]

PE[39]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul40"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 9216,imm_reg[0]
//iteration_cycle=11943936|start_cycle=12|II=1|out=8/*pe_up*/
%smul pe_left,imm_reg[0]

PE[40]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout60"*/
//iteration_cycle=11943936|start_cycle=6|II=1|out=6/*pe_down*/
%rout pe_up

PE[41]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not6"*/
//iteration_cycle=11943936|start_cycle=3|II=1|out=8/*pe_up*/
%not pe_right

PE[42]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq16"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=11943936|start_cycle=2|II=1|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[43]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add67"*/
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
/*generating asm for node name "rout61"*/
//iteration_cycle=11943936|start_cycle=7|II=1|out=5/*pe_right*/
%rout pe_up

PE[49]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout62"*/
//iteration_cycle=11943936|start_cycle=8|II=1|out=5/*pe_right*/
%rout pe_left

PE[50]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "rout63"*/
//iteration_cycle=11943936|start_cycle=9|II=1|out=14/*gr[1]*/
%rout pe_left

