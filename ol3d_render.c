#include "ol3d_core.h"

unsigned char render_buffer[BUFFER_SIZE] = {};
unsigned char *render_target = &render_buffer;

#define AABB_MIN(x, y, z)   (fmin((x), fmin((y), (z))))
#define AABB_MAX(x, y, z)   (fmax((x), fmax((y), (z))))
#define isLeft(_a, _b, _p)  (((_b->x-_a->x) * (_p->y-_a->y) - (_b->y-_a->y) * (_p->x-_a->x))>0)
#define COORD(x)            (SCREEN_SIZE * ((x)*0.5 + 0.5))

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

void ol3d_draw_Pixel(unsigned char *target ,const ol3d_Vector3_t *color, const unsigned int x, const unsigned int y) {
    // Color conversion
    ol3d_Vector3_t rgb = {
        .x = COLOR_CHANNEL_RANGE_R,
        .y = COLOR_CHANNEL_RANGE_G,
        .z = COLOR_CHANNEL_RANGE_B
    };
    ol3d_Vector3_t raw = ol3d_vector_dot(color, &rgb);

    // RRRRRGGG
    // GGGBBBBB
    unsigned char h = (unsigned char)raw.x<<3 | (unsigned char)raw.y>>3;
    unsigned char l = (unsigned char)raw.y<<3 | (unsigned char)raw.z;

    // Override pixel
    if((x < SCREEN_SIZE) && (y < SCREEN_SIZE) && (x >= 0) && (y >= 0)) {
        unsigned int offset = y * SCREEN_SIZE * PIXEL_SIZE + x * PIXEL_SIZE;
        target[offset]      = h;
        target[offset+1]    = l;
    }
}

void ol3d_draw_Triangle(
    unsigned char *target,
    const ol3d_Vector3_t *a,
    const ol3d_Vector3_t *b,
    const ol3d_Vector3_t *c,
    const ol3d_Vector3_t *color_a,
    const ol3d_Vector3_t *color_b,
    const ol3d_Vector3_t *color_c
) {
    ol3d_matrix_t p;
    ol3d_matrix_setPerspective(p, 30, 1.5, 1, 100);
    ol3d_Vector3_t _a = *a;
    ol3d_Vector3_t _b = *b;
    ol3d_Vector3_t _c = *c;
    ol3d_matrix_multi_v3(&_a, p);
    ol3d_matrix_multi_v3(&_b, p);
    ol3d_matrix_multi_v3(&_c, p);

    // Screen space coords
    ol3d_Vector3_t ss_A = {
        .x = COORD(_a.x),
        .y = COORD(_a.y),
        .z = COORD(_a.z)
    };

    ol3d_Vector3_t ss_B = {
        .x = COORD(_b.x),
        .y = COORD(_b.y),
        .z = COORD(_b.z)
    };

    ol3d_Vector3_t ss_C = {
        .x = COORD(_c.x),
        .y = COORD(_c.y),
        .z = COORD(_c.z)
    };

    unsigned int minX, minY, maxX, maxY;
    minX = (unsigned int)(AABB_MIN(ss_A.x, ss_B.x, ss_C.x));
    maxX = (unsigned int)(AABB_MAX(ss_A.x, ss_B.x, ss_C.x));
    minY = (unsigned int)(AABB_MIN(ss_A.y, ss_B.y, ss_C.y));
    maxY = (unsigned int)(AABB_MAX(ss_A.y, ss_B.y, ss_C.y));

    // Vertex Shader
    for(unsigned int y = minY; y < maxY; y++) {
        for(unsigned int x = minX; x < maxX; x++) {
            if(inTriangle(&ss_A, &ss_B, &ss_C, x, y)) {
                // Fragment Shader
                ol3d_draw_Pixel(target, color_a, x, y);
            }
        }
    }

}

void ol3d_clean_buffer(unsigned char *target) {
    for(unsigned int y = 0; y < SCREEN_SIZE; y++) {
		for(unsigned int x = 0; x < SCREEN_SIZE; x++) {
			*target++ = 0;
			*target++ = 0;
		}
	}
}