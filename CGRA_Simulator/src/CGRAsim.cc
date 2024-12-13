// CGRAsim.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include <cstring>
#include<fstream>
#include<sstream>
#include<bitset>
using namespace std;
#include "stdlib.h"
#include <unistd.h>//linux pause
#include "../include/Instruction_decoder.hh"
#include "../include/WIRE.hh"
#include "../include/PEA.hh"
#include "../include/GR.hh"
#include "../include/CU.hh"
#include "../include/DebugSupport.hh"
//#include <assert.h>
#include <cassert>
#include <time.h>
static RceSimResource _rce;
static void *addrMapper(DATAWIDTH_0 addr, DATAWIDTH_0 len)
{

	int mem_upperbound = _rce.v_addr + _rce.mem.size() * sizeof(_rce.mem[0]);
	if(int(addr + len) <= mem_upperbound){
		return (uint8_t *)_rce.mem.data() + (addr - _rce.v_addr);
	}else{
		logi("ERROR addrMapper(), address access(%d) with length(%d) cross the border(%d)\n",(addr),len,mem_upperbound);
		abort();
	}
	
}



enum{EXECUTABLE,ALGORITHM_INPUT,TASK_COUNT,DEBUGTRACE,STATISTICS,DEBUGOUTPUTFLAG,COMPILEROUT};
int main(int argc, char* argv[])
{
	logi("Executable:%s\n",argv[EXECUTABLE]);
	logi("total task count:%d\n",stoi(argv[TASK_COUNT]));
	logi("preprocessing of algorithm input path:%s\n",argv[ALGORITHM_INPUT]);
	logi("path of debug statistics file:%s\n",argv[STATISTICS]);
	for(int i = 0 ; i < stoi(argv[TASK_COUNT]); i++)
	{
		logi("path of task(%d) instruction file :%s\n",i,argv[COMPILEROUT+i]);
	}
	

	bool debugflag;
	if(stoi(argv[DEBUGOUTPUTFLAG])){
		logi("debug output flag:true \n");
		debugflag = true;
	}else{
		logi("debug output flag:false\n");
		debugflag = false;
	}
	
	clock_t start_time = clock();
	clock_t end_time;
	DebugParam_t debug;
	debug.addr_map = addrMapper;

	get_resource(argv[ALGORITHM_INPUT], _rce, &debug);

	//Initialization
	WIRE::WIRE_setup();
	PEA::PEA_setup();

	//for (snt taskid = 0; taskid < stoi(argv[TASK_COUNT]) ; taskid++)
	for (int taskid = 0; taskid < stoi(argv[TASK_COUNT]); taskid++)
	{
		RceSimPerf task_simperf;
		debug.perf.push_back(task_simperf);
		debug.perf[taskid].task_id = taskid;


		WIRE::WIRE_reset();
		GR::GR_INIT();
		PEA::PEA_reset();
		bool Pea_enable[PE_SIZE];
		bool Lf_enable[8];
		bool Lw_enable[PE_SIZE];
		bool Sf_enable[8];
		memset(Pea_enable, 0, sizeof(Pea_enable));
		memset(Lf_enable, 0, sizeof(Lf_enable));
		memset(Lw_enable, 0, sizeof(Lw_enable));
		memset(Sf_enable, 0, sizeof(Sf_enable));
		for (int i = 0; i < PE_SIZE; i++)
		{
			CU::CSPM_PE[i].clear();

		}

		cout << "----------------Read Instruction File of Task["<<taskid<<"] Begins-------------" << endl;
		decoder(argv[COMPILEROUT+taskid], Pea_enable, argv[DEBUGTRACE],&debug, taskid);
		cout << "----------------Read Instruction File Finished-------------" << endl;		
		cout << "----------------Simulation of Task[" << taskid << "] Begins-----------------" << endl;
		PEA::PEA_ENABLE(Pea_enable, Lf_enable, Lw_enable, Sf_enable);
		PEA::START_SIG_RISING_EDGE(Pea_enable, Lf_enable, Lw_enable, Sf_enable);
		int output_counter = 0;
		ostringstream os; // for debug trace
		for (WIRE::cycle = 0; WIRE::cycle < 99999999; WIRE::cycle++)
		{
			if (WIRE::cycle == 1) 
			{
				PEA::START_SIG_FALLING_EDGE();
			}
			
			PEA::PEA_EXEC(debug,debugflag,taskid, os);
			PEA::PEA_OUTPUT();

			if(output_counter == 1000000)
			{
				end_time = clock();
				cout<<"Execution cycle : " << std::dec<<WIRE::cycle << " ,"; 
				cout<<"Running time is "<< static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC<<"s, "<<endl; 
				output_counter = 0;
			}
			output_counter++;
			if (WIRE::cycle > 0) 
			{
				if (PEA::PEA_CHECKIDLE() == true) 
				{
					cout << "----------------Simulation of Task[" << taskid << "] Ends-----------------" << endl;
					clock_t end_time = clock();
					cout<<"Execution cycle : " << std::dec<<WIRE::cycle << " ,"; 
					cout<<"Running time is "<< static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC<<"s, "<<endl; 
					debug.perf[taskid].execution_cycle = (uint32_t)WIRE::cycle;
					break;
				}
			}
		}
		write_result_to_file(taskid, &debug);
		verify_result(taskid);

	}
	perf_to_file(argv[STATISTICS],&debug);
 }
