function [flag,value] = get_axis_data(obj,axis_type)
% axis_type==0          x轴数据
% 
% 

ARR_NUM=18;
array = uint8(zeros(1,ARR_NUM));


    recdta=fread(obj,1,'uint8');                                          %读入数据
    while recdta~=36
        recdta=fread(obj,1,'uint8'); 
    end
   type1=fread(obj,1,'uint8') ; 
   type2 = fread(obj,1,'uint8') ;
   if (type1==3 && type2==axis_type)
           for write_cnt =1:ARR_NUM
               array(write_cnt) = fread(obj,1,'uint8');
    %               array(write_cnt) = fread(g,1,'uint32') ;
    %               这样读是不对的，因为程序默认的是高位在后
           end
           value = xyz_out(array(axis_type*4+1:axis_type*4+4));
           %判断是否能接收到结束位'\r'和'\n'
    %        r_val = fread(g,1,'uint8');
    %        n_val = fread(g,1,'uint8');   
    %        if(r_val==10 && n_val==13)
    %         error =1;
    %        end
        flag=1;
   else
       value = 0;
       flag=0;
    end
end
