function [ num,location,kalman_result ] = str_cong_d_f_f( data )
%STR_CONG_D_F_F Summary of this function goes here
%   Detailed explanation goes here
% num = double()
    try
        data1 = regexp(data, '-', 'split');
        num             = str2double(data1(1));
        location        = str2double(data1(2));
        kalman_result   = str2double(data1(3));
    catch ME
        num = 0;
        location = 0;
        kalman_result = 0;
    end
end

