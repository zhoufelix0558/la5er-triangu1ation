#include "stdio.h"
#include "stdint.h"
#include "inc/evmomapl138.h"
#include "inc/evmomapl138_uPP.h"
#include "Io_fpga.h"
#include "inc/evmomapl138_sysconfig.h"
#include "fpga_Upp.h"
#include "c674x/omapl138/interrupt.h"
#include "inc/trace_dsp.h"
#include "inc/hzzduart.h"

#include "evmomapl138_uart.h"

#define SETBIT(dest,mask)   (dest |= mask)
#define CLRBIT(dest,mask)   (dest &= ~mask)
#define TGLBIT(dest,mask)   (dest ^= mask)
#define CHKBIT(dest,mask)   (dest & mask)
#define GETREG(dest)		 (dest)
#define SETREG(dest,mask)	 (dest= mask)

#define UPISR_EOLI_TRUE		(1 << 4)
#define UPISR_EOWI_TRUE		(1 << 3)
#define UPPCR_EN_ENABLE		(1 << 3)
//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------

uint8_t buffer0[5064] = { 0 };
uint8_t buffer1[5064] = { 0 };
uint32_t  upp_serialNum;
uint32_t executeTest(void);
uint16_t buffer[2532] = { 0 };
int data_ready;
int trigger = 0;
extern void frameProcess(uint8_t *buffer);

void savetofile(uint8_t * buffer,int linecnt)
{
	FILE	*fp;
    int i;
	fp = fopen("../uppdata.txt", "wb");
	if (fp == NULL)
	{
		printf("Open file error!");
		return ;
	}
    int line=0;
	for(line=0;line<linecnt;line++)
	{
		fwrite("line\r\n", 6, 1, fp);
		for(i=0;i<2516;i=i+2)
		{
			char val[10];
			uint32_t u16= buffer[i];
			u16=(u16<<8)+buffer[i+1];
			sprintf(val," %d \r\n",u16);
			fwrite(val, 10, 1, fp);
		}

	}
    fclose(fp);

}


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
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   initialize the upp port
//
// \param   upp_config_t * config: structure containing nessisary information
//									to setup upp
//
// \return  uint32_t
//    ERR_NO_ERROR - everything is ok...upp ready to use.
//-----------------------------------------------------------------------------

uint32_t UPP_init(upp_config_t * config)
{
	uint32_t rtn = ERR_INIT_FAIL;
	uint32_t i = 0;

	//Provide power to uPP
	EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_RPI, PSC_ENABLE);

	//reset uPP
	SETBIT(UPP->UPPCR, UPP_UPPCR_SWRST);
	for(i = 0; i < 300; i++){};      		//wait 200 clock cycles for reset.
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

	return (rtn);
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

}



uint32_t config_upp(void)
{	
	upp_config_t config;
	data_ready = 0;
    //dma_over=0;
	//UPCTL 初始化
	config.UPCTL.value=0;

	//配置数据的A通道的对齐位.
	config.UPCTL.bits.DPFA = 0;
	config.UPCTL.bits.DPWA = 0;

	//配置时钟
	config.UPICR.bits.CLKDIVB = 5;      //UPP clk = PLL0_SYSCLK2 / (config.UPISR.bit.CLKDIVB+1)	= 456/2/2 /(3+1)	= 28.5MHz

	//配置A,B的数据线.
	config.UPCTL.bits.CHN = 0;			//single channel mode, DATA[7:0]:CHA
    config.UPCTL.bits.IWA = 1;          //xdata not use ,A: 0-d7. B: d8:d15
	config.UPCTL.bits.IWB = 0;			//8 bit interface

	//Operating mode Duplex 配置
	config.UPCTL.bits.MODE = 0;			//Duplex Mode0.Channel A receives and Channel B transmits. Requires CHN=1

	//UPICR  Interface Configuration Register (UPICR)
	config.UPICR.value = 0;
	config.UPICR.bits.STARTA = 1;		//START signal is enabled,CHA
	config.UPICR.bits.ENAA = 1;			//ENABLE signal is enabled,CHA


	//UPIVR  Interface Idle Value Register
	config.UPIVR.value=0;
	config.UPIVR.bits.VALB = 0xffff;	//Channel B idle value
	config.UPIVR.bits.VALA = 0x0000;

	//UPTCR Threshold Configuration Register
	config.UPTCR.value=3;				//all values 0 for 64byte DMA bursts read / write

	//UPDLB   Digital Loopback Register
	config.UPDLB.value=0;				//no loopback	
	
	//UPIES Interrupt Enabled Status Register
	config.UPIES.value=0x1f1f;				//enable any interrupts

	//UPPCR Peripheral Control Register
	config.UPPCR.value = 0;	
	config.UPPCR.bits.RTEMU = 1;		//allow emulator use
	config.UPPCR.bits.SOFT = 1;			//allow emulation
	config.UPPCR.bits.EN = 1;			//enable uPP
		
	UPP_PINMUX();
    UPP_init(&config); 	

    // Initialize the DSP interrupt controller
	IntDSPINTCInit();
	// Register the ISRs to the vector table
	IntRegister(C674X_MASK_INT4, uPP_Isr);
	IntEventMap(C674X_MASK_INT4,SYS_INT_UPP_INT);
	// Enable DSP interrupts globally
	write_reg(UPEOI_uPP,0x0);
	IntGlobalEnable();
    uint32_t  UPIES_uPPrr = read_reg(UPIES_uPP);
    IntEnable(C674X_MASK_INT4);       //enable the CPU masked INT4

     return RET_OK;
}




