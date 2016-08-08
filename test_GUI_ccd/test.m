% clear all; 
% close all;  
% load testdata1.mat
% N =size(loc,2);
% time = zeros(1,N);
% % rin  = zeros(1,N);
% rin = loc;
% yout  = zeros(1,N);
% du  = zeros(1,N);
% u  = zeros(1,N);
% error  = zeros(1,N);
% 
% ts=1/70; 
% sys=tf(5,[0.9,7, 0]); 
% dsys=c2d(sys,ts,'z'); 
% [num,den]=tfdata(dsys,'v');
% 
% 
% u_1=0.0;
% u_2=0.0;
% % y_1=0.0;
% % y_2=0.0;
% 
% y_1=loc(1);
% y_2=loc(1);
% 
% x=[0,0,0]';
% error_1=0;
% error_2=0;
% for k=1:1:N 
%     time(k)=k*ts;
% %     S=1; 
% %     if S==1 
% %         kp=10;
% %         ki=0.1;
% %         kd=15;               
% %         rin(k)=1;                       %Step Signal 
% %     elseif S==2     
% %         kp=10;
% %         ki=0.1;
% %         kd=15;          %Sine Signal 
% %         rin(k)=0.5*sin(2*pi*k*ts);            
% %     end 
%         kp=1;
%         ki=0;
%         kd=15;  
% 
% 
% du(k)=kp*x(1)+kd*x(2)+ki*x(3);    %PID Controller 
% u(k)=u_1+du(k); 
% 
% %Restricting the output of controller 
% if u(k)>=5           
%     u(k)=5; 
% end 
% if u(k)<=-5    
%     u(k)=-5; 
% end 
% %Linear model 
% yout(k)=-den(2)*y_1-den(3)*y_2+num(2)*u_1+num(3)*u_2;  
% error(k)=rin(k)-yout(k);  %Return of parameters 
% u_2=u_1;
% u_1=u(k); 
% y_2=y_1;
% y_1=yout(k);    
% x(1)=error(k)-error_1;          %Calculating P 
% x(2)=error(k)-2*error_1+error_2;   %Calculating D 
% x(3)=error(k);      %Calculating I  
% error_2=error_1; 
% error_1=error(k);
% end 
% 
% figure(1); 
% plot(time,rin,'b',time,yout,'r'); 
% xlabel('time(s)'),ylabel('rin,yout');  
% 
% % figure(2); 
% % plot(time,error,'r') 
% % xlabel('time(s)');ylabel('error'); 

clear
clc
load testdata.mat

p = 20.0;
N = size(loc,2);
kalman_minus_tmp = [1,0,1,0,-1];
predata = loc(1);
kalman_res = zeros(1,N);
kalman_sum= zeros(1,N);

for cnt = 1:N
    if cnt==1
        error = 0;
        kalman_minus_tmp(mod(cnt,5)+1) = error;
    else 
        error = loc(cnt) - kalman_res(cnt-1);
        kalman_minus_tmp(mod(cnt,5)+1) = error;
    end
   kalman_ratio = kalman_ratio_adjust(kalman_minus_tmp);
%     if (abs(sum(kalman_minus_tmp))>0.2)
%         kalman_ratio = 1;
%     else
%         kalman_ratio = 0.0001;
%     end
    kalman_sum(cnt) = sum(kalman_minus_tmp);
    [p, predata] = kalman_realtime(loc(cnt), p, predata,kalman_ratio);
    kalman_res(cnt) = predata;
end


plot(kal_cnt,loc)
hold on
% plot(kal_cnt,kal_result)
% hold on
plot(kal_cnt,kalman_res)
hold on 
plot(kal_cnt,kalman_sum+1630,'-o')





















