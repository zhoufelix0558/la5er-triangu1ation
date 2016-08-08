function [ p,predata ] = kalman_realtime(data, p, predata,ratio)
%data       ��������� 
%p          ��һ������ֵ����
%predata    ��һ������ֵ
%Q          ���̷���
%R          ��������
R=1;
Q = ratio*R;
p=p+Q;
kGain = p / (p+R);
er= data - predata;
predata = predata + kGain*(data - predata);
p = (1-kGain)*p;

end

