/*
 * GPIO_C674x.h
 *
 *  Created on: 2016Äê6ÔÂ1ÈÕ
 *      Author: Hypersen03
 */

#ifndef INC_GPIO_C6748_H_
#define INC_GPIO_C6748_H_

/// direct do the address ,no to cal the offset
#define GPIO_baseAdd   0x01E26000


#define DIR67       GPIO_baseAdd+0x88
#define OUT_DATA67  GPIO_baseAdd+0x8c
#define SET_DATA67  GPIO_baseAdd+0x90
#define CLR_DATA67  GPIO_baseAdd+0x94
#define IN_DATA67   GPIO_baseAdd+0x98




#define DIR8        GPIO_baseAdd+0xB0
#define OUT_DATA8   GPIO_baseAdd+0x84
#define SET_DATA8   GPIO_baseAdd+0xb8
#define CLR_DATA8   GPIO_baseAdd+0xbc
#define IN_DATA8    GPIO_baseAdd+0xc0


#define SYSCFG      0x01C14000

#define PINMUX1     SYSCFG+0x120
#define PINMUX2     SYSCFG+0x124
#define PINMUX3     SYSCFG+0x128
#define PINMUX4     SYSCFG+0x12c
#define PINMUX5     SYSCFG+0x130
#define PINMUX6     SYSCFG+0x134
#define PINMUX7     SYSCFG+0x13c
#define PINMUX8     SYSCFG+0x140
#define PINMUX9     SYSCFG+0x144
#define PINMUX10     SYSCFG+0x148
#define PINMUX11     SYSCFG+0x14c
#define PINMUX12     SYSCFG+0x150
#define PINMUX13     SYSCFG+0x154
#define PINMUX14     SYSCFG+0x158
#define PINMUX15     SYSCFG+0x15c
#define PINMUX16     SYSCFG+0x160
#define PINMUX17     SYSCFG+0x164
#define PINMUX18     SYSCFG+0x168
#define PINMUX19     SYSCFG+0x16c


#endif



/* INC_GPIO_C6748_H_ */
