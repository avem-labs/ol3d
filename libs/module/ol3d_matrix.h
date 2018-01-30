#ifndef _OL3D_MATRIX_H_
#define _OL3D_MATRIX_H_

// 4x4 matrix
typedef float ol3d_matrix_t[16];

#define MATRIX_UNIT     {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}

extern void ol3d_matrix_setUnit(ol3d_matrix_t a);
extern void ol3d_matrix_copy(ol3d_matrix_t a, ol3d_matrix_t b);
extern void ol3d_matrix_transpose(ol3d_matrix_t a);

#endif