#include"../include/Instruction_decoder.hh"
#include"../include/CU.hh"
using namespace std;
#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
std::vector<std::vector<CSPM>> CU::CSPM_PE(PE_SIZE);
signed int binarytoint(string binary, bool signed_flag = false)
{
	
	
	if (binary[0] == '1'&& signed_flag == true)
	{
		string num2 = binary.substr(1, binary.size() - 1);
		bitset<31> num3(num2);
		signed int num4 = num3.to_ulong();//-1
		num4 = num4 - 0b0000000000000000000000000000001;
		bitset<31> num5(num4);
		num5 = num5.flip();//reverse
		num4 = num5.to_ulong();
		num4 = -num4;
		//cout << "binarytoint("<<binary<<") = " <<num4 << endl;
		return num4;
	}
	else
	{
		bitset<32> num3(binary);
		signed int num4 = num3.to_ulong();
		return num4;
		//cout << "binarytoint(" << binary << ") = " << num4 << endl;
	}
}

void outputmux(int outdecode, PECSPM &PECSPM_TEMP,ostringstream &os,DebugParam_t *debug,int taskid)
{
	switch (outdecode) {
	case(0): { 
		PECSPM_TEMP.PE_lr[0] = 6; 
		os << " OutDir(LR[0]) ";
		
		break; }
	case(1): { 
		PECSPM_TEMP.PE_lr[1] = 6; 
		os << " OutDir(LR[1]) ";
		
		
		break; }
	case(2): { 
		PECSPM_TEMP.PE_lr[2] = 6; 
		os << " OutDir(LR[2]) "; 
		
		
		break; }
	case(3): { 
		PECSPM_TEMP.GR_OUT[0] = true;
		os << " OutDir(GR[0]) "; 
		
		
		break;}
	case(4): { /*FIFO*/	
	break;	}
	case(5): { 
		PECSPM_TEMP.PE_OUT[0] = 6; 
		os << " OutDir(pe_right) "; 
		
		
		break; }
	case(6): { 
		PECSPM_TEMP.PE_OUT[1] = 6; 
		os << " OutDir(pe_down) ";
		
		
		break; }
	case(7): { 
		PECSPM_TEMP.PE_OUT[2] = 6; 
		os << " OutDir(pe_left) "; 
		
		
		break; }
	case(8): { 
		PECSPM_TEMP.PE_OUT[3] = 6; 
		os << " OutDir(pe_up) "; 
		
		
		break; }
	case(14): { 
		PECSPM_TEMP.GR_OUT[1] = true; 
		os << " OutDir(GR[1]) "; 
		
		
		break;}
	case(15): { 
		PECSPM_TEMP.GR_OUT[2] = true; 
		os << " OutDir(GR[2]) "; 
		
		
		break;}
	case(16): { 
		PECSPM_TEMP.GR_OUT[3] = true; 
		os << " OutDir(GR[3]) "; 
		
		
		break;}
	case(17): { 
		PECSPM_TEMP.GR_OUT[4] = true; 
		os << " OutDir(GR[4]) "; 
		
		
		break;}
	case(18): { 
		PECSPM_TEMP.GR_OUT[5] = true; 
		os << " OutDir(GR[5]) ";
		
		
		 break;}
	case(19): { 
		PECSPM_TEMP.GR_OUT[6] = true; 
		os << " OutDir(GR[6]) "; 
		
		
		break;}
	case(20): { 
		PECSPM_TEMP.GR_OUT[7] = true; 
		os << " OutDir(GR[7]) "; 
		
		
		break;}
	default: break;
	}

}


