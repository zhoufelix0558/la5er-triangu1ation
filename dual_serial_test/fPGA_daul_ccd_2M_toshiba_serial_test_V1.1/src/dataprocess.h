#pragma once
#include <stdint.h>
#include "dataprocess.h"
//上面这句话不加上就会显示"function "xxx" declared implicitly"

#define KALMAN_NUM 128
#define point_NUM 2532



extern void Data_Average(float float_data[], int loop_num, uint16_t leftpoint, uint16_t rightpoint);
extern void Data_Average_Int(uint16_t int_data[], float float_data[], int loop_num, uint16_t leftpoint, uint16_t rightpoint);
extern void Sum_To_Float(uint16_t data[], float float_data[], uint16_t leftpoint, uint16_t rightpoint);
extern uint16_t bi_side_search(const uint16_t data[point_NUM], uint16_t point_notclear, uint16_t direction, float ratio, uint16_t step);
extern uint16_t bi_side_search_float(const float data[point_NUM], uint16_t point_notclear, uint16_t direction, float ratio, uint16_t step,uint16_t MinValue);
extern uint16_t bi_side_search_withMinValue(const uint16_t data[point_NUM], uint16_t point_notclear, uint16_t direction, float ratio, int16_t step,uint16_t MinValue);
extern void region_gauss_filter(uint16_t data[], uint16_t startpoint, uint16_t endpoint,float float_data[]);
extern float location(const uint16_t data_test1[point_NUM]);
float location_float(float data_test1[point_NUM], uint16_t output);
extern void Sum_To_Float_4times(uint16_t data[], float float_data[], uint16_t leftpoint, uint16_t rightpoint, uint16_t startaddress);
extern void Trans_To_File(uint16_t * buffername);
extern void  Trans_To_File_float(float * result_name);
extern void interpol_trans(const uint16_t data[point_NUM], float step, uint16_t output[point_NUM]);
extern float step_location(const uint16_t * buffer1 , float step);
//extern void Sent_Data_To_Matlab(int cnt , uint16_t *buffer) ;
extern float kalman(const float data[], int kalmanloop);
extern float zhixin(const float float_data[point_NUM], uint16_t startpoint, uint16_t endpoint, uint16_t thershod_step);
extern float zhixin_downward(const float float_data[point_NUM], uint16_t startpoint, uint16_t endpoint, float ratio,uint16_t MinValue);
extern void region_gauss_filter_float(float data[], uint16_t startpoint, uint16_t endpoint);
extern uint16_t point_nclear(const uint16_t data[point_NUM], uint16_t  step);
extern uint16_t point_nclear_return_minValue(const uint16_t data[point_NUM], uint16_t  step, uint16_t *MinValue);
extern void clear_array(float array[], int length);
extern uint16_t point_nclear_jump(const uint16_t data[point_NUM*4], uint16_t  step,uint16_t jump_num);
extern uint16_t bi_side_search_jump(const uint16_t data[point_NUM * 4], uint16_t point_notclear, uint16_t direction, float ratio, uint16_t step, uint16_t jump_loop);
extern uint16_t Array_Average(uint16_t longbuffer[4 * point_NUM], float float_buffer[point_NUM]);
extern void Sum_To_Int(const uint16_t data[], uint16_t int_data[], uint16_t leftpoint, uint16_t rightpoint);
extern void Set_Zeros(uint16_t data[], uint16_t leftpoint, uint16_t rightpoint);
extern float kalman_realtime(float Data, float* preData_addr, float*p_addr,float ratio);
extern float range(float data[],int loop);
extern float max(float data[], int loop);
extern float sum(float data[],int loop);
extern float kalman_ratio_adjust(float data[],int loop);
extern float kalman_ratio_adjust_para(float data[],int loop,float k, float C_yaxis, float up_limit, float down_limit);
extern void str_get(char str[], char num[], int stpoint, int edpoint);
extern void para_get(char buffer[], float* k, float* C_yaxis, float*up_limit, float*down_limit, float*deria_threshold, float*deria_speed);




