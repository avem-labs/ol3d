#include "ol3d_core.h"


ol3d_buffer_t render_buffer = {};

ol3d_buffer_t *render_target = &render_buffer;

#define AABB_MIN(x, y, z)   (fmin((x), fmin((y), (z))))
#define AABB_MAX(x, y, z)   (fmax((x), fmax((y), (z))))
#define isLeft(_a, _b, _p)  (((_b->x-_a->x) * (_p->y-_a->y) - (_b->y-_a->y) * (_p->x-_a->x))>0)
#define COORD(x)            (BUFFER_SIZE * ((x) + 1.0) * 0.5)

static unsigned char inTriangle(
    ol3d_Vector3_t *a,
    ol3d_Vector3_t *b,
    ol3d_Vector3_t *c,
    unsigned int    x,
    unsigned int    y
) {
    ol3d_Vector3_t p = {
        .x = x,
        .y = y
    };

    if(isLeft(a, b, (&p)) != isLeft(b, c, (&p)))
        return 0;
    if(isLeft(a, b, (&p)) != isLeft(c, a, (&p)))
        return 0;
    return 1;
}

void ol3d_draw_Triangle(
    ol3d_buffer_t target,
    ol3d_Vector3_t *a,
    ol3d_Vector3_t *b,
    ol3d_Vector3_t *c,
    ol3d_Vector3_t *color_a,
    ol3d_Vector3_t *color_b,
    ol3d_Vector3_t *color_c
) {
    // Screen space coords
    ol3d_Vector3_t ss_A = {
        .x = COORD(a->x),
        .y = COORD(-a->y),
        .z = COORD(a->z)
    };

    ol3d_Vector3_t ss_B = {
        .x = COORD(b->x),
        .y = COORD(-b->y),
        .z = COORD(b->z)
    };

    ol3d_Vector3_t ss_C = {
        .x = COORD(c->x),
        .y = COORD(-c->y),
        .z = COORD(c->z)
    };

    unsigned int minX, minY, maxX, maxY;
    minX = (unsigned int)(AABB_MIN(ss_A.x, ss_B.x, ss_C.x));
    maxX = (unsigned int)(AABB_MAX(ss_A.x, ss_B.x, ss_C.x));
    minY = (unsigned int)(AABB_MIN(ss_A.y, ss_B.y, ss_C.y));
    maxY = (unsigned int)(AABB_MAX(ss_A.y, ss_B.y, ss_C.y));


    for(unsigned int y = minY; y < maxY; y++) {
        for(unsigned int x = minX; x < maxX; x++) {
            if(inTriangle(&ss_A, &ss_B, &ss_C, x, y)) {
                // Shader
                target[x][y] = 0xFF;
            }
        }
    }

}

void ol3d_clean_buffer(ol3d_buffer_t target) {
    for(unsigned int y = 0; y < BUFFER_SIZE; y++) {
		for(unsigned int x = 0; x < BUFFER_SIZE; x++) {
			target[x][y] = 0;
		}
	}
}