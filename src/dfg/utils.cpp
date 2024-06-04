#include "utils.h"

using namespace llvm;

struct Node* dump_addr = nullptr;
int OP_cnt[OP_ID::ID_CONST + 1] = {0};
const char* op_string[OP_ID::ID_CONST + 1] = {
    "add",
    "sub",
    "abs",
    "neg",
    "mul",
    "mod",
    "mac",
    "lt",
    "le",
    "eq",
    "and",
    "or",
    "not",
    "xor",
    "sel",
    "shr",
    "ashr",
    "shl",
    "rout",
    "load",
    "store",
    "const"
};

#pragma region util functions
std::string get_V_name(Value* v)
{
    std::string name;
    llvm::raw_string_ostream rso(name);
    v->Value::print(rso);
    int s_1 = name.find_first_of("@");
    int s_2 = name.find_first_of("%");
    int s = name.find("store");
    if (s != -1 && !(s_1 < s && s_1 != -1) && !(s_2 < s && s_2 != -1)) {
        return "store";
    }
    if (s_1 == -1) {
        s = s_2;
    } else if (s_2 == -1) {
        s = s_1;
    } else {
        s = s_1 < s_2 ? s_1 : s_2;
    }
    int e = name.find_first_of(" ", s);
    return name.substr(s,e - s);
}
void add_out_edge(struct Node* from, struct Node* to, enum Edge_Attr attr)
{
    struct Out_Conn* out = new struct Out_Conn;
    struct In_Conn* in = new struct In_Conn;
    out->node = to;
    in->node = from;
    if (attr == Edge_Attr::ATTR_IN_VALID) {
        if (from->op == OP_ID::ID_CONST) {
            out->attr = Edge_Attr::ATTR_CONST;
            in->attr = Edge_Attr::ATTR_CONST;
        } else {
            out->attr = Edge_Attr::ATTR_IN_VALID;
            in->attr = Edge_Attr::ATTR_IN_VALID;
        }
        in->operand = to->operand_cnt;
        to->operand_cnt++;
    } else {
        out->attr = attr;
        in->attr = attr;
    }
    from->outs.push_back(*out);
    to->ins.push_back(*in);
}
struct Node* create_node(enum OP_ID id, std::string llvm_name)
{
    assert(id != OP_ID::IN_VALID);
    struct Node* n = new struct Node;
    n->op = id;
    n->name = op_string[id] + itostr(OP_cnt[id]);
    n->llvm_name = llvm_name;
    OP_cnt[id]++;
    all_nodes.push_back(n);
    return n;
}
struct Node* create_tmp_phi_node(Instruction* I)
{
    static int cnt = 0;
    struct Node* n = new struct Node;
    n->op = IN_VALID;
    n->name = "tmp_phi" + itostr(cnt);
    n->llvm_name = get_V_name(I);
    cnt++;
    all_nodes.push_back(n);
    return n;
}
struct Node* create_node(enum OP_ID id, std::string llvm_name, std::vector<struct Node*> operands)
{
    struct Node* n = create_node(id, llvm_name);
    for (struct Node* op : operands) {
        add_out_edge(op, n);
    }
    return n;
}
struct Node* copy_node(struct Node* copee, unsigned long flag)
{
    struct Node* n = create_node(copee->op, copee->llvm_name);
    if (FLAG_IN_EDGE & flag) {
        for (int i = 0; i < copee->ins.size(); i++) {
            n->ins.push_back(copee->ins[i]);
            copee->ins[i].node->outs.push_back({n, copee->ins[i].attr});
        }
    }
    return n;
}
struct Node* get_output_addr(Instruction* I)
{
    if (!(I_map_Info.count(I) && I_map_Info[I].output_addr != nullptr)) {
        I_map_Info[I].output_addr = create_node(OP_ID::ID_CONST, get_V_name(I));
    }

    return I_map_Info[I].output_addr;
}
struct Node* get_dump_addr()
{
    if (dump_addr == nullptr) {
        dump_addr = create_node(OP_ID::ID_CONST, "@dump");
    }

