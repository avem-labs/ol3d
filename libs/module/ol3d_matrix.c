#include <ol3d_core.h>

// {
//     0, 1, 2, 3,
//     4, 5, 6, 7,
//     8, 9, 10, 11,
//     12, 13, 14, 15
// }

static unsigned char transpose4x4[] = {
    0, 4, 8, 12,
    1, 5, 9, 13,
    2, 6, 10, 14,
    3, 7, 11, 15
};

void ol3d_matrix_setUnit(ol3d_matrix_t a) {
    for(unsigned char i = 0; i < 0x10; i++) {
        if(i%5) {
            *a++ = 0;
        } else {
            *a++ = 1;
        }
    }
}

void ol3d_matrix_copy(ol3d_matrix_t a, ol3d_matrix_t b) {
    for(unsigned char i = 0; i < 0x10; i++) {
        b[i] = a[i];
    }
}

void ol3d_matrix_transpose(ol3d_matrix_t a) {
    ol3d_matrix_t temp;
    ol3d_matrix_copy(a, temp);
    for(unsigned char i = 0; i < 0x10; i++) {
        a[i] = temp[transpose4x4[i]];
    }
}