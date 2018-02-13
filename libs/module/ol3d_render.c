#include <ol3d_core.h>


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
    a->x = COORD(a->x);
    a->y = COORD(-a->y);
    a->z = COORD(a->z);

    b->x = COORD(b->x);
    b->y = COORD(-b->y);
    b->z = COORD(b->z);

    c->x = COORD(c->x);
    c->y = COORD(-c->y);
    c->z = COORD(c->z);

    unsigned int minX, minY, maxX, maxY;
    minX = (unsigned int)(AABB_MIN(a->x, b->x, c->x));
    maxX = (unsigned int)(AABB_MAX(a->x, b->x, c->x));
    minY = (unsigned int)(AABB_MIN(a->y, b->y, c->y));
    maxY = (unsigned int)(AABB_MAX(a->y, b->y, c->y));


    for(unsigned int y = minY; y < maxY; y++) {
        for(unsigned int x = minX; x < maxX; x++) {
            if(inTriangle(a, b, c, x, y)) {
                target[x][y] = 1;
            }
        }
    }

}
