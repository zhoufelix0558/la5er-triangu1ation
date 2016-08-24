function varargout = x_axis_analysis(varargin)
% X_AXIS_ANALYSIS MATLAB code for x_axis_analysis.fig
%      X_AXIS_ANALYSIS, by itself, creates a new X_AXIS_ANALYSIS or raises the existing
%      singleton*.
%
%      H = X_AXIS_ANALYSIS returns the handle to a new X_AXIS_ANALYSIS or the handle to
%      the existing singleton*.
%
%      X_AXIS_ANALYSIS('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in X_AXIS_ANALYSIS.M with the given input arguments.
%
%      X_AXIS_ANALYSIS('Property','Value',...) creates a new X_AXIS_ANALYSIS or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before x_axis_analysis_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to x_axis_analysis_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES



% Edit the above text to modify the response to help x_axis_analysis

% Last Modified by GUIDE v2.5 24-Aug-2016 15:51:51

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @x_axis_analysis_OpeningFcn, ...
                   'gui_OutputFcn',  @x_axis_analysis_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before x_axis_analysis is made visible.
function x_axis_analysis_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to x_axis_analysis (see VARARGIN)

% Choose default command line output for x_axis_analysis
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes x_axis_analysis wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = x_axis_analysis_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global obj1
obj1 = sample_init;


N = 10000;
LOOP_NUM = N;
accel_tmp = single(zeros(1,LOOP_NUM));
velo_tmp = single(zeros(1,LOOP_NUM));
displace_tmp = single(zeros(1,LOOP_NUM));
time_tmp=single(zeros(1,LOOP_NUM));
start_time = clock;
bias_num = 0;

number = 1;
MUNMUN = 200;

% for cnt=0:N
while number<=N    

%     mod_num = mod(number,LOOP_NUM)+1;
%     [flag,accel_tmp(mod_num)] = get_axis_data(obj1,0);
    [flag,accel_tmp(number)] = get_axis_data(obj1,0);
%     accel_tmp(mod_num),flag,number

%flag为0时候说明数据不对，重新进行循环
    if flag ==0
        continue
    end
 
%获取现在的时间
    current_time = clock;

%第一次获取的时间为基准，以后每次的时间量都是与这个基准的差值
    if number==1
        start_time = current_time;
    end
    
    accel_tmp(number) = accel_tmp(number) - bias_num;           %减去基准数值（平均值）
    
    if number>=2
        time_tmp(number) = etime(current_time ,start_time);
  
        velo_tmp(number) = velo_tmp(number-1)+(time_tmp(number)-time_tmp(number-1))*accel_tmp(number);
        displace_tmp(number) = displace_tmp(number-1)+(time_tmp(number)-time_tmp(number-1))*velo_tmp(number);
    end
%     time_tmp(mod_num) = etime(current_time ,start_time);
%     velo_tmp(mod_num) = velo_tmp(ahead(mod_num))+(time_tmp(mod_num)-time_tmp(ahead(mod_num)))*accel_tmp(mod_num);
%     displace_tmp(mod_num) = displace_tmp(ahead(mod_num))+(time_tmp(mod_num)-time_tmp(ahead(mod_num)))*velo_tmp(mod_num);
    if (number<=MUNMUN &&mod(number,1)==0)
        plot(handles.axes1,accel_tmp(1:number-1));
        plot(handles.axes2,velo_tmp(1:number-1));
        plot(handles.axes3,displace_tmp(1:number-1)); 
        drawnow
%         if number==50
%             save raw_data accel_tmp velo_tmp displace_tmp time_tmp
%         end
    elseif(mod(number,1)==0)
%         axes(handles.axes1);
%         plot(accel_tmp(number-199:number-1))
        plot(handles.axes1,accel_tmp(number-MUNMUN:number-1));
        plot(handles.axes2,velo_tmp(number-MUNMUN:number-1));
        plot(handles.axes3,displace_tmp(number-MUNMUN:number-1));
        drawnow
    end
    
    
    %循环结束number加1
    number = number+1;
%     清空缓冲区
    flushinput(obj1);
end
fclose(obj1);


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global obj1
fclose(obj1)
delete(obj1)

