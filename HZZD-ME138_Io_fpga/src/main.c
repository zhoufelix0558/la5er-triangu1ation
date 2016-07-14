#include  <math.h>
#include  <time.h>
#include  <stdio.h>
#include  "ad9822.h"

#include  "inc/evmomapl138.h"
#include  "hw_types.h"
#include  "inc/trace_dsp.h"
#include   <c6x.h>
#include  "inc/hzzduart.h"
#include  <src/Io_fpga.h>
#include  "fpga_config.h"
#include  "fpga_upp.h"
#include "divsp_i.h"
#include "inc/evmomapl138_timer.h"
#include "inc/evmomapl138_uart.h"

extern uint32_t USTIMER_init(void);
extern void print_all_reg();
extern float Kalman(int countForIterations,float newD);
extern float getMassCenter(int *pos,int *bri, int number,int indexPeak);
extern void sentData(char *dataSent);
extern float NN();
extern int gaussFilter(int *soucedata);
extern int  data_ready;

#define UPP_RX_LNCNT    1 //֡��
#define UPP_RX_BCNT	    5064
#define NUM_pixels      2500//��Ԫ��
#define NUM_FRAMES   	128
#define NUM_ACT_POINTS 	200

//uint8_t frame_buffer[UPP_RX_BCNT] = { 0 };
//uint8_t* buffer0 = (uint8_t *)0xC1000000;
//uint8_t* buffer1 = (uint8_t *)0xC2000000;
extern uint8_t buffer[5064];
//uint16_t buffer0[UPP_RX_LNCNT * UPP_RX_BCNT] = { 0 };
//uint16_t buffer1[UPP_RX_LNCNT * UPP_RX_BCNT] = { 0 };

char dataSent[32];
long long clockA = 0, clockB = 0, clockC = 0;
int16_t intensity[NUM_pixels] = { 0 };

int countForIterations = 0,
	indexNN = 0;//���������������������,trigger = 0
int bright[NUM_ACT_POINTS] = {0},
	position[NUM_ACT_POINTS]={0}; //ѡ���ĵ�
int candidate[5][2] = { 0 };
int NUMofMCP = 0;//������

float MCPeaks[NUM_FRAMES] = { 0 },
	NNresult[100] = { 0 },
	nnaaaa = 0,
	gggaaa = 0,
	mmcccc = 0,
	kkkaaa = 0;
FILE *result_NN, *center_MC;

uint32_t fpga_upp_test()
{
	uint32_t retVal = ERR_NO_ERROR;
	//int fcnt=UPP_RX_LNCNT;
	config_upp();
	//fpga_write_reg(RUN_FR_CNT,fcnt);
	fpga_write_reg(CCD_TINT,5);   //���û���ʱ�䣨ʮ΢�룩
	fpga_write_reg(CCD_START,0);
	dsp_delay(100);
	fpga_write_reg(CCD_START,1);
	fpga_write_reg(FIFO_rd_pos,4500);
	//retVal = upp_receive_fifo(buffer,UPP_RX_LNCNT,5064,trigger);
	return retVal;
}

void dataProcess(int num, int indexPeak)
{
	NUMofMCP = countForIterations % 128;
	mmcccc = MCPeaks[NUMofMCP] = getMassCenter(position,bright,num,indexPeak);
	mmcccc *= 5.252;
	if(mmcccc != 0) //������Ч֡��
	{
		if(NUMofMCP != 127) Kalman(countForIterations,MCPeaks[NUMofMCP]);
		else
		{
			kkkaaa = Kalman(countForIterations,MCPeaks[NUMofMCP])*5.252;

			//clockB=clock();//�������
			//clockC=clockB-clockA;//������ĵ�λ�Ǻ���

			sprintf(dataSent,"%f\r\n",kkkaaa);//���
			sentData(dataSent);//���ڴ�ӡ����

			//clockA=clock();//���⿪ʼ��ʱ
		}
		countForIterations++;//��¼֡��
	}

}

