#include "ol3d_core.h"

#define ENABLE_DEPTH
// AABB box
#define AABB_MIN(x, y, z)   (fmin((x), fmin((y), (z))))
#define AABB_MAX(x, y, z)   (fmax((x), fmax((y), (z))))

#define isLeft(_a, _b, _px, _py)    (((_b.x-_a.x) * (_py-_a.y) - (_b.y-_a.y) * (_px-_a.x))>0)
#define inTriangle(a, b, c, x, y)   ((isLeft(a, b, x, y) == isLeft(b, c, x, y)) && (isLeft(a, b, x, y) == isLeft(c, a, x, y)))

#define COORD(x)            (SCREEN_SIZE * ((x)*0.5 + 0.5))

#ifdef ENABLE_DEPTH
static unsigned char ol3d_render_Zbuffer[SCREEN_SIZE*SCREEN_SIZE] = {};
#endif

void ol3d_draw_Pixel(unsigned char *target ,const ol3d_Vector3_t *color, const unsigned int x, const unsigned int y, const unsigned char z) {
    // Color conversion
    ol3d_Vector3_t rgb = {
        .x = COLOR_CHANNEL_RANGE_R,
        .y = COLOR_CHANNEL_RANGE_G,
        .z = COLOR_CHANNEL_RANGE_B
    };
    ol3d_Vector3_t raw = ol3d_vector_dot(color, &rgb);

    // Override pixel
    if((x < SCREEN_SIZE) && (y < SCREEN_SIZE) && (x >= 0) && (y >= 0)) {
        unsigned int offset = y * SCREEN_SIZE * PIXEL_SIZE + x * PIXEL_SIZE;
#ifdef ENABLE_DEPTH
        unsigned int zoffset = y * SCREEN_SIZE + x;
        if(z >= ol3d_render_Zbuffer[zoffset]) {
#endif

#ifdef BLEND_MODE
            target[offset]      |= (unsigned char)raw.x;
            target[offset+1]    |= (unsigned char)raw.y;
            target[offset+2]    |= (unsigned char)raw.z;
#else
            target[offset]      = (unsigned char)raw.x;
            target[offset+1]    = (unsigned char)raw.y;
            target[offset+2]    = (unsigned char)raw.z;
#endif

#ifdef ENABLE_DEPTH
            ol3d_render_Zbuffer[zoffset] = z;
        }
#endif
    }
}

// Flat Shading
void ol3d_draw_Triangle(
    unsigned char *target,
    const ol3d_Vector3_t *a,
    const ol3d_Vector3_t *b,
    const ol3d_Vector3_t *c,
    const ol3d_Vector3_t *color
) {
    // Screen space coords
    ol3d_Vector3_t ss_A = {
        .x = COORD(a->x),
        .y = COORD(a->y),
        .z = COORD(a->z)
    };

    ol3d_Vector3_t ss_B = {
        .x = COORD(b->x),
        .y = COORD(b->y),
        .z = COORD(b->z)
    };

    ol3d_Vector3_t ss_C = {
        .x = COORD(c->x),
        .y = COORD(c->y),
        .z = COORD(c->z)
    };

    unsigned int minX, minY, maxX, maxY;
    minX = (unsigned int)(AABB_MIN(ss_A.x, ss_B.x, ss_C.x));
    maxX = (unsigned int)(AABB_MAX(ss_A.x, ss_B.x, ss_C.x));
    minY = (unsigned int)(AABB_MIN(ss_A.y, ss_B.y, ss_C.y));
    maxY = (unsigned int)(AABB_MAX(ss_A.y, ss_B.y, ss_C.y));
#ifdef ENABLE_DEPTH
    unsigned char z = (unsigned int)(AABB_MAX(ss_A.z, ss_B.z, ss_C.z));
#endif

    for(unsigned int y = minY; y < maxY; y++) {
        for(unsigned int x = minX; x < maxX; x++) {
            if(inTriangle(ss_A, ss_B, ss_C, x, y)) {
                // Fragment Shader
#ifdef ENABLE_DEPTH
                ol3d_draw_Pixel(target, color, x, y, z);
#else
                ol3d_draw_Pixel(target, color, x, y, 0);
#endif
            }
        }
    }

}

void ol3d_clean_buffer(unsigned char *target) {
#ifdef ENABLE_DEPTH
    unsigned char *zbuf = ol3d_render_Zbuffer;
#endif
    for(unsigned int y = 0; y < SCREEN_SIZE; y++) {
		for(unsigned int x = 0; x < SCREEN_SIZE; x++) {
			*target++ = 0;
			*target++ = 0;
			*target++ = 0;
#ifdef ENABLE_DEPTH
            *zbuf++ = 0;
#endif
		}
	}
}

void ol3d_draw_Element(unsigned char *target, long *f, double *v, double *n, unsigned int len, ol3d_matrix_t vs) {
    while((*f)!=0) {
        // Line number start from 1
        // Array offset start from 0
        ol3d_Vector3_t color;
        ol3d_Vector3_t a = ((ol3d_Vector3_t *)v)[((ol3d_obj_face *)f)->v1-1];
        color.x = a.z * 1000;
        ol3d_matrix_multi_v3(&a, vs);
        ol3d_Vector3_t b = ((ol3d_Vector3_t *)v)[((ol3d_obj_face *)f)->v2-1];
        color.y = b.z * 1000;
        ol3d_matrix_multi_v3(&b, vs);
        ol3d_Vector3_t c = ((ol3d_Vector3_t *)v)[((ol3d_obj_face *)f)->v3-1];
        color.z = c.z * 1000;
        ol3d_matrix_multi_v3(&c, vs);
        f = ((ol3d_obj_face *)f) + 1;

        ol3d_draw_Triangle(target, &a, &b, &c, &color);
    }

}