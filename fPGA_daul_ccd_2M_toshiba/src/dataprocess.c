//#include <hzzduart.h>
#define  _CRT_SECURE_NO_WARNINGS



#include<stdio.h>
#define RATIO 0.8			//阈值
#define point_NUM 2532		//一行数据的点数		(之后要改成2532)?
#include <stdint.h>
#include <math.h>

#define LIGHT_MAX 13969.0


void Data_Average(float float_data[], int loop_num, uint16_t leftpoint, uint16_t rightpoint)
{
	int cnt = 0;
	for (cnt = leftpoint; cnt <= rightpoint; cnt++)
		float_data[cnt] = float_data[cnt] / loop_num;
}


void Data_Average_Int(uint16_t int_data[], float float_data[] , int loop_num, uint16_t leftpoint, uint16_t rightpoint)
{
	int cnt = 0;
	for (cnt = leftpoint; cnt <= rightpoint; cnt++)
		float_data[cnt] = (float)int_data[cnt] / loop_num;
}


void Sum_To_Float(uint16_t data[], float float_data[], uint16_t leftpoint, uint16_t rightpoint)
{
	int cnt;
	for (cnt = leftpoint; cnt <= rightpoint; cnt++)
		float_data[cnt] = float_data[cnt] + (float)(data[cnt]);
}


//（这地方要改）要尽量避免浮点型的计算，能用整型的地方就用整型
void Sum_To_Float_4times(uint16_t data[], float float_data[], uint16_t leftpoint, uint16_t rightpoint,uint16_t startaddress)
{
	int cnt;
	leftpoint = leftpoint + startaddress;
	rightpoint = rightpoint + startaddress;
	for (cnt = leftpoint; cnt <= rightpoint; cnt++)
		float_data[cnt] = float_data[cnt] + (float)(data[cnt]);
}


//质心算法之前的在region的范围中对高斯滤波处理（coff进行卷积）
//直接传入数组改值是可以的，如果不想被改动，加上const就行
void region_gauss_filter(uint16_t data[], uint16_t startpoint, uint16_t endpoint, float float_data[])
{
	float sum = 0.0;
	float coff[5] = { 1, 4, 6, 4, 1 };
	uint16_t DATA_CNT, GAUSS_CNT;

	float_data[20] = (float)data[20];
	float_data[2510] = (float)data[2510];

	for (DATA_CNT = startpoint; DATA_CNT <= endpoint; DATA_CNT++)
	{
		//sum_data = 0.0;
		sum = 0.0;
		for (GAUSS_CNT = 0; GAUSS_CNT < 5; GAUSS_CNT++)
		{
			sum = sum + (float)data[DATA_CNT + GAUSS_CNT - 2] * coff[GAUSS_CNT];
			//sum_data = sum_data + data[DATA_CNT + GAUSS_CNT];
		}
		float_data[DATA_CNT] = (uint16_t)(sum / 16.0);
	}
}

void region_gauss_filter_float(float data[], uint16_t startpoint, uint16_t endpoint)
{
	float sum = 0.0;
	float coff[5] = { 1, 4, 6, 4, 1 };
	uint16_t DATA_CNT, GAUSS_CNT;
	for (DATA_CNT = startpoint; DATA_CNT <= endpoint; DATA_CNT++)
	{
		//sum_data = 0.0;
		sum = 0.0;
		for (GAUSS_CNT = 0; GAUSS_CNT < 5; GAUSS_CNT++)
		{
			sum = sum + data[DATA_CNT + GAUSS_CNT - 2] * coff[GAUSS_CNT];
			//sum_data = sum_data + data[DATA_CNT + GAUSS_CNT];
		}
		data[DATA_CNT] = (uint16_t)(sum / 16.0);
	}
}

//thershod_step  最高的处理数据值
float zhixin(const float float_data[point_NUM], uint16_t startpoint, uint16_t endpoint, uint16_t thershod_step)
{
	//	float output;
	float sum_jiaquan = 0.0;
	float sum_light = 0.0;
	//	uint16_t i0;
	uint16_t cnt;


	uint16_t step = (endpoint - startpoint) / thershod_step + 1;


	for (cnt = startpoint; cnt <= endpoint; cnt = cnt + step) {


		//b_cnt = startpoint + (float)cnt * step;
		//如果定点运算的话总和的这个数据会溢出

		sum_jiaquan += ((LIGHT_MAX - float_data[cnt]) * (LIGHT_MAX - float_data[cnt]) * cnt / 10000);
		sum_light += (LIGHT_MAX - float_data[cnt]) * (LIGHT_MAX - float_data[cnt]) / 10000;
	}


	//pruint16_tf("here  %f  %f", sum_jiaquan, sum_light);

	//注意这个结果matlab的结果相差为1，因为这个软件的计数起始位不一样
	return sum_jiaquan / sum_light;
}

