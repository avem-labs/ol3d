#include <ol3d_core.h>


ol3d_buffer_t render_buffer = {};

ol3d_buffer_t *render_target = &render_buffer;

#define AABB_MIN(x, y, z)   (fmin((x), fmin((y), (z))))
#define AABB_MAX(x, y, z)   (fmax((x), fmax((y), (z))))
#define isLeft(_a, _b, _p)  (((_b->x-_a->x) * (_p->y-_a->y) - (_b->y-_a->y) * (_p->x-_a->x))>0)
#define _UV(x)             (BUFFER_SIZE * ((x) + 1.0) * 0.5)
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

    if(isLeft(a, b, (&p)) != isLeft(b, c, (&p))) {
        return 0;
    }
    if(isLeft(a, b, (&p)) != isLeft(c, a, (&p))) {
        return 0;
    }
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
    unsigned int minX, minY, maxX, maxY;
    minX = (unsigned int)(BUFFER_SIZE * (AABB_MIN(a->x, b->x, c->x) + 1.0) * 0.5);
    maxX = (unsigned int)(BUFFER_SIZE * (AABB_MAX(a->x, b->x, c->x) + 1.0) * 0.5);
    minY = (unsigned int)(BUFFER_SIZE * (AABB_MIN(a->y, b->y, c->y) + 1.0) * 0.5);
    maxY = (unsigned int)(BUFFER_SIZE * (AABB_MAX(a->y, b->y, c->y) + 1.0) * 0.5);

    a->x = _UV(a->x);
    a->y = _UV(-a->y);
    a->z = _UV(a->z);

    b->x = _UV(b->x);
    b->y = _UV(-b->y);
    b->z = _UV(b->z);

    c->x = _UV(c->x);
    c->y = _UV(-c->y);
    c->z = _UV(c->z);

    for(unsigned int y = minY; y < maxY; y++) {
        for(unsigned int x = minX; x < maxX; x++) {
            if(inTriangle(a, b, c, x, y) == 1) {
                target[x][y] = 1;
            }
        }
    }

}
