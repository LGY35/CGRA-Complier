#include "bitmatrix.h"
#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"

#define CELL_BIT_POW 6
#define CELL_BIT_LEN (1 << CELL_BIT_POW)
#define BIT_OFFSET_MASK (CELL_BIT_LEN - 1)

void set_bit(struct Bit_Matrix* matrix, int row, int col)
{
    int index = row * matrix->cols + col;
    int byte8_index = index >> CELL_BIT_POW;    // same as division by 64
    int bit_index = index & BIT_OFFSET_MASK;     // same as mod 64

    matrix->data[byte8_index] |= 1UL << bit_index;
}

void rec_bit(struct Bit_Matrix* matrix, int row, int col)
{
    int index = row * matrix->cols + col;
    int byte8_index = index >> CELL_BIT_POW;    // same as division by 64
    int bit_index = index & BIT_OFFSET_MASK;     // same as mod 64

    matrix->data[byte8_index] &= ~(1UL << bit_index);
}

int get_bit(struct Bit_Matrix* matrix, int row, int col)
{
    int index = row * matrix->cols + col;
    int byte8_index = index >> CELL_BIT_POW;    // same as division by 64
    int bit_index = index & BIT_OFFSET_MASK;     // same as mod 64

    return (matrix->data[byte8_index] >> bit_index) & 1;
}

