#ifndef ___INSTRUCTION_DECODER_HH__
#define ___INSTRUCTION_DECODER_HH__

#include <cstring>
#include<sstream>

#include"../include/DebugSupport.hh"
#include"../include/CSPM.hh"
#include "../include/CU.hh"//
#include "../include/CGRA_define.hh"
signed int binarytoint(std::string binary, bool signed_flag);
void outputmux(int outdecode, PECSPM &PECSPM_TEMP,std::ostringstream &os,DebugParam_t *debug,int taskid);
void input_debugoutput(int inputdecode,char ch, std::ostringstream &os,DebugParam_t *debug,int taskid, int renum);
void decoder(string decode_dir, bool (&Pea_enable)[PE_SIZE], char* debugtrace,DebugParam_t *debug, int taskid);

#endif