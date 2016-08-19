function [ output ] = kalman_qr(data,ratio)
%data       原始数据(1xN)

p=1;


q=ratio;
r=1;


kGain=0;

prevData=sum(data)/size(data,2);
% prevData = 1000;

for i = 1:length(data)
    p=p+q;
    kGain=p/(p+r);
    temp=data(i);
    temp=prevData+(kGain*(temp-prevData));
    p=(1-kGain)*p
    prevData=temp;
    outData(i)=temp;
end

cnt=1:size(data,2);
plot(cnt,data,cnt,outData)
output = outData;

