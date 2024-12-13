#ifndef __PE_HH__
#define __PE_HH__
//

#include <cstdint>
#include <vector>
#include <queue>
#include "CGRA_define.hh"
#include "DebugSupport.hh"
#include "CSPM.hh"
#include<sstream>
////#define CGRALIBRARY_API __declspec(dllimport);






struct PECONTROLL  ////////////ṹ////////////PECSPM
{
	
	DATAWIDTH_0 input_fp16_x;
	DATAWIDTH_0 input_fp16_y;
	DATAWIDTH_0 input_fp16_z;
	DATAWIDTH_1 input_8t_x_0;
	DATAWIDTH_1 input_8t_y_0;
	DATAWIDTH_1 input_8t_z_0;
	DATAWIDTH_1 input_8t_x_1;
	DATAWIDTH_1 input_8t_y_1;
	DATAWIDTH_1 input_8t_z_1;
	DATAWIDTH_0 result_fp16;
	DATAWIDTH_1 result_8t_0;
	DATAWIDTH_1 result_8t_1;
	DATAWIDTH_0 output_0;
	DATAWIDTH_0 output_1;
	//DATAWIDTH_0 output_r;
	//DATAWIDTH_0 output_d;
	BEATWIDTH beat;
	//BEATWIDTH output_beat;
	std::vector<DATAWIDTH_0> output_PE_delay[4];
	std::vector<DATAWIDTH_0> output_LSU_delay;
	std::vector<DATAWIDTH_0> output_gr_delay;
	std::vector<BEATWIDTH> output_beat_delay;
	unsigned int delay;
	
	std::vector<unsigned int> valid_delay;
	
	unsigned int CSPM_addr;
	
	unsigned int top_renum = 0;
	
	// change to vector
	//std::vector<unsigned int> CSPM_EX_addr;
	std::vector<unsigned int> renum ;
	std::vector<unsigned int> start_cycle;
	std::vector<unsigned int> II;
	unsigned int idle_instr_count = 0;
};


struct PEINTERFACE  //
{
	//pe connection
	std::vector <DATAWIDTH_0*> PE_DATA_IN = {NULL};
	std::vector <BEATWIDTH*> PE_BEAT_IN = {NULL};
	std::vector <DATAWIDTH_0*> PE_DATA_OUT = {NULL};
	std::vector <BEATWIDTH*> PE_BEAT_OUT = {NULL};

	//LSU connection
	BEATWIDTH* PE_LSU_BEAT_OUT = NULL;
	DATAWIDTH_0* PE_LSU_DATA_OUT = NULL;
	std::vector<BEATWIDTH*> LSU_PE_BEAT_IN = {NULL};
	//std::queue<BEATWIDTH> FIFO_PE_BEAT_IN;//[]
	std::vector<DATAWIDTH_0*> LSU_PE_DATA_IN = {NULL};

	unsigned int INDEX = 0;
	//////////ӿ//
	bool* PE_ENABLE_IN = NULL;
	bool* PE_IDLE_OUT = NULL;
	bool* PE_START_IN = NULL;
	bool* PE_CSPM_IDLE_OUT = NULL;
};



class PE
{
public:
	//2023.3.4
	unsigned int INDEX = 0;

	PEINTERFACE PE_INTERFACE;
	//PEINTERFACEREG PE_INTERFACEREG;


	//commonly Used local param
	
	int arbitrate_index = 0;

	//local reg
	DATAWIDTH_0 local_reg[3];
	//CSPM
	CSPM_TOP_TEMPLATE PE_CSPM_TOP;
	std::vector<PECSPM>PE_CSPM;
	//ctrl_reg
	//std::vector<bool>PE_CSPM_EN;
	PECONTROLL PE_CONTROLL;
	uint8_t PE_STATE;
	uint8_t CSPM_STATE;
	//////////
	PE(PEINTERFACE &Pe_interface, int index);
	PE();
	~PE() = default;
	void PE_reset();
	void PE_checkbeat(PECSPM &PE_CSPM);
	void PE_selectinput(PECSPM &PE_CSPM,std::ostringstream &os,DebugParam_t &debug,int &taskid);
	void PE_calculate(PECSPM &PE_CSPM,std::ostringstream &os, DebugParam_t &debug,int &taskid);
	//void PE_cal_LOOP(PECSPM PE_CSPM);
	void PE_cal_ROUTE(PECSPM &PE_CSPM,ostringstream &os);
	void PE_cal_IF(PECSPM &PE_CSPM,ostringstream &os, DebugParam_t &debug,int &taskid);
	void PE_cal_ARITH(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid);
	void PE_cal_LOGIC(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid);
	void PE_cal_SHIFTER(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid);
	//void PE_cal_CLIPBITS(PECSPM PE_CSPM);
	//void PE_cal_NONLINEAR(PECSPM PE_CSPM);
	void PE_cal_LSU_Opcode(PECSPM &PE_CSPM,std::ostringstream &os, DebugParam_t &debug, int &taskid);
	inline void PE_set_Interface(PEINTERFACE Pe_interface) 
	{
		PE_INTERFACE = Pe_interface;
	}

	void PE_OUTMUX(PECSPM &PE_CSPM,std::ostringstream &os,DebugParam_t &debug,int &taskid);
	
	void FIFO_BEAT_ENQUEUE();

	void PE_OUTPUT();
	void PE_EXEC( DebugParam_t &debug, bool &debugflag, int &taskid,std::ostringstream &os);
};

#endif