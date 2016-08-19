function ratio = kalman_ratio_adjust(kalman_minus_tmp)


sum_num = abs(sum(kalman_minus_tmp));
value = 38.46*sum_num-9.73/3;
if value <= -5
    value = -5;
end
if value>=0
    value = 0;
end
ratio = 10^value;
end

% A=[ 0.2,1; 0.05,1];
% B=[0;-5];
% inv(A)*B