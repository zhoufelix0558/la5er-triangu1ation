
//-----------------------------------------------------------------------------
// \file    HZZD-ME138_Upp.h
// \brief   .
//
//-----------------------------------------------------------------------------
#ifndef __FPGA_UPP_H__
#define __FPGA_UPP_H__

#include "stdint.h"





//#define UPP_REG_BASE  0x01E16000

#define UPPID_uPP UPP_REG_BASE+0x0
#define UPPCR_uPP UPP_REG_BASE+0x4
#define UPDLB_uPP UPP_REG_BASE+0x8
#define UPCTL_uPP UPP_REG_BASE+0x10
#define UPICR_uPP UPP_REG_BASE+0x14
#define UPIVR_uPP UPP_REG_BASE+0x18
#define UPTCR_uPP UPP_REG_BASE+0x1C
#define UPISR_uPP UPP_REG_BASE+0x20
#define UPIER_uPP UPP_REG_BASE+0x24
#define UPIES_uPP UPP_REG_BASE+0x28
#define UPIEC_uPP UPP_REG_BASE+0x2C
#define UPEOI_uPP UPP_REG_BASE+0x30
#define UPID0_uPP UPP_REG_BASE+0x40
#define UPID1_uPP UPP_REG_BASE+0x44
#define UPID2_uPP UPP_REG_BASE+0x48
#define UPIS0_uPP UPP_REG_BASE+0x50
#define UPIS1_uPP UPP_REG_BASE+0x54
#define UPIS2_uPP UPP_REG_BASE+0x58
#define UPQD0_uPP UPP_REG_BASE+0x60
#define UPQD1_uPP UPP_REG_BASE+0x64
#define UPQD2_uPP UPP_REG_BASE+0x68
#define UPQS0_uPP UPP_REG_BASE+0x70
#define UPQS1_uPP UPP_REG_BASE+0x74
#define UPQS2_uPP UPP_REG_BASE+0x78




//-----------------------------------------------------------------------------
// Private Defines
//-----------------------------------------------------------------------------
#define PINMUX_UPP_REG_13	(13)   		//CHA_WAIT,CHA_ENABLE,CHA_START,CHA_CLK
#define PINMUX_UPP_MASK_13	(0xFFFF0000)
#define PINMUX_UPP_VAL_13	(0x44440000)

#define PINMUX_UPP_REG_14	(14)		//D10~D15
#define PINMUX_UPP_MASK_14	(0xFFFFFF00)
#define PINMUX_UPP_VAL_14	(0x44444400)

#define PINMUX_UPP_REG_15	(15)		//D2~D9
#define PINMUX_UPP_MASK_15	(0xFFFFFFFF)
#define PINMUX_UPP_VAL_15	(0x44444444)

#define PINMUX_UPP_REG_16	(16)		//D0~D1
#define PINMUX_UPP_MASK_16	(0x000000FF)
#define PINMUX_UPP_VAL_16	(0x00000044)

#define PINMUX_UPP_REG_18	(18) 		//CHB_WAIT,CHB_ENABLE,CHB_START,CHB_CLK
#define PINMUX_UPP_MASK_18	(0x00FFFF00)
#define PINMUX_UPP_VAL_18	(0x00444400)




//-----------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------
uint32_t fpga_upp_test(void);
uint32_t CHA_RX_UPP(void);
uint32_t config_upp(void);
void  savetofile();
void uPP_Isr(void);
int getTrigger();
uint32_t upp_receive_fifo(uint8_t * rxwind,uint32_t rx_lncnt,uint32_t rx_bcnt);
#endif

