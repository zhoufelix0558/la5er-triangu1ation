

#include "stdio.h"
#include "stdint.h"
#include "inc/evmomapl138.h"
#include "inc/evmomapl138_uPP.h"
#include "Io_fpga.h"
#include "inc/evmomapl138_sysconfig.h"
#include "fpga_Upp.h"
#include "c674x/omapl138/interrupt.h"
#include "inc/trace_dsp.h"
#include "dsp_uart.h"

#define SETBIT(dest,mask)   (dest |= mask)
#define CLRBIT(dest,mask)   (dest &= ~mask)
#define TGLBIT(dest,mask)   (dest ^= mask)
#define CHKBIT(dest,mask)   (dest & mask)
#define GETREG(dest)		 (dest)
#define SETREG(dest,mask)	 (dest= mask)

#define UPISR_EOLI_TRUE		 (1 << 4)
#define UPISR_EOWI_TRUE		 (1 << 3)
#define UPPCR_EN_ENABLE		 (1 << 3)
void  config_reg(void);
//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------


void  UPP_init(upp_config_t * config)
{
	uint32_t i = 0;

	//Provide power to uPP
	// EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_RPI, PSC_ENABLE);

	//reset uPP
	SETBIT(UPP->UPPCR, UPP_UPPCR_SWRST);

	for(i = 0; i < 200; i++){};  	//wait 200 clock cycles for reset.
	CLRBIT(UPP->UPPCR, UPP_UPPCR_SWRST);

	//setup control registers
	UPP->UPCTL=config->UPCTL.value;
	UPP->UPICR=config->UPICR.value;
	UPP->UPIVR=config->UPIVR.value;
	UPP->UPTCR=config->UPTCR.value;
	UPP->UPDLB=config->UPDLB.value;
	UPP->UPIES=config->UPIES.value;
	UPP->UPPCR=config->UPPCR.value;
	//UPP->UPICR |= ((0x3<<19)|(0x3<<3));  //START signal is enabled.
}
void  UPP_stop()
{
	uint32_t i = 0;

	//Provide power to uPP
	// EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_RPI, PSC_ENABLE);
	write_mask_reg(UPPCR_uPP,0x8,0);

	//reset uPP
//	SETBIT(UPP->UPPCR, UPP_UPPCR_SWRST);
//	for(i = 0; i < 200; i++)
//	{

//	}
	//for(i = 0; i < 200; i++){};  	//wait 200 clock cycles for reset.
	//CLRBIT(UPP->UPPCR, UPP_UPPCR_SWRST);
}

void UPP_PINMUX()
{
	//Provide power to uPP
	// EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_RPI, PSC_ENABLE);
	//take care of pin muxing
	EVMOMAPL138_pinmuxConfig(PINMUX_UPP_REG_13,PINMUX_UPP_MASK_13, PINMUX_UPP_VAL_13);
	EVMOMAPL138_pinmuxConfig(PINMUX_UPP_REG_14,PINMUX_UPP_MASK_14, PINMUX_UPP_VAL_14);
	EVMOMAPL138_pinmuxConfig(PINMUX_UPP_REG_15,PINMUX_UPP_MASK_15, PINMUX_UPP_VAL_15);
	EVMOMAPL138_pinmuxConfig(PINMUX_UPP_REG_16,PINMUX_UPP_MASK_16, PINMUX_UPP_VAL_16);
	EVMOMAPL138_pinmuxConfig(PINMUX_UPP_REG_18,PINMUX_UPP_MASK_18, PINMUX_UPP_VAL_18);

	EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_RPI, PSC_ENABLE);
	config_reg();
}



uint32_t      upp_serialNum;
uint32_t      executeTest(void);
int          dma_over;
upp_config_t  config;
void  config_reg(void)
{	


    dma_over=0;
	//UPCTL 初始化
	config.UPCTL.value=0;

	//配置数据的A通道的对齐位.
	config.UPCTL.bits.DPFA = 0;
	config.UPCTL.bits.DPWA = 0;

	//配置时钟
	config.UPICR.bits.CLKDIVB = 3;      //UPP clk = PLL0_SYSCLK2 / (config.UPISR.bit.CLKDIVB+1)	= 456/2/2 /(3+1)	= 28.5MHz

	//配置A,B的数据线.
	config.UPCTL.bits.CHN = 0;			//single channel mode, DATA[7:0]:CHA
    config.UPCTL.bits.IWA = 1;          //xdata not use ,A: 0-d7. B: d8:d15
	config.UPCTL.bits.IWB = 0;			//8 bit interface

	//Operating mode  Duplex 配置
	config.UPCTL.bits.MODE = 0;			//Duplex Mode0.Channel A receives and Channel B transmits. Requires CHN=1

	//UPICR  Interface Configuration Register (UPICR)
	config.UPICR.value = 0;
	config.UPICR.bits.STARTA = 1;		//START signal is enabled,CHA
	config.UPICR.bits.ENAA = 1;			//ENABLE signal is enabled,CHA


	//UPIVR  Interface Idle Value Register
	config.UPIVR.value=0;
	config.UPIVR.bits.VALB = 0xffff;	//Channel B idle value
	config.UPIVR.bits.VALA = 0x0000;

	//UPTCR  Threshold Configuration Register
	config.UPTCR.value=3;				//all values 0 for 64byte DMA bursts read / write

	//UPDLB   Digital Loopback Register
	config.UPDLB.value=0;				//no loopback	
	
	//UPIES		  Interrupt Enabled Status Register
	config.UPIES.value=0x1f1f;				//enable any interrupts

	//UPPCR   Peripheral Control Register
	config.UPPCR.value = 0;	
	config.UPPCR.bits.RTEMU = 1;		//allow emulator use
	config.UPPCR.bits.SOFT = 1;			//allow emulation
	config.UPPCR.bits.EN = 1;			//enable uPP
}
void config_upp()
{
	UPP_init(&config);
    // Initialize the DSP interrupt controller
	IntDSPINTCInit();
	   // Register the ISRs to the vector table
/*
	IntRegister(C674X_MASK_INT4, uPP_Isr);
	IntEventMap(C674X_MASK_INT4, SYS_INT_UPP_INT);
	   // Enable DSP interrupts globally
	write_reg(UPEOI_uPP,0x0);
	IntGlobalEnable();
    uint32_t  UPIES_uPPrr = read_reg(UPIES_uPP);
    IntEnable(C674X_MASK_INT4);       //enable the CPU masked INT4
*/
}

