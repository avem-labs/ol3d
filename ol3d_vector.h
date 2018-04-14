#ifndef _OL3D_VECTOR_H_
#define _OL3D_VECTOR_H_

typedef struct {
    double x;
    double y;
    double z;
} ol3d_Vector3_t;

extern ol3d_Vector3_t   ol3d_vector_dot(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b);
extern double           ol3d_vector_length(const ol3d_Vector3_t *a);
extern ol3d_Vector3_t   ol3d_vector_normalize(const ol3d_Vector3_t *a);
extern ol3d_Vector3_t   ol3d_vector_add(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b);
extern ol3d_Vector3_t   ol3d_vector_subtract(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b);
extern ol3d_Vector3_t   ol3d_vector_multiply(const ol3d_Vector3_t *a, float b);
extern ol3d_Vector3_t   ol3d_vector_divide(const ol3d_Vector3_t *a, float b);
extern ol3d_Vector3_t   ol3d_vector_cross(const ol3d_Vector3_t *a, const ol3d_Vector3_t *b);

#endif