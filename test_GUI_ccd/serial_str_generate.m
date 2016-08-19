function [ out_string ] = serial_str_generate( k , C_yaxis , up_limit , down_limit , deria_threshold, deria_speed )
% k ,积分线的斜率                                    2.3f     01.000 -99.999
% C_yaxis ,与y轴的交点                               2.3f     01.000 -99.999
% up_limit , 上限（>0）                              1.1f     1.0-9.9
% down_limit ,下限（一般为负值<-5），这里正值输出      1.1f     1.0-9.9
% deria_threshold,微分收敛的阈值                      1.2f     1.00-9.99
% deria_speed, 微分收敛的速度（约等于10）              2.3f     01.000-99.999

out_string = blanks(30);
%start signal
out_string(1) = 'A';

%k
k_str = sprintf('%2.3f',k);
if length(k_str)==5
    out_string(3:7) = k_str;
else 
    out_string(2:7) = k_str;
end

%C_yaxis
C_str = sprintf('%2.3f',C_yaxis);
if length(C_str)==5
    out_string(9:13) = C_str;
else 
    out_string(8:13) = C_str;
end

%up_limit
up_limit_str = sprintf('%1.1f',up_limit);
out_string(14:16) = up_limit_str;

%down_limit
down_limit_str = sprintf('%1.1f',down_limit);
out_string(17:19) = down_limit_str;

% deria_threshold
deria_threshold_str = sprintf('%1.2f',deria_threshold);
out_string(20:23) = deria_threshold_str;

% deria_speed
deria_speed_str = sprintf('%2.3f',deria_speed);
if length(deria_speed_str)==5
    out_string(25:29) = deria_speed_str;
else 
    out_string(24:29) = deria_speed_str;
end

%end
out_string(30) = 'B';

end

