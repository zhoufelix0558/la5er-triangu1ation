% clear
% clc
% 
% load data_static_87hz.mat
% 
% len = length(data_static_87);
% cnt = 1:len;
% tic
% [fit_result, gof] = fit(cnt',data_static_87', 'poly2');
% % linearinterp
% toc
% 
% x1 = 1:len;
% y1 = 2.984/100000*x1 + 1.953;                       %x1Ğ´³ÉÁËx
% 
% 
% plot(cnt,data_static_87 - y1);
% 
% filter_data = data_static_87 - y1;

p=10.0;

data = data_static_87_filter;

predata = data(1);

for cnt =1:length(data)

[p,predata]=kalman_realtime(data,p,predata,1);


end













