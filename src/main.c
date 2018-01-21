#include <ol3d_core.h>

int main() {

	ol3d_core_module_st.init_module(NULL);

	while(1) {
		uart_sendStr("Hello World!\r\n");
	}
}
