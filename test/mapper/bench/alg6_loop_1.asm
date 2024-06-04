PE[0]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "rout54"*/
//iteration_cycle=2985984|start_cycle=4|II=2|out=15/*gr[2]*/
%rout gr[4]
/*generating asm for node name "rout65"*/
//iteration_cycle=2985984|start_cycle=15|II=2|out=14/*gr[1]*/
%rout gr[4]

PE[1]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "ashr1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 7,imm_reg[0]
//iteration_cycle=2985984|start_cycle=14|II=2|out=5/*pe_right*/|out=14/*gr[1]*/
%srl pe_down,imm_reg[0]
/*generating asm for node name "rout71"*/
//iteration_cycle=2985984|start_cycle=7|II=2|out=18/*gr[5]*/
%rout gr[2]

PE[2]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "le3"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 511,imm_reg[0]
//iteration_cycle=2985984|start_cycle=15|II=2|out=5/*pe_right*/
%if a<=b,pe_left,imm_reg[0]
/*generating asm for node name "rout56"*/
//iteration_cycle=2985984|start_cycle=6|II=2|out=18/*gr[5]*/
%rout gr[2]

PE[3]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "sel8"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 511,imm_reg[0]
//iteration_cycle=2985984|start_cycle=16|II=2|out=5/*pe_right*/|out=3/*gr[0]*/
%if a==1,pe_left,gr[1],imm_reg[0]
/*generating asm for node name "rout77"*/
//iteration_cycle=2985984|start_cycle=13|II=2|out=16/*gr[3]*/
%rout gr[6]

PE[4]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "le4"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm -512,imm_reg[0]
//iteration_cycle=2985984|start_cycle=17|II=2|out=5/*pe_right*/
%if a<=b,pe_left,imm_reg[0]
/*generating asm for node name "rout58"*/
//iteration_cycle=2985984|start_cycle=8|II=2|out=19/*gr[6]*/
%rout gr[5]

PE[5]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "sel9"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm -512,imm_reg[0]
//iteration_cycle=2985984|start_cycle=18|II=2|out=5/*pe_right*/
%if a==1,pe_left,imm_reg[0],gr[0]
/*generating asm for node name "rout63"*/
//iteration_cycle=2985984|start_cycle=13|II=2|out=17/*gr[4]*/
%rout gr[7]

PE[6]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "add47"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 512,imm_reg[0]
//iteration_cycle=2985984|start_cycle=19|II=2|out=5/*pe_right*/
%sadd pe_left,imm_reg[0]
/*generating asm for node name "rout74"*/
//iteration_cycle=2985984|start_cycle=10|II=2|out=6/*pe_down*/
%rout pe_right

PE[7]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "store3"*/
//iteration_cycle=2985984|start_cycle=20|II=2
%store pe_left,pe_down
/*generating asm for node name "rout73"*/
//iteration_cycle=2985984|start_cycle=9|II=2|out=7/*pe_left*/
%rout gr[5]

PE[8]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "shl1"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 6,imm_reg[0]
//iteration_cycle=2985984|start_cycle=12|II=2|out=5/*pe_right*/
%sll pe_down,imm_reg[0]

PE[9]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add46"*/
//iteration_cycle=2985984|start_cycle=13|II=2|out=8/*pe_up*/
%sadd pe_right,pe_left
/*generating asm for node name "rout60"*/
//iteration_cycle=2985984|start_cycle=10|II=2|out=20/*gr[7]*/
%rout gr[6]

PE[10]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add45"*/
//iteration_cycle=2985984|start_cycle=12|II=2|out=7/*pe_left*/
%sadd pe_down,pe_right

PE[11]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul26"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm -42,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=2|out=7/*pe_left*/
%smul pe_down,imm_reg[0]

PE[12]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul27"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2304,imm_reg[0]
//iteration_cycle=2985984|start_cycle=16|II=2|out=5/*pe_right*/
%smul gr[3],imm_reg[0]

PE[13]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add48"*/
//iteration_cycle=2985984|start_cycle=17|II=2|out=5/*pe_right*/
%sadd pe_left,gr[1]

