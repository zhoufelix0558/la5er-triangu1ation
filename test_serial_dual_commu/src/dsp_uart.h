/*
 * dsp_uart.h
 *
 *  Created on: 2016��7��8��
 *      Author: Hypersen03
 */
#include<stdint.h>
#ifndef SRC_DSP_UART_H_
#define SRC_DSP_UART_H_

#include "stdio.h"
#include "inc/evmomapl138.h"
#include "inc/evmomapl138_timer.h"
#include "inc/evmomapl138_uart.h"


//#ifdef _UART1
//#define DEBUG_PORT   (UART1)
//#else
#define DEBUG_PORT   (UART2)
//#endif

void Uart_Init_edited(void);
uint32_t TEST_uart(void);

void   str2com(char*  out_txt);
uint32_t  com2str(uint8_t *  out_txt);
#endif /* SRC_DSP_UART_H_ */

