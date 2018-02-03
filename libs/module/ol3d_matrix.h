#ifndef _OL3D_MATRIX_H_
#define _OL3D_MATRIX_H_

// 4x4 matrix
typedef float ol3d_matrix_t[16];

#define PI          3.14
#define R(angle)    ((angle) * PI/180)

#define MATRIX_UNIT {\
    1, 0, 0, 0,\
    0, 1, 0, 0,\
    0, 0, 1, 0,\
    0, 0, 0, 1 \
}
#define MATRIX_TRANSLATE(x, y, z) {\
    1, 0, 0, 0,\
    0, 1, 0, 0,\
    0, 0, 1, 0,\
    (x), (y), (z), 1 \
}

#define MATRIX_SCALE(x, y, z) {\
    (x), 0, 0, 0,\
    0, (y), 0, 0,\
    0, 0, (z), 0,\
    0, 0, 0, 1 \
}

#define MATRIX_ROTATE_X(a) {\
    1, 0, 0, 0,\
    0, cos(a), sin(a), 0,\
    0, -sin(a), cos(a), 0,\
    0, 0, 0, 1 \
}

#define MATRIX_ROTATE_Y(a) {\
    cos(a), 0, sin(a), 0,\
    0, 1, 0, 0,\
    -sin(a), 0, cos(a), 0,\
    0, 0, 0, 1 \
}

#define MATRIX_ROTATE_Z(a) {\
    cos(a), sin(a), 0, 0,\
    -sin(a), cos(a), 0, 0,\
    0, 0, 1, 0,\
    0, 0, 0, 1 \
}

#define M_AXIS_X    0x0001
#define M_AXIS_Y    0x0002
#define M_AXIS_Z    0x0004

extern void     ol3d_matrix_setUnit(ol3d_matrix_t a);
extern void     ol3d_matrix_setTranslate(ol3d_matrix_t a, float x, float y, float z);
extern void     ol3d_matrix_setScale(ol3d_matrix_t a, float x, float y, float z);
extern void     ol3d_matrix_setRotate( ol3d_matrix_t a, float angle, unsigned char axis);
extern void     ol3d_matrix_copy(ol3d_matrix_t a, ol3d_matrix_t b);
extern void     ol3d_matrix_transpose(ol3d_matrix_t a);
extern float    ol3d_matrix_multi_chunk(ol3d_matrix_t a, ol3d_matrix_t b, unsigned char pos);
extern void     ol3d_matrix_multiply(ol3d_matrix_t a, ol3d_matrix_t b, ol3d_matrix_t c);
extern void     ol3d_matrix_translate(ol3d_matrix_t a, float x, float y, float z);
extern void     ol3d_matrix_scale(ol3d_matrix_t a, float x, float y, float z);
extern void     ol3d_matrix_rotate(ol3d_matrix_t a, float angle, unsigned char axis);

#endif