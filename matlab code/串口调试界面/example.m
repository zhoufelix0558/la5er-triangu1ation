function varargout = example(varargin)
% EXAMPLE MATLAB code for example.fig
%      EXAMPLE, by itself, creates a new EXAMPLE or raises the existing
%      singleton*.
%
%      H = EXAMPLE returns the handle to a new EXAMPLE or the handle to
%      the existing singleton*.
%
%      EXAMPLE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in EXAMPLE.M with the given input arguments.
%
%      EXAMPLE('Property','Value',...) creates a new EXAMPLE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before example_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to example_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help example

% Last Modified by GUIDE v2.5 07-Aug-2016 15:38:12

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @example_OpeningFcn, ...
                   'gui_OutputFcn',  @example_OutputFcn, ...
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

% --- Executes just before example is made visible.
function example_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to example (see VARARGIN)

% Choose default command line output for example
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% This sets up the initial plot - only do when we are invisible
% so window can get raised using example.
if strcmp(get(hObject,'Visible'),'off')
    plot(rand(5));
end

% UIWAIT makes example wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = example_OutputFcn(hObject, eventdata, handles)
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
axes(handles.axes1);

cla;

interval=300;
obj1 = sample_init;
num_cnt = 3;
N =100000;
kal_cnt = zeros(1,N);
loc = zeros(1,N);
kal_result = zeros(1,N);

buffer = fscanf(obj1, '%s');
[kal_cnt(1),loc(1),kal_result(1)] = str_cong_d_f_f(buffer);
p = plot(kal_cnt(1),loc(1),kal_cnt(1),kal_result(1))
[kal_cnt(2),loc(2),kal_result(2)] = str_cong_d_f_f(buffer);
p = plot(kal_cnt(2),loc(2),kal_cnt(2),kal_result(2))
for cnt =3:N
    buffer = fscanf(obj1, '%s');
    [kal_cnt(num_cnt),loc(num_cnt),kal_result(num_cnt)] = str_cong_d_f_f(buffer);
    if kal_cnt(num_cnt) ~= 0 & ~isnan(kal_cnt(num_cnt))
        %之前用的一直是或|，导致这段话一直会被执行
        num_cnt=num_cnt+1;
    end
    if mod(num_cnt,1)==0
        if num_cnt<=interval+10
%             plot(kal_cnt(1:num_cnt-1),loc(1:num_cnt-1),kal_cnt(1:num_cnt-1),kal_result(1:num_cnt-1));
            set(p(1),'XData',kal_cnt(1:num_cnt-1),'YData',loc(1:num_cnt-1));
            set(p(2),'XData',kal_cnt(1:num_cnt-1),'YData',kal_result(1:num_cnt-1));
            drawnow
            xlim([kal_cnt(1) kal_cnt(1)+2000])
            %20000是个预估值
            
            pos = position(kal_result(num_cnt-1));
            set(handles.edit1,'String',num2str(position(loc(num_cnt-1)),'%4.5f'));
            set(handles.edit2,'String',num2str(pos,'%4.2f'));
            set(handles.edit3,'String',num2str(mod(floor(pos*100000),1000)));
            set(handles.edit4,'String',num2str(cnt));
            
            
        else
            set(p(1),'XData',kal_cnt(num_cnt-interval:num_cnt-1),'YData',loc(num_cnt-interval:num_cnt-1));
            set(p(2),'XData',kal_cnt(num_cnt-interval:num_cnt-1),'YData',kal_result(num_cnt-interval:num_cnt-1));
            xlim([kal_cnt(num_cnt-interval) kal_cnt(num_cnt-1)])
            
            pos = position(kal_result(num_cnt-1));
            set(handles.edit1,'String',num2str(position(loc(num_cnt-1)),'%4.5f'));
            set(handles.edit2,'String',num2str(pos,'%4.2f'));
            set(handles.edit3,'String',num2str(mod(floor(pos*100000),1000)));
            set(handles.edit4,'String',num2str(cnt));
            
            
 %           ylim auto
            drawnow
        end
        drawnow
    end
    flushinput(obj1);
end
fclose(obj1);




% --------------------------------------------------------------------
function FileMenu_Callback(hObject, eventdata, handles)
% hObject    handle to FileMenu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function OpenMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to OpenMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
file = uigetfile('*.fig');
if ~isequal(file, 0)
    open(file);
end

% --------------------------------------------------------------------
function PrintMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to PrintMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
printdlg(handles.figure1)

% --------------------------------------------------------------------
function CloseMenuItem_Callback(hObject, eventdata, handles)
% hObject    handle to CloseMenuItem (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
selection = questdlg(['Close ' get(handles.figure1,'Name') '?'],...
                     ['Close ' get(handles.figure1,'Name') '...'],...
                     'Yes','No','Yes');
if strcmp(selection,'No')
    return;
end

delete(handles.figure1)


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
     set(hObject,'BackgroundColor','white');
end

set(hObject, 'String', {'plot(rand(5))', 'plot(sin(1:0.01:25))', 'bar(1:.5:10)', 'plot(membrane)', 'surf(peaks)'});



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
