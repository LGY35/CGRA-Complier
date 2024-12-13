#ifndef __GR_HH__
#define __GR_HH__
#include "CGRA_define.hh"
#include "GR.hh"
#include <map>
#include <vector>
//#define CGRALIBRARY_API __declspec(dllimport);
class GR
{
public:
	// static DATAWIDTH_0 Global_REG[8][8];
	// static BEATWIDTH GR_BT[8][8];
	// static void GR_INIT();
	// static void GR_SHIFT();
	//
	static DATAWIDTH_0 Global_REG[GLOBAL_REG_SIZE];
	static std::vector<DATAWIDTH_0> GR_INPUT_INTERFACE[GLOBAL_REG_SIZE];
	static std::vector<DATAWIDTH_0> Global_REG_EXEC[GLOBAL_REG_SIZE];
	//static BEATWIDTH GR_BT[8][8];
	static void GR_INIT();
	static void GR_EXEC();
	static void GR_OUTPUT();
	//static void GR_SHIFT();
private:
	/*static bool output_flag[GLOBAL_REG_SIZE];*/
};

#endif