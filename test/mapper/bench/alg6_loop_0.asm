PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "rout81"*/
//iteration_cycle=2985984|start_cycle=4|II=2|out=14/*gr[1]*/
%rout gr[4]
/*generating asm for node name "rout100"*/
//iteration_cycle=2985984|start_cycle=11|II=2|out=15/*gr[2]*/
%rout gr[4]

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "mul36"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 75,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=2|out=5/*pe_right*/
%smul pe_down,imm_reg[0]
/*generating asm for node name "rout83"*/
//iteration_cycle=2985984|start_cycle=6|II=2|out=18/*gr[5]*/
%rout gr[1]

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add63"*/
//iteration_cycle=2985984|start_cycle=12|II=2|out=5/*pe_right*/
%sadd pe_down,pe_left
/*generating asm for node name "rout96"*/
//iteration_cycle=2985984|start_cycle=7|II=2|out=18/*gr[5]*/
%rout gr[3]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add64"*/
//iteration_cycle=2985984|start_cycle=13|II=2|out=5/*pe_right*/
%sadd pe_left,pe_down
/*generating asm for node name "rout89"*/
//iteration_cycle=2985984|start_cycle=12|II=2|out=16/*gr[3]*/
%rout gr[6]

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "shr5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 7,imm_reg[0]
//iteration_cycle=2985984|start_cycle=14|II=2|out=5/*pe_right*/|out=3/*gr[0]*/
%sra pe_left,imm_reg[0]
/*generating asm for node name "rout98"*/
//iteration_cycle=2985984|start_cycle=9|II=2|out=17/*gr[4]*/
%rout gr[5]

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "le5"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1023,imm_reg[0]
//iteration_cycle=2985984|start_cycle=15|II=2|out=5/*pe_right*/
%if a<=b,pe_left,imm_reg[0]
/*generating asm for node name "rout85"*/
//iteration_cycle=2985984|start_cycle=8|II=2|out=6/*pe_down*/
%rout gr[5]

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=4
/*generating asm for node name "sel10"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 1023,imm_reg[0]
//iteration_cycle=2985984|start_cycle=16|II=2|out=5/*pe_right*/|out=15/*gr[2]*/
%if a==1,pe_left,gr[0],imm_reg[0]
/*generating asm for node name "add67"*/
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm %1,imm_reg[1]
//iteration_cycle=2985984|start_cycle=17|II=2|out=5/*pe_right*/
%sadd imm_reg[1],gr[1]

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "store4"*/
//iteration_cycle=2985984|start_cycle=17|II=2
%store pe_left,pe_down
/*generating asm for node name "store5"*/
//iteration_cycle=2985984|start_cycle=18|II=2
%store gr[2],pe_left

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load9"*/
//iteration_cycle=2985984|start_cycle=10|II=2|out=8/*pe_up*/
%load pe_down

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add62"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 64,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=2|out=8/*pe_up*/
%sadd pe_down,imm_reg[0]

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul37"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 15,imm_reg[0]
//iteration_cycle=2985984|start_cycle=12|II=2|out=8/*pe_up*/
%smul pe_down,imm_reg[0]

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul38"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2304,imm_reg[0]
//iteration_cycle=2985984|start_cycle=13|II=2|out=5/*pe_right*/
%smul gr[2],imm_reg[0]

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add65"*/
//iteration_cycle=2985984|start_cycle=14|II=2|out=5/*pe_right*/
%sadd pe_left,gr[3]
/*generating asm for node name "rout86"*/
//iteration_cycle=2985984|start_cycle=9|II=2|out=19/*gr[6]*/
%rout pe_up

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul39"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=15|II=2|out=5/*pe_right*/|out=14/*gr[1]*/
%smul pe_left,imm_reg[0]

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add66"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @d3_1,imm_reg[0]
//iteration_cycle=2985984|start_cycle=16|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_left

PE[17]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add58"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=9|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_down

PE[18]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul35"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 38,imm_reg[0]
//iteration_cycle=2985984|start_cycle=10|II=2|out=8/*pe_up*/
%smul pe_down,imm_reg[0]

PE[19]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load10"*/
//iteration_cycle=2985984|start_cycle=11|II=2|out=8/*pe_up*/
%load pe_right

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add61"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=10|II=2|out=7/*pe_left*/
%sadd imm_reg[0],pe_right

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add60"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4,imm_reg[0]
//iteration_cycle=2985984|start_cycle=9|II=2|out=7/*pe_left*/
%sadd gr[0],imm_reg[0]

PE[25]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add57"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=8|II=2|out=8/*pe_up*/
%sadd pe_down,imm_reg[0]

PE[26]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load8"*/
//iteration_cycle=2985984|start_cycle=9|II=2|out=8/*pe_up*/
%load pe_down

PE[32]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul29"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 13824,imm_reg[0]
//iteration_cycle=2985984|start_cycle=6|II=2|out=5/*pe_right*/
%smul pe_down,imm_reg[0]

PE[33]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add54"*/
//iteration_cycle=2985984|start_cycle=7|II=2|out=5/*pe_right*/|out=8/*pe_up*/|out=3/*gr[0]*/
%sadd pe_left,pe_down

PE[34]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add55"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=8|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_left

PE[40]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "loop_add69"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=5|II=0|out=8/*pe_up*/|out=16/*gr[3]*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=2985983|start_cycle=7|II=2|out=8/*pe_up*/|out=16/*gr[3]*/|out=0/*lr[0]*/
%sadd lr[0],pe_down

PE[41]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul30"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 6,imm_reg[0]
//iteration_cycle=2985984|start_cycle=6|II=2|out=8/*pe_up*/
%smul gr[1],imm_reg[0]

PE[48]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and5"*/
//iteration_cycle=2985984|start_cycle=4|II=2|out=8/*pe_up*/
%and pe_down,pe_right

PE[49]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq14"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=3|II=2|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[50]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2304,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=2|out=7/*pe_left*/|out=17/*gr[4]*/
%smod pe_down,imm_reg[0]

PE[56]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not4"*/
//iteration_cycle=2985984|start_cycle=3|II=2|out=8/*pe_up*/
%not pe_right

PE[57]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq15"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=2|out=7/*pe_left*/
%if a==b,pe_right,imm_reg[0]

PE[58]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add70"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=8/*pe_up*/|out=7/*pe_left*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=2985983|start_cycle=3|II=2|out=8/*pe_up*/|out=7/*pe_left*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

