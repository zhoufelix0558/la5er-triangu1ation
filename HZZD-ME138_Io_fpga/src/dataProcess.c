//#include "STDINT.H"

//#include "string.h"
#include "triangleHeader.h"
//#include "expsp_i.h"
#include "divsp_i.h"

double sum = 0;//�͵��ݴ�
float prePeak;//�ϴ����Ľ��
float Filted[NUM_OF_FRAMES];//���������
//kalman�̳в���
float preEV = 0.0,preEP = 0.0;

float Kalman(int countForIterations,float newD)
{
	float tempEV = 0.0f,
		tempEP = 0.0f,
		EVnew = 0.0f,
		EPnew = 0.0f,
		Kgain = 0.0f,
		qqq = 0.000001f,
		rrr = 0.1f;
	int countForFrame = countForIterations % NUM_OF_FRAMES;

	if(countForFrame == 0)
	{
		EVnew = preEV = Filted[countForFrame] = newD;
		EPnew = preEP = 10.0f;
	}
	else
	{
		//kalman�˲�
		tempEV = preEV;                                 //1
		tempEP = preEP + qqq;                           //2
		Kgain = divsp_i(preEP,(preEP + rrr));           //4
		EVnew = tempEV + Kgain * (newD - tempEV);		//3
		EPnew = (1 - Kgain) * tempEP;                   //5
		preEP = EPnew;
		preEV = EVnew;
		Filted[countForFrame] = EVnew;
	}
	return EVnew;
}

float getMassCenter(int *position,int *bright, int num, int indexPeak)//��Ȩ���ķ�
{
	double brighten = 0.0f,weight = 0.0f;
	int count, distance = 0;
	sum = 0;
	brighten = 0;
	//ȡ�����������֮��,Ȩ�أ����뵹���������Ⱥ�
	for (count = 0; count <= num; count++)
	{
		distance = abs(position[count] - indexPeak);
		if(distance != 0)
		{
			weight = divsp_i((float)1,(float)distance);
		}
		else
		{
			weight = 1;
		}
		sum += bright[count] * weight * position[count];//��ֹ���  divsp_i((bright[count] * bright[count]) , 10000) * weight * position[count];
		brighten += bright[count] * weight;//��ֹ��� divsp_i((bright[count] * bright[count]) , 10000) * weight;
	}

	//�쳣����
	if (indexPeak < 5 || indexPeak > 2495 || brighten == 0) return prePeak;
	else prePeak = divsp_i(sum,brighten);
	return prePeak;
}