int get_focus(int candy)//��λ֡��������
{
	int cddt = 0,
		worst = 10,
		worstindex = 0,
		best = 0,
		ifnew = 1,
		i = 0,j = 0;
	if(countForIterations % NUM_FRAMES == 0)//��ʼ��
	{
		for(i = 0;i < 5;i++)
		{
			for(j = 0; j<2;j++)
			{
				candidate[i][j] = 0;
			}
		}
	}
	for(i = 0;i < 5;i++)//��¼��
	{
		if(candidate[i][0] == candy)
		{
			candidate[i][1]++;
			ifnew = 0;
			break;
		}
		else if(candidate[i][0] == 0)
		{
			candidate[i][0] = candy;
			candidate[i][1]++;
			ifnew = 0;
			break;
		}
	}
	for(i = 0;i < 5;i++)
	{
		if(candidate[i][1] < worst)//���ٵ�
		{
			worstindex = i;
			worst = candidate[i][1];
		}
		if(candidate[i][1] > best)//����
		{
			best = candidate[i][1];
			cddt = candidate[i][0];
		}
	}
	if(ifnew)//�滻���ٵ�
	{
		candidate[worstindex][0] = candy;
		candidate[worstindex][1] = 1;
	}
	return cddt;
}

int get_subIndex()
{
	NUMofMCP = countForIterations % NUM_FRAMES;
	return NUMofMCP;
}

//�������ȣ�ѡ����
void frameProcess(uint8_t *buffer)
{
	int i = 0,
		sumFirst = 0,
		startPoint = 0,
		tempPeak = 0,
		indexPeak = 0,
		index = 0;
	int	rangeMark = 1000,//ѡ����ֵ
		valid_NUM = 0;

	sumFirst = 0;
	for(i = 0;i < UPP_RX_BCNT; i++)
	{
		uint32_t  h = buffer[i];
		uint32_t  l = buffer[i + 1];
		uint32_t u16 = (h<<8)+(l);
		u16 = u16>>2;

		if(i > 4 && i < 22) sumFirst += u16;//ѡ��������ʮ����Ԫ�������׼ֵ
		else if(i == 22) startPoint = sumFirst>>3; //�ų�����С��������
		if(i > 30 && i < UPP_RX_BCNT - 32)
		{
			index = i>>1 - u16;
			intensity[index] = startPoint - u16;//��Ч����

			if(intensity[index] > rangeMark)//��һ��ѡ��
			{
				if (intensity[index] > tempPeak)//ѡȡ������
				{
					tempPeak = intensity[index];
					indexPeak = index;
				}
				bright[valid_NUM] = intensity[index];
				position[valid_NUM++] = index;
				//selectedindex[valid_NUM++] = index;
				//if(valid_NUM == 199)//��ֹ���
				//{
				//	valid_NUM = 0;
				//	rangeMark += 100;
				//	i = 32;
				//}
			}
		}
	}
	//�ڶ���ѡ��
	index = 0;
	indexPeak = get_focus(indexPeak);
	dataProcess(index,indexPeak);
}



int main(void)
{
	uint32_t REVID_reg=HWREG(SYSCONFIG_REG_BASE);
	if(REVID_reg!=0x4E840102)
	{
		//printf("fail to read revid ,error debug ");
		SW_BREAKPOINT;
		return 1;
	}

	EVMOMAPL138_init();
	EVMOMAPL138_initRAM();
	init_9822();
	load_fpga();
	EMIF_init();

	clockA=clock();//���⿪ʼ��ʱ
	clockB=clock();//�������
	clockC=clockB-clockA;//������ĵ�λ�Ǻ���
	printf("the time cost is %d\n", clockC);
	USTIMER_init();
	fpga_upp_test();
	upp_receive_fifo(buffer,1,5064);			//����һ��buffer��copy



	while(1)
	{

		dsp_delay(1);

			while(1)
		{
			dsp_delay(1);
			if(data_ready)
			{countForIterations++;
				//frameProcess();
			//	printf("the NO.%d frame", countForIterations);
				config_upp();
				upp_receive_fifo(buffer,UPP_RX_LNCNT,5064);
				//frameProcess();

				//trigger = trigger == 1 ? 0 : 1; //�ɼ�һ�λ�һ�������ַ����
				//if(trigger != 0)
				//{
				//	upp_receive_fifo(buffer1,UPP_RX_LNCNT,5064,trigger);
				//	frameProcess(buffer0);
				//}
				//else
				//{
				//	upp_receive_fifo(buffer0,UPP_RX_LNCNT,5064,trigger);
				//	frameProcess(buffer1);
				//}
			}
		}



	}
}






//
