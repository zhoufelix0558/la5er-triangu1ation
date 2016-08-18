//#define  DEBUG
#include   <src/ad9822.h>
#include   "stdio.h"
#include   "inc/evmomapl138.h"
#include   "hw_types.h"
#include   "inc/trace_dsp.h"
#include   <c6x.h>
#include   <src/Io_fpga.h>
#include   "fpga_config.h"
#include   "fpga_upp.h"
#include   "nand_flash.h"
#include   "string.h"
#include   "dsp_uart.h"
#include   "dataprocess.h"
//#include   "dsp_uart.c"
#include   "interrupt.h"

//#include  "evmomapl138_uart.h"
uint32_t rtn;
uint8_t rcv_data = 0;
int cnt = 0;
char string[30];
void _test_isr_1(void)
{
	cnt++;

	//IntGlobalDisable();
sprintf(string,"%d times enter interrupt\n",cnt);

dsp_delay(50000);
str2com("interrupt entered");
str2com(string);

	do
	{
		rtn = UART_rxByte(DEBUG_PORT, &rcv_data);
		if(rtn == ERR_NO_ERROR)
		{
			if(rcv_data == 'q')
			{
				rcv_data = 255;
			}
			else
			{
				UART_txByte(DEBUG_PORT, rcv_data);
			}
		}
	}
	while(rcv_data!=255);
	rcv_data = 0;

	//CSR |= 0x00000001;
	str2com("interrupt exited\n");
	while(rtn !=6)
	rtn = UART_rxByte(DEBUG_PORT, &rcv_data);

	//DEBUG_PORT
	//IntGlobalEnable();
}




interrupt void _test_isr(void)
{
str2com("interrupt entered\n");
}







void main()
{

	IntDSPINTCInit();
	Uart_Init_edited();
	IntRegister (C674X_MASK_INT8, _test_isr);
	IntEventMap(C674X_MASK_INT8,SYS_INT_UART2_INT);
	//IntEnable(C674X_MASK_INT8);
	//CSR |= 0x00000003;
	//UART2DSP->IER &=0xFFFFFFFE;
	IntGlobalEnable();

	while(1)
	{
		dsp_delay(2000000);
		str2com("main location\n");


	}


//	return 0;
}
