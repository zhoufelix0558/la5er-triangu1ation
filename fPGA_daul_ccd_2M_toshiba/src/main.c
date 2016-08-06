

#define  DEBUG

#include   <src/ad9822.h>
#include   "stdio.h"
#include   "inc/evmomapl138.h"
#include   "hw_types.h"
#include   "inc/trace_dsp.h"
#include   <c6x.h>
#include   <src/Io_fpga.h>
#include   "fpga_config.h"
#include   "fpga_upp.h"
#include   "nand_flash.h"
#include   "string.h"
#include   "dsp_uart.h"
#include   "dataprocess.h"

extern uint32_t USTIMER_init(void);
extern void print_all_reg();

extern int  dma_over;


#define UPP_RX_LNCNT        1

//调整
///   S12443_CCD    2532    ； 东芝的  TCD1254GFG    2532
#define UPP_RX_BCNT	         2532

#define UPP_DMA_BCNT	     UPP_RX_BCNT*2

uint16_t    recv_adc_buffer[UPP_RX_LNCNT*UPP_RX_BCNT];


uint32_t fpga_upp_test(void)
{


	 // ADC_CFG 设置为4.是连续采集， 设置为0是按照帧数采集（参照下面采集帧数）

	fpga_write_reg(ADC_CFG,0x4);

	///  RUN_FR_CNT1  采集帧数，
	fpga_write_reg(RUN_FR_CNT1,0x1);
	fpga_write_reg(RUN_FR_CNT2,0x0);

	///  SELECT_CCD ==0 冰松的S12443_CCD       SELECT_CCD ==1   东芝的 TCD1254GFG
	fpga_write_reg(SELECT_CCD,0x1);



	 //CCD_TINT 积分时间   S12443_CCD ,设置范围50-5000 .积分实际单位为0.11us  .  东芝的 TCD1254GFG  设置范围为1-128   积分实际单位为10us.
	fpga_write_reg(CCD_TINT,5);


    //// uppp 的fifo 读取点。   设置范围100-1000 .   S12443_CCD ：参考值 1000， TCD1254GFG ：参考值 1000
	fpga_write_reg(FIFO_RD_ST,1000);
	/// CCD_ST 采集开始。
	fpga_write_reg(CCD_ST,0);
	dsp_delay(100);
	fpga_write_reg(CCD_ST,1);
    return 0;
}
void savetofile(uint8_t * buffer,int linecnt)
{
	FILE	*fp;
    int i;
	fp = fopen("../uppdata.txt", "wb");
	if (fp == NULL)
	{
		printf("Open file error!");
		return ;
	}
    int line=0;
	for(line=0;line<linecnt;line++)
	{
		fwrite("line\r\n", 6, 1, fp);
		for(i=0;i<2516;i=i+2)
		{
			char val[10];
			uint32_t u16= buffer[i];
			u16=(u16<<8)+buffer[i+1];
			sprintf(val," %d \r\n",u16);
			fwrite(val, 10, 1, fp);
		}

	}
    fclose(fp);

}

uint32_t  Loadfromfile(uint8_t*  buffer)
{
	FILE	*fp;
	fp = fopen("../me138.bin", "rb");
	if (fp == NULL)
	{
		printf("Open file error!");
		SW_BREAKPOINT;
		return 0;
	}
	fseek(fp, 0L, SEEK_END);

	long  flen=ftell(fp);
	uint32_t  byte_cnt=flen;
	fseek(fp, 0L, SEEK_SET);
	fread(buffer, byte_cnt, 1, fp);
	fclose(fp);
	SW_BREAKPOINT;
    return   byte_cnt;

}
void print_reg(uint32_t base,int cnt)
{
    int i=0;
	for(i=0;i<cnt;i++)
	{
		uint32_t  r1=read_reg(base+i*4);
		printf("r%d  %X  \n",i, r1);

	}
}



//float buffer_tmp[10128];
float mylocation;
float ratio = 0.8;
int loop_num = 2;			//累加的次数，uint16_t的极限是2次及以下（东芝输出的结果就是叠加两次的）
uint16_t buffer_int_data[2532]  ;
float buffer_tmp[2532];
uint16_t MinValue ;			//检测的光斑可能最小值
uint16_t point_notclear,leftpoint,rightpoint;

int kalman_loop_num = 0;
float buffer_float_data[2532];
float kalman_p = 20.0;
float kalman_preData = 0.0;
float kalman_result = 0.0;

