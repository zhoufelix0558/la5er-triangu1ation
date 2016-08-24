%��·����
% Accelerometer         ���ٶȼ�
% Gyroscope             ������
% Compass               ��������


clear;clc;                                                                 %�������
g=serial('com11');                                                          %�������ڶ���
g.baudrate=115200;                                                           %���ò�����,ȱʡ9600bit/s
g.parity='none';                                                           %����żУ��
g.stopbits=1;                                                              %ֹͣλ
g.timeout=0.5;                                                             %���ö��������ʱ��Ϊ1s,ȱʡ10s                                          
g.inputbuffersize=256;                                                     %���뻺����Ϊ32b��ȱʡֵΪ512b
%����
recbuf=zeros(1,40);                                                        %����ջ�������40��        
framelen=23;                                                               %֡���ȣ�ÿ֡23byte)
framenum=0;                                                                %�����֡��
rectr=0;                                                                   %���ռ���������
xctr=0;
%������յ�����֡��
%�򿪴����豸
fopen(g);                                                                  %�򿪴����豸����g
%�������ѭ��

LOOP_TIME_CNT =100                                              %�������ݵ���
x_tmp = single(zeros(1,LOOP_TIME_CNT));
time_tmp = single(zeros(1,LOOP_TIME_CNT));
cpu_time = single(zeros(1,LOOP_TIME_CNT));
ARR_NUM=18;
array = uint8(zeros(1,ARR_NUM));
error = 0;
loop_cnt=0;
loop=1;
while loop~=LOOP_TIME_CNT+1                                                   %
       recdta=fread(g,1,'uint8');                                          %��������
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
    %               �������ǲ��Եģ���Ϊ����Ĭ�ϵ��Ǹ�λ�ں�
               end
               [x_tmp(loop),y,z] = xyz_out(array(1:12));
               if loop==1
                   start_clock = clock;
               else
                   time_tmp(loop)=etime(clock,start_clock);
               end
               loop = loop+1;
               %�ж��Ƿ��ܽ��յ�����λ'\r'��'\n'
               r_val = fread(g,1,'uint8');
               n_val = fread(g,1,'uint8');   
               if(r_val==10 && n_val==13)
                error =1;
               end
          end
           
       end
       loop_cnt =0;
  end
fclose(g);                                                                 %�رմ���                                                               
delete(g);                                                                 %ɾ�����ڶ���
clear g ;       
plot(x_tmp)