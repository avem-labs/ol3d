#include <ol3d_core.h>

void debug_buffer(ol3d_buffer_t target) {
	for(unsigned int y = 0; y < BUFFER_SIZE; y++) {
		for(unsigned int x = 0; x < BUFFER_SIZE; x++) {
			if(target[x][y]) {
				uart_sendStr("##");
			} else {
				uart_sendStr("__");
			}
		}
		UART_CR();
	}
	UART_CR();
	UART_CR();
	delay_ms(1000);

}

int main() {

	ol3d_core_module_st.init_module(NULL);

	ol3d_Vector3_t a = {
		.x = 0.0,
		.y = 1.0,
		.z = 0.0
	};
	ol3d_Vector3_t b = {
		.x = -0.4,
		.y = -0.6,
		.z = 0.0
	};
	ol3d_Vector3_t c = {
		.x = 1.0,
		.y = -1.0,
		.z = 0.0
	};

	ol3d_matrix_t t = MATRIX_ROTATE_Z(10);


	// ol3d_draw_Triangle(render_buffer, &a, &b, &c, &a, &b, &c);
	while(1) {
		ol3d_draw_Triangle(render_buffer, &a, &b, &c, &a, &b, &c);
		// debug_buffer(render_buffer);
		ol3d_clean_buffer(render_buffer);
		ol3d_matrix_multi_v3(&a, t);
		ol3d_matrix_multi_v3(&b, t);
		ol3d_matrix_multi_v3(&c, t);
		delay_ms(1000);
	}
}
