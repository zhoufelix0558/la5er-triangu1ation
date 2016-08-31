#include "process.h"
#include<math.h>
#define U16 unsigned short

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


float range(float*buffer, int length)
{
	int cnt;
	float Max_tmp = 0, Min_tmp = 0;
	for (cnt = 0; cnt < length; cnt++)
	{
		if (buffer[cnt] < Min_tmp)
			Min_tmp = buffer[cnt];
		if (buffer[cnt] > Max_tmp)
			Max_tmp = buffer[cnt];
	}
	return Max_tmp - Min_tmp;
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


//通过给定的数值选择不同的收敛速度
float ratio_select(float input_data)
{
	//右边的点
	float x1 = 1.3;
	float y1 = 0.5;
	//左边的点
	float x2 = 1;
	float y2 = -5;
	float ratio_tmp;
	float k = (y1 - y2) / (x1 - x2);

	if (input_data >= x1)
		ratio_tmp = y1;
	else if (input_data <= x2)
		ratio_tmp = y2;
	else
		ratio_tmp = k*input_data + 1 - x1*k;

	return pow(10, ratio_tmp);
}


//改进后的extend kalman filter算法
U16 ext_kalman_f(U16 input_data)
{	//predata为上次预测的数值
	static float predata = 0;
	float ratio;
	//kf处理之前的误差
	static float error_buffer[3] = { 0,0,0 };
	//kf处理之后的误差
	static float vari_buffer[3] = { 0,0,0 };
	float ratio_value;
	float assess_value;
	static float integral_sum = 0;
	//fifo上写数据
	fifo(error_buffer, (float)input_data - predata, 3);

	assess_value = range(error_buffer, 3) / RANGE_ASSUMP;
	//修正后的值，不然的话data_static_87会出现一个突变点
	//对于80hz静态最好的数值为0.8
	//对于阶跃80hz最好的数值为1.0
	//对于动态响应最好的数值为1.0 - 2.0
	//此处的0.4是信号滤波后大致的极差
	float xiuzheng = 5;
	static float integral_accum = 0;
	integral_accum = fabs(integral_sum / RANGE_ASSUMP*xiuzheng);
	//两种方式计算的结果取最大值。
	ratio_value = integral_accum > assess_value ? integral_accum : assess_value;
	//p的初值，静态的时候p会根据ratio的大小进行收敛。
	static float p = 5;


	ratio = ratio_select(ratio_value);

	float kGain;
	p += ratio;
	kGain = p / (p + 1);
	predata = predata + kGain*(float)((int)input_data - predata);
	p = (1.0 - kGain)*p;

	fifo(vari_buffer, (float)input_data - predata, 3);
	integral_sum = sum(vari_buffer, 3);

	return U16(predata);
}
