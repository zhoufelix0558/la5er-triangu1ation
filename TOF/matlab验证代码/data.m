function [ output ] = data( input )
%DATA Summary of this function goes here
%   Detailed explanation goes here
% temp = uint16(0);
temp = uint16(input);
temp2= temp*412;

output = uint8(temp2/uint8(256));
end

