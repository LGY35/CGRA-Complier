#ifndef __PEA_HH__
#define __PEA_HH__
//
#include<vector>
#include"PE.hh"
#include"LSU.hh"
#include"WIRE.hh"
#include<cstdint>
#include<fstream>
#include<sstream>


class PEA
{
public:
	static std::vector<PE> PEid;
	//static PE PEid[];
	
	/*
	static PE PE0;
	static PE PE1;
	static PE PE2;
	static PE PE3;
	static PE PE4;
	static PE PE5;
	static PE PE6;
	static PE PE7;
	static PE PE8;
	static PE PE9;
	static PE PE10;
	static PE PE11;
	static PE PE12;
	static PE PE13;
	static PE PE14;
	static PE PE15;
	static PE PE16;
	static PE PE17;
	static PE PE18;
	static PE PE19;
	static PE PE20;
	static PE PE21;
	static PE PE22;
	static PE PE23;
	static PE PE24;
	static PE PE25;
	static PE PE26;
	static PE PE27;
	static PE PE28;
	static PE PE29;
	static PE PE30;
	static PE PE31;
	static PE PE32;
	static PE PE33;
	static PE PE34;
	static PE PE35;
	static PE PE36;
	static PE PE37;
	static PE PE38;
	static PE PE39;
	static PE PE40;
	static PE PE41;
	static PE PE42;
	static PE PE43;
	static PE PE44;
	static PE PE45;
	static PE PE46;
	static PE PE47;
	static PE PE48;
	static PE PE49;
	static PE PE50;
	static PE PE51;
	static PE PE52;
	static PE PE53;
	static PE PE54;
	static PE PE55;
	static PE PE56;
	static PE PE57;
	static PE PE58;
	static PE PE59;
	static PE PE60;
	static PE PE61;
	static PE PE62;
	static PE PE63;*/

	//static LSU LOAD_F0;
	//static LSU LOAD_F1;
	//static LSU LOAD_F2;
	//static LSU LOAD_F3;
	//static LSU LOAD_F4;
	//static LSU LOAD_F5;
	//static LSU LOAD_F6;
	//static LSU LOAD_F7;

	//static LSU LOAD_W0;
	//static LSU LOAD_W1;
	//static LSU LOAD_W2;
	//static LSU LOAD_W3;
	//static LSU LOAD_W4;
	//static LSU LOAD_W5;
	//static LSU LOAD_W6;
	//static LSU LOAD_W7;
	//static LSU LOAD_W8;
	//static LSU LOAD_W9;
	//static LSU LOAD_W10;
	//static LSU LOAD_W11;
	//static LSU LOAD_W12;
	//static LSU LOAD_W13;
	//static LSU LOAD_W14;
	//static LSU LOAD_W15;
	//static LSU LOAD_W16;
	//static LSU LOAD_W17;
	//static LSU LOAD_W18;
	//static LSU LOAD_W19;
	//static LSU LOAD_W20;
	//static LSU LOAD_W21;
	//static LSU LOAD_W22;
	//static LSU LOAD_W23;
	//static LSU LOAD_W24;
	//static LSU LOAD_W25;
	//static LSU LOAD_W26;
	//static LSU LOAD_W27;
	//static LSU LOAD_W28;
	//static LSU LOAD_W29;
	//static LSU LOAD_W30;
	//static LSU LOAD_W31;
	//static LSU LOAD_W32;
	//static LSU LOAD_W33;
	//static LSU LOAD_W34;
	//static LSU LOAD_W35;
	//static LSU LOAD_W36;
	//static LSU LOAD_W37;
	//static LSU LOAD_W38;
	//static LSU LOAD_W39;
	//static LSU LOAD_W40;
	//static LSU LOAD_W41;
	//static LSU LOAD_W42;
	//static LSU LOAD_W43;
	//static LSU LOAD_W44;
	//static LSU LOAD_W45;
	//static LSU LOAD_W46;
	//static LSU LOAD_W47;
	//static LSU LOAD_W48;
	//static LSU LOAD_W49;
	//static LSU LOAD_W50;
	//static LSU LOAD_W51;
	//static LSU LOAD_W52;
	//static LSU LOAD_W53;
	//static LSU LOAD_W54;
	//static LSU LOAD_W55;
	//static LSU LOAD_W56;
	//static LSU LOAD_W57;
	//static LSU LOAD_W58;
	//static LSU LOAD_W59;
	//static LSU LOAD_W60;
	//static LSU LOAD_W61;
	//static LSU LOAD_W62;
	//static LSU LOAD_W63;
	//
	//static LSU STORE_F0;
	//static LSU STORE_F1;
	//static LSU STORE_F2;
	//static LSU STORE_F3;
	//static LSU STORE_F4;
	//static LSU STORE_F5;
	//static LSU STORE_F6;
	//static LSU STORE_F7;

	static void PEA_setup();
	static void PEA_reset();

	static void START_SIG_RISING_EDGE(bool* Pea_enable, bool* Lf_enable, bool* Lw_enable, bool* Sf_enable);

	static void START_SIG_FALLING_EDGE();

	static void PEA_ENABLE(bool* Pea_enable, bool* Lf_enable, bool* Lw_enable, bool* Sf_enable);
	
	static bool PEA_CHECKIDLE();
	static void PEA_EXEC(DebugParam_t &debug, bool &debugflag,int &taskid, std::ostringstream &os);
	static void PEA_OUTPUT();

	//------------------------------------------------------

	//-----------------------------------------------
};


#endif

