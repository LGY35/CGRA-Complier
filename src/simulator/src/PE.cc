#include <cstring>
#include <cmath>
#include <iostream>
#include "assert.h" 
#include "../include/PE.hh"
#include "../include/CU.hh"
#include "../include/GR.hh"
//#include "../include/SRAM.hh"
#include "../include/WIRE.hh"
#include "../include/NLParam_BF.hh"
#include"../include/CSPM.hh"
#include "../include/DebugSupport.hh"
#include <exception>



#define STD_ABS(x) ((x) < 0 ? -(x) : (x))

DATAWIDTH_0 CU::PARA_BUFFER[PE_SIZE][PARAM_BUFFER_SIZE];



PE::PE(PEINTERFACE &Pe_interface, int index) {
	PE_INTERFACE = Pe_interface;
	INDEX = index;
	//PE_INTERFACEREG;
	//local reg
	memset(local_reg, 0, sizeof(local_reg));
	PE_STATE = PE_IDLE;
	CSPM_STATE = CSPM_IDLE;
}

PE::PE() {
	PEINTERFACE PE_INTERFACE;
	//PE_INTERFACEREG;
	//local reg
	memset(local_reg, 0, sizeof(local_reg));
	PE_STATE = PE_IDLE;
	CSPM_STATE = CSPM_IDLE;

}

void PE::PE_reset() {
	//std::fill(PE_INTERFACEREG.PE_DATA_OUT.begin(), PE_INTERFACEREG.PE_DATA_OUT.end(), 0);
	//std::fill(PE_INTERFACEREG.PE_BEAT_OUT.begin(), PE_INTERFACEREG.PE_BEAT_OUT.end(), 0);
	//PE_INTERFACEREG.PE_LSU_BEAT_OUT = 0;
	//PE_INTERFACEREG.PE_LSU_DATA_OUT = 0;
	//PE_INTERFACEREG.PE_IDLE_OUT = 0;
	//PE_INTERFACEREG.PE_CSPM_IDLE_OUT = 0;
	//local reg
	//memset(local_reg, 0, sizeof(local_reg));
	local_reg[0] = 0;
	local_reg[1] = 0;
	local_reg[2] = 0;

	PE_CSPM.clear();
	//CSPM
	PE_CONTROLL.renum.clear();
	PE_CONTROLL.start_cycle.clear();
	PE_CONTROLL.II.clear();
	PE_CONTROLL.idle_instr_count = 0;
	PE_CONTROLL.top_renum = 0;
	PE_CONTROLL.CSPM_addr = 0;
	PE_CONTROLL.valid_delay.clear();
	PE_CONTROLL.delay = 0;
	PE_CONTROLL.output_beat_delay.clear();
	PE_CONTROLL.output_gr_delay.clear();
	PE_CONTROLL.output_LSU_delay.clear();
	PE_CONTROLL.output_PE_delay[0].clear();
	PE_CONTROLL.output_PE_delay[1].clear();
	PE_CONTROLL.output_PE_delay[2].clear();
	PE_CONTROLL.output_PE_delay[3].clear();
	PE_CONTROLL.beat = 0;







	//PE_CSPM.clear();
	
	PE_STATE = PE_IDLE;
	CSPM_STATE = CSPM_IDLE;

	//ctrl_reg
	//PE_CSPM_EN=0;
	return;
}

void PE::PE_checkbeat(PECSPM &PE_CSPM) {
	if (PE_CSPM.enable_beat < 4) {
		PE_CONTROLL.beat = *PE_INTERFACE.PE_BEAT_IN[PE_CSPM.enable_beat];//0-3
	}
	else if (PE_CSPM.enable_beat < 6) {
		PE_CONTROLL.beat = *PE_INTERFACE.LSU_PE_BEAT_IN[PE_CSPM.enable_beat - 4];//4-5
	}
	//else if (PE_CSPM.enable_beat < 7) {//localreg
	//	PE_CONTROLL.beat = END;
	//}
	else if (PE_CSPM.enable_beat == 12) {
	}

	return;

}

