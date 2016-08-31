#include "process.h"
#include "data.h"
#include<stdio.h>




void save_to_file(U16*orign, U16*ekf_val, int length)
{
	FILE *f;
	int i = 600;
	f = fopen("D:\\TOF_VS2015_test.csv", "wt");
	if (f == NULL)
	{
		printf("文件打开失败!\n");
		return;
	}
	else
	{
		printf("文件打开成功!\n");
		for (i = 0; i<length; i++)
			fprintf(f, "%d,%d\n", orign[i], ekf_val[i]);
		printf("文件写入成功!\n");
	}
	i = fclose(f);
	if (i == 0)
		printf("文件关闭成功!\n");
	else
		printf("文件关闭失败!\n");



}


float powf_fast(float a, float b) {
	union { float d; int x; } u = { a };
	u.x = (int)(b * (u.x - 1064866805) + 1064866805);
	return u.d;
}

int main()
{

	

	U16 outputdata[N] = { 0 };
	int i = 0;

	for (; i < N; i++)
	{
	outputdata[i] = ext_kalman_f(data_static_87hz[i]);

	}

	save_to_file(data_static_87hz, outputdata, N);


	getchar();

}
