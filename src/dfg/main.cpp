#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/CommandLine.h"

#include <cstdlib>
#include <string>

#include "utils.h"
#include "visitor.h"
#include "spec_i.h"
#include "output.h"
#include "passes.h"

#include <iostream>  
#include <ostream>   

using namespace llvm;

const llvm::DataLayout* dl = nullptr; 
BasicBlock* preheader = nullptr;
Loop* target_L = nullptr;

cl::opt<std::string> input_filename(cl::Positional, cl::Required, cl::desc("<input file>"));
static cl::opt<std::string> output_filename("o",cl::desc("Specify output filename"), cl::value_desc("filename"));

// void debug_delay_queue() {
//     std::cout << "Delay Queue:" << std::endl;
//     for (Instruction* I : delay_I) {
//         I->print(errs());
//         std::cout << std::endl;
//     }
// }


int main(int argc, char **argv)
{
    cl::ParseCommandLineOptions(argc, argv);

    std::string output_file =  output_filename;
    if (!output_filename.size()) {
        output_file = input_filename;
    }
    
    LLVMContext CurrContext;
    SMDiagnostic Err;
    std::unique_ptr<Module> mod = parseIRFile(StringRef(input_filename.c_str()), Err, CurrContext); //读取LLVM IR的文件
    dl = &(mod->getDataLayout());

    // mod->print(errs(), nullptr);
    int loop_cnt = 0;
    for (Function &fn : *mod) {
        if (!fn.isDeclaration()) {
            // fn.print(errs());
            //get the dominatortree of the current function
            DominatorTree* DT = new DominatorTree();         
            DT->recalculate(fn);
            LoopInfoBase<BasicBlock, Loop>* LoopInfo = new LoopInfoBase<BasicBlock, Loop>();
            LoopInfo->releaseMemory();
            LoopInfo->analyze(*DT);
            loop_cnt = LoopInfo->getTopLevelLoops().size() - 1;
            // Iterate over the loops in the function
            for (Loop *L : LoopInfo->getTopLevelLoops()) {      //对于LLVM IR，提取Loop
                L->print(errs());
                target_L = L;
                preheader = L->getHeader();
                un_condi_BB.insert(preheader);
                if (get_num_preds(preheader, true) != 1) {
                    printf("Has more than 1 exiting block");
                    exit(1);
                }
                for (BasicBlock *pred : predecessors(preheader)) {
                    if (is_loop_BB(pred)) {
                        un_condi_BB.insert(pred);
                        break;
                    }
                }
                visitBB(preheader, nullptr);            //遍历loop，生成operator
                handle_delay_I();
                // debug_delay_queue();
                run_all_passes();                       //跑pass。消除无用节点，进行调度
                output_dot(output_file + "_loop_" + itostr(loop_cnt) + ".dot"); // .dot文件内部就是调度图，route为节点，然后下面是边
                clean_all_struct();
                loop_cnt--;
            }
        }
    }

    return 0;
}
