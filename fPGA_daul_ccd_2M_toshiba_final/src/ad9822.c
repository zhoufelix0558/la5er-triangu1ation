

#include <src/ad9822.h>
#include "stdio.h"
#include "hw_types.h"
#include "evmomapl138.h"
#include "inc/trace_dsp.h"
#include "inc/GPIO_C6748.h"
#include "evmomapl138.h"
#include "gpio.h"

inline void   set_scl_H();
inline void   set_scl_L();

void  inline  set_scl(uint8_t bitValue);
void  inline  set_sda(uint8_t bitValue);
void  inline  set_en(uint8_t bitValue);
void  inline  set_sdadir(uint8_t flag);
uint8_t inline read_sda();
void           sdio_write_byte(uint8_t  b);
uint8_t        sdio_read_byte();

inline  void    delay(int ccc)
{
   int i=0;
   while(i<ccc)
   {
	   i++;
   }
}

void      test_AD9822_reg()
{

	 delay(100);
	 delay(100);
	 uint16_t rr2=AD_readRegister(2);
	 delay(100);
	 uint16_t r0=AD_readRegister(0x0);
	 delay(200);
	 uint16_t r1=AD_readRegister(0x1);
	 delay(200);
	 uint16_t r3=AD_readRegister(0x2);
	 delay(200);
	 uint16_t r4=AD_readRegister(0x3);
	 delay(200);
	 SW_BREAKPOINT ;
	 delay(1000000);

}
uint32_t  init_9822()
{
	 GPIO_AD_init();
	 delay(100);
	 uint16_t R0;
	 uint16_t R1;
	 uint16_t R2;
	 uint16_t R5;
	 R0=0x0040;
	 R1=0x0040;
	 R2=0;
	// R5=100;   ///TCD1245 冰松的推荐值为R5=100

	 R5 = 0x1f;//东芝 推荐值0x1f或者0x13f
//	 R5=100;   ///S12443

	 AD_writeRegister(0,R0);
	 uint16_t r=AD_readRegister(0x0);
	 if(r!=R0)
	 {
		 SW_BREAKPOINT ;
		 return ERR_AD9822_RW;
	 }
	 AD_writeRegister(1,R1);
	 r=AD_readRegister(0x1);

	 if(r!=R1)
	 {
		 SW_BREAKPOINT ;

		 return ERR_AD9822_RW;
	 }


	 AD_writeRegister(2,R2);
	 r=AD_readRegister(0x2);

	 if(r!=R2)
	 {
			 SW_BREAKPOINT ;

			 return ERR_AD9822_RW;
	 }
	 AD_writeRegister(5,R5);
	 r=AD_readRegister(0x5);
	 if(r!=R5)
	 {
			 SW_BREAKPOINT ;
			 return ERR_AD9822_RW;
	 }
	 return RET_OK;
}
uint8_t  AD_writeRegister(uint8_t in_reg_addr, uint16_t in_data)
{
	uint8_t A2,A1,A0;
	A2=(in_reg_addr&0x4)>>2;
	A1=(in_reg_addr&0x2)>>1;
	A0=in_reg_addr&0x1;

	set_scl_L();	delay(2);
	set_scl_H();	delay(2);
	set_scl_L();	delay(2);
	set_sdadir(GPIO_DIR_OUTPUT);
	set_en(1);
	set_en(0);
	//设置SDA方向为输入
	set_sda(0x0);   delay(1);
	set_scl_H(); 	delay(2);
	set_scl_L();	delay(2);
	set_sda(A2);	delay(2);
	set_scl_H();	delay(2);
	set_scl_L();	delay(2);
	set_sda(A1);	delay(2);
	set_scl_H();	delay(2);
	set_scl_L();	delay(2);
	set_sda(A0);	delay(2);
	set_scl_H();	delay(2);
	set_scl_L();	delay(2);
//////////////////////////////
	set_sda(1);delay(2);
	set_scl_H();delay(2);
	set_scl_L();delay(2);
	set_sda(1);delay(2);
	set_scl_H();delay(2);
	set_scl_L();delay(2);
	set_sda(1);delay(2);
	set_scl_H();delay(2);

	int i=0;
    for (i=8; i>=0; i--)
	{
			set_scl_L();             // SCL变低
			delay(1);
			set_sda(0x1 & (in_data>>i));    //从高位到低位依次准备数据进行发送
			delay(1);
			set_scl_H();             // SCL变高
			delay(1);
	}
    set_en(1);  delay(2);
    set_scl_L();delay(2);
	set_scl_H();delay(2);
	set_scl_L();delay(2);
	set_sdadir(GPIO_DIR_INPUT);
    return RET_OK;

}

