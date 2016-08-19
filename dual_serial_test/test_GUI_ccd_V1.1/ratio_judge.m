function ratio = ratio_judge( buffer_tmp )
%RATIO_JUDGE Summary of this function goes here
%   Detailed explanation goes here

if (range(buffer_tmp)>0.09)
    ratio =1;
else
    ratio = 0.00001;
end
end