void PE::PE_selectinput(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid) {
	os << " cycle:" << WIRE::cycle << " " << "PE[" << INDEX << "] operation: ";
	void* a = NULL;
	//void* b = NULL;
	if (PE_CSPM.datawidth_mode == 0) {
		// DATAWIDTH_0 INPUTX0, INPUTX1, INPUTY0, INPUTY1, INPUTZ0, INPUTZ1;
		// if (PE_CSPM.INX < 4) {
		// 	INPUTX0 = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INX];
		// 	INPUTX1 = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INX] >> 8;
		// }
		// else if (PE_CSPM.INX < 6) {
		// 	// INPUTX0 = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INX - 4];
		// 	// INPUTX1 = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INX - 4] >> 8;
		// }
		// /*else if (PE_CSPM.INX < 9) {
		// 	INPUTX0 = local_reg[PE_CSPM.INX - 6];
		// 	INPUTX1 = local_reg[PE_CSPM.INX - 6] >> 8;
		// }
		// else if (PE_CSPM.INX < 12) {
		// 	INPUTX0 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INX - 9];
		// 	INPUTX1 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INX - 9] >> 8;
		// }*/
		// else if (PE_CSPM.INX < 14) {
		// 	INPUTX0 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INX - 11];
		// 	INPUTX1 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INX - 6] >> 8;
		// }
		// else if (PE_CSPM.INX < 21) {
		// 	INPUTX0 = local_reg[PE_CSPM.INX - 9];
		// 	INPUTX1 = local_reg[PE_CSPM.INX - 9] >> 8;
		// }
		// else if (PE_CSPM.INX == 31) {
		// 	INPUTX0 = 0xffff;
		// 	INPUTX1 = 0xffff;
		// }
		// else {
		// 	bool CSPM_INPUTX_ERROR = 1;
		// 	assert(!CSPM_INPUTX_ERROR);//ָ////x////////Խ//磬
		// }
		// a = &INPUTX0;
		// b = &INPUTX1;
		// PE_CONTROLL.input_8t_x_0 = *(DATAWIDTH_1*)a;
		// PE_CONTROLL.input_8t_x_1 = *(DATAWIDTH_1*)b;

		// if (PE_CSPM.INY < 4) {
		// 	INPUTY0 = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INY];
		// 	INPUTY1 = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INY] >> 8;
		// }
		// else if (PE_CSPM.INY < 6) {
		// 	INPUTY0 = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INY - 4];
		// 	INPUTY1 = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INY - 4] >> 8;
		// }
		// else if (PE_CSPM.INY < 9) {
		// 	INPUTY0 = local_reg[PE_CSPM.INY - 6];
		// 	INPUTY1 = local_reg[PE_CSPM.INY - 6] >> 8;
		// }
		// else if (PE_CSPM.INY < 12) {
		// 	INPUTY0 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INY - 9];
		// 	INPUTY1 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INY - 9] >> 8;
		// }
		// else if (PE_CSPM.INY == 15) {
		// 	INPUTY0 = 0xffff;
		// 	INPUTY1 = 0xffff;
		// }
		// else {
		// 	bool CSPM_INPUTY_ERROR = 1;
		// 	assert(!CSPM_INPUTY_ERROR);//ָ////Y////////Խ//磬
		// }
		// a = &INPUTY0;
		// b = &INPUTY1;
		// PE_CONTROLL.input_8t_y_0 = *(DATAWIDTH_1*)a;
		// PE_CONTROLL.input_8t_y_1 = *(DATAWIDTH_1*)b;

		// if (PE_CSPM.INZ < 4) {
		// 	INPUTZ0 = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INZ];
		// 	INPUTZ1 = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INZ] >> 8;
		// }
		// else if (PE_CSPM.INZ < 6) {
		// 	INPUTZ0 = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INZ - 4];
		// 	INPUTZ1 = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INZ - 4] >> 8;
		// }
		// else if (PE_CSPM.INZ < 9) {
		// 	INPUTZ0 = local_reg[PE_CSPM.INZ - 6];
		// 	INPUTZ1 = local_reg[PE_CSPM.INZ - 6] >> 8;
		// }
		// else if (PE_CSPM.INZ < 12) {
		// 	INPUTZ0 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INZ - 9];
		// 	INPUTZ1 = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INZ - 9] >> 8;
		// }
		// else if (PE_CSPM.INZ == 15) {
		// 	INPUTZ0 = 0xffff;
		// 	INPUTZ1 = 0xffff;
		// }
		// else {
		// 	bool CSPM_INPUTZ_ERROR = 1;
		// 	assert(!CSPM_INPUTZ_ERROR);//ָ////Z////////Խ//磬
		// }
		// a = &INPUTZ0;
		// b = &INPUTZ1;
		// PE_CONTROLL.input_8t_z_0 = *(DATAWIDTH_1*)a;
		// PE_CONTROLL.input_8t_z_1 = *(DATAWIDTH_1*)b;
	}
	else {
		DATAWIDTH_0 INPUTX = 0;
		DATAWIDTH_0 INPUTY = 0;
		DATAWIDTH_0 INPUTZ = 0;

		if (PE_CSPM.INX < 4) {
			INPUTX = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INX];
			switch (PE_CSPM.INX) {
			case(0): 
			os << " INX("<<INPUTX<<")(pe_left)"	; 
			debug.perf[taskid].operation_read_peinterconnect++; 
			break;
			case(1): 
			os << " INX("<<INPUTX<<")(pe_up)"		; 
			debug.perf[taskid].operation_read_peinterconnect++; 
			break;
			case(2): 
			os << " INX("<<INPUTX<<")(pe_right)"	; 
			debug.perf[taskid].operation_read_peinterconnect++; 
			break;
			case(3): 
			os << " INX("<<INPUTX<<")(pe_down)"	; 
			debug.perf[taskid].operation_read_peinterconnect++; 
			break;
			default: 
			os << "UNRECOGNIZED INX(" << INPUTX << ")";  
			break;
			};
			enum { PE_WEST, PE_NORTH, PE_EAST, PE_SOUTH };
		}
		else if (PE_CSPM.INX < 11) {
			INPUTX = local_reg[PE_CSPM.INX - 8];
			//if(INDEX == 9) std::cout<<"cycle:"<<dec<<WIRE::cycle<<" select_input: INPUTX("<<INPUTX<<") = local_reg["<<PE_CSPM.INX - 8<<"]("<<local_reg[PE_CSPM.INX - 8]<<")"<<endl;
			switch (PE_CSPM.INX - 8) {
			case(0): 
			os << " INX(" << INPUTX << ")(LR[0])"; 
			debug.perf[taskid].operation_write_localreg++; 
			break;
			case(1): 
			os << " INX(" << INPUTX << ")(LR[1])"; 
			debug.perf[taskid].operation_write_localreg++; 
			break;
			case(2): 
			os << " INX(" << INPUTX << ")(LR[2])"; 
			debug.perf[taskid].operation_write_localreg++;
			 break;
			default: 
			os << "UNRECOGNIZED INX(" << INPUTX << ")";  
			break;

			};
		}
		else if (PE_CSPM.INX < 14) {
			INPUTX = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INX - 11];
			switch (PE_CSPM.INX - 11) {
			case(0): 
				os << " INX(" << INPUTX << ")(ImmR[0])"; 
				debug.perf[taskid].operation_read_immreg++;
				break;
			case(1): 
				os << " INX(" << INPUTX << ")(ImmR[1])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			case(2): 
				os << " INX(" << INPUTX << ")(ImmR[2])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			default: 
				os << "UNRECOGNIZED INX(" << INPUTX << ")"; 
				break;

			};
		}
		else if (PE_CSPM.INX < 22) 
		{
			INPUTX = GR::Global_REG[PE_CSPM.INX-14];
			//cout <<WIRE::cycle<< ": PE[" << INDEX << "].INX <-" << "GR[" << PE_CSPM.INX - 14 << "]" << endl;
			switch(PE_CSPM.INX)
			{
				case(14): os << " INX(" << INPUTX << ")(GR[0])"; 
					debug.perf[taskid].operation_read_globalreg++; 
					break;
				case(15): os << " INX(" << INPUTX << ")(GR[1])"; 
					debug.perf[taskid].operation_read_globalreg++; 
					break;
				case(16): os << " INX(" << INPUTX << ")(GR[2])"; 
					debug.perf[taskid].operation_read_globalreg++; 
					break;
				case(17): os << " INX(" << INPUTX << ")(GR[3])"; 
					debug.perf[taskid].operation_read_globalreg++; 
					break;
				case(18): os << " INX(" << INPUTX << ")(GR[4])"; 
					debug.perf[taskid].operation_read_globalreg++; 
					break;
				case(19): os << " INX(" << INPUTX << ")(GR[5])"; 
					debug.perf[taskid].operation_read_globalreg++; 
					break;
				case(20): os << " INX(" << INPUTX << ")(GR[6])";
					 debug.perf[taskid].operation_read_globalreg++; 
					 break;
				case(21): os << " INX(" << INPUTX << ")(GR[7])"; 
					debug.perf[taskid].operation_read_globalreg++; 
					break;
						default: os << "UNRECOGNIZED INX(" << INPUTX << ")"; 
						break;
			};
		}
		else {
		    // cout<<"PE_CSPM.INX decode Error:"<<PE_CSPM.INX <<endl;
			// bool CSPM_INPUTX_ERROR = 1;
			// assert(!CSPM_INPUTX_ERROR);
		}
		a = &INPUTX;
		PE_CONTROLL.input_fp16_x = *(DATAWIDTH_0*)a;
		//if(INDEX==9) std::cout<<"cycle:"<<dec<<WIRE::cycle<<" PE_CONTROLL.input_fp16_x = "<<PE_CONTROLL.input_fp16_x<<endl;
		////a = NULL;
		if (PE_CSPM.INY < 4) {
			INPUTY = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INY];
			switch (PE_CSPM.INY) {
			case(0): 
				os << " INY(" << INPUTY << ")(pe_left)"	; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			case(1): 
				os << " INY(" << INPUTY << ")(pe_up)"		; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			case(2): 
				os << " INY(" << INPUTY << ")(pe_right)"	; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			case(3): 
				os << " INY(" << INPUTY << ")(pe_down)"	; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			default:
			os << "UNRECOGNIZED INY" << INPUTY << ")";
				break;
			};
		}
		else if (PE_CSPM.INY < 6) {
			INPUTY = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INY - 4];
		}
		else if (PE_CSPM.INY < 11) {
			INPUTY = local_reg[PE_CSPM.INY - 8];
			switch (PE_CSPM.INY - 8) {
			case(0): 
				os << " INY(" << INPUTY << ")(LR[0])"; 
				debug.perf[taskid].operation_write_localreg++; 
				break;
			case(1): 
				os << " INY(" << INPUTY << ")(LR[1])"; 
				debug.perf[taskid].operation_write_localreg++; 
				break;
			case(2): 
				os << " INY(" << INPUTY << ")(LR[2])"; 
				debug.perf[taskid].operation_write_localreg++; 
				break;
			default:
				os << "UNRECOGNIZED INY" << INPUTY << ")"; 
				break;

			};
		}
		else if (PE_CSPM.INY < 14) {
			INPUTY = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INY - 11];
			switch (PE_CSPM.INY - 11) {
			case(0): os << " INY(" << INPUTY << ")(ImmR[0])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			case(1): os << " INY(" << INPUTY << ")(ImmR[1])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			case(2): os << " INY(" << INPUTY << ")(ImmR[2])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			default:
				os << "UNRECOGNIZED INY" << INPUTY << ")";
				break;

			};
		}
		else if (PE_CSPM.INY < 22) 
		{
			INPUTY = GR::Global_REG[PE_CSPM.INY-14];
			//cout << WIRE::cycle << ": PE[" << INDEX << "].INY <-" << "GR[" << PE_CSPM.INY - 14 << "]" << endl;
			switch(PE_CSPM.INY)
			{
			case(14): os << " INY(" << INPUTY << ")(GR[0])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			case(15): os << " INY(" << INPUTY << ")(GR[1])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			case(16): os << " INY(" << INPUTY << ")(GR[2])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			case(17): os << " INY(" << INPUTY << ")(GR[3])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			case(18): os << " INY(" << INPUTY << ")(GR[4])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			case(19): os << " INY(" << INPUTY << ")(GR[5])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			case(20): os << " INY(" << INPUTY << ")(GR[6])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			case(21): os << " INY(" << INPUTY << ")(GR[7])"; 
				debug.perf[taskid].operation_read_globalreg++; 
				break;
			default:
			  os << "UNRECOGNIZED INY" << INPUTY << ")"; 
			  break;
			};
		}
		else {
			// cout<<"PE_CSPM.INY decode Error:"<<PE_CSPM.INY <<endl;
			// bool CSPM_INPUTY_ERROR = 1;
			// assert(!CSPM_INPUTY_ERROR);
		}

		a = &INPUTY;
		PE_CONTROLL.input_fp16_y = *(DATAWIDTH_0*)a;
		//a = NULL;

		if (PE_CSPM.INZ < 4) {
			INPUTZ = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.INZ];
			switch (PE_CSPM.INZ) {
			case(0): os << " INZ(" << INPUTZ << ")(pe_left)"		; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			case(1): os << " INZ(" << INPUTZ << ")(pe_up)"		; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			case(2): os << " INZ(" << INPUTZ << ")(pe_right)"		; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			case(3): os << " INZ(" << INPUTZ << ")(pe_down)"		; 
				debug.perf[taskid].operation_read_peinterconnect++; 
				break;
			default:
				os << "UNRECOGNIZED INZ" << INPUTZ << ")"	; 
				break;
			};
		}
		else if (PE_CSPM.INZ < 6) {
			INPUTZ = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.INZ - 4];
		}
		else if (PE_CSPM.INZ < 11) {
			INPUTZ = local_reg[PE_CSPM.INZ - 8];
			switch (PE_CSPM.INZ - 8) {
			case(0): os << " INZ(" << INPUTZ << ")(LR[0])"; 
				debug.perf[taskid].operation_write_localreg++; 
				break;
			case(1): os << " INZ(" << INPUTZ << ")(LR[1])"; 
				debug.perf[taskid].operation_write_localreg++; 
				break;
			case(2): os << " INZ(" << INPUTZ << ")(LR[2])"; 
				debug.perf[taskid].operation_write_localreg++; 
				break;
			default:
				os << "UNRECOGNIZED INZ" << INPUTZ << ")"; 
				break;
			};
		}
		else if (PE_CSPM.INZ < 14) {
			INPUTZ = CU::PARA_BUFFER[PE_INTERFACE.INDEX][PE_CSPM.INZ - 11];
			switch (PE_CSPM.INZ - 11) {
			case(0): os << " INZ(" << INPUTZ << ")(ImmR[0])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			case(1): os << " INZ(" << INPUTZ << ")(ImmR[1])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			case(2): os << " INZ(" << INPUTZ << ")(ImmR[2])"; 
				debug.perf[taskid].operation_read_immreg++; 
				break;
			default:
				os << "UNRECOGNIZED INZ" << INPUTZ << ")"; 
				break;
			};
		}
		else if (PE_CSPM.INZ < 22) 
		{
			INPUTZ = GR::Global_REG[PE_CSPM.INZ-14];
			//cout << WIRE::cycle << ": PE[" << INDEX << "].INZ <-" << "GR["<< PE_CSPM.INZ - 14 <<"]"<<endl;
			switch(PE_CSPM.INZ)
			{
			case(14): os << " INZ(" << INPUTZ << ")(GR[0])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
			case(15): os << " INZ(" << INPUTZ << ")(GR[1])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
			case(16): os << " INZ(" << INPUTZ << ")(GR[2])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
			case(17): os << " INZ(" << INPUTZ << ")(GR[3])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
			case(18): os << " INZ(" << INPUTZ << ")(GR[4])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
			case(19): os << " INZ(" << INPUTZ << ")(GR[5])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
			case(20): os << " INZ(" << INPUTZ << ")(GR[6])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
			case(21): os << " INZ(" << INPUTZ << ")(GR[7])"; 
			debug.perf[taskid].operation_read_globalreg++; break;
				os << "UNRECOGNIZED INZ" << INPUTZ << ")"; 
				break;
			};
		}
		else {
			// cout<<"PE_CSPM.INZ decode Error:"<<PE_CSPM.INZ <<endl;
			// bool CSPM_INPUTZ_ERROR = 1;
			// assert(!CSPM_INPUTZ_ERROR);//ָ////Z////////Խ//磬
		}

		a = &INPUTZ;
		PE_CONTROLL.input_fp16_z = *(DATAWIDTH_0*)a;
		//a = NULL;
	}
	return;
}