void input_debugoutput(int inputdecode, char ch, ostringstream &os,DebugParam_t *debug,int taskid, int renum)
{
	switch (inputdecode) {
	case(0): {
		os << " IN"<<ch<<"(pe_left) ";
		
		
		break; }
	case(1): {
		os << " IN"<<ch<<"(pe_up) ";
		
		;
		break; }
	case(2): {
		os << " IN"<<ch<<"(pe_right) ";
		
		;
		 break; }
	case(3): {
		os << " IN"<<ch<<"(pe_down) ";
		
		;
		break; }
	case(8): {
		os << " IN"<<ch<<"(LR[0]) "; 
		
		
		break; }
	case(9): {
		os << " IN"<<ch<<"(LR[1]) "; 
		
		
		break; }
	case(10): {
		os << " IN"<<ch<<"(LRR[2]) ";
		
		
		 break; }
	case(11): {
		os << " IN"<<ch<<"(ImmR[0]) ";
		
		
		break; }
	case(12): {
		os << " IN"<<ch<<"(ImmR[1]) ";
		
		
		break; }
	case(13): {
		os << " IN"<<ch<<"(ImmR[2]) ";
		
		
		break; }
	case(14): {
		os << " IN"<<ch<<"(GR[0]) ";
		
		
		
		break; }
	case(15): {
		os << " IN"<<ch<<"(GR[1]) ";
		
		
		break; }
	case(16): {
		os << " IN"<<ch<<"(GR[2]) ";
		
		
		break; }
	case(17): {
		os << " IN"<<ch<<"(GR[3]) ";
		
		
		break; }
	case(18): {
		os << " IN"<<ch<<"(GR[4]) ";
		
		
		break; }
	case(19): {
		os << " IN"<<ch<<"(GR[5]) ";
		
		
		break; }
	case(20): {
		os << " IN"<<ch<<"(GR[6]) ";
		
		
		break; }
	case(21): {
		os << " IN"<<ch<<"(GR[7]) ";
		
		
		break; }
	default: {
		// cout<<"||||| inputdecode = "<<inputdecode<<"|||||";
		break;
		}
	}

}


