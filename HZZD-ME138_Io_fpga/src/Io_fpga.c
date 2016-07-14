


#include <src/Io_fpga.h>
#include "stdio.h"
#include "stdint.h"
#include "inc/evmomapl138.h"
#include "inc/evmomapl138_emif.h"

#define PINMUX_EMIFA_REG_5 		5
#define PINMUX_EMIFA_MASK_5	    0x0F000000  //EAB1
#define PINMUX_EMIFA_VAL_5		0x01000000

#define PINMUX_EMIFA_REG_7 		7
#define PINMUX_EMIFA_MASK_7	    0x00FFF000  //CS5,OE,WE
#define PINMUX_EMIFA_VAL_7		0x00111000

#define PINMUX_EMIFA_REG_8 		8
#define PINMUX_EMIFA_MASK_8	    0xFFFFFFFF  //EMA_D
#define PINMUX_EMIFA_VAL_8		0x11111111

#define PINMUX_EMIFA_REG_9 		9
#define PINMUX_EMIFA_MASK_9	    0xFFFFFFFF //EMA_D
#define PINMUX_EMIFA_VAL_9		0x11111111

#define PINMUX_EMIFA_REG_11 	11 
#define PINMUX_EMIFA_MASK_11	0xFFF00000  //EMA_A8~10
#define PINMUX_EMIFA_VAL_11		0x11100000

#define PINMUX_EMIFA_REG_12 	12
#define PINMUX_EMIFA_MASK_12	0xFFFFFFFF  //EMA_A0~7
#define PINMUX_EMIFA_VAL_12		0x11111111

//-----------------------------------------------------------------------------
// /brief Init emif to 16bit, the address line is BA1~EMA_10.
//-----------------------------------------------------------------------------
void EMIF_init(void)
{
	EVMOMAPL138_lpscTransition(PSC0, DOMAIN0, LPSC_EMIFA, PSC_ENABLE);
    EVMOMAPL138_pinmuxConfig(PINMUX_EMIFA_REG_5, PINMUX_EMIFA_MASK_5, PINMUX_EMIFA_VAL_5);
    EVMOMAPL138_pinmuxConfig(PINMUX_EMIFA_REG_7, PINMUX_EMIFA_MASK_7, PINMUX_EMIFA_VAL_7);
    EVMOMAPL138_pinmuxConfig(PINMUX_EMIFA_REG_8, PINMUX_EMIFA_MASK_8, PINMUX_EMIFA_VAL_8);
	EVMOMAPL138_pinmuxConfig(PINMUX_EMIFA_REG_9, PINMUX_EMIFA_MASK_9, PINMUX_EMIFA_VAL_9);
	EVMOMAPL138_pinmuxConfig(PINMUX_EMIFA_REG_11, PINMUX_EMIFA_MASK_11, PINMUX_EMIFA_VAL_11);
	EVMOMAPL138_pinmuxConfig(PINMUX_EMIFA_REG_12, PINMUX_EMIFA_MASK_12, PINMUX_EMIFA_VAL_12);
   
    // config for 16-bit data bus.
	EMIFA->CE5CFG =(3 << 26) | (7 << 20) | (2 << 17) | (3 << 13) | (7 << 7) | (2 << 4) | (2 << 2) | 1;
}


uint16_t fpga_read_reg(uint32_t addr)
{

		/* read back data */
	    uint16_t	group1=0;
	    group1= *(uint16_t *)addr;
		return group1;

}

void  fpga_write_reg(uint32_t addr,uint16_t val)
{
	 /* write 1 to every io */
	  *(uint16_t *)addr = val;

}
void test_fpga_reg()
{
	     uint16_t r0= fpga_read_reg(FPGA_BASE);
		 uint16_t r1= fpga_read_reg(FPGA_VER);
		 uint16_t r2= fpga_read_reg(FPGA_BASE+2);
		 uint16_t r3= fpga_read_reg(FPGA_BASE+3);
		 uint16_t r4= fpga_read_reg(FPGA_BASE+4);
		 uint16_t r5= fpga_read_reg(FPGA_BASE+5);
		 uint16_t r6= fpga_read_reg(FPGA_BASE+6);
		 uint16_t r7= fpga_read_reg(FPGA_BASE+7);
		 uint16_t r8= fpga_read_reg(FPGA_BASE+8);
		 uint16_t r9= fpga_read_reg(FPGA_BASE+9);
		 uint16_t r10= fpga_read_reg(FPGA_BASE+10);
		 uint16_t r11= fpga_read_reg(FPGA_BASE+11);
		 uint16_t r12= fpga_read_reg(FPGA_BASE+12);
		 uint16_t rTint= fpga_read_reg(CCD_TINT);
		 fpga_write_reg(CCD_TINT,10);
		 uint16_t  rTint2= fpga_read_reg(CCD_TINT);
		 printf("fpga r0=%d r1=%d \r\n ",r0,r1);
}