void PE::PE_calculate(PECSPM &PE_CSPM, ostringstream &os, DebugParam_t &debug,int &taskid) {
	
	switch (PE_CSPM.PE_opcode)
	{
	case 0:
		//PE_cal_LOOP(PE_CSPM);
		//os << " OP(LOOP)";
		break;
	case 1:
		PE_cal_ROUTE(PE_CSPM,os);
		break;
	case 2:
		PE_cal_IF(PE_CSPM, os, debug, taskid);
		break;
	case 3:
		PE_cal_ARITH(PE_CSPM, os, debug, taskid);
		break;
	case 4:
		PE_cal_LOGIC(PE_CSPM, os, debug, taskid);
		break;
	case 5:
		PE_cal_SHIFTER(PE_CSPM, os, debug, taskid);
		break;
	case 6:
		//PE_cal_NONLINEAR(PE_CSPM);
		//os << " OP(NONLINEAR)";
		break;
	case 7:
		// UNUSED
		// PE_cal_CLIPBITS(PE_CSPM);
		// os << " OP(CLIPBITS)";
		 break;
	case 8:
		PE_cal_LSU_Opcode(PE_CSPM, os, debug, taskid);
		break;
	default:
		break;
	}
	os << " ";
	return;
}

// void PE::PE_cal_LOOP(PECSPM &PE_CSPM) {

// }

void PE::PE_cal_ROUTE(PECSPM &PE_CSPM, ostringstream &os) {
	void* a = NULL;
	void* b = NULL;
	os << " OP(ROUTE)";
	if (PE_CSPM.datawidth_mode == 0) {
		a = &PE_CONTROLL.input_8t_x_1;
		PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
		b = &PE_CONTROLL.input_8t_x_0;
		PE_CONTROLL.output_0 += *(uint8_t*)b;
	}
	else {
		a = &PE_CONTROLL.input_fp16_x;
		PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
	}
	PE_CONTROLL.delay = 1 + PE_CSPM.PE_ROUTE.route_delay;
	return;
}

void PE::PE_cal_IF(PECSPM &PE_CSPM,ostringstream &os, DebugParam_t &debug,int &taskid) {
	bool cpr_result_0 = 0;
	//bool cpr_result_1 = 0;
	//DATAWIDTH_1 true_result_8t_0;
	//DATAWIDTH_1 false_result_8t_0;
	//DATAWIDTH_1 true_result_8t_1;
	//DATAWIDTH_1 false_result_8t_1;
	// DATAWIDTH_0 true_result_fp16;
	// DATAWIDTH_0 false_result_fp16;
	if (PE_CSPM.datawidth_mode == 0) {
		// switch (PE_CSPM.PE_IF.mode) {
		// case 0://s a< b
		// 	cpr_result_0 = PE_CONTROLL.input_8t_x_0 < PE_CONTROLL.input_8t_y_0;
		// 	cpr_result_1 = PE_CONTROLL.input_8t_x_1 < PE_CONTROLL.input_8t_y_1;
		// 	break;
		// case 1://s a<=b
		// 	cpr_result_0 = PE_CONTROLL.input_8t_x_0 <= PE_CONTROLL.input_8t_y_0;
		// 	cpr_result_1 = PE_CONTROLL.input_8t_x_1 <= PE_CONTROLL.input_8t_y_1;
		// 	break;
		// case 2://s a==b
		// 	cpr_result_0 = PE_CONTROLL.input_8t_x_0 == PE_CONTROLL.input_8t_y_0;
		// 	cpr_result_1 = PE_CONTROLL.input_8t_x_1 == PE_CONTROLL.input_8t_y_1;
		// 	break;
		// case 3://s a==1
		// 	cpr_result_0 = PE_CONTROLL.input_8t_x_0 == 1;
		// 	cpr_result_1 = PE_CONTROLL.input_8t_x_1 == 1;
		// 	break;
		// default:
		// 	bool CSPM_IF_opcode_ERROR = 1;
		// 	assert(!CSPM_IF_opcode_ERROR);
		// 	break;
		// }
		// switch (PE_CSPM.PE_IF.result) {
		// case 0://1,0
		// 	true_result_8t_0 = 1;
		// 	false_result_8t_0 = 0;
		// 	true_result_8t_1 = 1;
		// 	false_result_8t_1 = 0;
		// 	break;
		// case 1://a,b
		// 	true_result_8t_0 = PE_CONTROLL.input_8t_x_0;
		// 	false_result_8t_0 = PE_CONTROLL.input_8t_y_0;
		// 	true_result_8t_1 = PE_CONTROLL.input_8t_x_1;
		// 	false_result_8t_1 = PE_CONTROLL.input_8t_y_1;
		// 	break;
		// case 2://b,	
		// 	true_result_8t_0 = PE_CONTROLL.input_8t_y_0;
		// 	false_result_8t_0 = PE_CONTROLL.input_8t_z_0;
		// 	true_result_8t_1 = PE_CONTROLL.input_8t_y_1;
		// 	false_result_8t_1 = PE_CONTROLL.input_8t_z_1;
		// 	break;
		// case 3://c,c
		// 	true_result_8t_0 = PE_CONTROLL.input_8t_z_0;
		// 	false_result_8t_0 = PE_CONTROLL.input_8t_z_0;
		// 	true_result_8t_1 = PE_CONTROLL.input_8t_z_1;
		// 	false_result_8t_1 = PE_CONTROLL.input_8t_z_1;
		// 	break;
		// default:
		// 	bool CSPM_IF_result_ERROR = 1;
		// 	assert(!CSPM_IF_result_ERROR);
		// 	break;
		// }
		// DATAWIDTH_1 x = cpr_result_0 ? true_result_8t_0 : false_result_8t_0;
		// DATAWIDTH_1 y = cpr_result_0 ? false_result_8t_0 : true_result_8t_0;
		// DATAWIDTH_1 z = cpr_result_1 ? true_result_8t_1 : false_result_8t_1;
		// DATAWIDTH_1 w = cpr_result_1 ? false_result_8t_1 : true_result_8t_1;
		// void* a = &z;
		// PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
		// void* b = &x;
		// PE_CONTROLL.output_0 += *(uint8_t*)b;
		// void* c = &w;
		// PE_CONTROLL.output_1 = *(uint8_t*)c << 8;
		// void* d = &y;
		// PE_CONTROLL.output_1 += *(uint8_t*)d;
	}
	else {
		switch (PE_CSPM.PE_IF.mode)
		{
		case 0://s a< b
			cpr_result_0 = PE_CONTROLL.input_fp16_x < PE_CONTROLL.input_fp16_y;
			os << " OP(IF(lessthan))";
			debug.perf[taskid].operation_lessthan++;
			//void* a = &(cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_y);
			//PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
			//PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_y);
			break;
		case 1://s a<=b
			os << " OP(IF(lessthanequal))";
			cpr_result_0 = PE_CONTROLL.input_fp16_x <= PE_CONTROLL.input_fp16_y;
			debug.perf[taskid].operation_lessthanequal++;
			//void* a = &(cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_y);
			//PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_y);
			break;
		case 2://s a==b
			os << " OP(IF(INX==INY)))";
			cpr_result_0 = PE_CONTROLL.input_fp16_x == PE_CONTROLL.input_fp16_y;
			debug.perf[taskid].operation_equal++;
			/*void* a = &(cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_y);*/
			//PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_y);
			break;
		case 3://s a==1
			os << " OP(IF(INX==1))";
			cpr_result_0 = PE_CONTROLL.input_fp16_x == 1;
			debug.perf[taskid].operation_equalone++;
			//void* a = &(cpr_result_0 ? PE_CONTROLL.input_fp16_y : PE_CONTROLL.input_fp16_z);
			//PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_y : PE_CONTROLL.input_fp16_z);
			break;
		default:
			break;
		}

		if (!PE_CSPM.PE_IF.if_pattern) {
			switch (PE_CSPM.PE_IF.result)
			{       //result (False) (True)
					// result 1 0
			case 0: {PE_CONTROLL.output_0 = (cpr_result_0 ? 1 : 0); break; }
					// result INX INY
			case 1: {PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_y); break; }
					// result INY INZ
			case 2: {PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_y : PE_CONTROLL.input_fp16_z); break; }
					// result INX INZ
			case 3: {PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_z); break; }
			default: { 
				break; }
			}
		}
		else {
			switch (PE_CSPM.PE_IF.result)
			{   //result (False) (True)
				// result 1 0
			case 0: {PE_CONTROLL.output_0 = (cpr_result_0 ? 0 : 1); break; }
					// result INX INY
			case 1: {PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_y : PE_CONTROLL.input_fp16_x); break; }
					// result INY INZ
			case 2: {PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_z : PE_CONTROLL.input_fp16_y); break; }
					// result INX INZ
			case 3: {PE_CONTROLL.output_0 = (cpr_result_0 ? PE_CONTROLL.input_fp16_z : PE_CONTROLL.input_fp16_x); break; }
			default: { 
				break; }
			}
		}

	}
	PE_CONTROLL.delay = 1;
	return;
}