float zhixin_downward(const float float_data[point_NUM], uint16_t startpoint, uint16_t endpoint,  float ratio ,uint16_t MinValue)
{
	float thershold;
	float sum_jiaquan = 0.0;
	float sum_light = 0.0;
	//	uint16_t i0;
	uint16_t cnt;
	//uint16_t step = (endpoint - startpoint) / thershod_step + 1;
	thershold = (float)(MinValue)*(1-ratio) + ratio*(float)(float_data[20]+float_data[2510])/2.0;

	for (cnt = startpoint; cnt <= endpoint; cnt ++) {


		//b_cnt = startpoint + (float)cnt * step;
		//如果定点运算的话总和的这个数据会溢出

		sum_jiaquan += ((thershold - float_data[cnt] ) * (thershold - float_data[cnt] ) * cnt / 10000);
		sum_light += (thershold - float_data[cnt]) * (thershold - float_data[cnt]) / 10000;
	}

	//pruint16_tf("here  %f  %f", sum_jiaquan, sum_light);

	//注意这个结果matlab的结果相差为1，因为这个软件的计数起始位不一样
	return sum_jiaquan / sum_light;
}

//计算的结果和matlab之间的差别在于matlab全部是float型
uint16_t bi_side_search(const uint16_t data[point_NUM], uint16_t point_notclear, uint16_t direction, float ratio, int16_t step)
{
	int16_t onestep = 1;
	uint16_t threshold;
	uint16_t cnt;
	//uint16_t saturatedUnaryMinus=step;
	//long i0;
	//	onestep = 1;


	threshold = (uint16_t)(((float)(data[0] + data[2531]) / 2.0 - (float)data[point_notclear]) * ratio + (float)data[point_notclear]);
	cnt = point_notclear;
	if (direction == 0) {
		step = -step;
	}
	else {
		onestep = -1;
	}

	while (data[cnt] <= threshold) {
		cnt = cnt + step;
	}
	cnt = cnt + onestep;

	while (data[cnt] > threshold) {
		cnt = cnt + onestep;
	}
	return cnt;
}
uint16_t bi_side_search_float(const float data[point_NUM], uint16_t point_notclear, uint16_t direction, float ratio, uint16_t step,uint16_t MinValue)
{
	int16_t onestep = 1;
	float threshold;
	uint16_t cnt;
	//uint16_t saturatedUnaryMinus=step;
	//long i0;
	//	onestep = 1;
	threshold = (float)(MinValue)*(1-ratio) + ratio*(float)(data[20]+data[2510])/2.0;
	//threshold = (((data[0] + data[2531]) / 2.0 - data[point_notclear]) * ratio + data[point_notclear]);
	cnt = point_notclear;
	if (direction == 0) {
		step = -step;
	}
	else {
		onestep = -1;
	}

	while (data[cnt] <= threshold) {
		cnt = cnt + step;
	}
	//cnt = cnt + onestep;

	while (data[cnt] > threshold) {
		cnt = cnt + onestep;
	}
	return cnt;
}

uint16_t bi_side_search_withMinValue(const uint16_t data[point_NUM], uint16_t point_notclear, uint16_t direction, float ratio, int16_t step,uint16_t MinValue)
{
	int16_t onestep = 1;
	uint16_t threshold;
	uint16_t cnt;
	//threshold = (uint16_t)(((float)(data[0] + data[2531]) / 2.0 - (float)data[point_notclear]) * ratio + (float)data[point_notclear]);
	threshold = (uint16_t)((float)(MinValue)*(1-ratio) + ratio*(float)(data[20]+data[2510])/2.0);
	cnt = point_notclear;
	if (direction == 0) {		//左边
		step = -step;
	}
	else {
		onestep = -1;
	}

	while (data[cnt] <= threshold) {
		cnt = cnt + step;
	}
	//cnt = cnt + onestep;

	while (data[cnt] > threshold) {
		cnt = cnt + onestep;
	}
	return cnt;
}

#define DARKEST_VALUE 16383   //理论最暗值

uint16_t point_nclear(const uint16_t data[point_NUM], uint16_t  step)
{
	uint16_t num_max_tmp;
	uint16_t num_max_index_tmp;
	//uint16_t i0;
	uint16_t cnt;
	//float b_cnt;

	/* 点数为2532个。 */
	num_max_tmp = DARKEST_VALUE;
	num_max_index_tmp = 0;
	//i0 = (uint16_t)((2532.0 + (step - 1.0)) / step);
	for (cnt = 0; cnt < point_NUM; cnt = cnt + step) {
		//b_cnt = 1.0 + (float)cnt * step;

		if (num_max_tmp > data[cnt]) {
			num_max_tmp = data[cnt];
			num_max_index_tmp = cnt;
		}
	}
	return  num_max_index_tmp;
}

