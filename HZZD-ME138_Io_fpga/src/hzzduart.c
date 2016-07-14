/***************************************************************************
 *                                                                         *
 * HZZD modify the test files.                        　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　��
 *                                                                         *
 * -URL:		 http://www.hz-dsp.com                                     *
 * -telephone:   010-82463740                                              *
 * -Fax Number:  010-82463240-8006                                         *
 * -Sales email: sales@hz-dsp.com                                          *
 *                                                                         *
****************************************************************************/

//-----------------------------------------------------------------------------
// \file    HZZD-ME138_Uart.c
// \brief   implementation of OMAP-L138 uart test.
//
//-----------------------------------------------------------------------------
#include <hzzduart.h>
#include "stdio.h"
#include "types.h"
#include "evmomapl138.h"
#include "evmomapl138_timer.h"
#include "evmomapl138_uart.h"

#ifdef _UART1
#define DEBUG_PORT   (UART1)
#else
#define DEBUG_PORT   (UART2)
#endif

//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------
static uint32_t terminal_counting(void);

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   tests timer and uart. counts to 1...10, printing messages
//          out the debug port along the way.
//
// \param   none.
//
// \return  uint32_t
//-----------------------------------------------------------------------------
void TEST_uart(void)
{
	uint32_t rtn;
/*
	printf("------------------------------------------------------------\r\n");
	printf("                     HZZD-ME138 UART Test\r\n\r\n");
	printf("Additional Equipment\r\n");
	printf("--------------------\r\n");
	printf("- RS232 serial cable \r\n\r\n");
	printf("Test Description\r\n");
	printf("----------------\r\n");
	printf("Connect the serial cable from the board to a computer and \r\n");
	printf("open a terminal program (Tera Term), configuring it for  \r\n");
	printf("115200 baud, 8-bit, no parity, 1 stop bit, no flow control.  \r\n");
	printf("This code will configure the UART and use a microsecond timer \r\n");
	printf("to count to 10, printing each second.  \r\n");
	printf("and write a portion of SPI flash. \r\n");
	printf("------------------------------------------------------------\r\n\r\n");
*/
	//-------------------------------------
	// initialize the required bsl modules.
	//-------------------------------------
/*	printf("Initialize the Required BSL Modules\r\n");
	printf("-----------------------------------\r\n\r\n");
*/
	rtn = UART_init(DEBUG_PORT, 115200);
	if (rtn != ERR_NO_ERROR)
	{
		printf("error initializing uart!\r\n");
	}

	//--------------
	// execute test.
	//--------------
//	printf("\r\nExecute Test\r\n");
//	printf("------------\r\n\r\n");

//	UART_txString(DEBUG_PORT, "Uart Execute Test\r\n");
//	UART_txString(DEBUG_PORT, "-----------------\r\n\r\n");

//  print to a terminal...must have EVM connected to a PC.
//	rtn = terminal_counting();

}

//-----------------------------------------------------------------------------
// Private Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// counts/prints 0 to 10 to the debug port
// designed to be run with an RS-232 cable connecting the EVM to a
// PC with a terminal program open to view output.
//-----------------------------------------------------------------------------
uint32_t terminal_counting(void)
{
	uint32_t 	rtn;
	uint8_t 		rcv_data = 1;

	printf("--- open terminal (hyperterminal/tera term) window to view debug messages ---\r\n");

	UART_txString(DEBUG_PORT, "\n\rPls input any keys, 'q' is exit!\t");
	UART_txString(DEBUG_PORT, "\r\n");

	do
	{
		rtn = UART_rxByte(DEBUG_PORT, &rcv_data);
		if(rtn == ERR_NO_ERROR)
		{
			if(rcv_data == 'q')
			{
				rcv_data = 0;
			}
			else
			{
				UART_txByte(DEBUG_PORT, rcv_data);
			}
		}
	}while(rcv_data);

	UART_txString(DEBUG_PORT, "\r\n");
	UART_txString(DEBUG_PORT, "\n\rtest OK!\t");
	UART_txString(DEBUG_PORT, "\r\n");

	return (rtn);
}

void sentData(char *dataSent)
{
	UART_txString(DEBUG_PORT, dataSent);
}
