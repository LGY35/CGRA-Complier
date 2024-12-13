#ifndef __CSPM_HH__
#define __CSPM_HH__
//
#include <cstdint>
#include <vector>
#include "CGRA_define.hh"

/* Unused or Preset */
struct LOOP
{
    //INX start;
    //INY step;
    //INZ end;
    unsigned int passive_beat;
    int step_opcode;
    /*
    00 add
    01 >>
    02 <<
    */
    int cpr_mode;
    /*
    00 <
    01 >
    02 ==
    */
    bool loop_mode;
};
struct NONLINEAR
{
	int mode;
	/*
	00 relu
	01 sigmoid
	 tanh
	02 leakyrelu
	*/
};
struct CSPM_TOP_TEMPLATE {
	//CSPM instruction count
	unsigned int CSPM_total = 0;//4bit
	//CSPMTOPָ instr repeat count
	unsigned int CSPM_TOP_renum = 0;
};
struct LSUCSPM {
	bool mode; //0 load 1 store
	unsigned int CSPM_renum;
	unsigned int renum_delay;
	bool data_from;
	unsigned int delay;
	unsigned int bank_id;
	unsigned int addr_start;
	unsigned int length;
};


/* Need Revision */
struct IF
{
	//output = (IF.mode) ? b : c
    //inx a
    //iny b
    //inz c
    int mode;
    /*
    00 s a< b 
    01 s a<=b
    02 s a==b
    03 s a==1
    */
    
	/* UNUSED */
	bool if_pattern = 0;
	/*
	0 t f
	1 f t
	*/
	int result = 2;
    /*
    00 1,0	
    01 a,b
    02 b,c
    03 c,c
    */
};

struct ROUTE
{
    //inx a
    uint8_t route_delay;
};

struct ARITH
{
    //inx a
    //iny b
    int mode;
    /*
    00 sadd 
    01 ssub
    02 sabs |sA|
    03 NEG s=-sA
    04 smul
    05 smac
	06 smod

    */
};

struct LOGIC
{
    //inx a
    //iny b
    int mode;
    /*Ĭ//////޷//////////
    00 AND
    01 OR
    02 NOT ~
    03 XOR
    */
};

struct SHIFTER
{
    //inx a
    //iny b
    int mode;
    /*
    00 uSRL uA[31:0]>>uB[4:0]
    01 sARL sA[31:0]>>sB[4:0]
    02 uSLL uA[31:0]<<uB[4:0]
    */
};

struct LSU_Opcode
{
	int mode;
	//0: load
	//1: store
	//int bankid;
};






struct PECSPM  
{
	/* UNUSED OR PRSET*/
	unsigned int enable_beat = 0xf;//unused
	bool datawidth_mode = 1;//uint_32, 
	bool PE_beat_mode;//1bit 0 EN ,  1 END
	unsigned int PE_lsu = 0xf;
	//unsigned int PE_gr = 0xf;//3bit
    unsigned int II = 0XF;

   
	/* CONFIG THROUGH INSTRUCTION DECODE */
    unsigned int CSPM_renum = 0;//iteration count
 
	//newly inserted in 2023.3.3
	unsigned int start_cycle = 0;;

	/* 
		input channel
		0-3: pe left/up/right/down
		4-5: lsu in(unused)
		6-8: imm register[0:2]
		9-11:local register[0:2]
		
	*/
    unsigned int INX = 0XF;
    unsigned int INY = 0XF;
    unsigned int INZ = 0XF;

	/*
		Output Channel
		PE_OUT[0:3] represent output direction: pe right/down/left/up

		0-3: pe left/up/right/down

		6:cal result(output0)
		9-11:local register[0:2]

		unused:
		4-5: lsu in(unused)
		7: cal result(output1)


	*/
	unsigned int PE_OUT[4] = { 0xf,0xf,0xf,0xf };
	unsigned int PE_lr[3] = { 0xf,0xf,0xf };
    bool GR_OUT[8] = {false,false,false,false,false,false,false,false};
    unsigned int PE_opcode = 0xf;//3bit
    /*
    0 Loop
    1 Route
    2 if
    3 arith
    4 logic
    5 shift
    6 nl
	//7 UNUSED
	8 lsu
    */
    LOOP PE_LOOP;
    ROUTE PE_ROUTE;
    IF PE_IF;
    ARITH PE_ARITH;
    LOGIC PE_LOGIC;
    SHIFTER PE_SHIFTER;
	NONLINEAR PE_NONLINEAR;
	LSU_Opcode PE_LSU;
};


struct CSPM {
    CSPM_TOP_TEMPLATE CSPM_TOP;//Unused
    PECSPM PE_CSPM;
    LSUCSPM LSU_CSPM;//Unused
};
#endif