PE[14]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "mul28"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=18|II=2|out=5/*pe_right*/
%smul pe_left,imm_reg[0]
/*generating asm for node name "rout75"*/
//iteration_cycle=2985984|start_cycle=11|II=2|out=19/*gr[6]*/
%rout pe_up

PE[15]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add49"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm @d3_2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=19|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_left

PE[16]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load7"*/
//iteration_cycle=2985984|start_cycle=11|II=2|out=8/*pe_up*/
%load pe_down

PE[17]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul25"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm -22,imm_reg[0]
//iteration_cycle=2985984|start_cycle=10|II=2|out=5/*pe_right*/
%smul pe_down,imm_reg[0]

PE[18]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add44"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 64,imm_reg[0]
//iteration_cycle=2985984|start_cycle=11|II=2|out=8/*pe_up*/
%sadd pe_left,imm_reg[0]

PE[19]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load6"*/
//iteration_cycle=2985984|start_cycle=10|II=2|out=8/*pe_up*/
%load pe_down

PE[20]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq11"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=3|II=2|out=6/*pe_down*/
%if a==b,pe_right,imm_reg[0]

PE[21]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mod2"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2304,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=2|out=7/*pe_left*/|out=17/*gr[4]*/
%smod pe_right,imm_reg[0]

PE[22]
%TOP CP_index_=x|CP_num=x|Instruction_num=3
/*generating asm for node name "loop_add52"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=1|II=0|out=7/*pe_left*/|out=6/*pe_down*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=1|start_cycle=0|II=0|out=12
%imm 1,imm_reg[1]
//iteration_cycle=2985983|start_cycle=3|II=2|out=7/*pe_left*/|out=6/*pe_down*/|out=0/*lr[0]*/
%sadd lr[0],imm_reg[1]

PE[24]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add43"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=10|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_down

PE[25]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "load5"*/
//iteration_cycle=2985984|start_cycle=9|II=2|out=8/*pe_up*/
%load pe_down

PE[26]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add39"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=8|II=2|out=5/*pe_right*/
%sadd pe_down,imm_reg[0]

PE[27]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add40"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=9|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_left

PE[28]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "and4"*/
//iteration_cycle=2985984|start_cycle=4|II=2|out=6/*pe_down*/
%and pe_right,pe_up

PE[29]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "not3"*/
//iteration_cycle=2985984|start_cycle=3|II=2|out=7/*pe_left*/
%not pe_right

PE[30]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "eq12"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=2985984|start_cycle=2|II=2|out=7/*pe_left*/
%if a==b,pe_up,imm_reg[0]

PE[32]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add42"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 4,imm_reg[0]
//iteration_cycle=2985984|start_cycle=9|II=2|out=8/*pe_up*/
%sadd gr[0],imm_reg[0]

PE[33]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "add37"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm %2,imm_reg[0]
//iteration_cycle=2985984|start_cycle=8|II=2|out=8/*pe_up*/
%sadd imm_reg[0],pe_right

PE[34]
%TOP CP_index_=x|CP_num=x|Instruction_num=1
/*generating asm for node name "add36"*/
//iteration_cycle=2985984|start_cycle=7|II=2|out=7/*pe_left*/|out=8/*pe_up*/|out=3/*gr[0]*/
%sadd pe_right,pe_down

PE[35]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul19"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 13824,imm_reg[0]
//iteration_cycle=2985984|start_cycle=6|II=2|out=7/*pe_left*/
%smul pe_right,imm_reg[0]

PE[36]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "loop_add51"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 0,imm_reg[0]
//iteration_cycle=1|start_cycle=5|II=0|out=7/*pe_left*/|out=15/*gr[2]*/|out=0/*lr[0]*/
%rout imm_reg[0]
//iteration_cycle=2985983|start_cycle=7|II=2|out=7/*pe_left*/|out=15/*gr[2]*/|out=0/*lr[0]*/
%sadd lr[0],pe_up

PE[42]
%TOP CP_index_=x|CP_num=x|Instruction_num=2
/*generating asm for node name "mul20"*/
//iteration_cycle=1|start_cycle=0|II=0|out=11
%imm 6,imm_reg[0]
//iteration_cycle=2985984|start_cycle=6|II=2|out=8/*pe_up*/
%smul gr[2],imm_reg[0]

