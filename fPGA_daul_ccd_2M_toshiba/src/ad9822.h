

#include "stdint.h"
#ifndef ___AD9822_H
#define ___AD9822_H

uint8_t     AD_writeRegister(uint8_t in_reg_addr, uint16_t in_data);
uint16_t    AD_readRegister(uint8_t in_reg_addr);
void        test_AD9822_reg();
uint32_t     init_9822();
void GPIO_AD_init();

#endif


