#ifndef __CU_HH__
#define __CU_HH__
#include <cstdio>
#include <vector>
#include <queue>
#include "CSPM.hh"
#include "CGRA_define.hh"





class CU
{
public:
	//cspm
	static std::vector<std::vector<CSPM>> CSPM_PE;
	static CSPM CSPM_LSU[LSU_SIZE][CSPM_LSU_SIZE];
	static DATAWIDTH_0 PARA_BUFFER[PE_SIZE][PARAM_BUFFER_SIZE];
	
	
	
};

#endif