uint16_t point_nclear_return_minValue(const uint16_t data[point_NUM], uint16_t  step, uint16_t *MinValue)
{
	uint16_t num_min_tmp;
	uint16_t num_min_index_tmp;
	//uint16_t i0;
	uint16_t cnt;
	//float b_cnt;

	/* 点数为2532个。 */
	num_min_tmp = 16383*2;
	num_min_index_tmp = 0;
	//i0 = (uint16_t)((2532.0 + (step - 1.0)) / step);
	for (cnt = 0; cnt < point_NUM; cnt = cnt + step) {
		//b_cnt = 1.0 + (float)cnt * step;

		if (num_min_tmp > data[cnt]) {
			num_min_tmp = data[cnt];
			num_min_index_tmp = cnt;
		}
	}
	*MinValue = num_min_tmp;
	return  num_min_index_tmp;
}



//#define KALMAN_NUM 128
float kalman(const float data[],int kalmanloop)
{
	float outData;
	float y;
	uint16_t k;
	float prevData;
	float p;
	float kGain;
	float temp;
	y = data[0];
	for (k = 0; k < kalmanloop; k++) {
		y += data[k + 1];
	}

	prevData = y / kalmanloop;
	p = 20.0;
	for (k = 0; k < kalmanloop; k++) {
		p += 0.001;
		kGain = p / (p + 1.0);
		temp = prevData + kGain * (data[k] - prevData);
		p *= 1.0 - kGain;
		prevData = temp;
		outData = temp;
	}
	return outData;
}


float location(uint16_t data_test1[point_NUM]) {
	uint16_t output, leftpoint, rightpoint;
	float float_dat[point_NUM];
	float my_location;
	output = point_nclear(data_test1, 20);
	//pruint16_tf("unclear point select output is %d\n", output);
	leftpoint = bi_side_search(data_test1, output, 0, RATIO, 5);
	rightpoint = bi_side_search(data_test1, output, 1, RATIO, 5);
	region_gauss_filter(data_test1, leftpoint, rightpoint, float_dat);
	//pruint16_tf("left %d----right %d\n", leftpoint, rightpoint);
	//kalman(Data, OUTDATA);
	//2016年7月25
	//2016年7月19日修改
	//
	//region_gauss_filter(data_test1, leftpoint, rightpoint);

	my_location = zhixin(float_dat, leftpoint, rightpoint, 200);
	//pruint16_tf("location  --%f\n", location);
	return my_location;
}


float location_float(float data_test1[point_NUM], uint16_t output)
{
	uint16_t leftpoint, rightpoint;
	leftpoint = bi_side_search_float(data_test1, output, 0, RATIO, 5,15383);
	rightpoint = bi_side_search_float(data_test1, output, 1, RATIO, 5,15383);
	region_gauss_filter_float(data_test1, leftpoint, rightpoint);
	return zhixin(data_test1, leftpoint, rightpoint, 200);
}

void Trans_To_File(uint16_t * buffername)
{
	FILE *fp;
	int i;
	fp = fopen("laserdata.csv", "a+");
	if (fp == NULL)
	{
		printf("File cannot open! ");
		//      exit(0);
	}
	//输入5名员工的工号，并保存到文件中
	for (i = 0; i < 2531; i++)
	{
		fprintf(fp, "%d,", buffername[i]);
	}
	fprintf(fp, "%d\n", buffername[i]);
	printf("log%d ", i);
	fclose(fp);

	// return 0;
}


void  Trans_To_File_float(float * result_name) {
	FILE *fp;
	int i;
	fp = fopen("zhixindata128.csv", "a+");
	if (fp == NULL)
	{
		printf("File cannot open! ");
		//      exit(0);
	}
	//保存到文件中
	for (i = 0; i < 127; i++)
	{
		fprintf(fp, "%f,", result_name[i]);
	}



	fprintf(fp, "%f\n", result_name[i]);
	printf("zhixindata128 succeed \n");
	fclose(fp);

}


void interpol_trans(const uint16_t data1[point_NUM], float step, uint16_t output[point_NUM])
{
	int cnt;
	output[0] = data1[0];
	output[point_NUM] = data1[point_NUM];
	for (cnt = 0; cnt < point_NUM - 1; cnt++) {

		output[cnt + 1] = (uint16_t)((-step)*(float)(data1[cnt] - data1[cnt + 1]) + (float)data1[cnt + 1]);
		//output[cnt+1]= (uint16_t)((-step)*(data1[cnt]-data1[cnt+1])+data1[cnt+1]);
		// output[cnt + 1] = (uint16_t)(-((((2.0 + (double)cnt) - step) - (2.0 + (double)cnt)) *(data[cnt] - data[cnt + 1])) + data[cnt + 1]);
	}

}

