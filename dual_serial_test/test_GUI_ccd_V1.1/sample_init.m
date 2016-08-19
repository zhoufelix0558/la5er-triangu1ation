function [ handle ] = sample_init()
%SAMPLE Summary of this function goes here
%   打开并返回串口的句柄

% Find a serial port object.
obj1 = instrfind('Type', 'serial', 'Port', 'COM7', 'Tag', '');

% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(obj1)
    obj1 = serial('COM7');
else
    fclose(obj1);
    obj1 = obj1(1);
end


% Configure instrument object, obj1.
set(obj1, 'BaudRate', 115200);

fopen(obj1);
handle = obj1;
end

