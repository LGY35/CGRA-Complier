#ifndef __DEBUGSUPPORT_HH__
#define __DEBUGSUPPORT_HH__
#include<vector>
#include<string>
#include "./CGRA_define.hh"
#include "../include/alg6.hh"
using namespace std;

struct RceSimResource {
    std::vector<unsigned short>mem;
    DATAWIDTH_0 v_addr;    
};

struct RceSimPerf{

    uint32_t  task_id = 0;
    uint32_t  execution_cycle= 0;
    // idle pe + active pe
    uint32_t  idle_pe_num= PE_SIZE;
    uint32_t  active_pe_num = 0;
    //imm instruction
    uint32_t  operation_write_immreg= 0;
    //load & store
    uint32_t  memory_load_count= 0;
    uint32_t  memory_store_count= 0;
    uint32_t  lsu_load_count= 0;
    uint32_t  lsu_store_count= 0;
    //if
    uint32_t  operation_lessthan=0;
    uint32_t  operation_lessthanequal=0;
    uint32_t  operation_equal=0;
    uint32_t  operation_equalone=0;
    //reg read
    uint32_t  operation_read_localreg= 0;
    uint32_t  operation_read_immreg= 0;
    uint32_t  operation_read_globalreg= 0;
    uint32_t  operation_read_peinterconnect= 0;
    //reg write
    uint32_t  operation_write_localreg= 0;
    uint32_t  operation_write_globalreg= 0;
    uint32_t  operation_write_peinterconnect= 0;
    //arith
    uint32_t  operation_arith_sadd= 0;
    uint32_t  operation_arith_ssub= 0;
    uint32_t  operation_arith_sabs= 0;
    uint32_t  operation_arith_neg= 0;
    uint32_t  operation_arith_smul= 0;
    uint32_t  operation_arith_smac= 0;
    uint32_t  operation_arith_smod= 0;
    //logic
    uint32_t  operation_logic_and= 0;
    uint32_t  operation_logic_or= 0;
    uint32_t  operation_logic_not= 0;
    uint32_t  operation_logic_xor= 0;
    //shift
    uint32_t  operation_shifter_sll= 0;
    uint32_t  operation_shifter_sra= 0;
    uint32_t  operation_shifter_srl= 0;
}; 

typedef void * (*RceAddrMapper)(DATAWIDTH_0 addr, DATAWIDTH_0 len);

typedef struct DebugParam_s {
	RceAddrMapper addr_map;
    vector<RceSimPerf> perf;
} DebugParam_t;


int get_resource(char *f_name, RceSimResource &res, DebugParam_t *debug);

void debug_to_file(char* filename, std::string debuginfo);

void perf_to_file(char* filename, DebugParam_t *debug);

void write_result_to_file(int taskcount, DebugParam_t *debug);

void verify_result(int taskid);

void isp_main();
# endif

