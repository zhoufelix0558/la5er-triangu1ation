/*
 * debug.h
 *
 *  Created on: 2016Äê5ÔÂ31ÈÕ
 *      Author: Hypersen03
 */
#include "stdint.h"
#include "hw_types.h"
#define SW_BREAKPOINT     asm(" SWBP 0 ");
#ifndef INC_TRACE_DSP_H_
#define INC_TRACE_DSP_H_

#define RET_OK                      (0)
#define ERR_AD9822_RW               (1)

inline  void    dsp_delay(int ccc)
{
   int iii=0;
   while(iii<ccc)
   {
	   iii++;
   }
}

uint32_t inline  read_reg( uint32_t addr)
{
	   return  HWREG(addr);
//	    return  *(uint32_t *)addr;
}
void inline write_reg(uint32_t addr,uint32_t val)
{
	     HWREG(addr)=val;
	   /* write 1 to every io */
//	    *(uint32_t *)addr = val;
}
// bitmask use the 1 is valid
void inline write_mask_reg(uint32_t addr,uint32_t bitmask,uint32_t val)
{
	   uint32_t regval;
	 	 /* write 1 to every io */
	   regval =  HWREG(addr);
//	   uint32_t regvala= ~bitmask;
	   regval =  (~bitmask)& (regval);
	   HWREG(addr)=(regval)|(bitmask&val);
}
#endif

/* INC_TRACE_DSP_H_ */









