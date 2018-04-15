#include "ol3d_core.h"

// {
//     0, 1, 2, 3,
//     4, 5, 6, 7,
//     8, 9, 10, 11,
//     12, 13, 14, 15
// }

static const unsigned char transpose4x4[] = {
    0, 4, 8, 12,
    1, 5, 9, 13,
    2, 6, 10, 14,
    3, 7, 11, 15
};

void ol3d_matrix_setUnit(ol3d_matrix_t a) {
    ol3d_matrix_t temp = MATRIX_UNIT;
    ol3d_matrix_copy(temp, a);
}

void ol3d_matrix_setTranslate(ol3d_matrix_t a, float x, float y, float z) {
    ol3d_matrix_t temp = MATRIX_TRANSLATE(x, y, z);
    ol3d_matrix_copy(temp, a);
}

void ol3d_matrix_setScale(ol3d_matrix_t a, float x, float y, float z) {
    ol3d_matrix_t temp = MATRIX_SCALE(x, y, z);
    ol3d_matrix_copy(temp, a);
}

void ol3d_matrix_setRotate(ol3d_matrix_t a, float angle, unsigned char axis) {
    if(angle) {
        if(axis == M_AXIS_X) {
            ol3d_matrix_t temp = MATRIX_ROTATE_X(angle);
            ol3d_matrix_copy(temp, a);
        } else if(axis == M_AXIS_Y) {
            ol3d_matrix_t temp = MATRIX_ROTATE_Y(angle);
            ol3d_matrix_copy(temp, a);
        } else if(axis == M_AXIS_Z) {
            ol3d_matrix_t temp = MATRIX_ROTATE_Z(angle);
            ol3d_matrix_copy(temp, a);
        }
    }
}

void ol3d_matrix_setPerspective(ol3d_matrix_t a, double fov, double aspect, double near, double far) {
    double cot  = tan(fov/2);
    double rd   = 1 / (far - near);
    ol3d_matrix_t p = {
        cot/aspect, 0, 0, 0,
        0, cot, 0, 0,
        0, 0, -(far+near)*rd, -1,
        0, 0, -2*far*near*rd, 0
    };
    ol3d_matrix_copy(p, a);
}


void ol3d_matrix_copy(ol3d_matrix_t a, ol3d_matrix_t b) {
    for(unsigned char i = 0; i < 0x10; i++) {
        b[i] = a[i];
    }
}

void ol3d_matrix_transpose(ol3d_matrix_t a) {
    ol3d_matrix_t temp;
    ol3d_matrix_copy(temp, a);
    for(unsigned char i = 0; i < 0x10; i++) {
        a[i] = temp[transpose4x4[i]];
    }
}

// 牺牲空间, 换取时间 - 代替(i/4)
static const unsigned char rowOf[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    2, 2, 2, 2,
    3, 3, 3, 3
};

float ol3d_matrix_multi_chunk(ol3d_matrix_t a, ol3d_matrix_t b, unsigned char pos) {
    unsigned char row       = transpose4x4[rowOf[pos]];
    unsigned char column    = transpose4x4[rowOf[transpose4x4[pos]]];
    float sum = 0;
    for(unsigned char i = 0; i < 4; i++) {
        sum += a[row++] * b[transpose4x4[column++]];
    }
    return sum;
}

void ol3d_matrix_multiply(ol3d_matrix_t a, ol3d_matrix_t b, ol3d_matrix_t c) {
    for(unsigned char i = 0; i < 0x10; i++) {
        c[i] = ol3d_matrix_multi_chunk(a, b, i);
    }
}

void ol3d_matrix_translate(ol3d_matrix_t a, float x, float y, float z) {
    ol3d_matrix_t temp  = MATRIX_TRANSLATE(x, y, z); // operation
    ol3d_matrix_t _a;
    ol3d_matrix_copy(a, _a); // Backup
    ol3d_matrix_multiply(_a, temp, a);
}

void ol3d_matrix_scale(ol3d_matrix_t a, float x, float y, float z) {
    ol3d_matrix_t temp  = MATRIX_SCALE(x, y, z); // operation
    ol3d_matrix_t _a;
    ol3d_matrix_copy(a, _a); // Backup
    ol3d_matrix_multiply(_a, temp, a);
}

void ol3d_matrix_rotate(ol3d_matrix_t a, float angle, unsigned char axis) {
    ol3d_matrix_t temp;
    ol3d_matrix_setRotate(temp, angle, axis);
    ol3d_matrix_t _a;
    ol3d_matrix_copy(a, _a); // Backup
    ol3d_matrix_multiply(_a, temp, a);
}

void ol3d_matrix_multi_v3(ol3d_Vector3_t *a, ol3d_matrix_t b) {
    ol3d_matrix_t temp = {a->x, a->y, a->z, 1};
    ol3d_matrix_t result;
    for(unsigned char i = 0; i < 4; i++) {
        result[i] = ol3d_matrix_multi_chunk(temp, b, i);
    }
    a->x = result[0];
    a->y = result[1];
    a->z = result[2];
}