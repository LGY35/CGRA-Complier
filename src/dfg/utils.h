#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>

#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/GetElementPtrTypeIterator.h"

enum Edge_Attr {
    ATTR_IN_VALID = -1,
    ATTR_CONST    = 1,
    ATTR_REV,
    ATTR_ORDER,
    ATTR_CONST_BASE
};

enum OP_ID {
    IN_VALID = -1,
    // arithmetic IDeration
    ID_ADD = 0,
    ID_SUB, 
    ID_ABS,
    ID_NEG,// sub in llvm
    ID_MUL,
    ID_MOD,
    ID_MAC,
    // compare
    ID_LT,
    ID_LE,
    ID_EQ,
    // logic IDeration
    ID_AND,
    ID_OR,
    ID_NOT, // xor 1 and self in llvm
    ID_XOR,
    ID_SEL,
    // shift
    ID_SHR,
    ID_ASHR,
    ID_SHL,
    // rout
    ID_ROUT,
    // mem
    ID_LOAD,
    ID_STORE,
    // const
    ID_CONST
};
struct Node;
struct In_Conn {
    struct Node*    node;
    enum Edge_Attr  attr;
    int             operand;
};

struct Out_Conn {
    struct Node*    node;
    enum Edge_Attr  attr;
};

struct Node {
    std::string                     name;
    std::string                     llvm_name;
    enum OP_ID                      op = OP_ID::IN_VALID;
    int                             operand_cnt = 0;
    int                             schedule = IN_VALID;
    long                            val = -1;
    std::vector<struct In_Conn>     ins;
    std::vector<struct Out_Conn>    outs;
};

struct Inst_Info {
    struct Node* val = nullptr;
    struct Node* output_addr = nullptr;
    struct Node* output_store = nullptr;
};

struct next_BB {
    llvm::BasicBlock* BB;
    struct Node* cond;
};

struct BB_Info {
    struct Node* cond = NULL;
    std::vector<struct next_BB> next_BBs;
    llvm::BasicBlock* next_uncondi = NULL;
    int visit_cnt = 0;
    int num_preds = -1;
};

extern const llvm::DataLayout* dl;
extern llvm::BasicBlock* preheader;
extern llvm::Loop* target_L;
extern std::set<llvm::BasicBlock*> un_condi_BB;
extern std::map<llvm::Instruction*, struct Inst_Info> I_map_Info;
extern std::list<llvm::Instruction*> delay_I;
extern std::map<llvm::Value*, struct Node*> V_map_Node;
extern std::map<int, struct Node*> C_map_Node;
extern std::map<llvm::BasicBlock*, BB_Info> BB_map_Info;
extern std::vector<struct Node*> all_nodes;
extern std::vector<struct Node*> store_stack;
extern const char* op_string[OP_ID::ID_CONST + 1];

std::string get_V_name(llvm::Value* v);
void add_out_edge(struct Node* from, struct Node* to, enum Edge_Attr attr = Edge_Attr::ATTR_IN_VALID);
struct Node* create_node(enum OP_ID id, std::string llvm_name);
struct Node* create_node(enum OP_ID id, std::string llvm_name, std::vector<struct Node*> operands);
struct Node* create_tmp_phi_node(llvm::Instruction* I);
struct Node* get_output_addr(llvm::Instruction* I);
struct Node* get_dump_addr();
bool is_loop_BB(const llvm::BasicBlock* trg_BB);
int get_num_preds(llvm::BasicBlock *BB, bool in_loop = false);
bool is_input(llvm::Instruction* I);
bool is_output(llvm::Instruction* I);
bool is_in_loop_I(llvm::Instruction* I);
struct Node* find_or_create_V_node(llvm::Value* v);
struct Node* find_or_create_I_node(llvm::Instruction* I);
void clean_all_struct();

#define FLAG_IN_EDGE   (1UL)
struct Node* copy_node(struct Node* copee, unsigned long flag = 0);