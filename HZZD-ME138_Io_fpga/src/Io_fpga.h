

#ifndef HZZD_ME138_IO_FPGA_H
#define HZZD_ME138_IO_FPGA_H
#include "stdint.h"
//#include "evmomapl138_i2c.h"

#define EMIF_CS5_START_ADDR 	(0x66000000)

/* fpga io group write address */
#define IO_GROUP1_W_ADDR  	(0x66000000)
#define IO_GROUP2_W_ADDR  	(0x66000002)
#define IO_GROUP3_W_ADDR  	(0x66000004)

/* fpga io group read address */
#define IO_GROUP1_R_ADDR  	EMIF_CS5_START_ADDR+6
#define IO_GROUP2_R_ADDR  	EMIF_CS5_START_ADDR+8
#define IO_GROUP3_R_ADDR  	EMIF_CS5_START_ADDR+0xA

#define FPGA_BASE      	    EMIF_CS5_START_ADDR
#define FPGA_VER      	    EMIF_CS5_START_ADDR+4

#define CCD_TINT      	        EMIF_CS5_START_ADDR+200
#define CCD_START      	        EMIF_CS5_START_ADDR+204
#define UPP_CNT      	        EMIF_CS5_START_ADDR+208
#define RD_FIFO_CNT      	    EMIF_CS5_START_ADDR+212
#define WR_FIFO_CNT      	    EMIF_CS5_START_ADDR+216
#define RUN_FR_CNT      	    EMIF_CS5_START_ADDR+220
#define OUT_FR_CNT      	    EMIF_CS5_START_ADDR+224
#define FIFO_CNT_RD    	        EMIF_CS5_START_ADDR+228
#define FIFO_CNT_WR   	        EMIF_CS5_START_ADDR+232
#define FIFO_rd_pos   	        EMIF_CS5_START_ADDR+236


void EMIF_init(void);

uint32_t   fpga_io_test(void);
uint16_t   fpga_read_reg(uint32_t addr);
void       fpga_write_reg(uint32_t addr,uint16_t val);
void       test_fpga_reg();

#endif


