function [ handle ] = sample_init()

% Find a serial port object.
g = instrfind('Type', 'serial', 'Port', 'COM11', 'Tag', '');
% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(g)
    g = serial('COM11');
else
    fclose(g);
    g = g(1);
end

% Configure instrument object, obj1.
% set(g, 'BaudRate', 115200);
% g=serial('com11');                                                          %创建串口对象
g.baudrate=115200;                                                           %设置波特率,缺省9600bit/s
g.parity='none';                                                           %无奇偶校验
g.stopbits=1;                                                              %停止位
g.timeout=0.5;                                                             %设置读操作完成时间为1s,缺省10s                                          
g.inputbuffersize=256;                                                     %输入缓冲区为32b，缺省值为512b

%输入接收的数据帧数
%打开串口设备
fopen(g);                                                                  %打开串口设备对象g
%进入接收循环
handle = g;
end