//-----------------------------------------------------------------------------
uint16_t  AD_readRegister(uint8_t in_reg_addr)
{


	    uint8_t A2,A1,A0;
		A2=(in_reg_addr&0x4)>>2;
		A1=(in_reg_addr&0x2)>>1;
		A0=in_reg_addr&0x1;
	    set_sdadir(GPIO_DIR_OUTPUT);

	    set_scl_L();  delay(2);
	    set_scl_H();  delay(2);
	    set_scl_L();  delay(2);

	    set_en(1);      delay(2);
	    delay(2);
		set_en(0);
		delay(2);
		set_scl_L();
		set_sda(1);			  delay(2);  // read
		set_scl_H();		  delay(2);
   		set_scl_L();		  delay(2);
		set_sda(A2);		  delay(2);
		set_scl_H();		  delay(2);
		set_scl_L();		  delay(2);
		set_sda(A1);          delay(2);
		set_scl_H();		  delay(2);
		set_scl_L();		  delay(2);
		set_sda(A0);		  delay(2);
		set_scl_H();		  delay(2);

		set_scl_L();		  delay(2);
		set_scl_H();	      delay(2);
		set_scl_L();		  delay(2);
		set_scl_H();		  delay(2);
		set_scl_L();		  delay(2);set_sdadir(GPIO_DIR_INPUT);
		set_scl_H();
		set_sdadir(GPIO_DIR_INPUT);
		delay(2);
		int i;
		uint16_t  r = 0;
		for (i=8; i>=0; i--)
		{
				set_scl_L();         // SCL变低
				delay(1);
				set_scl_H();         // SCL变高
				r = (r <<1) | read_sda();      //从高位到低位依次准备数据进行读取
				delay(1);
		}
		delay(2);
		set_en(1);
		set_scl_L();    delay(2);
		set_scl_H();    delay(2);
		set_scl_L();    delay(2);

		return (r);
}


/*
 *
 *   clk ------ gp6 pin= 1
 *   sda ------ gp6 pin= 2
 *   en  ------ gp6 pin= 3
 */
void GPIO_AD_init()
{
	//PINMUXING
	 write_mask_reg(PINMUX19,  0x00ffff00,0x00888800);
	 uint32_t rr= read_reg(PINMUX19);
	 write_mask_reg(DIR67,0x1e,0x4);
	 uint32_t rr2= read_reg(DIR67);

}
void  set_en(uint8_t bitValue)
{

	if(GPIO_PIN_LOW == bitValue)
	 {
	     HWREG(CLR_DATA67) = 0x8;
	 }
	 else if(GPIO_PIN_HIGH == bitValue)
	 {
	     HWREG(SET_DATA67) = 0x8;
	 }

}
inline void   set_scl_H()
{
	 HWREG(SET_DATA67) =0x2 ;
}
inline  void   set_scl_L()
{
	 HWREG(CLR_DATA67) = 0x2;
}

void   set_scl(uint8_t bitValue)
{

	 if(GPIO_PIN_LOW == bitValue)
	 {
		     HWREG(CLR_DATA67) = 0x2;
	 }
	 else if(GPIO_PIN_HIGH == bitValue)
	 {
		     HWREG(SET_DATA67) =0x2 ;
	 }
}

void   set_sda(uint8_t bitValue)
{
	 if(GPIO_PIN_LOW == bitValue)
	 {
		 HWREG(CLR_DATA67) = 0x4;
	 }
	 else if(GPIO_PIN_HIGH == bitValue)
	 {
		 HWREG(SET_DATA67) =0x4 ;
	 }
}

uint8_t   read_sda()
{
	uint32_t gpio_val=HWREG(IN_DATA67);

	return  (gpio_val&0x4)>>2;

}
void   set_sdadir(uint8_t flag)
{
	if(flag==GPIO_DIR_OUTPUT)
	{
		 write_mask_reg(DIR67,0x4,0x0);
	}
	else if(flag==GPIO_DIR_INPUT)
	{
		 write_mask_reg(DIR67,0x4,0x4);
	}
}