void PE::PE_cal_ARITH(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid) {
	switch (PE_CSPM.PE_ARITH.mode) {
	case 0://sadd
		os << " OP(SADD)";
		debug.perf[taskid].operation_arith_sadd++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = 0, out1 = 0;
			int16_t output0 = (int16_t)PE_CONTROLL.input_8t_x_0 + (int16_t)PE_CONTROLL.input_8t_y_0;
			if (output0 >= 0x7f) {
				out0 = 0x7f;
			}
			else if (output0 < -128) {
				out0 = 0x80;
			}
			else
				out0 = output0;
			int16_t output1 = (int16_t)PE_CONTROLL.input_8t_x_1 + (int16_t)PE_CONTROLL.input_8t_y_1;
			if (output1 >= 0x7f) {
				out1 = 0x7f;
			}
			else if (output1 < -128) {
				out1 = 0x80;
			}
			else
				out1 = output1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = PE_CONTROLL.input_fp16_x + PE_CONTROLL.input_fp16_y;
			void* a = &output0;
			//PE_CONTROLL.output_0 = *(uint16_t*)a;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	case 1://ssub
		os << " OP(SSUB)";
		debug.perf[taskid].operation_arith_ssub++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = 0, out1 = 0;
			int16_t output0 = (int16_t)PE_CONTROLL.input_8t_x_0 - (int16_t)PE_CONTROLL.input_8t_y_0;
			if (output0 >= 0x7f) {
				out0 = 0x7f;
			}
			else if (output0 < -128) {
				out0 = 0x80;
			}
			else
				out0 = output0;
			int16_t output1 = (int16_t)PE_CONTROLL.input_8t_x_1 - (int16_t)PE_CONTROLL.input_8t_y_1;
			if (output1 >= 0x7f) {
				out1 = 0x7f;
			}
			else if (output1 < -128) {
				out1 = 0x80;
			}
			else
				out1 = output1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = PE_CONTROLL.input_fp16_x - PE_CONTROLL.input_fp16_y;
			void* a = &output0;
			//PE_CONTROLL.output_0 = *(uint16_t*)a;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	case 2://sabs
		os << " OP(SABS)";
		debug.perf[taskid].operation_arith_sabs++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = STD_ABS(PE_CONTROLL.input_8t_x_0);
			int8_t out1 = STD_ABS(PE_CONTROLL.input_8t_x_1);
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = STD_ABS(PE_CONTROLL.input_fp16_x);
			void* a = &output0;
			//PE_CONTROLL.output_0 = *(uint16_t*)a;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	case 3://sneg
		os << " OP(SNEG)";
		debug.perf[taskid].operation_arith_neg++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = -PE_CONTROLL.input_8t_x_0;
			int8_t out1 = -PE_CONTROLL.input_8t_x_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = -PE_CONTROLL.input_fp16_x;
			void* a = &output0;
			//PE_CONTROLL.output_0 = *(uint16_t*)a;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	case 4://sMUL
		os << " OP(SMUL)";
		debug.perf[taskid].operation_arith_smul++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = 0, out1 = 0;
			int16_t output0 = (int16_t)PE_CONTROLL.input_8t_x_0 * (int16_t)PE_CONTROLL.input_8t_y_0;
			if (output0 >= 0x7f) {
				out0 = 0x7f;
			}
			else if (output0 < -128) {
				out0 = 0x80;
			}
			else
				out0 = output0;
			int16_t output1 = (int16_t)PE_CONTROLL.input_8t_x_1 * (int16_t)PE_CONTROLL.input_8t_y_1;
			if (output1 >= 0x7f) {
				out1 = 0x7f;
			}
			else if (output1 < -128) {
				out1 = 0x80;
			}
			else
				out1 = output1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = PE_CONTROLL.input_fp16_x * PE_CONTROLL.input_fp16_y;
			void* a = &output0;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	case 5://sMAC
		os << " OP(SMAC)";
		debug.perf[taskid].operation_arith_smac++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = 0, out1 = 0;
			int16_t output0 = (int16_t)PE_CONTROLL.input_8t_x_0 * (int16_t)PE_CONTROLL.input_8t_y_0 + (int16_t)PE_CONTROLL.input_8t_z_0;
			if (output0 >= 0x7f) {
				out0 = 0x7f;
			}
			else if (output0 < -128) {
				out0 = 0x80;
			}
			else
				out0 = output0;
			int16_t output1 = (int16_t)PE_CONTROLL.input_8t_x_1 * (int16_t)PE_CONTROLL.input_8t_y_1 + (int16_t)PE_CONTROLL.input_8t_z_1;
			if (output1 >= 0x7f) {
				out1 = 0x7f;
			}
			else if (output1 < -128) {
				out1 = 0x80;
			}
			else
				out1 = output1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = PE_CONTROLL.input_fp16_x * PE_CONTROLL.input_fp16_y + PE_CONTROLL.input_fp16_z;
			void* a = &output0;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	case 6://SMOD
		os << " OP(SMOD)";
		debug.perf[taskid].operation_arith_smod++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = 0, out1 = 0;
			int16_t output0 = (int16_t)PE_CONTROLL.input_8t_x_0 / (int16_t)PE_CONTROLL.input_8t_y_0;
			if (output0 >= 0x7f) {
				out0 = 0x7f;
			}
			else if (output0 < -128) {
				out0 = 0x80;
			}
			else
				out0 = output0;
			int16_t output1 = (int16_t)PE_CONTROLL.input_8t_x_1 / (int16_t)PE_CONTROLL.input_8t_y_1;
			if (output1 >= 0x7f) {
				out1 = 0x7f;
			}
			else if (output1 < -128) {
				out1 = 0x80;
			}
			else
				out1 = output1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = PE_CONTROLL.input_fp16_x % PE_CONTROLL.input_fp16_y;
			void* a = &output0;
			//PE_CONTROLL.output_0 = *(uint16_t*)a;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	default:
		break;
	}
	return;
}

