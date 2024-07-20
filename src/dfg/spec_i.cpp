#include "spec_i.h"

using namespace llvm;

bool handle_store_or_output(Instruction* I)
{
    if (!un_condi_BB.count(I->getParent())) {
        struct Node* store = nullptr;
        struct Node* store_addr = nullptr;
        if (I->getOpcode() == Instruction::Store) {
            store_addr = find_or_create_V_node(I->getOperand(1));
            store = find_or_create_I_node(I);
        } else {
            store_addr = I_map_Info[I].output_addr;
            store = I_map_Info[I].output_store;
        }
        assert(store_addr);
        assert(store);
        struct Node* sel_addr = create_node(OP_ID::ID_SEL, get_V_name(I), {BB_map_Info[I->getParent()].cond, store_addr, get_dump_addr()});
        for (int i = 0; i < store->ins.size(); i++) {
            if (store->ins[i].node == store_addr) {
                store->ins[i].node = sel_addr;
            }
        }
        for (int i = 0; i < store_addr->outs.size(); i++) {
            if (store_addr->outs[i].node == store) {
                sel_addr->outs.push_back(store_addr->outs[i]);
                store_addr->outs.erase(store_addr->outs.begin() + i);
                break;
            }
        }
    }
    return false;
}

void replace_phi_out(struct Node* old_n, struct Node* new_n, struct Node* I_n = nullptr)
{
    if (old_n->ins.size()) {
        printf("target node has in edge, cannot be replaced");
        exit(1);
    }
    if (new_n->outs.size()) {
        printf("new node has out edge, cannot be replaced");
        exit(1);
    }
    
    for (int i = 0; i < old_n->outs.size(); i++) {
        for (int j = 0; j < old_n->outs[i].node->ins.size(); j++) {
            if (old_n->outs[i].node->ins[j].node == old_n) {
                old_n->outs[i].node->ins[j].node = new_n;
            }
        }
        new_n->outs.push_back(old_n->outs[i]);
    }
    old_n->outs.clear();

    if (I_n != nullptr) {
        for (int i = 0; i < I_n->outs.size(); i++) {
            new_n->outs.push_back(I_n->outs[i]);
            for (int j = 0; j < I_n->outs[i].node->ins.size(); j++) {
                if (I_n->outs[i].node->ins[j].node == I_n) {
                    I_n->outs[i].node->ins[j].node = new_n;
                }
            }
        }
        I_n->outs.clear();
    }
}

Instruction* is_loop_phi(PHINode* phi)
{
    if (phi->getNumIncomingValues() != 2) {
        return nullptr;
    }
    int num_out_BB = 0;
    for (unsigned i = 0; i < phi->getNumIncomingValues(); ++i) {
        BasicBlock* BB = phi->getIncomingBlock(i);
        if (!is_loop_BB(BB)) {
            num_out_BB++;
        }
    }
    if (num_out_BB != 1) {
        return nullptr;
    }
    Instruction* ret = nullptr;
    for (const Use &U_1 : phi->uses()) {
        const Instruction *I_1 = cast<Instruction>(U_1.getUser());
        if (un_condi_BB.count(const_cast<BasicBlock*>(I_1->getParent()))) {
            for (const Use &U_2 : I_1->uses()) {
                const Instruction *I_2 = const_cast<Instruction *>(cast<Instruction>(U_2.getUser()));
                if (I_2 == phi) {
                    if (ret == nullptr) {
                        ret = const_cast<Instruction*>(I_1);
                    } else {
                        return nullptr;
                    }
                }
            }
        }
    }
    return ret;
}

struct Node* handle_normal_phi(PHINode* phi)
{
    struct Node* n = NULL;
    for (unsigned i = 0; i < phi->getNumIncomingValues(); ++i) {
        BasicBlock* BB = phi->getIncomingBlock(i);
        Value* val = phi->getIncomingValue(i);
        if (n == NULL) {
            n = find_or_create_V_node(val);
        } else {
            if (BB_map_Info[BB].next_uncondi == phi->getParent()) {
                if (!un_condi_BB.count(BB)) {
                    n = create_node(OP_ID::ID_SEL, get_V_name(phi), {BB_map_Info[BB].cond, find_or_create_V_node(val), n});
                } else {
                    n = find_or_create_V_node(val);
                    break;
                }
            } else {
                int j = 0;
                for (j = 0; j < BB_map_Info[BB].next_BBs.size(); j++) {
                    //add
                    // BB_map_Info[BB].next_BBs[j].BB->print(errs());
                    // printf("BB_map_Info[BB].next_BBs.size(): %zu\n",BB_map_Info[BB].next_BBs.size());
                    if (BB_map_Info[BB].next_BBs[j].BB == phi->getParent()) {
                        
                        n = create_node(OP_ID::ID_SEL, get_V_name(phi), {BB_map_Info[BB].next_BBs[j].cond, find_or_create_V_node(val), n});
                        break;
                    }
                }
                if (j == BB_map_Info[BB].next_BBs.size()) {
                    BB->print(errs());
                    phi->print(errs());
                    phi->getParent()->print(errs());
                    printf("error in pred and next BB\n");
                    exit(1);
                }
            }
        }
    }
    replace_phi_out(I_map_Info[phi].val,n);
    return n;
}

struct Node* handle_loop_phi(PHINode* phi, Instruction* I)
{
    struct Node* old_phi = find_or_create_I_node(phi);
    struct Node* const_n = nullptr;
    for (int i = 0; i < phi->getNumIncomingValues(); i++) {
        BasicBlock* BB = phi->getIncomingBlock(i);
        if (!is_loop_BB(BB)) {
            assert(const_n == nullptr);
            const_n = find_or_create_V_node(phi->getIncomingValue(i));
        }
    }
    assert(const_n != nullptr);
    struct Node* I_node = find_or_create_I_node(I);
    struct Node* new_phi = copy_node(I_node, FLAG_IN_EDGE);
    new_phi->llvm_name = old_phi->llvm_name;
    new_phi->name = "loop_" + new_phi->name;
    for (int i = 0; i < new_phi->ins.size(); i++) {
        if (new_phi->ins[i].node == old_phi) {
            new_phi->ins[i].node = const_n;
            new_phi->ins[i].attr = Edge_Attr::ATTR_CONST_BASE;
            struct Out_Conn* out = new struct Out_Conn;
            out->attr = Edge_Attr::ATTR_CONST_BASE;
            out->node = new_phi;
            const_n->outs.push_back(*out);
        }
    }
    for (int i = 0; i < old_phi->outs.size(); i++) {
        if (old_phi->outs[i].node == new_phi || old_phi->outs[i].node == I_node) {
            old_phi->outs.erase(old_phi->outs.begin() + i);
            i--;
        }
    }
    replace_phi_out(old_phi, new_phi, I_node);
    return new_phi;
}

bool handle_phi(PHINode* phi)
{
    struct Node* n = nullptr;
    if (Instruction* I = is_loop_phi(phi)) {
        if (!I_map_Info[I].val->name.compare(0, 7, "tmp_phi")) {
            return true;
        }
        n = handle_loop_phi(phi, I);
    } else {
        n = handle_normal_phi(phi);
    }
    I_map_Info[phi].val = n;
    return false;
}
void handle_delay_I()
{
    while (!delay_I.empty()) {
        Instruction* I = delay_I.front();
        delay_I.pop_front();
        bool delay = false;
        if (PHINode* phi = dyn_cast<PHINode>(I)) {
            delay = handle_phi(phi);
        } else {
            delay = handle_store_or_output(I);
        }
        if (delay) {
            delay_I.push_back(I);
        }
    }
}