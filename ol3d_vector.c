#include "ol3d_core.h"

// dot product
ol3d_Vector3_t ol3d_vector_dot(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b) {
    return (ol3d_Vector3_t){
        .x = a->x * b->x,
        .y = a->y * b->y,
        .z = a->z * b->z
    };
}

double ol3d_vector_length(const ol3d_Vector3_t *a) {
    ol3d_Vector3_t temp = ol3d_vector_dot(a, a);
    return (double)sqrt(temp.x + temp.y + temp.z);
}

ol3d_Vector3_t ol3d_vector_normalize(const ol3d_Vector3_t *a) {
    return ol3d_vector_divide(a, ol3d_vector_length(a));
}

ol3d_Vector3_t ol3d_vector_add(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b) {
    return (ol3d_Vector3_t) {
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
}

ol3d_Vector3_t ol3d_vector_subtract(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b) {
    return (ol3d_Vector3_t) {
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };
}

ol3d_Vector3_t ol3d_vector_multiply(const ol3d_Vector3_t *a, double b) {
    return (ol3d_Vector3_t) {
        .x = a->x * b,
        .y = a->y * b,
        .z = a->z * b
    };
}

ol3d_Vector3_t ol3d_vector_divide(const ol3d_Vector3_t *a, double b) {
    return (ol3d_Vector3_t) {
        .x = a->x / b,
        .y = a->y / b,
        .z = a->z / b
    };
}

// cross product
ol3d_Vector3_t ol3d_vector_cross(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b) {
    return (ol3d_Vector3_t) {
        .x = a->y * b->z - a->z * b->y,
        .y = a->z * b->x - a->x * b->z,
        .z = a->x * b->y - a->y * b->x
    };
}
