clear
clc
test_num = 1;
if test_num == 1
    load('data_static_87hz.mat')
    data = data_static_87;
    NN=4000;
end
if test_num == 2
    load('step_89hz.mat')
    data = step_89hz;
end
if test_num == 3
    load('data_static_10hz.mat')
    data = data_static_10hz;
    NN = 900;
end
if test_num == 4
    load('step_10hz.mat')
    data = hz;
    NN = 170;
end
if test_num == 5
    load('dynamic_10hz.mat')
    data =hz;
    NN=160;
end
if test_num == 6
    load('dynamic_88hz.mat')
    data =hz;
    NN=1860;
end
if test_num == 7
    load('long_distance.mat')
    data =Distance;
    NN=2000;
end

str='';
% NN = 7900
for cnt=1:NN
    str = [str,num2str(round(data(cnt)*1000)),','];
end




