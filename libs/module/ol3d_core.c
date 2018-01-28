#include <ol3d_core.h>

static unsigned char ol3d_core_init(void *arg);

ol3d_module_t ol3d_core_module_st = {
	0,
	NULL,
	ol3d_core_init,
	NULL,
	NULL
};

void jump2ISP() {
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	__set_MSP(*(unsigned int *)ISP_ADDR);
	((void (*)(void))*((unsigned int *)(ISP_ADDR + 4)))();
}

void delay_ms(unsigned int t) {
	SysTick->LOAD = 9000 * t;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x01;
	for(unsigned int tmp = SysTick->CTRL;(tmp&0x01)&&(!(tmp&SysTick_CTRL_COUNTFLAG));tmp = SysTick->CTRL);
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}

// 延时函数, 单位为微秒
void delay_us(unsigned int t) {
	SysTick->LOAD = 9 * t;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x01;
	for(unsigned int tmp = SysTick->CTRL;(tmp&0x01)&&(!(tmp&SysTick_CTRL_COUNTFLAG));tmp = SysTick->CTRL);
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}

ol3d_module_t *ol3d_modules_pool[] = {
	&ol3d_core_module_st,
    &ol3d_uart_module_st,
    NULL
};

static unsigned char ol3d_core_init(void *arg) {
	NVIC_SetPriorityGrouping(0x07 - NVIC_GROUPING);

	ol3d_module_t *p_core = ol3d_modules_pool[0];
	// Count
	static unsigned char ol3d_modules_num = 0;
	for(;ol3d_modules_pool[ol3d_modules_num] != NULL;ol3d_modules_num++) {
		ol3d_modules_pool[ol3d_modules_num]->index = ol3d_modules_num;
	}

	p_core->confs = (void *)&ol3d_modules_num;	// Stored
	// Initial
	ol3d_module_t **this = &ol3d_modules_pool[1];
	for(;*this != NULL;this++) {
			(*this)->init_module((*this)->confs);
	}

	return 0;
}
