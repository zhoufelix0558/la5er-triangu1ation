#include<stdio.h>
#include"testdata.h"
#include"dataprocess.h"

//extern float location(const int data_test1[POINT_NUM]);

int main() {
	float locationval;
	locationval = location (data_test);
	printf("location is %f\n", locationval);


	getchar();

}