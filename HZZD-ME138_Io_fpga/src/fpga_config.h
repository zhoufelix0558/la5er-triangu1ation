/*
 * fpga_config.h
 *
 *  Created on: 2016Äê6ÔÂ15ÈÕ
 *      Author: Hypersen03
 */

#ifndef SRC_FPGA_CONFIG_H_
#define SRC_FPGA_CONFIG_H_

void init_load_GPIO(void);
uint32_t fpga_write(const char *buffer,uint32_t count);
void load_fpga();
#endif /* SRC_FPGA_CONFIG_H_ */
