#include<stdio.h>
#define RATIO 0.8			//阈值
#define point_NUM 2532		//一行数据的点数		(之后要改成2532)
#include <stdint.h>

//thershod_step  最高的处理数据值
float zhixin(const uint16_t data[point_NUM], uint16_t startpoint, uint16_t endpoint, uint16_t thershod_step)
{
	//	float output;
	float sum_jiaquan = 0.0;
	float sum_light = 0.0;
	//	uint16_t i0;
	uint16_t cnt;

	sum_jiaquan = 0.0;
	sum_light = 0.0;

	uint16_t step = (endpoint - startpoint) / thershod_step + 1;


	for (cnt = startpoint; cnt <= endpoint; cnt = cnt + step) {


		//b_cnt = startpoint + (float)cnt * step;
		//如果定点运算的话总和的这个数据会溢出

		sum_jiaquan += (float)(data[cnt] * cnt);
		sum_light += (float)data[cnt];
	}


	//pruint16_tf("here  %f  %f", sum_jiaquan, sum_light);

	//注意这个结果matlab的结果相差为1，因为这个软件的计数起始位不一样
	return sum_jiaquan / sum_light;
}





//计算的结果和matlab之间的差别在于matlab全部是float型
uint16_t bi_side_search(const uint16_t data[point_NUM], uint16_t point_notclear, uint16_t direction, float ratio, uint16_t step)
{
	uint16_t onestep = 1;
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







#define KALMAN_NUM 19
void kalman(const float data[KALMAN_NUM], float outData[KALMAN_NUM])
{
	float y;
	uint16_t k;
	float prevData;
	float p;
	float kGain;
	float temp;
	y = data[0];
	for (k = 0; k < 18; k++) {
		y += data[k + 1];
	}

	prevData = y / 19.0;
	p = 20.0;
	for (k = 0; k < 19; k++) {
		p += 0.001;
		kGain = p / (p + 1.0);
		temp = prevData + kGain * (data[k] - prevData);
		p *= 1.0 - kGain;
		prevData = temp;
		outData[k] = temp;
	}
}


float location(uint16_t data_test1[point_NUM]){
	uint16_t output,leftpoint,rightpoint;
	float location;
    output = point_nclear(data_test1, 20);
	//pruint16_tf("unclear point select output is %d\n", output);
	leftpoint = bi_side_search(data_test1, output, 0, RATIO, 5);
	rightpoint = bi_side_search(data_test1, output, 1, RATIO, 5);
	//pruint16_tf("left %d----right %d\n", leftpoint, rightpoint);
	//kalman(Data, OUTDATA);
	location = zhixin(data_test1, leftpoint, rightpoint, 200);
	//pruint16_tf("location  --%f\n", location);
	return location;
}
