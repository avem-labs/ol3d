#include <ol3d_core.h>

// dot product
ol3d_Vector3_t ol3d_vector_dot(ol3d_Vector3_t *a, ol3d_Vector3_t *b) {
    return (ol3d_Vector3_t){
        .x = a->x * b->x,
        .y = a->y * b->y,
        .z = a->z * b->z
    };
}

float ol3d_vector_length(ol3d_Vector3_t *a) {
    ol3d_Vector3_t temp = ol3d_vector_dot(a, a);
    return (float)sqrt(temp.x + temp.y + temp.z);
}

ol3d_Vector3_t ol3d_vector_normalize(ol3d_Vector3_t *a) {
    return ol3d_vector_divide(a, ol3d_vector_length(a));
}

ol3d_Vector3_t ol3d_vector_add(ol3d_Vector3_t *a, ol3d_Vector3_t *b) {
    return (ol3d_Vector3_t) {
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
}

ol3d_Vector3_t ol3d_vector_subtract(ol3d_Vector3_t *a, ol3d_Vector3_t *b) {
    return (ol3d_Vector3_t) {
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };
}

ol3d_Vector3_t ol3d_vector_multiply(ol3d_Vector3_t *a, float b) {
    return (ol3d_Vector3_t) {
        .x = a->x * b,
        .y = a->y * b,
        .z = a->z * b
    };
}

ol3d_Vector3_t ol3d_vector_divide(ol3d_Vector3_t *a, float b) {
    return (ol3d_Vector3_t) {
        .x = a->x / b,
        .y = a->y / b,
        .z = a->z / b
    };
}

// cross product
ol3d_Vector3_t ol3d_vector_cross(ol3d_Vector3_t *a, ol3d_Vector3_t *b, ol3d_Vector3_t *o) {
    ol3d_Vector3_t temp;
    return temp;
}
