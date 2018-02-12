#ifndef _OL3D_CORE_H_
#define _OL3D_CORE_H_

typedef struct ol3d_module_s     ol3d_module_t;
// typedef struct ol3d_string_s     ol3d_string_t;

#include <math.h>
#include <stm32f10x.h>
#include <ol3d_bit.h>
#include <ol3d_uart.h>
#include <ol3d_vector.h>
#include <ol3d_matrix.h>
#include <ol3d_render.h>

struct ol3d_module_s {
    unsigned short  index;
    unsigned int    *confs;
    unsigned char   (*init_module)(void *arg);
    unsigned char   (*enable_module)(void);
    unsigned char   (*disable_module)(void);
};

extern ol3d_module_t *ol3d_modules_pool[];
extern ol3d_module_t ol3d_core_module_st;

void delay_ms(unsigned int t);
void delay_us(unsigned int t);

#define NVIC_GROUPING	3
// Jump to built-in bootloader
#define ISP_ADDR		0x1FFFF000
void jump2ISP();


#endif