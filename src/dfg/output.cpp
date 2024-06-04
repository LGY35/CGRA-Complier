#include "output.h"
#include <stdio.h>

void output_dot(std::string filename)
{
    FILE * file = fopen(filename.c_str(), "w");
    fprintf(file, "digraph G {\n");
    for (struct Node* n : all_nodes) {
        fprintf(file,"\t%s[opcode=%s", n->name.c_str(), op_string[n->op]);
        if (n->val != -1 || (n->val == -1 && n->llvm_name == "-1")) {
            fprintf(file,", val=%ld", n->val);
        } else if (n->llvm_name.size()) {
            fprintf(file,", llvm=\"%s\"", n->llvm_name.c_str());
        }
        if (n->schedule != IN_VALID) {
            fprintf(file,", schedule=%d", n->schedule);
        }
        fprintf(file,"]\n");
    }
    for (struct Node* n : all_nodes) {
        for (struct In_Conn in : n->ins) {
            fprintf(file,"\t%s->%s[", in.node->name.c_str(), n->name.c_str());
            if (in.attr != Edge_Attr::ATTR_IN_VALID) {
                switch (in.attr) {
                    case Edge_Attr::ATTR_CONST:
                        fprintf(file, "operand=%d", in.operand);
                        break; // Auto detected by read dot
                    case Edge_Attr::ATTR_CONST_BASE:
                        fprintf(file, "operand=%d, type=const_base", in.operand);
                        break;
                    case Edge_Attr::ATTR_ORDER:
                        fprintf(file, "operand=-1, type=order");
                        break;
                    case Edge_Attr::ATTR_REV:
                        fprintf(file, "operand=%d, type=rev", in.operand);
                        break;
                    default:
                        printf("unknown edge attribute type!\n");
                        exit(1);
                }
            } else {
                fprintf(file, "operand=%d", in.operand);
            }
            fprintf(file,"]\n");
        }
    }
    fprintf(file, "}");
    fclose(file);
}