float step_location(const uint16_t * buffer1, float step)
{
	uint16_t output_data1[point_NUM];

	interpol_trans(buffer1, step, output_data1);

	return location(output_data1);
	//return 0.0;

}



//float location_float()



/*

void Sent_Data_To_Matlab(int cnt , uint16_t *buffer)
{
	int NUM_SENT;
	for (NUM_SENT = 0; NUM_SENT < 2532; NUM_SENT++ )
	{
		char string[20] = {0};
		sprintf(string, "%d,%d,%d\n", cnt,NUM_SENT,buffer[NUM_SENT]);
		sentData(string);
	}
}

*/


void clear_array(float array[], int length)
{
	int cnt;
	for (cnt = 0; cnt < length ; cnt++)
		array[cnt] = 0.0;
}




//处理一下过采样四个点的数组
uint16_t point_nclear_jump(const  uint16_t data[point_NUM*4], uint16_t  step,uint16_t jump_num)
{
	uint16_t num_max_tmp;
	uint16_t num_max_index_tmp;
	//uint16_t i0;
	uint16_t cnt;
	//float b_cnt;

	//点数为2532个。
	num_max_tmp = DARKEST_VALUE;
	num_max_index_tmp = 0;
	//i0 = (uint16_t)((2532.0 + (step - 1.0)) / step);
	for (cnt = 0; cnt < point_NUM*4; cnt = cnt + step*jump_num) {
		//b_cnt = 1.0 + (float)cnt * step;

		if (num_max_tmp > data[cnt]) {
			num_max_tmp = data[cnt];
			num_max_index_tmp = cnt;
		}
	}
	return  num_max_index_tmp>>4;
	//返回的值还是和单帧采集是一样的
}


uint16_t bi_side_search_jump(const uint16_t data[point_NUM*4], uint16_t point_notclear, uint16_t direction, float ratio, uint16_t step, uint16_t jump_loop)
{
	int16_t onestep = jump_loop;
	uint16_t threshold;
	uint16_t cnt;
	//uint16_t saturatedUnaryMinus=step;
	//long i0;
	//	onestep = 1;


	threshold = (uint16_t)(((float)(data[0] + data[2531]) / 2.0 - (float)data[point_notclear]) * ratio + (float)data[point_notclear]);
	cnt = point_notclear*jump_loop;
	if (direction == 0) {
		step = -step;
	}
	else {
		onestep = -1;
	}

	while (data[cnt] <= threshold) {
		cnt = cnt + step*jump_loop;
	}
	cnt = cnt + onestep;

	while (data[cnt] > threshold) {
		cnt = cnt + onestep;
	}
	return cnt>>2;
}

//4倍ADC采样频率的预处理
//返回值为模糊的最小点
uint16_t Array_Average(uint16_t longbuffer[4 * point_NUM], float float_buffer[point_NUM])
{
	uint16_t output, leftpoint, rightpoint;
	int pro_cnt;
	uint16_t buffer_tmp[point_NUM] = {0};
	//函数出错
	output = point_nclear_jump(longbuffer, 20, 4);
	leftpoint = bi_side_search_jump(longbuffer, output, 0, RATIO, 5, 4) - 3;
	rightpoint = bi_side_search_jump(longbuffer, output, 1, RATIO, 5, 4) + 3;


	for (pro_cnt = leftpoint*4; pro_cnt <= rightpoint*4; pro_cnt= pro_cnt+4)
		{
			buffer_tmp[pro_cnt] = longbuffer[pro_cnt] + longbuffer[pro_cnt + 1] + longbuffer[pro_cnt + 2] + longbuffer[pro_cnt + 3];
			float_buffer[pro_cnt] = (float)buffer_tmp[pro_cnt]/4.0;
		}
	return output;

}




void Sum_To_Int(const uint16_t data[], uint16_t int_data[], uint16_t leftpoint, uint16_t rightpoint)
{
	int cnt;
	for (cnt = leftpoint; cnt <= rightpoint; cnt++)
		int_data[cnt] = int_data[cnt] + data[cnt];
	//以下是两个基准点
	int_data[20] = int_data[20] + data[20];
	int_data[2510] = int_data[2510] + data[2510];
}

void Set_Zeros(uint16_t data[], uint16_t leftpoint, uint16_t rightpoint)
{
	int cnt;

	for (cnt = leftpoint; cnt <= rightpoint; cnt++)
	{
		data[cnt] = 0;
	}
	//以下是两个基准点
	data[20] = 0;
	data[2510] = 0;
}


float kalman_realtime(float Data, float* preData_addr, float*p_addr)
{
	float kGain;
	*p_addr += 0.00001;
	kGain = *p_addr / (*p_addr + 1);
	*preData_addr = *preData_addr + kGain*(Data - *preData_addr);
	*p_addr = (1.0 - kGain)*(*p_addr);
	return *preData_addr;
}