    return dump_addr;
}
bool is_loop_BB(const BasicBlock* trg_BB)
{
    for (const BasicBlock * BB : target_L->getBlocks()) {
        if (trg_BB == BB) {
            return true;
        }
    }
    return false;
}
int get_num_preds(BasicBlock *BB, bool in_loop)
{
    unsigned int numPreds = 0;
    for (BasicBlock *pred : predecessors(BB)) {
        if (in_loop) {
            if (is_loop_BB(pred)) {
                numPreds++;
            }
        } else {
            numPreds++;
        }
    }
    return numPreds;
}
bool is_input(Instruction* I)
{
    if (is_loop_BB(I->getParent())) {
        return false;
    }
    return true;
}
bool is_output(Instruction* I)
{
    for (const Use &U : I->uses()) {
        const Instruction *I = cast<Instruction>(U.getUser());
        if (!is_loop_BB(I->getParent())) {
            return true;
        }
    }
    return false;
}
enum OP_ID get_I_OP_ID(Instruction* I)
{
    switch(I->getOpcode())
    {
        case Instruction::Select    :   return OP_ID::ID_SEL;
        case Instruction::Add       :   return OP_ID::ID_ADD;
        case Instruction::Sub       :   return OP_ID::ID_SUB;
        case Instruction::Shl       :   return OP_ID::ID_SHL;
        case Instruction::LShr      :   return OP_ID::ID_SHR;
        case Instruction::AShr      :   return OP_ID::ID_ASHR;
        case Instruction::And       :   return OP_ID::ID_AND;
        case Instruction::Or        :   return OP_ID::ID_OR;
        case Instruction::Xor       :   return OP_ID::ID_XOR;
        case Instruction::Mul       :   return OP_ID::ID_MUL;
        case Instruction::Load      :   return OP_ID::ID_LOAD;
        case Instruction::Store     :   return OP_ID::ID_STORE;
        case Instruction::URem      :   return OP_ID::ID_MOD;
        case Instruction::SRem      :   return OP_ID::ID_MOD;
    }
    return OP_ID::IN_VALID;
}
struct Node* find_or_create_C_node(int c)
{
    if (C_map_Node.count(c)) {
        return C_map_Node[c];
    }
    struct Node* n = create_node(OP_ID::ID_CONST, itostr(c));
    n->val = c;
    C_map_Node[c] = n;
    return n;
}
struct Node* find_or_create_V_node(Value* v)
{
    if (Instruction* I = dyn_cast<Instruction>(v)) {
        if (!is_input(I)) {
            assert(I_map_Info.count(I));
            assert(I_map_Info[I].val != nullptr);
            return I_map_Info[I].val;
        }
    }
    if (V_map_Node.count(v)) {
        return V_map_Node[v];
    }
    if (ConstantInt* C = dyn_cast<ConstantInt>(v)) {
        return find_or_create_C_node(C->getValue().getLimitedValue());
    }
    std::string name;
    
    struct Node* n = create_node(OP_ID::ID_CONST, get_V_name(v));
    // v->print(errs());
    // n->name = v->getName().data();
    V_map_Node[v] = n;
    return n;
}
struct Node* create_Icmp_node(ICmpInst* icmp)
{
    struct Node* left = find_or_create_V_node(icmp->getOperand(0));
    struct Node* right = find_or_create_V_node(icmp->getOperand(1));

    switch (icmp->getPredicate()) {
        case CmpInst::Predicate::ICMP_EQ:
            return create_node(OP_ID::ID_EQ, get_V_name(icmp), {left, right});
        case CmpInst::Predicate::ICMP_NE:
            return create_node(OP_ID::ID_NOT, get_V_name(icmp), {create_node(OP_ID::ID_EQ, get_V_name(icmp), {left, right})});
        case CmpInst::Predicate::ICMP_SLE:
        case CmpInst::Predicate::ICMP_ULE:
            return create_node(OP_ID::ID_LE, get_V_name(icmp), {left, right});
        case CmpInst::Predicate::ICMP_SLT:
        case CmpInst::Predicate::ICMP_ULT:
            return create_node(OP_ID::ID_LT, get_V_name(icmp), {left, right});
        case CmpInst::Predicate::ICMP_SGE:
        case CmpInst::Predicate::ICMP_UGE:
            return create_node(OP_ID::ID_LE, get_V_name(icmp), {right, left});
        case CmpInst::Predicate::ICMP_SGT:
        case CmpInst::Predicate::ICMP_UGT:
            return create_node(OP_ID::ID_LT, get_V_name(icmp), {right, left});
    }
    
