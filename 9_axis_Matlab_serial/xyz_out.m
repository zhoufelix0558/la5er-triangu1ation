function x = xyz_out(data)
%ACCEL_OUT Summary of this function goes here
%   Detailed explanation goes here
% data_in
% if type==1
%     x=typecast(data_in(1)*16777216+data_in(2)*65536+data_in(3)*256+data_in(4),'single');
%    
%     y=typecast(data_in(5)*16777216+data_in(6)*65536+data_in(7)*256+data_in(8),'single');
% 
%     z=typecast(data_in(9)*16777216+data_in(10)*65536+data_in(11)*256+data_in(12),'single');
% 
% end
    data = uint32(data);
%     data_in = uint32(zeros(1,0));
    data_in= data(1)*16777216+data(2)*65536+data(3)*256+data(4);
%     data_in(2) = data(5)*16777216+data(6)*65536+data(7)*256+data(8);
%     data_in(3) = data(9)*16777216+data(10)*65536+data(11)*256+data(12);
    
    x = single(typecast(data_in,'int32'))/65536;
%     y = single(typecast(data_in(2),'int32'))/65536;
%     z = single(typecast(data_in(3),'int32'))/65536;

end

