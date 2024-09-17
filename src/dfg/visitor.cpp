#include "visitor.h"
#include "llvm/Analysis/CFG.h"

using namespace llvm;

std::map<BasicBlock*, BB_Info> BB_map_Info;
std::set<BasicBlock*> un_condi_BB;
std::map<Instruction*, struct Inst_Info> I_map_Info;
std::list<Instruction*> delay_I;
std::vector<struct Node*> store_stack;
std::map<Value*, struct Node*> V_map_Node;
std::map<int, struct Node*> C_map_Node;
std::vector<struct Node*> all_nodes;

void visitBB(BasicBlock *BB, struct Node *cond)
{
    // collect conditions
    BB_map_Info[BB].visit_cnt++;
    if (BB_map_Info[BB].num_preds == -1) {
        BB_map_Info[BB].num_preds = get_num_preds(BB, true);
    }
    if (!un_condi_BB.count(BB)) {
        if (BB_map_Info[BB].cond == NULL) {
            BB_map_Info[BB].cond = cond;
        } else {
            BB_map_Info[BB].cond = create_node(OP_ID::ID_OR, "", {cond, BB_map_Info[BB].cond});
        }
    }
    if (BB_map_Info[BB].visit_cnt < BB_map_Info[BB].num_preds) {
        return;
    }

    // errs() << "Visiting BB: ";
    // BB->print(errs());
    // errs() << "\n";

    // visit instructions
    Instruction *I = NULL;
    std::vector<struct Node *> store_nodes;
    for(Instruction & i : *BB) {
        I = &i;
        if (I->getOpcode() == Instruction::Br || I->getOpcode() == Instruction::Switch) {
            continue;
        } else if (I->getOpcode() == Instruction::PHI) {
            I_map_Info[I].val = create_tmp_phi_node(I);
            delay_I.push_back(I);
        } else if (I->getOpcode() == Instruction::Store) {
            I_map_Info[I].val = find_or_create_I_node(I);
            store_nodes.push_back(I_map_Info[I].val);
            delay_I.push_back(I);
        } else {
            I_map_Info[I].val = find_or_create_I_node(I);
            if (is_output(I)) {
                I_map_Info[I].output_addr = get_output_addr(I);
                I_map_Info[I].output_store = create_node(OP_ID::ID_STORE, "", {I_map_Info[I].output_addr, I_map_Info[I].val});
                store_nodes.push_back(I_map_Info[I].output_store);
                delay_I.push_back(I);
            }
        }
    }

    // visit next BB
    if (BranchInst *br = dyn_cast<BranchInst>(I)) {
        // handle store order
        for (int i = 0; i < store_nodes.size(); i++) {
            for (int j = 0; j < store_stack.size(); j++) {
                add_out_edge(store_stack[j], store_nodes[i], Edge_Attr::ATTR_ORDER);
            }
            store_stack.push_back(store_nodes[i]);
        }
        if (br->isUnconditional()) {
            if (BasicBlock *next_BB = dyn_cast<BasicBlock>(I->getOperand(0))) {
                if (next_BB != preheader && is_loop_BB(next_BB)) {
                    if (un_condi_BB.count(BB)) {
                        un_condi_BB.insert(next_BB);
                    } else {
                        BB_map_Info[BB].next_uncondi = next_BB;
                    }
                    visitBB(next_BB, cond);
                }
            } else {
                printf("first operand of unconditional br is not block");
                exit(1);
            }
        } else {
            // Conditional branch operand(0)=cond, operand(1)=false, operand(2)=true
            struct Node *br_cond = find_or_create_V_node(br->getCondition());
            if (BasicBlock *next_BB = dyn_cast<BasicBlock>(I->getOperand(2))) {
                if (next_BB != preheader && is_loop_BB(next_BB)) {
                    struct next_BB next ={
                        .BB = next_BB,
                        .cond = br_cond
                    };
                    if (cond != NULL) {
                        next.cond = create_node(OP_ID::ID_AND, "", {cond, next.cond});
                    }
                    BB_map_Info[BB].next_BBs.push_back(next);
                    visitBB(next.BB, next.cond);
                }
            } else {
                printf("second operand of conditional br is not block");
                exit(1);
            }
            if (BasicBlock *next_BB = dyn_cast<BasicBlock>(I->getOperand(1))) {
                if (next_BB != preheader && is_loop_BB(next_BB)) {
                    struct next_BB next ={
                        .BB = next_BB,
                        .cond = create_node(OP_ID::ID_NOT, "", {br_cond})
                    };
                    if (cond != NULL) {
                        next.cond = create_node(OP_ID::ID_AND, "", {cond, next.cond});
                    }
                    BB_map_Info[BB].next_BBs.push_back(next);
                    visitBB(next.BB, next.cond);
                }
            } else {
                printf("third operand of conditional br is not block");
                exit(1);
            }
        }
        // handle store order
        for (int i = 0; i < store_nodes.size(); i++) {
            store_stack.pop_back();
        }
    } else if (SwitchInst *sw = dyn_cast<SwitchInst>(I)) {
        struct Node* condition = find_or_create_V_node(sw->getCondition());
        struct Node* default_condition = nullptr;
        BasicBlock* default_BB = sw->getDefaultDest();
        bool has_default = isPotentiallyReachable(const_cast<BasicBlock*>(preheader), const_cast<BasicBlock*>(default_BB));
        for (auto caseIt = sw->case_begin(); caseIt != sw->case_end(); ++caseIt) {
            struct Node* case_value = find_or_create_V_node(caseIt->getCaseValue());
            struct Node* case_eq = create_node(OP_ID::ID_EQ, "", {condition, case_value});
            BasicBlock* case_BB = caseIt->getCaseSuccessor();
            struct next_BB next ={
                .BB = case_BB,
                .cond = case_eq
            };
            if (cond != NULL) {
                next.cond = create_node(OP_ID::ID_AND, "", {cond, case_eq});
            }
            BB_map_Info[BB].next_BBs.push_back(next);
            visitBB(next.BB, next.cond);
            if (has_default) {
                if (default_condition == nullptr) {
                    default_condition = case_eq;
                } else {
                    default_condition = create_node(OP_ID::ID_OR, "", {default_condition, case_eq});
                }
            }
        }
        if (has_default) {
            default_condition = create_node(OP_ID::ID_NOT, "", {default_condition});
            struct next_BB next ={
                .BB = default_BB,
                .cond = default_condition
            };
            visitBB(next.BB, next.cond);
        }
    } else {
        printf("last instruction of basic block is opkind: %s", I->getOpcodeName());
        exit(1);
    }
}