    printf("unrecognized icmp type\n");
    exit(1);
}
struct Node* create_getelmptr_node(Instruction* I)
{
    GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(I);
    gep_type_iterator GTI = gep_type_begin(I);
    struct Node* base = find_or_create_V_node(I->getOperand(0));
    struct Node* offset = nullptr;
    for(User::op_iterator i = gep->op_begin() + 1, e = gep->op_end(); i != e; ++i, ++GTI) {
        Type* t = GTI.getIndexedType();
        uint64_t tSize = dl->getTypeSizeInBits(t) / 8;
        if(ConstantInt *OpC = dyn_cast<ConstantInt>(*i)) {
            if(OpC->isZero()) {
                continue;
            }
            if (offset) {
                offset = create_node(OP_ID::ID_ADD, get_V_name(I), {offset, find_or_create_C_node(OpC->getValue().getLimitedValue() * tSize)});
            } else {
                offset = find_or_create_C_node(OpC->getValue().getLimitedValue());
            }
        } else {
            struct Node* offset_tmp = find_or_create_C_node(tSize);
            Instruction *in = dyn_cast<Instruction>(*i);
            assert(I_map_Info.count(in) && I_map_Info[in].val);
            if (offset) {
                offset = create_node(OP_ID::ID_ADD, get_V_name(I), {offset, create_node(OP_ID::ID_MUL, get_V_name(I), {I_map_Info[in].val, offset_tmp})});
            } else {
                offset = create_node(OP_ID::ID_MUL, get_V_name(I), {I_map_Info[in].val, offset_tmp});
            }
        }
    }
    return create_node(OP_ID::ID_ADD, get_V_name(I), {base, offset});
}
struct Node* create_call_node(CallInst* call)
{
    struct Node* n = nullptr;
    if (!call->getCalledFunction()->getName().str().compare(0, 8, "llvm.abs")) {
        n = create_node(OP_ID::ID_ABS, get_V_name(call), {find_or_create_V_node(call->getOperand(0))});
    } else if ((!call->getCalledFunction()->getName().str().compare(0, 9, "llvm.umin")) ||
        (!call->getCalledFunction()->getName().str().compare(0, 9, "llvm.smin"))) {
        struct Node* left = find_or_create_V_node(call->getOperand(0));
        struct Node* right = find_or_create_V_node(call->getOperand(1));
        n = create_node(OP_ID::ID_LE, get_V_name(call), {left, right});
        n = create_node(OP_ID::ID_SEL, get_V_name(call), {n, left, right});
    } else if (!call->getCalledFunction()->getName().str().compare(0, 9, "llvm.smin") ||
        !call->getCalledFunction()->getName().str().compare(0, 9, "llvm.smax")) {
        struct Node* left = find_or_create_V_node(call->getOperand(0));
        struct Node* right = find_or_create_V_node(call->getOperand(1));
        n = create_node(OP_ID::ID_LE, get_V_name(call), {left, right});
        n = create_node(OP_ID::ID_SEL, get_V_name(call), {n, right, left});
    } else {
        printf("containing call to %s", call->getCalledFunction()->getName().str().c_str());
        exit(1);
    }
    return n;
}
struct Node* find_or_create_I_node(Instruction* I)
{
    if (I_map_Info.count(I) && I_map_Info[I].val != nullptr) {
        return I_map_Info[I].val;
    }

    if (get_I_OP_ID(I) != -1) {
        std::vector<struct Node*> operands;
        for (int i = 0; i < I->getNumOperands(); i++) {
            operands.push_back(find_or_create_V_node(I->getOperand(i)));
        }
        return create_node((enum OP_ID)get_I_OP_ID(I), get_V_name(I),  operands);
    } else if(isa<CastInst>(I)) {
        Instruction* pre = dyn_cast<Instruction>(I->getOperand(0));
        return I_map_Info[pre].val;
    } else if (ICmpInst* icmp = dyn_cast<ICmpInst>(I)) { // also handles zext instructions
        return create_Icmp_node(icmp);
    } else if (I->getOpcode() == Instruction::GetElementPtr) {
        return create_getelmptr_node(I);
    } else if (CallInst* call = dyn_cast<CallInst>(I)) {
        return create_call_node(call);
    } else {
        I->print(errs());
        printf("\nunknow instruction op code\n");
        exit(1);
        return nullptr;
    }
    return nullptr;
}
void clean_all_struct()
{
    preheader = nullptr;
    target_L = nullptr;
    un_condi_BB.clear();
    I_map_Info.clear();
    delay_I.clear();
    V_map_Node.clear();
    BB_map_Info.clear();
    store_stack.clear();
    C_map_Node.clear();
    for (struct Node* n : all_nodes) {
        delete n;
    }
    dump_addr = nullptr;
    all_nodes.clear();
}
#pragma endregion