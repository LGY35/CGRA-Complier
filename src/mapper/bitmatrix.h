#include "utils.h"

struct Bit_Matrix {
    unsigned long* data;
    int rows;
    int cols;
    int num_byte8;
};

struct M_Pos {
    unsigned long byte8;
    int curr_col;
    int byte8_index;
    int bit_index;
    enum {MODE_FIRST, MODE_CONT} mode;
};

void set_bit(struct Bit_Matrix* matrix, int row, int col);
void rec_bit(struct Bit_Matrix* matrix, int row, int col);
int get_bit(struct Bit_Matrix* matrix, int row, int col);
struct Bit_Matrix* create_bit_matrix(int rows, int cols);
void rm_bit_matrix(struct Bit_Matrix* matrix);
int get_next_set_column(struct Bit_Matrix* matrix, int row, struct M_Pos* m_pos);
int get_tot_set_column(struct Bit_Matrix* matrix, int row);
void test_bit_matrix();
void transpos_matrix(struct Bit_Matrix* from, struct Bit_Matrix* to);