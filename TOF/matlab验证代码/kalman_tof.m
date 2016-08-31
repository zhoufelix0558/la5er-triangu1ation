% function [ output_args ] = kalman_tof( input)
%KALMAN_TOF Summary of this function goes here
%   Detailed explanation goes here
%data       输入的数据 
%p          上一刻最优值方差
%predata    上一刻最优值
%Q          过程方差
%R          测量方差
clear
clc
test_num = 7;
if test_num == 1
    load('data_static_87hz.mat')
    data = data_static_87
end
if test_num == 2
    load('step_89hz.mat')
    data = step_89hz;
end
if test_num == 3
    load('data_static_10hz.mat')
    data = data_static_10hz;
end
if test_num == 4
    load('step_10hz.mat')
    data = hz;
end
if test_num == 5
    load('dynamic_10hz.mat')
    data =hz;
end
if test_num == 6
    load('dynamic_88hz.mat')
    data =hz;
end
if test_num == 6
    load('long_distance.mat')
    data =Distance;
end
if test_num ==7
    
    data=xdata;
end 


NN = length(data);

%先验
error_buffer = zeros(1,3);
error_buffer_array = zeros(1,NN);
range_error_buffer = zeros(1,NN);
%后验
vari_buffer = rand(1,3);
vari_buffer_array = zeros(1,NN);
jifen_error_array = zeros(1,NN);
%预估值
p=10;
predata = 0;

ratio_buffer = zeros(1,NN);
p_tmp = zeros(1,NN);
kalman_result = zeros(1,NN);
vari_buffer_array = zeros(1,3);
jifen_leiji = 0;

for cnt = 1:NN
    input = data(cnt);
    
    error_buffer(1) = error_buffer(2);
    error_buffer(2) = error_buffer(3);
    error_buffer(3) = input - predata;
%     error_buffer
    error_buffer_array(cnt) = input - predata;
%     ratio = abs(range(error_buffer)/range(vari_buffer))/10;
bizhi = range(error_buffer)/0.4;

%修正后的值，不然的话data_static_87会出现一个突变点
%对于80hz静态最好的数值为0.8
%对于阶跃80hz最好的数值为1.0
%对于动态响应最好的数值为1.0-2.0
xiuzheng = 1.2;
jifen = abs(jifen_leiji/0.4*xiuzheng);

bizhi = max(bizhi,jifen);

range_error_buffer(cnt) = range(error_buffer);
    ratio = ratio_select(bizhi);
    ratio_buffer(cnt) = ratio;

%     if ratio ==inf
%         ratio = 3;
%     end
    
    [p,predata] = kalman_realtime(input,p,predata,ratio);
    kalman_result(cnt) = predata;
    p_tmp(cnt)=p; 
    vari_buffer(1) = vari_buffer(2);
    vari_buffer(2) = vari_buffer(3);
    vari_buffer(3) = input - predata;
    jifen_leiji = vari_buffer(1)+vari_buffer(2)+vari_buffer(3);
        jifen_error_array(cnt) = vari_buffer(1)+vari_buffer(2)+vari_buffer(3);
%     vari_buffer
    vari_buffer_array(cnt) = input - predata;
end
 plot(1:NN,data,1:NN,kalman_result)
 hold on
%  plot(1:NN,jifen_error_array)
% plot(1:NN,log10(ratio_buffer))
%  plot(1:NN,range_error_buffer/0.4);

