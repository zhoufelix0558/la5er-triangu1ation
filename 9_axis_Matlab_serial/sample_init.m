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
% g=serial('com11');                                                          %�������ڶ���
g.baudrate=115200;                                                           %���ò�����,ȱʡ9600bit/s
g.parity='none';                                                           %����żУ��
g.stopbits=1;                                                              %ֹͣλ
g.timeout=0.5;                                                             %���ö��������ʱ��Ϊ1s,ȱʡ10s                                          
g.inputbuffersize=256;                                                     %���뻺����Ϊ32b��ȱʡֵΪ512b

%������յ�����֡��
%�򿪴����豸
fopen(g);                                                                  %�򿪴����豸����g
%�������ѭ��
handle = g;
end