void PE::PE_cal_LOGIC(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid) {
	switch (PE_CSPM.PE_LOGIC.mode) {
	case 0://AND
		os << " OP(AND)";
		debug.perf[taskid].operation_logic_and++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = PE_CONTROLL.input_8t_x_0 & PE_CONTROLL.input_8t_y_0;
			int8_t out1 = PE_CONTROLL.input_8t_x_1 & PE_CONTROLL.input_8t_y_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			void* a = &PE_CONTROLL.input_fp16_x;
			void* b = &PE_CONTROLL.input_fp16_y;
			//PE_CONTROLL.output_0 = *(uint16_t*)a & *(uint16_t*)b;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a & *(DATAWIDTH_0*)b;
		}
		break;
	case 1://OR
		os << " OP(OR)";
		debug.perf[taskid].operation_logic_or++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = PE_CONTROLL.input_8t_x_0 | PE_CONTROLL.input_8t_y_0;
			int8_t out1 = PE_CONTROLL.input_8t_x_1 | PE_CONTROLL.input_8t_y_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			void* a = &PE_CONTROLL.input_fp16_x;
			void* b = &PE_CONTROLL.input_fp16_y;
			//PE_CONTROLL.output_0 = *(uint16_t*)a | *(uint16_t*)b;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a | *(DATAWIDTH_0*)b;
		}
		break;
	case 2://NOT
		os << " OP(NOT)";
		debug.perf[taskid].operation_logic_not++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = ~PE_CONTROLL.input_8t_x_0;
			int8_t out1 = ~PE_CONTROLL.input_8t_x_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			void* a = &PE_CONTROLL.input_fp16_x;
			//PE_CONTROLL.output_0 =~ *(uint16_t*)a;
			
			if(*(DATAWIDTH_0*)a == 1){
				PE_CONTROLL.output_0 = 0;
				break;
			}else if(*(DATAWIDTH_0*)a == 0){
				PE_CONTROLL.output_0 = 1;
				break;
			}else{
				PE_CONTROLL.output_0 = ~*(DATAWIDTH_0*)a;
				break;
			}
			
		}
		break;
	case 3://XOR
		os << " OP(XOR)";
		debug.perf[taskid].operation_logic_xor++;
		if (PE_CSPM.datawidth_mode == 0) {
			int8_t out0 = PE_CONTROLL.input_8t_x_0 ^ PE_CONTROLL.input_8t_y_0;
			int8_t out1 = PE_CONTROLL.input_8t_x_1 ^ PE_CONTROLL.input_8t_y_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			void* a = &PE_CONTROLL.input_fp16_x;
			void* b = &PE_CONTROLL.input_fp16_y;
			//PE_CONTROLL.output_0 = *(uint16_t*)a ^ *(uint16_t*)b;
			PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a ^ *(DATAWIDTH_0*)b;
		}
		break;
	default:
		break;
	}
	PE_CONTROLL.delay = 1;
	return;
}

