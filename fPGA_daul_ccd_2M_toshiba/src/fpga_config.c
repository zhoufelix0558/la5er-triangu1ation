
#include "stdio.h"
#include "stdint.h"
#include "inc/trace_dsp.h"
#include "inc/gpio_c6748.h"
#include "evmomapl138.h"
#include "gpio.h"
#include "io_fpga.h"


//初始化通用IO管脚
void init_load_GPIO(void)
{

	/*
	 *   GCLK  ------ gp6 _1
	 *   PRAG_B------ gp6 _2
	 *   INIT  ------ gp6 _3
	 *   DIN   ------ gp6_ 4
	 *   DONE  -----  GP8_10
	 */

         //set gp6  and  set as output

		   write_mask_reg(PINMUX19,  0x00ffff00,0x00888800);
		   write_mask_reg(DIR67,0x1e,0x0);
	    // set gpio8_10 as gpio  and as input
		   write_mask_reg(PINMUX18,  0xf0000000,0x80000000);
		   write_mask_reg(DIR8,0x400,0x400);

         if(1)
         {
        	 uint32_t r1= read_reg(PINMUX19);
        	 uint32_t r2= read_reg(PINMUX18);
        	 uint32_t r3= read_reg(DIR67);
        	 uint32_t r4= read_reg(DIR8);
        	printf("reg  %d /n",r1);
         }

}

inline void   set_GCLK_H()
{
	   HWREG(SET_DATA8) =0x4 ;
}
inline  void   set_GCLK_L()
{
	   HWREG(CLR_DATA8) = 0x4;
}

void   set_INIT(uint8_t bitValue)
{
	   if(GPIO_PIN_LOW == bitValue)
	   {
		 HWREG(CLR_DATA67) = 0x8;
	   }
	   else if(GPIO_PIN_HIGH == bitValue)
	   {
		 HWREG(SET_DATA67) =0x8 ;
	   }
}


void   set_PRAG_B(uint8_t bitValue)
{
	   if(GPIO_PIN_LOW == bitValue)
	   {
		 HWREG(CLR_DATA67) = 0x4;
	   }
	   else if(GPIO_PIN_HIGH == bitValue)
	   {
		 HWREG(SET_DATA67) =0x4;
	   }
}


void   set_DIN(uint8_t bitValue)
{
	   if(GPIO_PIN_LOW == bitValue)
	   {
		 HWREG(CLR_DATA67) = 0x10;
	   }
	   else if(GPIO_PIN_HIGH == bitValue)
	   {
		 HWREG(SET_DATA67) =0x10 ;
	   }
}

inline uint8_t   read_DONE()
{

	uint32_t gpio_val=HWREG(IN_DATA8);
	return  (gpio_val&0x40)>>10;

}

uint32_t fpga_write(const uint8_t *buffer,uint32_t count)
{


 	int i;
	int c;
	 set_GCLK_L();
	for(c=0;c<count;c++)
    {

		uint8_t  in_data=buffer[c];
	    for (i=8; i>=0; i--)
	 	{
	    	 set_GCLK_L();             // SCL变低

	    	 set_DIN(0x1 & (in_data>>i));    //从高位到低位依次准备数据进行发送

	 		 set_GCLK_H();             // SCL变高

	 	}

    }
	 set_GCLK_L();
	 set_GCLK_H();

//　　printf("data write finished \n");
    return c;

}


void load_fpga(const uint8_t* buffer,int cnt)
{


	  uint16_t r0= fpga_read_reg(FPGA_BASE);
	 uint16_t r1= fpga_read_reg(FPGA_VER);

	printf("fpga baseaddr  %d    version %d \n",r0,r1);



	 init_load_GPIO();

	// set  PRAG_B  and init

	 set_INIT(1);
	 dsp_delay(10);
	 set_PRAG_B(1);
	 dsp_delay(10);
	 set_PRAG_B(0);
	 dsp_delay(10);

	 set_INIT(0);
	 dsp_delay(10);

	 set_PRAG_B(1);
	 dsp_delay(10);
	 set_INIT(1);
	 dsp_delay(10);
	 fpga_write(buffer,cnt);

	  int j=0;
    for(j=0;j<10;j++)
    {
	   dsp_delay(100000);
       if(read_DONE()==1)
	   {
		 printf("fpga load  finished \n");
	   }
	   else
	   {
		 printf("fpga fail to get done  \n");
	   }

   }

      r0= fpga_read_reg(FPGA_BASE);
	  r1= fpga_read_reg(FPGA_VER);

	 printf("fpga baseaddr  %d    version %d \n",r0,r1);


}


