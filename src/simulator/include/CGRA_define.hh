#ifndef __CSPM_DEFINE_HH__
#define __CSPM_DEFINE_HH__


#include <stdint.h>
#include <vector>

# define DATAWIDTH_0 int32_t
# define DATAWIDTH_1 int8_t
# define BEATWIDTH uint8_t
# define DATAWIDTH_1 int8_t
# define BEATWIDTH uint8_t
# define MEMORY_DATAWIDTH (unsigned short)

# define IDLE 0
# define INVALID 1
# define EN 2
# define END 3

# define PE_IDLE 0
# define PE_PREPARE 1
# define PE_EX 2

# define CSPM_IDLE 0
# define CSPM_LD 1
# define LSU_IDLE 0
# define LSU_PREPARE 1
# define LSU_EX 2

# define PE_SIZE 64
# define LSU_SIZE 80
# define PARAM_BUFFER_SIZE 3
# define CSPM_PE_SIZE 8
# define CSPM_LSU_SIZE 8
# define GLOBAL_REG_SIZE 8
# define IMM_INSTR_WIDTH 58
# define NIMM_INSTR_WIDTH 76

# define PE_CSPM_MAXUSED 4   //3 seems to be true ,but 4 for insurance. All PE wait to load PE_CSPM_MAXUSED-numbered Instruction to get start

//isp code
#define SIZE_D1_H (2592)
#define SIZE_D1_W (4608)
#define D2_WIDTH_IN 4608
#define D2_HEIGHT_IN 2592
#define D2_WIDTH_OUT  2304
#define D2_HEIGHT_OUT 1296
#define GRID_H 16
#define GRID_W 8
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))
#endif


//performance_reference
#define NORMALIZED_POW_READ_REG 0.5;
#define NORMALIZED_POW_WRITE_REG 0.5;
#define NORMALIZED_POW_MEM_READ 2;
#define NORMALIZED_POW_MEM_WRITE 2;
#define NORMALIZED_POW_LSU_LOAD 1.1;
#define NORMALIZED_POW_LSU_STORE 1.2;
#define NORMALIZED_POW_LESSTHAN 1;
#define NORMALIZED_POW_LESSTHANEQUAL 1;
#define NORMALIZED_POW_EQU 1;
#define NORMALIZED_POW_EQUONE 1;
#define NORMALIZED_POW_READ_FROM_PE 0.3;
#define NORMALIZED_POW_WRITE_TO_PE 0.3;
#define NORMALIZED_POW_SADD 1;
#define NORMALIZED_POW_SSUB 1;
#define NORMALIZED_POW_SABS 1;
#define NORMALIZED_POW_NEG 1;
#define NORMALIZED_POW_SMUL 6;
#define NORMALIZED_POW_SMAC 7;
#define NORMALIZED_POW_SMOD 1;
#define NORMALIZED_POW_AND 1;
#define NORMALIZED_POW_OR 1;
#define NORMALIZED_POW_NOT 1;
#define NORMALIZED_POW_XOR 1;
#define NORMALIZED_POW_SLL 1;
#define NORMALIZED_POW_SRA 1;
#define NORMALIZED_POW_SRL 1;


#define logi(...) printf(__VA_ARGS__)


#endif