void PE::PE_cal_SHIFTER(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid) {
	switch (PE_CSPM.PE_SHIFTER.mode) {
	case 0://uSRL unsigned shift right logic
		os << " OP(SRL)";
		debug.perf[taskid].operation_shifter_srl++;
		if (PE_CSPM.datawidth_mode == 0) {
			uint8_t out0 = (uint8_t)PE_CONTROLL.input_8t_x_0 >> (uint8_t)PE_CONTROLL.input_8t_y_0;
			uint8_t out1 = (uint8_t)PE_CONTROLL.input_8t_x_1 >> (uint8_t)PE_CONTROLL.input_8t_y_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {


			//uint8_t temp0 = (uint16_t)PE_CONTROLL.input_fp16_x >> (uint16_t)PE_CONTROLL.input_fp16_y;
			//short temp1 = (uint16_t)PE_CONTROLL.input_fp16_x >> (uint16_t)PE_CONTROLL.input_fp16_y;
			//int temp2 = (uint16_t)PE_CONTROLL.input_fp16_x >> (uint16_t)PE_CONTROLL.input_fp16_y;
		 //   uint16_t temp3 = (uint16_t)PE_CONTROLL.input_fp16_x >> (uint16_t)PE_CONTROLL.input_fp16_y;
			//int16_t temp4 = (uint16_t)PE_CONTROLL.input_fp16_x >> (uint16_t)PE_CONTROLL.input_fp16_y;
			//DATAWIDTH_0 temp5 = (uint16_t)PE_CONTROLL.input_fp16_x >> (uint16_t)PE_CONTROLL.input_fp16_y; 
			DATAWIDTH_0 temp5 = (DATAWIDTH_0)PE_CONTROLL.input_fp16_x >> (DATAWIDTH_0)PE_CONTROLL.input_fp16_y;
			PE_CONTROLL.output_0 = temp5;
		}
		break;
	case 1://ASR arithmetic shift right
		os << " OP(SRA)";
		debug.perf[taskid].operation_shifter_sra++;
		if (PE_CSPM.datawidth_mode == 0) {
			uint8_t out0 = PE_CONTROLL.input_8t_x_0 >> PE_CONTROLL.input_8t_y_0;
			uint8_t out1 = PE_CONTROLL.input_8t_x_1 >> PE_CONTROLL.input_8t_y_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			//PE_CONTROLL.output_0 = (uint16_t)PE_CONTROLL.input_fp16_x >> (uint16_t)PE_CONTROLL.input_fp16_y;
			PE_CONTROLL.output_0 = PE_CONTROLL.input_fp16_x >> PE_CONTROLL.input_fp16_y;
		}
		break;
	case 2://uSLL unsigned shift left logic
		os << " OP(SLL)";
		debug.perf[taskid].operation_shifter_sll++;
		if (PE_CSPM.datawidth_mode == 0) {
			uint8_t out0 = PE_CONTROLL.input_8t_x_0 << PE_CONTROLL.input_8t_y_0;
			uint8_t out1 = PE_CONTROLL.input_8t_x_1 << PE_CONTROLL.input_8t_y_1;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			//PE_CONTROLL.output_0 = (uint16_t)PE_CONTROLL.input_fp16_x << (uint16_t)PE_CONTROLL.input_fp16_y;
			PE_CONTROLL.output_0 = (DATAWIDTH_0)PE_CONTROLL.input_fp16_x << (DATAWIDTH_0)PE_CONTROLL.input_fp16_y;
		}
		break;
	default:
		break;
	}
	PE_CONTROLL.delay = 1;
	return;
}
/*
void PE::PE_cal_CLIPBITS(PECSPM &PE_CSPM) {
	bool cpr_result_0;
	bool cpr_result_1;
	bool cpr_result_2;
	bool cpr_result_3;
	if (PE_CSPM.datawidth_mode == 0) {
		cpr_result_0 = PE_CONTROLL.input_8t_x_0 < PE_CONTROLL.input_8t_y_0; // x<MIN
		cpr_result_1 = PE_CONTROLL.input_8t_x_1 < PE_CONTROLL.input_8t_y_1;
		cpr_result_2 = PE_CONTROLL.input_8t_x_0 < PE_CONTROLL.input_8t_z_0;
		cpr_result_3 = PE_CONTROLL.input_8t_x_1 < PE_CONTROLL.input_8t_z_1;
		DATAWIDTH_1 x;
		DATAWIDTH_1 y;
		if (cpr_result_0) {
			x = PE_CONTROLL.input_8t_y_0;
		}
		else if (cpr_result_2) {
			x = PE_CONTROLL.input_8t_x_0;
		}
		else {
			x = PE_CONTROLL.input_8t_z_0;
		}
		if (cpr_result_1) {
			y = PE_CONTROLL.input_8t_y_1;
		}
		else if (cpr_result_3) {
			y = PE_CONTROLL.input_8t_x_1;
		}
		else {
			y = PE_CONTROLL.input_8t_z_1;
		}
		void* a = &x;
		PE_CONTROLL.output_0 = *(uint8_t*)a << 8;//Higher 8 bits
		void* b = &y;
		PE_CONTROLL.output_0 += *(uint8_t*)b; //Lower 8 bits		'
	}
	else
	{
		DATAWIDTH_0 output0 = 0;
		cpr_result_0 = PE_CONTROLL.input_fp16_x < PE_CONTROLL.input_fp16_y;
		cpr_result_1 = PE_CONTROLL.input_fp16_x > (PE_CONTROLL.input_fp16_z - 1);
		if (cpr_result_0)
		{
			output0 = PE_CONTROLL.input_fp16_y;
		}
		else if (cpr_result_1)
		{
			output0 = (PE_CONTROLL.input_fp16_z - 1);
		}
		else {
			output0 = PE_CONTROLL.input_fp16_x;
		}

		void* a = &output0;
		//PE_CONTROLL.output_0 = *(uint16_t*)a;
		PE_CONTROLL.output_0 = *(DATAWIDTH_0*)a;
		//std::cout << PE_CONTROLL.output_0 << std::endl;

		//DATAWIDTH_0 output0 = PE_CONTROLL.input_fp16_x * PE_CONTROLL.input_fp16_y;
		//void* ab = &output0;
		////PE_CONTROLL.output_0 = *(uint16_t*)a;
		//PE_CONTROLL.output_0 = *(DATAWIDTH_0*)ab;
		//std::cout << PE_CONTROLL.output_0 << std::endl;

	}
	PE_CONTROLL.delay = 1;
	return;
}

void PE::PE_cal_NONLINEAR(PECSPM &PE_CSPM) {
	switch (PE_CSPM.PE_NONLINEAR.mode) {
	case 0://relu
		if (PE_CSPM.datawidth_mode == 0) {
			DATAWIDTH_1 out0 = (PE_CONTROLL.input_8t_x_0 > 0) ? PE_CONTROLL.input_8t_x_0 : 0;
			DATAWIDTH_1 out1 = (PE_CONTROLL.input_8t_x_1 > 0) ? PE_CONTROLL.input_8t_x_1 : 0;
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
		}
		else {
			DATAWIDTH_0 output0 = (PE_CONTROLL.input_fp16_x > 0) ? PE_CONTROLL.input_fp16_x : (DATAWIDTH_0)0;
			void* a = &output0;
			PE_CONTROLL.output_0 = *(uint16_t*)a;
		}
		PE_CONTROLL.delay = 1;
		break;
	case 1://sigmoid
if (PE_CSPM.datawidth_mode == 0) {
	int i = 0;
	int j = 0;
	while (PE_CONTROLL.input_8t_x_0 > NLParam_BF::NL_TH_INT8[i]) {
		i++;
	}
	while (PE_CONTROLL.input_8t_x_1 > NLParam_BF::NL_TH_INT8[j]) {
		j++;
	}
	DATAWIDTH_1 out0 = 0, out1 = 0;
	int16_t output0 = (int16_t)PE_CONTROLL.input_8t_x_0 * (int16_t)NLParam_BF::NL_A_INT8[i] + (int16_t)NLParam_BF::NL_B_INT8[i];
	if (output0 >= 0x7f) {
		out0 = 0x7f;
	}
	else if (output0 < -128) {
		out0 = 0x80;
	}
	else
		out0 = output0;
	int16_t output1 = (int16_t)PE_CONTROLL.input_8t_x_1 * (int16_t)NLParam_BF::NL_A_INT8[j] + (int16_t)NLParam_BF::NL_B_INT8[j];
	if (output1 >= 0x7f) {
		out1 = 0x7f;
	}
	else if (output1 < -128) {
		out1 = 0x80;
	}
	else
		out1 = output1;
	void* a = &out1;
	PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
	void* b = &out0;
	PE_CONTROLL.output_0 += *(uint8_t*)b;
	PE_CONTROLL.delay = 2 + (i > j) ? i : j;
}
else {
	int i = 0;
	while (PE_CONTROLL.input_fp16_x > NLParam_BF::NL_TH_FP16[i]) {
		i++;
	}
	DATAWIDTH_0 output0 = PE_CONTROLL.input_fp16_x * NLParam_BF::NL_A_FP16[i] + NLParam_BF::NL_B_FP16[i];
	void* a = &output0;
	PE_CONTROLL.output_0 = *(uint16_t*)a;
	PE_CONTROLL.delay = 1 + i;
}
break;
	case 2://leakyrelu
		if (PE_CSPM.datawidth_mode == 0) {
			DATAWIDTH_1 out0 = (PE_CONTROLL.input_8t_x_0 > 0) ? PE_CONTROLL.input_8t_x_0 : PE_CONTROLL.input_8t_x_0 * local_reg[1];
			DATAWIDTH_1 out1 = (PE_CONTROLL.input_8t_x_1 > 0) ? PE_CONTROLL.input_8t_x_1 : PE_CONTROLL.input_8t_x_1 * local_reg[1];
			void* a = &out1;
			PE_CONTROLL.output_0 = *(uint8_t*)a << 8;
			void* b = &out0;
			PE_CONTROLL.output_0 += *(uint8_t*)b;
			PE_CONTROLL.delay = 3;
		}
		else {
			DATAWIDTH_0 output0 = (PE_CONTROLL.input_fp16_x > 0) ? PE_CONTROLL.input_fp16_x : PE_CONTROLL.input_fp16_x*(DATAWIDTH_0)local_reg[1];
			void* a = &output0;
			PE_CONTROLL.output_0 = *(uint16_t*)a;
			PE_CONTROLL.delay = 3;
		}
		break;
	default:
		bool CSPM_MAC_opcode_ERROR = 1;
		assert(!CSPM_MAC_opcode_ERROR);//MAC//
		break;
	}
	return;
}
*/
void PE::PE_cal_LSU_Opcode(PECSPM &PE_CSPM, ostringstream &os, DebugParam_t &debug,int &taskid)
{
	switch (PE_CSPM.PE_LSU.mode)
	{
	case(0)://load , inputx = address
		os << " OP(Load)";
		debug.perf[taskid].lsu_load_count++;
		if (PE_CSPM.datawidth_mode == 0)
		{
		}
		else
		{

			
			PE_CONTROLL.output_0 = (DATAWIDTH_0)*(unsigned short*)(debug.addr_map(PE_CONTROLL.input_fp16_x, sizeof(unsigned short)));;
			os <<": Load : addr(" << (DATAWIDTH_0)PE_CONTROLL.input_fp16_x << ")= " << PE_CONTROLL.output_0;
			if(WIRE::cycle<50){
				//cout<<dec<<WIRE::cycle<<": PE["<<INDEX<<"]: Load : addr(" << (DATAWIDTH_0)PE_CONTROLL.input_fp16_x << ")= " << PE_CONTROLL.output_0<<endl;
			}	

		}
		break;
	case(1)://store, inputx = address, inputy = data
		os << " OP(Store)";
		debug.perf[taskid].lsu_store_count++;
		if (PE_CSPM.datawidth_mode == 0)
		{
		}
		else
		{
			*(unsigned short*)(debug.addr_map((DATAWIDTH_0)PE_CONTROLL.input_fp16_y, sizeof(unsigned short))) = (unsigned short)PE_CONTROLL.input_fp16_x;
			if( (WIRE::cycle <50) )  {
					//cout<<dec<<WIRE::cycle<<": PE["<<INDEX<<"]: Store : addr(" << (DATAWIDTH_0)PE_CONTROLL.input_fp16_y << "), data(" << (DATAWIDTH_0)PE_CONTROLL.input_fp16_x << ")"<<endl;
			}
			os << "Store : addr(" << (DATAWIDTH_0)PE_CONTROLL.input_fp16_y << "), data(" << (DATAWIDTH_0)PE_CONTROLL.input_fp16_x << ")";
			//cout << os.str() << endl;
		}	
		break;
	default:
		break;
	}
	PE_CONTROLL.delay = 1;
	return;
}

void PE::PE_EXEC(DebugParam_t &debug, bool &debugflag, int &taskid, std::ostringstream &os) {
	
	switch (CSPM_STATE)
	{
	case CSPM_IDLE:
		//reached in cycle 0
		if (*PE_INTERFACE.PE_START_IN == true) {
			CSPM_STATE = CSPM_LD;
			PE_CONTROLL.CSPM_addr = 0;
		}
		break;
	case CSPM_LD://reached in cycle1
		if (PE_CONTROLL.CSPM_addr == 0) {
			PE_CSPM_TOP = (CU::CSPM_PE[PE_INTERFACE.INDEX][PE_CONTROLL.CSPM_addr]).CSPM_TOP;
			//PE_CONTROLL.top_renum = PE_CSPM_TOP.CSPM_TOP_renum;
			PE_CONTROLL.CSPM_addr++;
		}
		else
		{
			//if(INDEX==4 && WIRE::cycle< 3) cout<<"PE_CSPM_TOP.CSPM_total = "<<PE_CSPM_TOP.CSPM_total<<endl;
			if ((PE_CONTROLL.CSPM_addr - 1) <= PE_CSPM_TOP.CSPM_total)
			{
				

				PE_CSPM.push_back((CU::CSPM_PE[PE_INTERFACE.INDEX][PE_CONTROLL.CSPM_addr]).PE_CSPM);
				PE_CONTROLL.renum.push_back(PE_CSPM[PE_CONTROLL.CSPM_addr-1].CSPM_renum);
				PE_CONTROLL.start_cycle.push_back(PE_CSPM[PE_CONTROLL.CSPM_addr-1].start_cycle);
				PE_CONTROLL.II.push_back(PE_CSPM[PE_CONTROLL.CSPM_addr-1].II);
				

				//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
				//if(INDEX==2 && WIRE::cycle <20) { cout<<"PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<", PE_CSPM.push_back("<<"PE_CONTROLL.CSPM_addr["<<dec<<PE_CONTROLL.CSPM_addr-1<<"]"<<")"<< ", PE_CONTROLL.renum["<<dec<<PE_CONTROLL.CSPM_addr-1<<"] = "<<dec<<PE_CONTROLL.renum[PE_CONTROLL.CSPM_addr-1]<<", PE_CONTROLL.start_cycle["<<dec<<PE_CONTROLL.CSPM_addr-1<<"] = " <<dec<<PE_CONTROLL.start_cycle[PE_CONTROLL.CSPM_addr-1]<< " PE_CONTROLL.II["<<dec<<PE_CONTROLL.CSPM_addr-1<<"] = "<<dec<<PE_CONTROLL.II[PE_CONTROLL.CSPM_addr-1]<<endl; }
				//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
				PE_CONTROLL.CSPM_addr++;
				
			}
			else
			{
				if(PE_STATE != PE_IDLE){
					CSPM_STATE = CSPM_IDLE; // YOU NEED TO WAIT FOR PE TO GET STARTED AND AVOID FALL INTO IDLE TOO EARLY
				}
				//if(INDEX==28&& WIRE::cycle< 50) { cout<<"PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<"Check CSPM_STATE = CSPM_IDLE" <<endl;}
			}
			if(WIRE::cycle == ( PE_CSPM_MAXUSED))
				PE_STATE = PE_PREPARE;
		}
		break;
	default:
		break;
	}


	switch (PE_STATE)
	{
		case PE_IDLE:
			break;
		case PE_PREPARE://reached in cycle2
		{
			//PE_CONTROLL.CSPM_EX_addr = 0;
			//PE_CONTROLL.renum = PE_CSPM[PE_CONTROLL.CSPM_EX_addr].CSPM_renum;
			//assert(PE_CONTROLL.renum > 0);
			//PE_CONTROLL.start_cycle = PE_CSPM[PE_CONTROLL.CSPM_EX_addr].start_cycle;
			PE_STATE = PE_EX;
			break;
		}
		case PE_EX://reached in cycle3
		{
			// if(INDEX == 14 && (WIRE::cycle % 10000 == 0)){
			// 		cout<<"WIRE::CYCLE("<<WIRE::cycle<<") ";
			// 		cout<<" PE_CSPM.capacity("<<PE_CSPM.capacity()<<")";
			// 		cout<<" PE_CONTROLL.renum..capacity("<<PE_CONTROLL.renum.capacity()<<")";
			// 		cout<<" PE_CONTROLL.start_cycle("<<PE_CONTROLL.start_cycle.capacity()<<")";
			// 		cout<<" PE_CONTROLL.start_cycle("<<PE_CONTROLL.II.capacity()<<")"<<endl;
			// 	}
			int activate_count = 0;
			//ostringstream os;
			for(arbitrate_index = 0 ; arbitrate_index < int(PE_CSPM.size()) ; arbitrate_index++)
			{
				if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 4 PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

				if(PE_CONTROLL.renum[arbitrate_index] > 0)
				{
					if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 5 PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;
					if (PE_CONTROLL.start_cycle[arbitrate_index] == 0)
					{
						if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 6 PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;
						
						if( (PE_CONTROLL.II[arbitrate_index] == 0) || (PE_CONTROLL.II[arbitrate_index] == PE_CSPM[arbitrate_index].II) ) 
						{
							if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 7-true PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

							
							
							
							PE_selectinput(PE_CSPM[arbitrate_index], os,debug,taskid);
							PE_calculate(PE_CSPM[arbitrate_index], os, debug,taskid );
							PE_OUTMUX(PE_CSPM[arbitrate_index], os,debug ,taskid);
							PE_CONTROLL.II[arbitrate_index] = PE_CSPM[arbitrate_index].II - 1;
							PE_CONTROLL.renum[arbitrate_index]--;
							if(debugflag){	
								//if(WIRE::cycle < 50)
								std::cout << os.str() << std::endl; 
							}
							os.str("");

							//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
							//if(INDEX==2 && WIRE::cycle <  30) { cout<<"PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle 	\
							<<", INSTR("<<arbitrate_index<<") ITEARTION("<<PE_CONTROLL.renum[arbitrate_index]			\
							<<")OK, START(" <<PE_CONTROLL.start_cycle[arbitrate_index]									\
							<<") OK , II(" <<PE_CONTROLL.II[arbitrate_index]											\
							<<")  , Iteration(" <<PE_CONTROLL.renum[arbitrate_index]									\
							<<") OK ******FIRE IN THE HOLE****"<<endl; }
							//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
							
							if(activate_count != 0)
							{
								logi("Error: in PE:PE_EXEC() : There are more than one instruction executed in PE[%d] at Cycle(%d)\n", INDEX, WIRE::cycle);
								abort();
							}
							activate_count++;//Each should cycle should be only one instrcuction fired	

							if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 8-true PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

						}else{
							if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 9-false PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

							PE_CONTROLL.II[arbitrate_index]--;
							//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
							//if(INDEX==2 && WIRE::cycle <  30 && arbitrate_index == 1) { cout<<"PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle		\
							<<", INSTR("<<arbitrate_index<<") ITEARTION("<<PE_CONTROLL.renum[arbitrate_index]			\
							<<")OK, START(" <<PE_CONTROLL.start_cycle[arbitrate_index]									\
							<<") OK , II(" <<PE_CONTROLL.II[arbitrate_index]											\
							<<") NOT OK , Iteration(" <<PE_CONTROLL.renum[arbitrate_index]								<<endl; }
							//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************

							if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 10-true PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

						}
						
						

						//debug_to_file(debugtrace, os.str());
						
					
						if(PE_CONTROLL.renum[arbitrate_index] == 0){
							PE_CONTROLL.idle_instr_count++;
							//PE_CSPM.erase(PE_CSPM.begin()+arbitrate_index);
							//PE_CONTROLL.II.erase(PE_CONTROLL.II.begin()+arbitrate_index);
							//PE_CONTROLL.renum.erase(PE_CONTROLL.renum.begin()+arbitrate_index);
							//PE_CONTROLL.start_cycle.erase(PE_CONTROLL.start_cycle.begin()+arbitrate_index);
							//if(INDEX==28 ) { cout<<"PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<"Check idle_instr_count++" <<endl;}

							//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
							if(INDEX==2 && WIRE::cycle <  30 && arbitrate_index == 1) {cout<<"PE["<<dec<<INDEX<<"] Cycle:" \
							<<dec<<WIRE::cycle<<", PE_CSPM_COUNT = "<<dec<<PE_CSPM.size()<<", idle_instr_count = "<<dec<<PE_CONTROLL.idle_instr_count<<endl;}
							//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
						}
						
					}
					else{
						 if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 1 PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

						
						 
						PE_CONTROLL.start_cycle[arbitrate_index] = PE_CONTROLL.start_cycle[arbitrate_index]-1;

						if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 2 PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

						//if(INDEX==2 && WIRE::cycle <  30 && arbitrate_index == 1) cout<<"	                                                                   	debug4	 PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" PE_CONTROLL["<<INDEX<<"].start_cycle["<<arbitrate_index<<"] = "<<PE_CONTROLL.start_cycle[arbitrate_index]<<";"<<endl;
						//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
						if(INDEX==2 && WIRE::cycle <  30 && arbitrate_index == 1) { cout<<"PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<", INSTR("<<arbitrate_index<<") ITEARTION("<<PE_CONTROLL.renum[arbitrate_index]<<")OK, START("<<PE_CONTROLL.start_cycle[arbitrate_index]<<") NOT OK ,Iteration(" <<PE_CONTROLL.renum[arbitrate_index]	<<")"<<endl; }
						//***********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&****************************
						if(INDEX==2 && (WIRE::cycle >  7  && WIRE::cycle < 10) && arbitrate_index == 1 ) cout<<"debug 3 PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" start_cycle[1] = "<<PE_CONTROLL.start_cycle[1]<<";"<<endl;

					}
				}
				
			}						

			
			if(PE_CONTROLL.idle_instr_count == PE_CSPM.size()){
				PE_STATE = PE_IDLE;
			}
		}
	}
	os.str("");
}