struct Bit_Matrix* create_bit_matrix(int rows, int cols)
{
    struct Bit_Matrix* matrix = rpmalloc(sizeof(struct Bit_Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->num_byte8 = (rows * cols + BIT_OFFSET_MASK) >> CELL_BIT_POW;
    matrix->data = rpmalloc(matrix->num_byte8 * sizeof(unsigned long));
    memset(matrix->data, 0, matrix->num_byte8 * sizeof(unsigned long));

    return matrix;
}

void rm_bit_matrix(struct Bit_Matrix* matrix)
{
    rpfree(matrix->data);
    rpfree(matrix);
}

void transpos_matrix(struct Bit_Matrix* from, struct Bit_Matrix* to)
{
    assert((from->rows == to->cols) && (from->cols == to->rows));
    memset(to->data, 0, to->num_byte8 * sizeof(unsigned long));
    for (int x = 0; x < from->cols; x++) {
        for (int y = 0; y < from->rows; y++) {
            if (get_bit(from, y, x)) {
                set_bit(to, x, y);
            }
        }
    }
}

int get_tot_set_column(struct Bit_Matrix* matrix, int row)
{
    int index = row * matrix->cols;
    int byte_offset = index >> CELL_BIT_POW;
    int bit_offset = index & BIT_OFFSET_MASK;
    int col_left = matrix->cols;
    int col_overflow;
    int set_cnt = 0;
    unsigned long byte8;

    col_left -= CELL_BIT_LEN - bit_offset;
    col_overflow = col_left < 0 ? -col_left : 0;
    byte8 = (matrix->data[byte_offset] << col_overflow) >> (bit_offset + col_overflow);
    set_cnt += __builtin_popcountll(byte8);
    byte_offset++;

    while (col_left > 0) {
        col_left -= CELL_BIT_LEN;
        col_overflow = col_left < 0 ? -col_left : 0;
        byte8 = (matrix->data[byte_offset] << col_overflow) >> col_overflow;
        set_cnt += __builtin_popcountll(byte8);
        byte_offset++;
    }

    return set_cnt;
}

int get_next_set_column(struct Bit_Matrix* matrix, int row, struct M_Pos* m_pos) 
{
    int result = IN_VALID;
    assert(row >= 0 && row < matrix->rows);

    if (m_pos->mode == MODE_CONT) {
        m_pos->curr_col++;

        if (m_pos->bit_index == BIT_OFFSET_MASK) {
            m_pos->bit_index = 0;
            m_pos->byte8_index++;
            if (m_pos->byte8_index >= matrix->num_byte8) {
                return IN_VALID; // no more set columns in row
            }
            m_pos->byte8 = matrix->data[m_pos->byte8_index];
        } else {
            m_pos->bit_index++;
            m_pos->byte8 >>= 1;
        }
    } else if (m_pos->mode == MODE_FIRST) {
        int index = row * matrix->cols;
        m_pos->byte8_index = index >> CELL_BIT_POW;
        m_pos->bit_index = index & BIT_OFFSET_MASK;

        m_pos->byte8 = matrix->data[m_pos->byte8_index];
        m_pos->byte8 >>= m_pos->bit_index;
        m_pos->curr_col = 0;
    } else {
        printf("unrecognized mode %d", m_pos->mode);
        exit(1);
    }

    if (m_pos->byte8) {
        result = __builtin_ctzll(m_pos->byte8);
        m_pos->byte8 >>= result;
        m_pos->curr_col += result;
        if (m_pos->curr_col >= matrix->cols) {
            return IN_VALID;
        }
        m_pos->bit_index += result;
        return m_pos->curr_col;
    }

    m_pos->curr_col += (CELL_BIT_LEN - m_pos->bit_index);
    m_pos->bit_index = 0;

    while (m_pos->curr_col < matrix->cols) {
        m_pos->byte8_index++;
        m_pos->byte8 = matrix->data[m_pos->byte8_index];
        if (m_pos->byte8) {
            result = __builtin_ctzll(m_pos->byte8);
            m_pos->byte8 >>= result;
            m_pos->curr_col += result;
            if (m_pos->curr_col >= matrix->cols) {
                return IN_VALID;
            }
            m_pos->bit_index += result;
            return m_pos->curr_col;
        }
        m_pos->curr_col += CELL_BIT_LEN;
        m_pos->bit_index = 0;
    }

    return IN_VALID;  // no more set columns in row
}

void test_bit_matrix()
{
    #define ROW 28
    #define COL 547
    for (int i = 0; i < 100; i++) {
        // Test matrix
        struct Bit_Matrix* matrix = create_bit_matrix(ROW, COL);
        int num_set = rand() % (COL * ROW);
        int set_pos[ROW][COL] = {{0}};
        int row_cnt[ROW] = {0};
        for (int j = 0; j < num_set; j++) {
            int col = rand() % COL;
            int row = rand() % ROW;
            set_bit(matrix, row, col);
            if (!set_pos[row][col]) {
                row_cnt[row]++;
            }
            set_pos[row][col] = 1;
        }
        for (int x = 0; x < COL; x++) {
            for (int y = 0; y < ROW; y++) {
                if (get_bit(matrix, y, x) != set_pos[y][x]) {
                    printf("error\n");
                } 
            }
        }
        for (int y = 0; y < ROW; y++) {
            struct M_Pos m_pos;
            m_pos.mode = MODE_FIRST;
            int set_col = get_next_set_column(matrix, y, &m_pos);
            m_pos.mode = MODE_CONT;
            while (set_col != -1) {
                if (set_pos[y][set_col] != 1) {
                    printf("error\n");
                }
                set_pos[y][set_col] = -1;
                set_col = get_next_set_column(matrix, y, &m_pos);
            }    
        }
        for (int x = 0; x < COL; x++) {
            for (int y = 0; y < ROW; y++) {
                if (0 != set_pos[y][x] && -1 != set_pos[y][x]) {
                    printf("error\n");
                } 
            }
        }
        for (int y = 0; y < ROW; y++) {
            if (get_tot_set_column(matrix, y) != row_cnt[y]) {
                printf("error\n");
            }
        }
        //test transpose
        struct Bit_Matrix* matrix_trans = create_bit_matrix(COL, ROW);
        int set_pos_trans[COL][ROW] = {{0}};
        int row_cnt_trans[COL] = {0};
        transpos_matrix(matrix, matrix_trans);
        for (int x = 0; x < COL; x++) {
            for (int y = 0; y < ROW; y++) {
                if (set_pos[y][x]) {
                    set_pos_trans[x][y] = 1;
                    row_cnt_trans[x]++;
                }
            }
        }
        for (int x = 0; x < ROW; x++) {
            for (int y = 0; y < COL; y++) {
                if (get_bit(matrix_trans, y, x) != set_pos_trans[y][x]) {
                    printf("error\n");
                } 
            }
        }
        for (int y = 0; y < COL; y++) {
            struct M_Pos m_pos;
            m_pos.mode = MODE_FIRST;
            int set_col = get_next_set_column(matrix_trans, y, &m_pos);
            m_pos.mode = MODE_CONT;
            while (set_col != -1) {
                if (set_pos_trans[y][set_col] != 1) {
                    printf("error\n");
                }
                set_pos_trans[y][set_col] = -1;
                set_col = get_next_set_column(matrix_trans, y, &m_pos);
            }    
        }
        for (int x = 0; x < ROW; x++) {
            for (int y = 0; y < COL; y++) {
                if (0 != set_pos_trans[y][x] && -1 != set_pos_trans[y][x]) {
                    printf("error\n");
                } 
            }
        }
        for (int y = 0; y < COL; y++) {
            if (get_tot_set_column(matrix_trans, y) != row_cnt_trans[y]) {
                printf("error\n");
            }
        }
        rm_bit_matrix(matrix);
        rm_bit_matrix(matrix_trans);
    }
}