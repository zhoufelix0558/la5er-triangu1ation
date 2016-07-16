#include<stdio.h>
#include<time.h>
#include"testdata.h"
#include "dataprocess.c"


#define RATIO 0.8			//阈值
#define POINT_NUM 2532		//一行数据的点数		(之后要改成2532)


			//thershod_step  最高的处理数据值
double zhixin(const int data[POINT_NUM], int startpoint, int endpoint,int thershod_step)
{
//	double output;
	double sum_jiaquan = 0.0;
	double sum_light =0.0 ;
//	int i0;
	int cnt;

	sum_jiaquan = 0.0;
	sum_light = 0.0;

	int step = (endpoint - startpoint) / thershod_step + 1;


	for (cnt = startpoint; cnt <= endpoint; cnt = cnt+step) {

	
	//b_cnt = startpoint + (double)cnt * step;
		//如果定点运算的话总和的这个数据会溢出

		sum_jiaquan += (double)(data[cnt]*cnt);
		sum_light += (double)data[cnt];
	}


	printf("here  %f  %f", sum_jiaquan, sum_light);

	//注意这个结果matlab的结果相差为1，因为这个软件的计数起始位不一样
	return sum_jiaquan / sum_light;
}





//计算的结果和matlab之间的差别在于matlab全部是double型
int bi_side_search(const int data[POINT_NUM], int point_notclear, int direction , double ratio, int step)
{
	int onestep=1;
	int threshold;
	int cnt;
	//int saturatedUnaryMinus=step;
	//long i0;
//	onestep = 1;


	threshold = (int)(((double)(data[0] + data[2531]) /2.0 - (double)data[point_notclear]) * ratio + (double)data[point_notclear]);
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


void point_nclear(const int data[POINT_NUM], int  step, int output[2])
{
	int num_max_tmp;
	int num_max_index_tmp;
	//int i0;
	int cnt;
	//double b_cnt;

	/* 点数为2532个。 */
	num_max_tmp = DARKEST_VALUE;
	num_max_index_tmp = 0;
	//i0 = (int)((2532.0 + (step - 1.0)) / step);
	for (cnt = 0; cnt < POINT_NUM; cnt=cnt + step) {
		//b_cnt = 1.0 + (double)cnt * step;

		if (num_max_tmp > data[cnt]) {
			num_max_tmp = data[cnt];
			num_max_index_tmp = cnt;
		}
	}

	output[0] = num_max_tmp;
	output[1] = num_max_index_tmp;
}







#define KALMAN_NUM 19
void kalman(const double data[KALMAN_NUM], double outData[KALMAN_NUM])
{
	double y;
	int k;
	double prevData;
	double p;
	double kGain;
	double temp;
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




extern int data_test[2532];
int main() {
	
	double Data[19] = { 12,12,31,13,12,12,12,21,2,1,13,11,12,12,12,12,12,12,13 };
	double OUTDATA[19] = { 0 };
	double location;
	int output[2] = { 0 };
	int leftpoint, rightpoint;
	clock_t starttime , endtime;
	starttime = clock();

//	int intData[19] = { 12,12,31,13,12,12,12,21,2,1,2,11,12,12,12,12,12,12,13 };


	point_nclear(data_test, 20, output );
	printf("unclear point select output is %d,location is %d\n", output[0], output[1]);


	leftpoint = bi_side_search(data_test, output[1], 0, RATIO, 5);
	rightpoint = bi_side_search(data_test, output[1], 1, RATIO, 5);
	printf("leftpoint = %d three piont are %d,%d,%d\n", leftpoint, data_test[leftpoint - 1], data_test[leftpoint], data_test[leftpoint + 1]);
	printf("rightpoint = %d three piont are %d,%d,%d\n", rightpoint, data_test[rightpoint - 1], data_test[rightpoint], data_test[rightpoint+1]);
	kalman(Data, OUTDATA);


	location = zhixin(data_test, leftpoint , rightpoint , 200);


	printf("facula location is %f\n", location(data_test));
	printf("end of processing---%f\n", OUTDATA[18]);
	
	int cnt = 2000;



	endtime = clock();
	printf("time cost is %1d-%1d=%1d\n" ,endtime, starttime  , endtime-starttime );/// CLOCKS_PER_SEC
	getchar();
	return 0;
}