void PE::PE_OUTMUX(PECSPM &PE_CSPM, ostringstream &os,DebugParam_t &debug,int &taskid ) {
	// if (PE_CONTROLL.beat == EN && PE_CSPM.PE_beat_mode == 1) {
	// 	PE_CONTROLL.output_beat_delay.push_back(INVALID);
	// }
	// else
	// 	PE_CONTROLL.output_beat_delay.push_back(PE_CONTROLL.beat);
	PE_CONTROLL.valid_delay.push_back(PE_CONTROLL.delay);
	//if(INDEX==2 && WIRE::cycle <  30 && arbitrate_index == 1) { cout<<"PE["<<dec<<INDEX<<"] Cycle:"<<dec<<WIRE::cycle<<" PE_CONTROLL.valid_delay.push_back("<<PE_CONTROLL.delay<<"), PE_CONTROLL.valid_delay.size("<<PE_CONTROLL.valid_delay.size()<<")"<<endl;}
	for (int i = 0; i < 3; i++)
	{
		if (PE_CSPM.PE_lr[i] < 4) {
			local_reg[i] = *PE_INTERFACE.PE_DATA_IN[PE_CSPM.PE_lr[i]];
			//if(INDEX == 9) std::cout << "cycle:"<<WIRE::cycle<<" OUTPUT 0123 PE[" << INDEX << "].LR[" << i << "] = " << local_reg[i] << endl;
			debug.perf[taskid].operation_write_localreg++;
		}
		else if (PE_CSPM.PE_lr[i] < 6) {
			local_reg[i] = *PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.PE_lr[i] - 4];
			//if(INDEX == 9) std::cout << "cycle:"<<WIRE::cycle<<" OUTPUT=456 PE[" << INDEX << "].LR[" << i << "] = " << local_reg[i] << endl;
			debug.perf[taskid].operation_write_localreg++;
		}
		else if (PE_CSPM.PE_lr[i] == 6) {
			local_reg[i] = PE_CONTROLL.output_0;
			os << " OutDir(LR[" << i << "])";
			debug.perf[taskid].operation_write_localreg++;
			//if(INDEX == 9) std::cout << "cycle:"<<WIRE::cycle<<" OUTPUT=6 PE[" << INDEX << "].LR[" << i << "] = " << local_reg[i] << endl;
		}
		else if (PE_CSPM.PE_lr[i] == 7) {
			local_reg[i] = PE_CONTROLL.output_1;
			//if(INDEX == 9) std::cout << "cycle:"<<WIRE::cycle<<" OUTPUT=7 PE[" << INDEX << "].LR[" << i << "] = " << local_reg[i] << endl;
			debug.perf[taskid].operation_write_localreg++;
		}
		else{
			//local_reg[i] = 0;
			//if(INDEX == 9) std::cout << "cycle:"<<WIRE::cycle<<" OUTPUT=DEFAULT PE[" << INDEX << "].LR[" << i << "] = " << local_reg[i] << endl;
			}
	}
	for (int i = 0; i < 4; i++) {
		if (PE_CSPM.PE_OUT[i] < 4) {
			PE_CONTROLL.output_PE_delay[i].push_back(*PE_INTERFACE.PE_DATA_IN[PE_CSPM.PE_OUT[i]]);
			debug.perf[taskid].operation_write_peinterconnect++;
		}
		else if (PE_CSPM.PE_OUT[i] < 6) {
			//PE_CONTROLL.output_PE_delay[i].push_back(*PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.PE_OUT[i] - 4]);
		}
		else if (PE_CSPM.PE_OUT[i] == 6) {
			PE_CONTROLL.output_PE_delay[i].push_back(PE_CONTROLL.output_0);
			switch (i) {
			case(0):
			os << " OutDir(pe_right)"; 
			break;
			case(1):
			os << " OutDir(pe_down)"; 
			break;
			case(2):
			os << " OutDir(pe_left)"; 
			break;
			case(3):
			os << " OutDir(pe_up)"; 
			break;
			default:break;
			};


		}
		else if (PE_CSPM.PE_OUT[i] == 7) {
			PE_CONTROLL.output_PE_delay[i].push_back(PE_CONTROLL.output_1);
		}
	}
	for(int i = 0; i < GLOBAL_REG_SIZE ; i++){
		if(PE_CSPM.GR_OUT[i]){
			os << " OutDir(GR[" << i << "])";
			GR::GR_INPUT_INTERFACE[i].push_back(PE_CONTROLL.output_0);
			debug.perf[taskid].operation_write_globalreg++;
			//cout << WIRE::cycle << ":		 PE[" << INDEX << "]->GR_INPUT_INTERFACE[" << i << "]" << endl;;
		}
	}
	// if (PE_CSPM.PE_lsu < 4) {
	// 	PE_CONTROLL.output_LSU_delay.push_back(*PE_INTERFACE.PE_DATA_IN[PE_CSPM.PE_lsu]);
	// }
	// else if (PE_CSPM.PE_lsu < 6)
	// 	PE_CONTROLL.output_LSU_delay.push_back(*PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.PE_lsu - 4]);
	// }
	// else if (PE_CSPM.PE_lsu == 6) {
	// 	PE_CONTROLL.output_LSU_delay.push_back(PE_CONTROLL.output_0);
	// }
	// else if (PE_CSPM.PE_lsu == 7) {
	// 	PE_CONTROLL.output_LSU_delay.push_back(PE_CONTROLL.output_1);
	// }
	// else if (PE_CSPM.PE_gr < 6) {
	// 	PE_CONTROLL.output_gr_delay.push_back(*PE_INTERFACE.LSU_PE_DATA_IN[PE_CSPM.PE_gr - 4]);
	// }
	// else if (PE_CSPM.PE_gr == 6) {
	// 	PE_CONTROLL.output_gr_delay.push_back(PE_CONTROLL.output_0);
	// }
	// else if (PE_CSPM.PE_gr == 7) {
	// 	PE_CONTROLL.output_gr_delay.push_back(PE_CONTROLL.output_1);
	// }


	return;
}


