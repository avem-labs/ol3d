#include <stdio.h>
#include <stdlib.h>
#include <ol3d_core.h>
#include <mesh.h>

#define SIZE    256

static unsigned char buffer[SIZE*SIZE*3] = {};
float roll, yaw;


int export(const char *path);
void render();

int main(int argc, char const *argv[]) {
    yaw = 0;
    printf("hello\n");
    render();
    ol3d_clean_buffer(buffer);
    export("test.ppm");
    // return 0;
}

void render() {
    // MVP matrix
    ol3d_matrix_t p;
    ol3d_matrix_setPerspective(p, 60, 1, 1, 1000);
    ol3d_matrix_t v;
    ol3d_matrix_setTranslate(v, 0, 0, 100);
    ol3d_matrix_t vp;
    ol3d_matrix_multiply(v, p, vp);
    ol3d_matrix_t mvp;

// Render process
    // Model matrix of current frame
    ol3d_matrix_t m = MATRIX_UNIT;
    ol3d_matrix_translate(m, 0, -80, 0);    // Translate to center
    ol3d_matrix_rotate(m, (float)yaw, M_AXIS_Y);    // Rotate
    yaw += 8;

    ol3d_matrix_multiply(m, vp, mvp);

    ol3d_clean_buffer(buffer);
    ol3d_draw_Element(buffer, mesh_f, mesh_v, mesh_v, 100, mvp);
}

static char buf[SIZE*SIZE*3*3+100];

int export(const char *path) {

	FILE *fp = fopen(path, "w+");
	if(fp == NULL) {
		printf("Cannot write target file!");
		return 1;
	}

	char *p_obj = buf;

    p_obj += sprintf(p_obj, "P3\n");
    p_obj += sprintf(p_obj, "%d %d\n", SIZE, SIZE);
    p_obj += sprintf(p_obj, "255\n");

    long size = SIZE*SIZE;
    // unsigned char *pb = buffer;
	// for (long i = 0; i < size; i++)
	// {
	// 	int x = *pb++;
	// 	int y = *pb++;
	// 	int z = *pb++;
	// 	p_obj += sprintf(p_obj, "%b %b %b\n", x, y, z);
	// }

	fputs(buf, fp);
	// fputs(buffer, fp);
    fwrite(buffer, SIZE*SIZE, 3, fp);
	fclose(fp);
	fp = NULL;

	return 0;
}