int main(void)
{



	 uint32_t  REVID_reg=HWREG(SYSCONFIG_REG_BASE);
	 if(REVID_reg!=0x4E840102)
	 {
		 printf("fail to read revid ,error debug ");
		 SW_BREAKPOINT ;
		 return 1;
	 }
	 dsp_delay(200);

	 EMIF_init();
	 UPP_PINMUX();
	 test_fpga_reg();

	 // uint32_t  bcnt=  Loadfromfile(ptr);
	// int j=0;
     memset(recv_adc_buffer,0,UPP_RX_BCNT);
	 TEST_uart();

	// load_fpga(ptr,bcnt);
	 init_9822();
	 fpga_upp_test();

	 config_upp();
	 int frcnt = 0;
	 int cc=0;
	 static int calc_cnt = 0;

	 while(1)
	 {
  		config_upp();
  		calc_cnt++;
  		recv_adc_buffer[2531]=1;
  		upp_receive_fifo(recv_adc_buffer,UPP_RX_LNCNT,UPP_DMA_BCNT);
  		cc=0;
  		char show_str[50];

  		//送的数据速度太快，导致程序移植timeout，
  		//好像和buffer一直没有被取出会导致overflow相关。如果程序不运行需要大量时间的函数就不会出现问题

  		while(1)
  		{

  			if(recv_adc_buffer[2531]!=1  )
  			  {
  					//dsp_delay(10);

  				if (calc_cnt %loop_num ==1)
  				{
  					point_notclear = point_nclear_return_minValue(recv_adc_buffer, 6, &MinValue);
  					leftpoint  = bi_side_search_withMinValue(recv_adc_buffer, point_notclear, 0, ratio, 5, MinValue);
  					rightpoint = bi_side_search_withMinValue(recv_adc_buffer, point_notclear, 1, ratio, 5, MinValue);
  					Set_Zeros(buffer_int_data, leftpoint - 5, rightpoint + 5);
  					Sum_To_Int(recv_adc_buffer, buffer_int_data, leftpoint - 5, rightpoint + 5);

  				}
  				else
  				{
  					Sum_To_Int(recv_adc_buffer, buffer_int_data, leftpoint - 5, rightpoint + 5);
  					//dsp_delay(500000);
  					//Data_Average_Int(buffer_int_data, buffer_tmp , 4, 790, 850);
  					region_gauss_filter(buffer_int_data, leftpoint - 5, rightpoint + 5,buffer_float_data);
  					//point_notclear = point_nclear_return_maxValue(recv_adc_buffer, 20, &MaxValue);
  					leftpoint  = bi_side_search_float(buffer_float_data, point_notclear, 0 , ratio, 5, MinValue*2);
  					rightpoint  = bi_side_search_float(buffer_float_data, point_notclear, 1 , ratio, 5, MinValue*2);
  					mylocation = zhixin_downward(buffer_float_data, leftpoint, rightpoint, ratio ,MinValue);
  					kalman_result = kalman_realtime(mylocation, &kalman_preData, &kalman_p);

  					kalman_loop_num++;
  					//kalman_result1 = kalman_realtime(kalman_result, &kalman_preData1, &kalman_p1);
  					//kalman_result2 = kalman_realtime(kalman_result1, &kalman_preData2, &kalman_p2);
  					//mylocation = 0.235;
  				  //sprintf(show_str, "location = %f\t\t",kalman_result2);
  				   //str2com(show_str);
  				// Set_Zeros(buffer_int_data,745,865);
  				 // memset(buffer_int_data,0,sizeof(uint16_t) * 900);
  				}


//

  				frcnt++;
  				if(frcnt%2000 ==0)
  				{
  					uint16_t r0= fpga_read_reg(UPP_CNT);
  				    sprintf(show_str, " A %d %d %d ",frcnt,r0,cc);
  				    str2com(show_str);
  				}
  				break;

  			  }
  			cc++;
  			if(cc>80000)
  			{
  				uint16_t r0= fpga_read_reg(UPP_CNT);
  				sprintf(show_str, "B %d %d %d ",calc_cnt,r0,cc);
  				str2com(show_str);
  				break;

  			}
  		}
  		//str2com(show_str);
  		//continue;




//    SW_BREAKPOINT ;
	//  printf("end of ccd  \n");



	//  printf("over windows %d %d %d %d  \n",light[24],light[25],light[2028],light[2029]);


	 }

}
