//#ifndef __LSU_HH__
//#define __LSU_HH__
////
//#include <cstdint>
//#include <vector>
//#include "CGRA_define.hh"
//#include "CSPM.hh"
////#define CGRALIBRARY_API __declspec(dllimport);
////DATAWIDTH_0(*MONITOR_SRAM())[SRAM_BANK_SIZE];
//
//struct LSUINTERFACE  //
//{
//	//pe connection
//	DATAWIDTH_0* PE_DATA_IN = NULL;
//	BEATWIDTH* PE_BEAT_IN = NULL;
//	DATAWIDTH_0* LSU_PE_DATA_OUT = NULL;
//	BEATWIDTH* LSU_PE_BEAT_OUT = NULL;
//	unsigned int INDEX;
//	bool* LSU_ENABLE_IN = NULL;
//	bool* LSU_IDLE_OUT= NULL;
//	bool* LSU_START_IN= NULL;
//	bool* LSU_CSPM_IDLE_OUT= NULL;
//};
//
//struct LSUCONTROLL {
//	unsigned int CSPM_EX_addr;
//	unsigned int CSPM_addr;
//	unsigned int renum;//
//	unsigned int renum_delay;//
//	unsigned int top_renum;//
//	unsigned int bank_id;
//	DATAWIDTH_0 data;
//	unsigned int length;
//	BEATWIDTH beat;
//	unsigned int delay;//.valid_delay
//	unsigned int addr;
//	std::vector<BEATWIDTH> output_beat_delay;///END
//	std::vector<DATAWIDTH_0> output_PE_delay;//LSU 
//	std::vector<unsigned int> valid_delay;//
//};
//
//class LSU
//{
//public:
//	LSUINTERFACE LSU_INTERFACE;
//	//LSUINTERFACE* LSU_INTERFACE = NULL;
//	// NeuronAddrObject* PE_Neuron_Addr = NULL;
//
//	//CSPM
//	CSPM_TOP_TEMPLATE LSU_CSPM_TOP;
//	std::vector<LSUCSPM>LSU_CSPM;
//	//ctrl_reg
//	//std::vector<bool>PE_CSPM_EN;
//	LSUCONTROLL LSU_CONTROLL;
//	uint8_t LSU_STATE;
//	uint8_t CSPM_STATE;
//	LSU(LSUINTERFACE Lsu_interface);
//	//LSU();
//	~LSU()=default;
//
//	void LSU_reset();
//	void LSU_EXEC();
//	void LSU_OUTPUT();
//};
//
//#endif