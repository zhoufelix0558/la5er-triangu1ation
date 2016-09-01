#include "process.h"
#include "data.h"
#include "data1.h"
#include<stdio.h>

void save_to_file(U16*orign, U16*ekf_val, float*ratio, float*ratio_speed, int length)
{
	FILE *f;
	int i = 600;
	f = fopen("D:\\TOF_VS2015_test.csv", "wt");
	if (f == NULL)
	{
		printf("�ļ���ʧ��!\n");
		return;
	}
	else
	{
		printf("�ļ��򿪳ɹ�!\n");
		for (i = 0; i<length; i++)
			fprintf(f, "%d,%d,%f,%f\n", orign[i], ekf_val[i],ratio[i],ratio_speed[i]);
		printf("�ļ�д��ɹ�!\n");
	}
	i = fclose(f);
	if (i == 0)
		printf("�ļ��رճɹ�!\n");
	else
		printf("�ļ��ر�ʧ��!\n");



}

int main() 
{
	int cnt = 0;
	U16 result[N] = { 0 };
	float ratio_speed[N] = { 0 };
	float ratio[N] = { 0 };
	for (; cnt < N; cnt++) 
	{
		result[cnt] = adjust(test_all_array[cnt],&ratio[cnt],&ratio_speed[cnt]);
	
	}

	save_to_file(test_all_array, result,ratio,ratio_speed,N);
	
	//test_all_array

	//getchar();
	return 0;
}