function [ ratio ] = ratio_select( input )
%RATIO_SELECT Summary of this function goes here
%   Detailed explanation goes here

x1=1.3;
y1 = 0.5;

x2=1;
y2 =-5;


k = (y1-y2)/(x1-x2);
if input >=x1
    ratio_tmp = y1;
elseif input<=x2
    ratio_tmp = y2;
else
    ratio_tmp = k*input+1-x1*k;
end

ratio = power(10,ratio_tmp);

end

