#include "process.h"
#define U16 unsigned short
#include<stdio.h>



float sum(float*buffer, int length)
{
	int cnt;
	float sum_val = 0;
	for (cnt = 0; cnt < length; cnt++)
	{
		sum_val += buffer[cnt];
	}
	return sum_val;
}

float ABS(float value)
{
	if (value < 0)
		return -value;
	else
		return value;

}

//输出给ratio_select函数用的指标（里面有比例和积分环节）
void fifo(float *buffer, float predata, int length)
{
	int cnt;
	for (cnt = 0; cnt < length - 1; cnt++)
	{
		buffer[cnt] = buffer[cnt + 1];
	}
	buffer[cnt] = predata;
}

float banlance(float predata, float input_data, float ratio)
{
	return ratio*input_data + (1 - ratio)*predata;
}

float powf_fast(float a, float b) {
	typedef union { float d; U32 x; } un;
//	xdata un u;
	un u;
	u.d = a;
	u.x = (b * (u.x - 1064866805) + 1064866805);
	return u.d;
}

float ratio_select(float input_data)
{
	//右边的点
	float x1 = 10.0f;
	float y1 = 0.0f;
	//左边的点
	float x2 = 5.0f;
	float y2 = -5.0f;
	float ratio_tmp;
	float k = (y1 - y2) / (x1 - x2);

	if (input_data >= x1)
		ratio_tmp = y1;
	else if (input_data <= x2)
		ratio_tmp = y2;
	else
		ratio_tmp = k*input_data + y1 - x1*k;

	return powf_fast(10, ratio_tmp);
}

U16 adjust(U16 input_data,float*ratio_tmp,float*ratio_speed_tmp)
{
	static float predata = 0;
	float ratio;
	//kf处理之后的误差
	static float vari_buffer[3] = { 0 };
	float assess_value = 0;
	static float integral_sum = 0;

//--------------参数----------------------
	//xiuzheng 初始值为0.1，越大灵敏度越大，反应速度快，但是波动相对变大
	float xiuzheng = 0.2;
	//ADJUST1初始值20，越大，反应速度越快
	float ADJUST1 = 20;

//-----------------------------------------
	assess_value = ABS(integral_sum) / RANGE_ASSUMP*xiuzheng*input_data / 10000;
	ratio = ratio_select(assess_value);

	/*
	if (((float)input_data - predata)>=500)
	{
		predata = banlance(predata, (float)input_data, 0.00001);
	printf("ratio---%f\n", ratio);
	fifo(vari_buffer, (float)input_data - predata, 3);
	integral_sum = sum(vari_buffer, 3);
	predata = predata + integral_sum / ADJUST1;
	return  (U16(predata));
	}
*/
	//比例调节
	if (ABS((float)input_data - predata)>=(DERI_RANGE*(float)input_data/10000))
				ratio = 1;
		predata = banlance(predata, (float)input_data, ratio);
		printf("ratio---%f\n", ratio);
		fifo(vari_buffer, (float)input_data - predata, 3);
		integral_sum = sum(vari_buffer, 3);
		predata = predata + integral_sum / ADJUST1;


	*ratio_tmp = ratio;
	*ratio_speed_tmp = assess_value;

	return (U16)(predata);

}