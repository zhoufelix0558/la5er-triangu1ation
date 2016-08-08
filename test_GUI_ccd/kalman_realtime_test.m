
N = size(kal_cnt,2);
kalman_adjust = zeros(1,N);
loop_num = 5;
buffer_tmp = zeros(1,loop_num);
kalman_ratio = 1;
p = 20.0;
predata = 0.0;



for cnt = 1:N
    if cnt > loop_num
        kalman_ratio = ratio_judge(buffer_tmp);
    end
    
    if cnt==1
        buffer_tmp(mod(cnt,loop_num)+1) = loc(cnt) - buffer_tmp(1);
        [ p,predata ] = kalman_realtime(loc(cnt), p, predata,kalman_ratio);
        kalman_adjust(cnt) = predata;
    else
       buffer_tmp(mod(cnt,loop_num)+1) = loc(cnt) - buffer_tmp(mod(cnt -1,loop_num)+1);
        [ p,predata ] = kalman_realtime(loc(cnt), p, predata,kalman_ratio);
        kalman_adjust(cnt) = predata;
    end

    
end


plot(kal_cnt,loc,kal_cnt,kal_result,kal_cnt,kalman_adjust)
