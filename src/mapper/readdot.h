#include "utils.h"

struct Graph* read_dot(char* filename, int scheduled); 
void output_dot(struct Graph* dfg, char* filename);
void clear_dot();