/*
** upp Interrupt Service Routine
*/

 void uPP_Isr(void)
{

	//     SW_BREAKPOINT;
	     UPISR_t  interrupt_status;
	     interrupt_status.value = read_reg(UPIER_uPP);
	     while (interrupt_status.value != 0)
	     {
	          if (interrupt_status.bits.EOLI)
	          {
	                 // Handle EOLI...
	        	 SETBIT(UPP->UPISR, UPISR_EOLI_TRUE);
	        //	 printf("EOLI ");
	        	// str2com("eoli");
	          }
	          if (interrupt_status.bits.EOWI)
	          {
	               // Handle EOWI...
	        	  dma_over=1;
	        	//  printf("EOWI \n\r");
				  SETBIT(UPP->UPISR, UPISR_EOWI_TRUE);
	          }
	          if (interrupt_status.bits.ERRI)
	          {
//	               UPIER.ERRI = 1 // clear ERRI
	               // Handle ERRI...
	          }
	          if (interrupt_status.bits.UORI)
	          {
//	               UPIER.UORI = 1 // clear UORI
	               // Handle UORI...
	          }
	          if (interrupt_status.bits.DPEI)
	          {
//	               UPIER.DPEI = 1 // clear DPEI
	               // Handle DPEI...
	          }
	          if (interrupt_status.bits.EOLQ)
	          {
//	               UPIER.EOLQ = 1 // clear EOLQ
	               // Handle EOLQ...
	          }
	          if (interrupt_status.bits.EOWQ)
	          {
//	               UPIER.EOWQ = 1 // clear EOWQ
	               // Handle EOWQ...
	          }
	          if (interrupt_status.bits.ERRQ)
	          {
//	               UPIER.ERRQ = 1 // clear ERRQ
	               // Handle ERRQ...
	          }
	          if (interrupt_status.bits.UORQ)
	          {
//	               UPIER.UORQ = 1 // clear UORQ
	               // Handle UORQ...
	          }
	          if (interrupt_status.bits.DPEQ)
	          {
//	               UPIER.DPEQ = 1 // clear DPEQ
	               // Handle DPEQ...
	          }
	          interrupt_status.value = 0;
	          // loop again if any interrupts are left
	       //   interrupt_status = UPIER
	     } // end of while
	     // write end of interrupt vector to allow future calls
		 write_reg(UPEOI_uPP,0x0);
}


void  upp_receive_fifo(uint16_t*  rxwind,uint32_t rx_lncnt,uint32_t rx_bcnt)
{

	uint32_t dma_i_wind   = (uint32_t)rxwind;
	uint32_t dma_i_lncnt  = rx_lncnt <<16;
	uint32_t dma_i_bcnt   = rx_bcnt;


  // if(rxwind==0)
  //  	dma_i_wind=0xC1000000;


	uint32_t  rUPPCR =GETREG(UPP->UPPCR);

	//set uPP receive address ,ddr2 direct to dma
	SETREG(UPP->UPID0, dma_i_wind);
	SETREG(UPP->UPID1, dma_i_lncnt | dma_i_bcnt);
	SETREG(UPP->UPID2, dma_i_bcnt);

/*
    char show_str[20];
    uint32_t cnt=0;
	for(;;)
	{

	    UPISR_t  interrupt_status;
		interrupt_status.value =GETREG(UPP->UPISR);
		// line结束标志
		if (interrupt_status.bits.EOLI)
		{
			printf("end of line \r\n");
			SETBIT(UPP->UPISR, UPISR_EOLI_TRUE);
			break;
		}
		//判断窗口结束
		if (interrupt_status.bits.EOWI)
		{
			printf("\r  end of windows   \r\n");
            break;
		}

		cnt++;
		if(cnt>100)
		{
			//str2com("delay 10000");

			printf("\r  end of windows UPIEC= %08X \r\n",GETREG(UPP->UPIEC) );
			printf("\r  end of windows UPISR= %08X \r\n",GETREG(UPP->UPISR) );
			printf("\r  end of windows UPIS0= %08X \r\n",GETREG(UPP->UPIS0) );
			printf("\r  end of windows UPIS1= %08X \r\n",GETREG(UPP->UPIS1) );
			printf("\r  end of windows UPIS2= %08X \r\n",GETREG(UPP->UPIS2) );
			break;

		}
	}
	uint32_t  rUPP_CNT =fpga_read_reg(UPP_CNT);

	//sprintf(show_str," rUPP_CNT =%d",rUPP_CNT);
	//str2com(show_str);
	//printf("uppcnt = %d \n",rUPP_CNT);
*/

}

   
