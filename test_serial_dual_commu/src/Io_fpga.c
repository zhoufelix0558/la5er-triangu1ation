


#include <src/Io_fpga.h>
#include "stdio.h"
#include "stdint.h"
#include "inc/evmomapl138.h"
#include "inc/evmomapl138_emif.h"
#include "psc.h"
#include "hw_ddr2_mddr.h"

#include "hw_types.h"
#include "hw_syscfg0_OMAPL138.h"
#include "hw_pllc_OMAPL138.h"
#include "hw_ddr2_mddr.h"
#include "hw_syscfg1_OMAPL138.h"
#include "inc/trace_dsp.h"
#include "soc_OMAPL138.h"


  /* Fix DDR timing values/refresh rates */
  #define DDR2_SDCR_value                  0x00134A22
  #define DDR2_SDRCR_value                 0xC000030c

  #define DDR2_SDTIMR1_value               0x0e492140
  #define DDR2_SDTIMR2_value               0x3C0b0b02

  #define DRPHYC1R_value                   0x000000c6
  #define DDR2_SDRCR_CLEAR           0xC0000000
  #define VTPIO_CTL_HIGH             0x00080000




/******************************************************************************
**                     Internal Macro Definitions
*******************************************************************************/
//#define CLK_PLL0_SYSCLK3                  (0xFFFFFFF8)
//#define DDR2_MDDR_DRPYC1R_READ_LAT        (0x4)
//#define INTVECMAX                         (9)




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


/*
 * \brief This function is used to initialize and configure DDR.
 *
 * \param  none.
 *
 * \return none
*/
void DDRInit(void)
{

    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_DDR2_MDDR,  0, PSC_MDCTL_NEXT_ENABLE);

    if (HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) & SYSCFG1_VTPIO_CTL_POWERDN)
    {
         /* Set IOPWRDN bit, powerdown enable mode */
        HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |=SYSCFG1_VTPIO_CTL_IOPWRDN;
         /* Clear POWERDN bit (enable VTP) */
        HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |=SYSCFG1_VTPIO_CTL_POWERDN;
         /* Clear CLRZ bit */
	HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) &=
                                          ~SYSCFG1_VTPIO_CTL_CLKRZ;
	/* CLRZ bit should be low at least for 2ns */
        dsp_delay(4);
        /* Set CLRZ bit */
	HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |= SYSCFG1_VTPIO_CTL_CLKRZ;
        /* Poll ready bit in VTPIO_CTL Untill it is high */
	while (!(( HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) &
                                                     VTPIO_CTL_HIGH ) >> 15));
        /* Set Lock bit for static mode */
	HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |= SYSCFG1_VTPIO_CTL_LOCK;
        /* set PWRSAVE bit to save Power */
	HWREG(SOC_SYSCFG_1_REGS + SYSCFG1_VTPIO_CTL) |=
                                          SYSCFG1_VTPIO_CTL_PWRSAVE;
	/* VTP Calibration ends */
    }

    /* Set BOOTUNLOCK */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR) |= DDR2_MDDR_SDCR_BOOTUNLOCK;

    /* Set EXT_STRBEN and PWRDNEN bit of DDR PHY control register,
                                   assign desired value to the RL bit */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_DRPYC1R) =DRPHYC1R_value;

    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR)    = DDR2_SDCR_value;
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDTIMR1) = DDR2_SDTIMR1_value;
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDTIMR2) = DDR2_SDTIMR2_value;

    /* CLEAR TIMINGUNLOCK */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR) &= ~DDR2_MDDR_SDCR_BOOTUNLOCK;
    /*  IBANK_POS set to 0 so this register does not apply */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDCR2 ) = DDR2_MDDR_SDCR_IBANK_ONE;
    /* SET the refreshing rate */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDRCR) = DDR2_SDRCR_value;

    /* SyncReset the Clock to SDRAM */
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_DDR2_MDDR,
                              0,PSC_MDSTAT_STATE_SYNCRST);
    /* Enable clock to SDRAM */
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_DDR2_MDDR, 0,PSC_MDCTL_NEXT_ENABLE);
    /* Disable Self refresh rate */
    HWREG(SOC_DDR2_0_CTRL_REGS + DDR2_MDDR_SDRCR ) &= ~DDR2_SDRCR_CLEAR;

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

	     if(r0!=0x6600)
	    	  SW_BREAKPOINT;
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
		 //printf("fpga r0=%d r1=%d \r\n ",r0,r1);
}
