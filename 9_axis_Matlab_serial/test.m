%三路数据
% Accelerometer         加速度计
% Gyroscope             陀螺仪
% Compass               电子罗盘


clear;clc;                                                                 %清除变量
g=serial('com11');                                                          %创建串口对象
g.baudrate=115200;                                                           %设置波特率,缺省9600bit/s
g.parity='none';                                                           %无奇偶校验
g.stopbits=1;                                                              %停止位
g.timeout=0.5;                                                             %设置读操作完成时间为1s,缺省10s                                          
g.inputbuffersize=256;                                                     %输入缓冲区为32b，缺省值为512b
%设置
recbuf=zeros(1,40);                                                        %清接收缓冲区（40）        
framelen=23;                                                               %帧长度（每帧23byte)
framenum=0;                                                                %清接收帧数
rectr=0;                                                                   %接收计数器清零
xctr=0;
%输入接收的数据帧数
%打开串口设备
fopen(g);                                                                  %打开串口设备对象g
%进入接收循环

LOOP_TIME_CNT =100                                              %读出数据的量
x_tmp = single(zeros(1,LOOP_TIME_CNT));
time_tmp = single(zeros(1,LOOP_TIME_CNT));
cpu_time = single(zeros(1,LOOP_TIME_CNT));
ARR_NUM=18;
array = uint8(zeros(1,ARR_NUM));
error = 0;
loop_cnt=0;
loop=1;
while loop~=LOOP_TIME_CNT+1                                                   %
       recdta=fread(g,1,'uint8');                                          %读入数据
       if recdta==36
           loop_cnt = 1;
       end
       
       if loop_cnt==1
           type1=fread(g,1,'uint8') ; 
           type2 = fread(g,1,'uint8') ;
           if (type1==3 && type2==0)
               for write_cnt =1:ARR_NUM
                   array(write_cnt) = fread(g,1,'uint8');
    %               array(write_cnt) = fread(g,1,'uint32') ;
    %               这样读是不对的，因为程序默认的是高位在后
               end
               [x_tmp(loop),y,z] = xyz_out(array(1:12));
               if loop==1
                   start_clock = clock;
               else
                   time_tmp(loop)=etime(clock,start_clock);
               end
               loop = loop+1;
               %判断是否能接收到结束位'\r'和'\n'
               r_val = fread(g,1,'uint8');
               n_val = fread(g,1,'uint8');   
               if(r_val==10 && n_val==13)
                error =1;
               end
          end
           
       end
       loop_cnt =0;
  end
fclose(g);                                                                 %关闭串口                                                               
delete(g);                                                                 %删除串口对象
clear g ;       
plot(x_tmp)