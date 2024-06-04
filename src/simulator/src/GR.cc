#include "../include/GR.hh"
#include "../include/WIRE.hh"
#include<string.h>
#include<map>
#include<iostream>
//#include <cstring>
DATAWIDTH_0 GR::Global_REG[GLOBAL_REG_SIZE] = { {0} };
std::vector<DATAWIDTH_0> GR::GR_INPUT_INTERFACE[GLOBAL_REG_SIZE] = {};
std::vector<DATAWIDTH_0> GR::Global_REG_EXEC[GLOBAL_REG_SIZE] = {};

void GR::GR_INIT() {
	memset(Global_REG, DATAWIDTH_0(0), sizeof(Global_REG));
	GR_INPUT_INTERFACE->clear();
	Global_REG_EXEC->clear();
	return;
}

void GR::GR_EXEC() {
	for (int i = 0; i < GLOBAL_REG_SIZE; i++) 
	{
		if (GR_INPUT_INTERFACE[i].size() != 0) {
			Global_REG_EXEC[i].push_back(GR_INPUT_INTERFACE[i].front());
			//cout <<"cycle:" << WIRE::cycle << ": GR_INPUT_INTERFACE[" << i << "]("<<dec<<GR_INPUT_INTERFACE[i].front()<<") to Global_REG_EXEC[" << i << "]" << endl;
			GR_INPUT_INTERFACE[i].erase(GR_INPUT_INTERFACE[i].begin());
		}
	}
}

void GR::GR_OUTPUT() {
	for (int i = 0; i < GLOBAL_REG_SIZE; i++)
	{
		if (Global_REG_EXEC[i].size() != 0) {
			Global_REG[i] = Global_REG_EXEC[i].front();
			//cout <<"cycle:" <<WIRE::cycle << ": Global_REG_EXEC[" << i << "]("<<Global_REG_EXEC[i].front()<<") to GR[" << i << "]" << endl;
			Global_REG_EXEC[i].erase(Global_REG_EXEC[i].begin());
			/*output_flag[i] = false;*/
		}
		else {
			continue;
		}
	}
}