uint32_t config_upp2(void)
{
	upp_config_t config;
	data_ready = 0;
    //dma_over=0;
	//UPCTL 初始化
	config.UPCTL.value=0;

	//配置数据的A通道的对齐位.
	config.UPCTL.bits.DPFA = 0;
	config.UPCTL.bits.DPWA = 0;

	//配置时钟
	config.UPICR.bits.CLKDIVB = 5;      //UPP clk = PLL0_SYSCLK2 / (config.UPISR.bit.CLKDIVB+1)	= 456/2/2 /(3+1)	= 28.5MHz

	//配置A,B的数据线.
	config.UPCTL.bits.CHN = 0;			//single channel mode, DATA[7:0]:CHA
    config.UPCTL.bits.IWA = 1;          //xdata not use ,A: 0-d7. B: d8:d15
	config.UPCTL.bits.IWB = 0;			//8 bit interface

	//Operating mode Duplex 配置
	config.UPCTL.bits.MODE = 0;			//Duplex Mode0.Channel A receives and Channel B transmits. Requires CHN=1

	//UPICR  Interface Configuration Register (UPICR)
	config.UPICR.value = 0;
	config.UPICR.bits.STARTA = 1;		//START signal is enabled,CHA
	config.UPICR.bits.ENAA = 1;			//ENABLE signal is enabled,CHA


	//UPIVR  Interface Idle Value Register
	config.UPIVR.value=0;
	config.UPIVR.bits.VALB = 0xffff;	//Channel B idle value
	config.UPIVR.bits.VALA = 0x0000;

	//UPTCR Threshold Configuration Register
	config.UPTCR.value=3;				//all values 0 for 64byte DMA bursts read / write

	//UPDLB   Digital Loopback Register
	config.UPDLB.value=0;				//no loopback

	//UPIES Interrupt Enabled Status Register
	config.UPIES.value=0x1f1f;				//enable any interrupts

	//UPPCR Peripheral Control Register
	config.UPPCR.value = 0;
	config.UPPCR.bits.RTEMU = 1;		//allow emulator use
	config.UPPCR.bits.SOFT = 1;			//allow emulation
	config.UPPCR.bits.EN = 1;			//enable uPP

	UPP_PINMUX();
    UPP_init(&config);

    // Initialize the DSP interrupt controller
	IntDSPINTCInit();
	// Register the ISRs to the vector table
	IntRegister(C674X_MASK_INT4, uPP_Isr);
	IntEventMap(C674X_MASK_INT4,SYS_INT_UPP_INT);
	// Enable DSP interrupts globally
	write_reg(UPEOI_uPP,0x0);
	IntGlobalEnable();
    uint32_t  UPIES_uPPrr = read_reg(UPIES_uPP);
    IntEnable(C674X_MASK_INT4);       //enable the CPU masked INT4

     return RET_OK;
}






