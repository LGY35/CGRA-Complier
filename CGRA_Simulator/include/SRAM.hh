#ifndef __SRAM_HH__
#define __SRAM_HH__
#include "CGRA_define.hh"
#include <string>

class SRAM
{
public:
	static DATAWIDTH_0 DSPM[SRAM_BANK_NUM][SRAM_BANK_SIZE];
	static DATAWIDTH_0 WSPM_NEXT[10][128][SRAM_BANK_SIZE];
};
#endif

