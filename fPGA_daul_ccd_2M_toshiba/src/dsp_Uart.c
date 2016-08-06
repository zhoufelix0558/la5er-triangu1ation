


#include "stdio.h"
#include "inc/evmomapl138.h"
#include "inc/evmomapl138_timer.h"
#include "inc/evmomapl138_uart.h"


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
uint32_t TEST_uart(void)
{
	uint32_t rtn;

	rtn = UART_init(DEBUG_PORT, 115200);
	if (rtn != ERR_NO_ERROR)
	{
		//printf("error initializing uart!\r\n");
		return (rtn);
	}

	//--------------
	// execute test.
	//--------------
	//printf("\r\nExecute Test\r\n");
	//printf("---asbba---------\r\n\r\n");

	UART_txString(DEBUG_PORT, "Uart Execute Test\r\n");
	UART_txString(DEBUG_PORT, "--------aasbbb---------\r\n\r\n");

	// print to a terminal...must have EVM connected to a PC.
//	rtn = terminal_counting();

	return (rtn);
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
	uint32_t 	    rtn;
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
	}

	while(rcv_data);

	UART_txString(DEBUG_PORT, "\r\n");
	UART_txString(DEBUG_PORT, "\n\rtest OK!\t");
	UART_txString(DEBUG_PORT, "\r\n");

	return (rtn);
}
void   str2com(char*  out_txt)
{
	UART_txString(DEBUG_PORT, out_txt);
//	UART_txString(DEBUG_PORT, "\r\n");
}
