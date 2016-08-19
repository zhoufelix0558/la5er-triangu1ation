

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
//#include  "dsp_Uart.c"
#include   "interrupt.h"
#include   <math.h>

//#include  "evmomapl138_uart.h"

//0.1��ʱ��Ч���ȽϺ�
#define kalman_range_threshold  0.09
#define default_kalman_speed  0.00001
#define kalman_chase_loop 5
//#define kalman_minus_buffer_sum 0.2


extern uint32_t USTIMER_init(void);
extern void print_all_reg();

extern int  dma_over;


#define UPP_RX_LNCNT        1

//����
///   S12443_CCD    2532    �� ��֥��  TCD1254GFG    2532
#define UPP_RX_BCNT	         2532

#define UPP_DMA_BCNT	     UPP_RX_BCNT*2

uint16_t    recv_adc_buffer[UPP_RX_LNCNT*UPP_RX_BCNT];


char buffer[30];
int para_change = 0;
uint32_t rtn;
uint8_t rcv_data;
int cnt;

interrupt void _test_isr(void)
{

	if((uint8_t)DEBUG_PORT->RBR ==65)
		cnt = 0;
	if((uint8_t)DEBUG_PORT->RBR ==66)
		para_change = 1;
	buffer[cnt%30] = (uint8_t)DEBUG_PORT->RBR;
	cnt++;
}


uint32_t fpga_upp_test(void)
{


	 // ADC_CFG ����Ϊ4.�������ɼ��� ����Ϊ0�ǰ���֡���ɼ�����������ɼ�֡����

	fpga_write_reg(ADC_CFG,0x4);

	///  RUN_FR_CNT1  �ɼ�֡����
	fpga_write_reg(RUN_FR_CNT1,0x1);
	fpga_write_reg(RUN_FR_CNT2,0x0);

	///  SELECT_CCD ==0 ���ɵ�S12443_CCD       SELECT_CCD ==1   ��֥�� TCD1254GFG
	fpga_write_reg(SELECT_CCD,0x1);



	 //CCD_TINT ����ʱ��   S12443_CCD ,���÷�Χ50-5000 .����ʵ�ʵ�λΪ0.11us  .  ��֥�� TCD1254GFG  ���÷�ΧΪ1-128   ����ʵ�ʵ�λΪ10us.
	fpga_write_reg(CCD_TINT,5);


    //// uppp ��fifo ��ȡ�㡣   ���÷�Χ100-1000 .   S12443_CCD ���ο�ֵ 1000�� TCD1254GFG ���ο�ֵ 1000
	fpga_write_reg(FIFO_RD_ST,1000);
	/// CCD_ST �ɼ���ʼ��
	fpga_write_reg(CCD_ST,0);
	dsp_delay(100);
	fpga_write_reg(CCD_ST,1);
    return 0;
}


//float buffer_tmp[10128];
char show_str[50];
float mylocation;
float ratio = 0.8;
int data_second_come = 0;
int loop_num = 2;			//�ۼӵĴ�����uint16_t�ļ�����2�μ����£���֥����Ľ�����ǵ������εģ�
uint16_t buffer_int_data[2532]  ;
float buffer_tmp[2532];
uint16_t MinValue ;			//���Ĺ�߿�����Сֵ
uint16_t point_notclear,leftpoint,rightpoint;

float kalman_minus_buffer[kalman_chase_loop] = {0.5};
float kalman_buffer[kalman_chase_loop] = {0.0};
int kalman_buffer_cnt = 0;
float kalman_ratio=0.00001;
int kalman_loop_num = 0;

float buffer_float_data[2532];
float kalman_p = 20.0;
float kalman_preData = 0.0;
float kalman_result = 0.0;

float test1 ;
float test2;
float test3;

uint32_t receive_signal;
uint8_t serial_port_char;


float k=38.4, C_yaxis=9.36, up_limit=0.2, down_limit=5.0, deria_threshold=0.09, deria_speed=10;


