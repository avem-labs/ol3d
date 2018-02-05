#ifndef _OL3D_VECTOR_H_
#define _OL3D_VECTOR_H_

typedef struct {
    double x;
    double y;
    double z;
} ol3d_Vector3_t;

extern ol3d_Vector3_t   ol3d_vector_dot(ol3d_Vector3_t *a, ol3d_Vector3_t *b);
extern double           ol3d_vector_length(ol3d_Vector3_t *a);
extern ol3d_Vector3_t   ol3d_vector_normalize(ol3d_Vector3_t *a);
extern ol3d_Vector3_t   ol3d_vector_add(ol3d_Vector3_t *a, ol3d_Vector3_t *b);
extern ol3d_Vector3_t   ol3d_vector_subtract(ol3d_Vector3_t *a, ol3d_Vector3_t *b);
extern ol3d_Vector3_t   ol3d_vector_multiply(ol3d_Vector3_t *a, float b);
extern ol3d_Vector3_t   ol3d_vector_divide(ol3d_Vector3_t *a, float b);
extern ol3d_Vector3_t   ol3d_vector_cross(ol3d_Vector3_t *a, ol3d_Vector3_t *b, ol3d_Vector3_t *o);


#endif