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


#define PINMUX19    0x01C1416C



#endif



/* INC_GPIO_C6748_H_ */
