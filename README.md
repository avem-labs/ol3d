# ol3d

A tiny portable 3D graphics lib for micro controllers.

## Example

Render a low poly wolf

```c
#include <SPI.h>
#include <ol3d_core.h>
#include <Wolf.h> // .obj data

void OLED_init ();
void w_cmd (uint8_t c);
void w_data (uint8_t d);
void fill_ram (unsigned char *buf);

// Declare display buffer, see ol3d_render.h
uint8_t buffer[128*128*3] = {};

float roll, yaw;

void setup () {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    OLED_init(); // initialize your screen
    yaw = 0;
}

void loop () {

// MVP matrix
    ol3d_matrix_t p;
    ol3d_matrix_setPerspective(p, 60, 1, 1, 1000);
    ol3d_matrix_t v;
    ol3d_matrix_setTranslate(v, 0, 0, -700);
    ol3d_matrix_t vp;
    ol3d_matrix_multiply(v, p, vp);
    ol3d_matrix_t mvp;

// Render process
    for(;;) {
        // Model matrix of current frame
        ol3d_matrix_t m = MATRIX_UNIT;
        ol3d_matrix_translate(m, 0, -80, 0);    // Translate to center
        ol3d_matrix_rotate(m, (float)yaw, M_AXIS_Y);    // Rotate
        yaw += 8;

        ol3d_matrix_multiply(m, vp, mvp);

        ol3d_clean_buffer(buffer);
        ol3d_draw_Element(buffer, mesh_f, mesh_v, mesh_v, 100, mvp);
        OLED_fill(buffer);
    }
}
```

### OBJ model headerfile style

Simply modify a OBJ file

```c
double mesh_v[] = {
    -0.500000, -0.500000, 0.500000,
    0.500000, -0.500000, 0.500000,
    -0.500000, 0.500000, 0.500000,
    0.500000, 0.500000, 0.500000,
    -0.500000, 0.500000, -0.500000,
    0.500000, 0.500000, -0.500000,
    -0.500000, -0.500000, -0.500000,
    0.500000, -0.500000, -0.500000,
    -0.500000, -0.500000, 0.500000,
    0.500000, -0.500000, 0.500000,
    -0.500000, 0.500000, 0.500000,
    0.500000, 0.500000, 0.500000,
    -0.500000, 0.500000, -0.500000,
    0.500000, 0.500000, -0.500000,
    -0.500000, -0.500000, -0.500000,
    0.500000, -0.500000, -0.500000
};
long mesh_f[] = {
    1, 2, 3,
    3, 2, 4,
    3, 4, 5,
    5, 4, 6,
    5, 6, 7,
    7, 6, 8,
    7, 8, 1,
    1, 8, 2,
    2, 8, 4,
    4, 8, 6,
    7, 1, 5,
    5, 1, 3,
    9, 10, 11,
    11, 10, 12,
    11, 12, 13,
    13, 12, 14,
    13, 14, 15,
    15, 14, 16,
    15, 16, 9,
    9, 16, 10,
    10, 16, 12,
    12, 16, 14,
    15, 9, 13,
    13, 9, 11
};
```