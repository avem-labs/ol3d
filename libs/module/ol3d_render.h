#ifndef _OL3D_RENDER_H_
#define _OL3D_RENDER_H_

// Screen
#define BUFFER_SIZE             128

// Format : RRRR RGGG GGGB BBBB
#define COLOR_CHANNEL_RANGE_R   31
#define COLOR_CHANNEL_RANGE_B   63
#define COLOR_CHANNEL_RANGE_G   31

typedef short ol3d_pixel_t;

typedef ol3d_pixel_t ol3d_buffer_t[BUFFER_SIZE][BUFFER_SIZE];

extern ol3d_buffer_t render_buffer;
extern ol3d_buffer_t *render_target;

extern void ol3d_draw_Triangle(ol3d_buffer_t target, ol3d_Vector3_t *a, ol3d_Vector3_t *b, ol3d_Vector3_t *c, ol3d_Vector3_t *color_a, ol3d_Vector3_t *color_b, ol3d_Vector3_t *color_c);


#endif