int kalman_NAN_Error_cnt;
int frcnt = 0;
int cc=0;
int main(void)
{





	 uint32_t  REVID_reg=HWREG(SYSCONFIG_REG_BASE);
	 //�Ͼ仰ִ�����º�UART2DSP������ϣ�UART0��UART1���䣩
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

	 static int calc_cnt = 0;
		IntDSPINTCInit();
		Uart_Init_edited();
		IntRegister (C674X_MASK_INT8, _test_isr);
		IntEventMap(C674X_MASK_INT8,SYS_INT_UART2_INT);
		IntGlobalEnable();

	 while(1)
	 {
		if (para_change ==1)
		{
			para_get(buffer,&k, &C_yaxis, &up_limit, &down_limit, &deria_threshold, &deria_speed);

			para_change = 0;
		}
  		config_upp();
  		calc_cnt++;
  		recv_adc_buffer[2531]=1;
  		upp_receive_fifo(recv_adc_buffer,UPP_RX_LNCNT,UPP_DMA_BCNT);
  		cc=0;
  		receive_signal++;

  		//�͵������ٶ�̫�죬���³�����ֲtimeout��
  		//�����bufferһֱû�б�ȡ���ᵼ��overflow��ء��������������Ҫ����ʱ��ĺ����Ͳ����������

  		while(1)
  		{

  			if(recv_adc_buffer[2531]!=1  )
  			  {
  					//dsp_delay(10);

  				if (calc_cnt %loop_num ==1)
  				{	data_second_come = 1;
  					point_notclear = point_nclear_return_minValue(recv_adc_buffer, 6, &MinValue);
  					leftpoint  = bi_side_search_withMinValue(recv_adc_buffer, point_notclear, 0, ratio, 5, MinValue);
  					rightpoint = bi_side_search_withMinValue(recv_adc_buffer, point_notclear, 1, ratio, 5, MinValue);
  					Set_Zeros(buffer_int_data, leftpoint - 6, rightpoint + 6);
  					Sum_To_Int(recv_adc_buffer, buffer_int_data, leftpoint - 6, rightpoint + 6);

  				}
  				else
  				{   if(data_second_come == 1)
  					{
						Sum_To_Int(recv_adc_buffer, buffer_int_data, leftpoint - 6, rightpoint + 6);
						dsp_delay(500000);
						//Data_Average_Int(buffer_int_data, buffer_tmp , 4, 790, 850);
						region_gauss_filter(buffer_int_data, leftpoint - 6, rightpoint + 6,buffer_float_data);
						//point_notclear = point_nclear_return_maxValue(recv_adc_buffer, 20, &MaxValue);
						//������ļ������С��ԭ����չ�����߾��룬��Ȼ��ģ��Ѱ�����ֵ��ʱ�������0.0�ĵ����ˡ�
						leftpoint  = bi_side_search_float(buffer_float_data, point_notclear, 0 , ratio, 4, MinValue*2);
						rightpoint  = bi_side_search_float(buffer_float_data, point_notclear, 1 , ratio, 4, MinValue*2);
						mylocation = zhixin_downward(buffer_float_data, leftpoint, rightpoint, ratio ,MinValue);
						//dsp_delay(5000000);

						//���ֻ���
						kalman_ratio = 	kalman_ratio_adjust_para(kalman_minus_buffer,kalman_chase_loop,k,C_yaxis,up_limit,down_limit);

						//΢�ֻ���
						if(fabs(mylocation - kalman_result)>deria_threshold)
							kalman_ratio = kalman_ratio>deria_speed?kalman_ratio:deria_speed;


						/*if(kalman_buffer_cnt>kalman_chase_loop)
						{
							if(
									//(range(kalman_minus_buffer,kalman_chase_loop) > kalman_range_threshold)|
									//(max(kalman_minus_buffer,kalman_chase_loop)>kalman_range_threshold)|	//ûʲô��
									//(range(kalman_buffer,kalman_chase_loop) > 0.02)|						//ûʲô��
									(sum(kalman_minus_buffer,kalman_chase_loop)>kalman_minus_buffer_sum)
								)
								kalman_ratio = 3;
						//	if (sum(kalman_minus_buffer,kalman_chase_loop)>0.1)
						//		kalman_ratio = 0.1;
							else
								kalman_ratio = default_kalman_speed;
						}
						*/

						kalman_result = kalman_realtime(mylocation, &kalman_preData, &kalman_p, kalman_ratio);
						//������result��ʱ�����ʾΪNaN����ʱ��mylocation���Ƹ�kalman_result
						//ԭ�򣺹����ʧ��ʱ��ᵼ��kalman��ָ�����nan����inf��
						if (__isnanf(kalman_result)==1)
							{
							kalman_result = mylocation;
							kalman_NAN_Error_cnt++;
							}
						if (__isnanf(kalman_preData)==1)
							{
							kalman_preData = mylocation;
							kalman_NAN_Error_cnt++;
							}

						//���������ֵ�ʱ����Ҫ�����Ǻ��ԣ�����������ڲ�Ʒ������ʱ����˵




						//kalman_chase_loop��kalman�Ľ���ж������ٶȵ�ѡ��
						kalman_minus_buffer[kalman_buffer_cnt%kalman_chase_loop] = mylocation-kalman_result;
						kalman_buffer[kalman_buffer_cnt%kalman_chase_loop] = kalman_result;
						kalman_buffer_cnt++;
						//if(kalman_buffer_cnt%kalman_chase_loop == (kalman_chase_loop-1))

						//����΢�ֻ���(Ч���ܲ�)
						//if(fabs(mylocation - kalman_result)>kalman_range_threshold)
							//kalman_ratio = kalman_ratio>1?kalman_ratio:1;
						//test1 = range(kalman_minus_buffer,kalman_chase_loop);
						//test2 = max(kalman_minus_buffer,kalman_chase_loop);
						//test3 = range(kalman_buffer,kalman_chase_loop);


						kalman_loop_num++;
						//kalman_result1 = kalman_realtime(kalman_result, &kalman_preData1, &kalman_p1);
						//kalman_result2 = kalman_realtime(kalman_result1, &kalman_preData2, &kalman_p2);
						//mylocation = 0.235;
					  sprintf(show_str, "%7d-%4.8f-%4.8f\n",kalman_loop_num,mylocation,kalman_result);
					   str2com(show_str);
  					}
  				else
  					data_second_come =0;

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