uint32_t config_upp_again(void)
{

	 upp_config_t config;

	//UPPCR Peripheral Control Register
	config.UPPCR.value = 0;
	config.UPPCR.bits.RTEMU = 1;		//allow emulator use
	config.UPPCR.bits.SOFT = 1;			//allow emulation
	config.UPPCR.bits.EN = 1;			//enable uPP

	//UPIES Interrupt Enabled Status Register
	config.UPIES.value=0x1f1f;				//enable any interrupts

								//edited on 20160714
    //uint32_t rtn = ERR_INIT_FAIL;
	//uint32_t i = 0;

	// Register the ISRs to the vector table
	IntRegister(C674X_MASK_INT4, uPP_Isr);
	IntEventMap(C674X_MASK_INT4,SYS_INT_UPP_INT);
	// Enable DSP interrupts globally
	write_reg(UPEOI_uPP,0x0);
	IntGlobalEnable();
    uint32_t  UPIES_uPPrr = read_reg(UPIES_uPP);
    IntEnable(C674X_MASK_INT4);       //enable the CPU masked INT4
    return RET_OK;
}
/*
** upp Interrupt Service Routine
*/
int aaa=0;
 void uPP_Isr(void)
{
	aaa++;

	if(aaa%100==0)
	//	SW_BREAKPOINT;
	sentData("a");
	UPISR_t  interrupt_status;
	interrupt_status.value = read_reg(UPIER_uPP);
	while (interrupt_status.value != 0)
	{
	if (interrupt_status.bits.EOLI)				//EOLI位置1后，中断才能再次打开
	{
	  // Handle EOLI...
	  data_ready = 1;//标志位，每帧采集结束
	  trigger = trigger == 1 ? 0 : 1;
	  if(trigger == 0)
		  {
		  	//  upp_receive_fifo(buffer0,1,5064,0);
			 // frameProcess(buffer1);
		//  config_upp2();
		//	  upp_receive_fifo(buffer0,1,5064,0);
		  }
	  else
		  {
		            //  frameProcess(buffer0);
		//  config_upp2();
		//	  upp_receive_fifo(buffer1,1,5064,0);

		  }

	  SETBIT(UPP->UPISR, UPISR_EOLI_TRUE);
	  //printf("EOLI ");
	}
	if (interrupt_status.bits.EOWI)
	{
		//Handle EOWI...
		//dma_over=1;//标志位，每次采集结束
		printf("EOWI \n\r");
		SETBIT(UPP->UPISR, UPISR_EOWI_TRUE);
	}
	if (interrupt_status.bits.ERRI)
	{
		sentData("ERRI");
	//	               UPIER.ERRI = 1 // clear ERRI
	   // Handle ERRI...
	}
	if (interrupt_status.bits.UORI)
	{
		sentData("UORI");
		config_upp2();
	//	               UPIER.UORI = 1 // clear UORI
	   // Handle UORI...
	}
	if (interrupt_status.bits.DPEI)
	{
		sentData("DPEI");
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


uint32_t upp_receive_fifo(uint8_t * rxwind,uint32_t rx_lncnt,uint32_t rx_bcnt)
{
	uint32_t dma_i_wind=(uint32_t)rxwind;
	uint32_t dma_i_lncnt=rx_lncnt <<16;
	uint32_t dma_i_bcnt=rx_bcnt;

	uint32_t  rUPPCR = GETREG(UPP->UPPCR);

	//set uPP receive address ,ddr2 direct to dma
	//if(trigger == 0) SETREG(UPP->UPID0, 0xC1000000);//DDR切换
	//else SETREG(UPP->UPID0, 0xC2000000);

	SETREG(UPP->UPID0, dma_i_wind); //SRAM
	SETREG(UPP->UPID1, dma_i_lncnt | dma_i_bcnt);
	SETREG(UPP->UPID2, dma_i_bcnt);
	return 2;

/*
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
		if(cnt>2000000)
		{

			printf("\r  end of windows UPIEC= %d \r\n",GETREG(UPP->UPIEC) );
			printf("\r  end of windows UPISR= %d \r\n",GETREG(UPP->UPISR) );
			printf("\r  end of windows UPIS0= %d \r\n",GETREG(UPP->UPIS0) );
			printf("\r  end of windows UPIS1= %d \r\n",GETREG(UPP->UPIS1) );
			printf("\r  end of windows UPIS2= %d \r\n",GETREG(UPP->UPIS2) );
			break;

		}
	}
	*/

}

   
