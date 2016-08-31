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

//�����ratio_select�����õ�ָ�꣨�����б����ͻ��ֻ��ڣ�
void fifo(float *buffer, float predata, int length)
{
	int cnt;
	for (cnt = 0; cnt < length - 1; cnt++)
	{
		buffer[cnt] = buffer[cnt + 1];
	}
	buffer[cnt] = predata;
}


//ͨ����������ֵѡ��ͬ�������ٶ�
float ratio_select(float input_data)
{
	//�ұߵĵ�
	float x1 = 1.3;
	float y1 = 0.5;
	//��ߵĵ�
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


//�Ľ����extend kalman filter�㷨
U16 ext_kalman_f(U16 input_data)
{	//predataΪ�ϴ�Ԥ�����ֵ
	static float predata = 0;
	float ratio;
	//kf����֮ǰ�����
	static float error_buffer[3] = { 0,0,0 };
	//kf����֮������
	static float vari_buffer[3] = { 0,0,0 };
	float ratio_value;
	float assess_value;
	static float integral_sum = 0;
	//fifo��д����
	fifo(error_buffer, (float)input_data - predata, 3);

	assess_value = range(error_buffer, 3) / RANGE_ASSUMP;
	//�������ֵ����Ȼ�Ļ�data_static_87�����һ��ͻ���
	//����80hz��̬��õ���ֵΪ0.8
	//���ڽ�Ծ80hz��õ���ֵΪ1.0
	//���ڶ�̬��Ӧ��õ���ֵΪ1.0 - 2.0
	//�˴���0.4���ź��˲�����µļ���
	float xiuzheng = 5;
	static float integral_accum = 0;
	integral_accum = fabs(integral_sum / RANGE_ASSUMP*xiuzheng);
	//���ַ�ʽ����Ľ��ȡ���ֵ��
	ratio_value = integral_accum > assess_value ? integral_accum : assess_value;
	//p�ĳ�ֵ����̬��ʱ��p�����ratio�Ĵ�С����������
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