void PE::PE_OUTPUT() {
	
	*PE_INTERFACE.PE_CSPM_IDLE_OUT = (CSPM_STATE == CSPM_IDLE) ? 1 : 0;
	/*for (int i = 0; i < PE_INTERFACE.PE_BEAT_OUT.size(); i++) {
		*PE_INTERFACE.PE_BEAT_OUT[i] = IDLE;
	}
	*PE_INTERFACE.PE_LSU_BEAT_OUT = IDLE;*/
	//if (PE_STATE == PE_EX) {		
	if(PE_CONTROLL.valid_delay.size() > 2)
	{
		logi("Error: in PE:PE_OUTPUT() : There might be excessive push_back to vecotr PE_CONTROL.valid_delay of PE[%d] at Cycle(%d), could lead to memory fragmentation\n", INDEX, WIRE::cycle);
		abort();
	}
	if (PE_CONTROLL.valid_delay.size() != 0)
	{
		for (size_t i = 0; i < PE_CONTROLL.valid_delay.size(); i++)
		{
			PE_CONTROLL.valid_delay[i]--;
		}
		if (*PE_CONTROLL.valid_delay.begin() == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (PE_CONTROLL.output_PE_delay[i].size() != 0)
				{
					//*PE_INTERFACE.PE_BEAT_OUT[i] = *PE_CONTROLL.output_beat_delay.begin();
					*PE_INTERFACE.PE_DATA_OUT[i] = *PE_CONTROLL.output_PE_delay[i].begin();
					PE_CONTROLL.output_PE_delay[i].erase(PE_CONTROLL.output_PE_delay[i].begin());
				}
			}
			// if (PE_CONTROLL.output_LSU_delay.size() != 0)
			// {
			// 	*PE_INTERFACE.PE_LSU_BEAT_OUT = *PE_CONTROLL.output_beat_delay.begin();
			// 	*PE_INTERFACE.PE_LSU_DATA_OUT = *PE_CONTROLL.output_LSU_delay.begin();
			// 	PE_CONTROLL.output_LSU_delay.erase(PE_CONTROLL.output_LSU_delay.begin());
			// }
			// if (PE_CONTROLL.output_gr_delay.size() != 0)
			// {
			// 	//*PE_INTERFACE.PE_GR_INDEX = *PE_CONTROLL.output_gr_delay.begin();
			// 	GR::Global_REG[PE_INTERFACE.INDEX / 8][PE_INTERFACE.INDEX % 8] = *PE_CONTROLL.output_gr_delay.begin();
			// 	GR::GR_BT[PE_INTERFACE.INDEX / 8][PE_INTERFACE.INDEX % 8] = *PE_CONTROLL.output_beat_delay.begin();
			// 	PE_CONTROLL.output_gr_delay.erase(PE_CONTROLL.output_gr_delay.begin());
			// }
			//PE_CONTROLL.output_beat_delay.erase(PE_CONTROLL.output_beat_delay.begin());
			PE_CONTROLL.valid_delay.erase(PE_CONTROLL.valid_delay.begin());

		}
	}
	
	//}
	//if (CSPM_STATE == CSPM_IDLE && PE_STATE == PE_EX && PE_CONTROLL.beat == PE_IDLE && PE_CONTROLL.valid_delay.size() == 0) {
	// if (CSPM_STATE == CSPM_IDLE && PE_STATE == PE_EX && PE_CONTROLL.renum == 0 && PE_CONTROLL.valid_delay.size() == 0 && PE_CONTROLL.CSPM_EX_addr == PE_CSPM_TOP.CSPM_total) {
	// 	*PE_INTERFACE.PE_IDLE_OUT = 1;
	// }
	

	if (CSPM_STATE == CSPM_IDLE && PE_STATE == PE_IDLE && PE_CONTROLL.valid_delay.size() == 0 )
	{
		//if(*PE_INTERFACE.PE_IDLE_OUT == 0)  { cout<<"Execution cycle : "<<dec<<WIRE::cycle<<"PE["<<dec<<INDEX<<"] PE_INTERFACE.PE_IDLE_OUT = 1" <<endl;}		

		*PE_INTERFACE.PE_IDLE_OUT = 1;
	}
	else {
		*PE_INTERFACE.PE_IDLE_OUT = 0;
	}
}



// DATAWIDTH_0(*MONITOR_PARAM_BUFFER())[PARAM_BUFFER_SIZE] {
// 	return CU::PARA_BUFFER;
// }