void decoder(string decode_dir, bool (&Pea_enable)[PE_SIZE], char* debugtrace,DebugParam_t *debug, int taskid)
{
	//cout<<"hi7.5"<<endl;

	cout<<"Instruction Decode:  Begins: Instr_dir:"<<decode_dir<<endl;
	ifstream in(decode_dir, ios::in | ios::binary);
	if (!in){cout << "Error: failed to open machine code file" << endl;}
	assert(in);
	bool PE_HAS_CSPM_TOP[PE_SIZE] = { false };

	string line;
	ostringstream os;
	


	while (getline(in, line))
	{
		string Instr;
		
		if((line.size() == (NIMM_INSTR_WIDTH+1))||(line.size() == (IMM_INSTR_WIDTH+1))){
			Instr = line.substr(0, line.size() - 1);//Remove the '\n' 
		}else{
			Instr = line.substr(0, line.size());
		}
		
		
		int peid = binarytoint(Instr.substr(0, 6));
		int opcode = binarytoint(Instr.substr(6, 3));
		
		if (opcode == 6)//IMM Instr
		{
			os << "PE[" << peid << "] | ";
			os << "                ";
			signed int imm_signed = binarytoint(Instr.substr(35,32 ), true);
			
			signed int out_imm = binarytoint(Instr.substr(67, 5));
			os << "IMM(" <<std::dec<< imm_signed << ")";
			switch (out_imm)
			{
			
			case(11): {
				CU::PARA_BUFFER[peid][0] = imm_signed; 
				os << " ImmR[0] "; 
				break; }
			case(12): {
				CU::PARA_BUFFER[peid][1] = imm_signed; 
				os << " ImmR[1] "; 
				break; }
			case(13): {
				CU::PARA_BUFFER[peid][2] = imm_signed; 
				os << " ImmR[2] "; 
				break; }
			default:break;
			}
			
			//debug_to_file(debugtrace, os.str());
			cout<<os.str()<<endl;
			os.str("");
			
			debug->perf[taskid].operation_write_immreg++;

			continue;
		}
		else if (PE_HAS_CSPM_TOP[peid] == false)
		{
			//Ought to set up CSPM_Top when PE[index]'s instr is decoded in the first time, IMM instr is not counted
			Pea_enable[peid] = true;
			CSPM CSPM_TEMP;
			CU::CSPM_PE[peid].push_back(CSPM_TEMP);
			PE_HAS_CSPM_TOP[peid] = true;
			
			debug->perf[taskid].idle_pe_num--;
			debug->perf[taskid].active_pe_num++;

		}
		else
		{
			//Ought to increase the 'CSPM_total' context in CSPM_TOP_TEMPLATE when PE[index] has more than one instr decoded ,IMM instr is not counted 
			CU::CSPM_PE[peid][0].CSPM_TOP.CSPM_total++;
		}


		os << "PE[" <<peid << "] |  Start_TimeStamp:" << binarytoint(Instr.substr(73, 5));
		os << "| Iteration:" << binarytoint(Instr.substr(49, 24));
		os << " | II: "<<binarytoint(Instr.substr(78, 4));	


		//Inistatiate a CSPM struct
		CSPM PECSPM_TEMP_NEW;
		//CSPM_TOP_TEMPLATE CSPM_TOPTEMP;
		//PECSPM_TEMP1.CSPM_TOP = CSPM_TOPTEMP;
		//INPUT
		PECSPM_TEMP_NEW.PE_CSPM.INX = binarytoint(Instr.substr(14, 5));
		PECSPM_TEMP_NEW.PE_CSPM.INY = binarytoint(Instr.substr(19, 5));
		PECSPM_TEMP_NEW.PE_CSPM.INZ = binarytoint(Instr.substr(24, 5));
			
		int out_1 = binarytoint(Instr.substr(29, 5));
		int out_2 = binarytoint(Instr.substr(34, 5));
		int out_3 = binarytoint(Instr.substr(39, 5));
		int out_4 = binarytoint(Instr.substr(44, 5));
		PECSPM_TEMP_NEW.PE_CSPM.start_cycle = binarytoint(Instr.substr(73, 5));
		PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum = (binarytoint(Instr.substr(49, 24)));
		PECSPM_TEMP_NEW.PE_CSPM.II = binarytoint(Instr.substr(78, 4));; 

		int opcode_exd1;
		
		switch (opcode) {
		case(0): {os << " LOOP ";break;}
		case(1): {
			PECSPM_TEMP_NEW.PE_CSPM.PE_opcode = 2;//IF
			opcode_exd1 = binarytoint(Instr.substr(9, 2));
			switch (opcode_exd1) {
			case(0): {				os << " IF(INX<INY) "; 				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.mode = 0; 				break; }
			case(1): {				os << " IF(INX<=INY) ";				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.mode = 1; 				break; }
			case(2): {				os << " IF(INX==INY) "; 				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.mode = 2;						break; }
			case(3): {				os << " IF(INX==1) ";				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.mode = 3; 				break; }
			}
			opcode_exd1 = binarytoint(Instr.substr(11, 2));
			switch (opcode_exd1) {
			case(0): { 				os << " RESULT(1/0)";				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.result = 0;				break; }
			case(1): { 				os << " RESULT(INX/INY)";  				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.result = 1; 				break; }
			case(2): { 				os << " RESULT(INY/INZ)"; 				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.result = 2;				break; }
			case(3): { 				os << " RESULT(INX/INZ)"; 				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.result = 3; 				break; }
			}
			
			if (!binarytoint(Instr.substr(13, 1)))
			{ 				os << "|(T/F) ";				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.if_pattern = 0;}
			else {  				os << "|(F/T) ";				PECSPM_TEMP_NEW.PE_CSPM.PE_IF.if_pattern = 1; }
			break;
		}
		case(2): {
			//Route
			PECSPM_TEMP_NEW.PE_CSPM.PE_opcode = 1;
			opcode_exd1 = binarytoint(Instr.substr(9, 5));//Route Delay
			os << " ROUTE  route_delay(" << opcode_exd1 << ")";
			PECSPM_TEMP_NEW.PE_CSPM.PE_ROUTE.route_delay = opcode_exd1;
			break;
		}
		case(3): {
			
			//ARITH
			PECSPM_TEMP_NEW.PE_CSPM.PE_opcode = 3;
			opcode_exd1 = binarytoint(Instr.substr(9, 5));
			//PECSPM_TEMP.PE_ARITH.mode = opcode_exd1;
			switch (opcode_exd1) {
			case(0): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_ARITH.mode = 0; 				os << " SADD ";				break; }
			case(1): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_ARITH.mode = 1; 				os << " SSUB ";				break; }
			case(2): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_ARITH.mode = 2; 				os << " SABS ";				break; }
			case(3): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_ARITH.mode = 3; 				os << " NEG ";				break; }
			case(4): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_ARITH.mode = 4; 				os << " SMUL ";				break; }
			case(5): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_ARITH.mode = 5; 				os << " SMAC ";				break; }
			case(6): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_ARITH.mode = 6; 				os << " SMOD ";				break; }
			default: {
				cout << "Error: Unrecognized Opcode " << endl; 
				os << "Error: Unrecognized Opcode" << endl;
				abort(); 
				}
			}
			break;
		}
		case(4): {//logic
			PECSPM_TEMP_NEW.PE_CSPM.PE_opcode = 4;
			opcode_exd1 = binarytoint(Instr.substr(9, 5));
			//PECSPM_TEMP.PE_LOGIC.mode = opcode_exd1;
			switch (opcode_exd1)
			{
			case(0): {				PECSPM_TEMP_NEW.PE_CSPM.PE_LOGIC.mode = 0; 				os << " AND ";				break; }
			case(1): {				PECSPM_TEMP_NEW.PE_CSPM.PE_LOGIC.mode = 1; 				os << " OR ";				break; }
			case(2): {				PECSPM_TEMP_NEW.PE_CSPM.PE_LOGIC.mode = 2; 				os << " NOT ";				break; }
			case(3): {				PECSPM_TEMP_NEW.PE_CSPM.PE_LOGIC.mode = 3; 				os << " XOR ";				break; }
			default: {
				cout << "Error: Unrecognized Opcode " << endl; 
				os << "Error: Unrecognized Opcode" << endl;
				abort(); 
				}
			}
			break;
		}
		case(5): {//shifter
			PECSPM_TEMP_NEW.PE_CSPM.PE_opcode = 5;
			opcode_exd1 = binarytoint(Instr.substr(9, 5));
			switch (opcode_exd1)
			{
			case(0): {				PECSPM_TEMP_NEW.PE_CSPM.PE_SHIFTER.mode = 0; 				os << " SRL "; 			break; }
			case(1): {				PECSPM_TEMP_NEW.PE_CSPM.PE_SHIFTER.mode = 1; 				os << " SRA ";				break; }
			case(2): {				PECSPM_TEMP_NEW.PE_CSPM.PE_SHIFTER.mode = 2; 				os << " SL(A/L) ";				break; }
			default: {
				cout << "Error: Unrecognized Opcode " << endl; 
				os << "Error: Unrecognized Opcode" << endl;
				abort(); 
				}
			}
			break;
		}
		case(7): {//Load & Store 
			PECSPM_TEMP_NEW.PE_CSPM.PE_opcode = 8;
			opcode_exd1 = binarytoint(Instr.substr(9, 5));
			switch (opcode_exd1)
			{
			case(0): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_LSU.mode = 0; 
				os << " LOAD ";
				//INPUT MUX
				os << " ADDRESS:";
				input_debugoutput(PECSPM_TEMP_NEW.PE_CSPM.INX, 'X', os, debug, taskid, PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum);
				//OUTPUT MUX
				outputmux(out_1, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);
				outputmux(out_2, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);		
				outputmux(out_3, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);
				outputmux(out_4, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);		

				CU::CSPM_PE[peid].push_back(PECSPM_TEMP_NEW);
				//debug_to_file(debugtrace, os.str());
				cout<<os.str()<<endl;
				os.str("");
				
				debug->perf[taskid].memory_load_count+=PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum;
				break; 
			}
			case(1): {
				PECSPM_TEMP_NEW.PE_CSPM.PE_LSU.mode = 1; 
				os << " STORE ";
				//INPUT MUX
				os << " DATA:";
				input_debugoutput(PECSPM_TEMP_NEW.PE_CSPM.INX, 'X',os,debug,taskid,PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum);
				os << " ADDRESS:";
				input_debugoutput(PECSPM_TEMP_NEW.PE_CSPM.INY, 'Y',os,debug,taskid,PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum);
				CU::CSPM_PE[peid].push_back(PECSPM_TEMP_NEW);
				//debug_to_file(debugtrace, os.str());
				cout<<os.str()<<endl;
				os.str("");
				
				debug->perf[taskid].memory_store_count+=PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum;
				break; 
			}
			
			default: {
				cout << "Error: Unrecognized Opcode " << endl; 
				os << "Error: Unrecognized Opcode" << endl;
				abort();
				 }
			}
			continue;
		}
		default: 
			cout << "Error: Unrecognized Opcode " << endl; 
			os << "Error: Unrecognized Opcode" << endl;
			abort();
		}


		//INPUT MUX
		input_debugoutput(PECSPM_TEMP_NEW.PE_CSPM.INX,'X',os,debug,taskid,PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum);
		input_debugoutput(PECSPM_TEMP_NEW.PE_CSPM.INY,'Y',os,debug,taskid,PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum);
		input_debugoutput(PECSPM_TEMP_NEW.PE_CSPM.INZ,'Z',os,debug,taskid,PECSPM_TEMP_NEW.PE_CSPM.CSPM_renum);
		//OUTPUT MUX
		//cout<<"out1/2/3/4:"<<out_1<<" "<<out_2<<" "<<out_3<<" "<<out_4<<" ";
		outputmux(out_1, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);
		outputmux(out_2, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);		
		outputmux(out_3, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);
		outputmux(out_4, PECSPM_TEMP_NEW.PE_CSPM,os,debug,taskid);		
		CU::CSPM_PE[peid].push_back(PECSPM_TEMP_NEW);
		//debug_to_file(debugtrace, os.str());
		cout << os.str()<<endl;
		os.str("");
	}
	cout<<"Instruction Decode:  Ends"<<endl;
}
