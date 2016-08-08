function [ p,predata ] = kalman_realtime(data, p, predata,ratio)
%data       输入的数据 
%p          上一刻最优值方差
%predata    上一刻最优值
%Q          过程方差
%R          测量方差
R=1;
Q = ratio*R;
p=p+Q;
kGain = p / (p+R);
er= data - predata;
predata = predata + kGain*(data - predata);
p = (1-kGain)*p;

end

