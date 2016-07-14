
#include "stdint.h"
#include "inc/trace_dsp.h"
#include "inc/gpio_c6748.h"
void load_fpga()
{


}
//兜兵晒宥喘IO砿重
void init_load_GPIO(void)
{

	/*
	 *
	 *   GCLK  ------ gp6 _1
	 *   PRAG_B------ gp6 _2
	 *   INIT  ------ gp6 _3
	 *   DIN   ------ gp6_ 4
	 *   DONE  -----  GP8_10
	 */

         //PINMUXING
		 write_mask_reg(PINMUX19,  0x00ffff00,0x00888800);
		 uint32_t rr= read_reg(PINMUX19);
		 write_mask_reg(DIR67,0x1e,0x4);
		 uint32_t rr2= read_reg(DIR67);
		// SW_BREAKPOINT ;


}

uint32_t fpga_write(const char *buffer,uint32_t count)
{

/*
	int i=0;
　　for(i=0;i<count;i++)
    {
	;
　　   //write buf()buf[i];
	   // set_register_bit(FPGA_CCLK);
　　}
　　printf("data write finished\n");
　　 for(i=0;i<4;i++)
     {
　  　  //set_register_bit(FPGA_CCLK);
　　   //clear_register_bit(FPGA_CCLK);
  　　}
　　  return count;
*/


	return 1;

}
