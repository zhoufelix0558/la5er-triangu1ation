% data_static_87_16bit = uint16(zeros(1,4181));
% 
% data_static_87_16bit = round(1000*data_static_87);
% error = data_static_87_16bit - 1000*data_static_87;

clear
clc
load data_static_87hz.mat

kalman_qr(data_static_87_filter , 0.001);



 
