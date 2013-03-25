function varargout = T_nullclines(varargin)
% T_NULLCLINES MATLAB code for T_nullclines.fig
%      T_NULLCLINES, by itself, creates a new T_NULLCLINES or raises the existing
%      singleton*.
%
%      H = T_NULLCLINES returns the handle to a new T_NULLCLINES or the handle to
%      the existing singleton*.
%
%      T_NULLCLINES('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in T_NULLCLINES.M with the given input arguments.
%
%      T_NULLCLINES('Property','Value',...) creates a new T_NULLCLINES or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before T_nullclines_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to T_nullclines_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help T_nullclines

% Last Modified by GUIDE v2.5 14-Feb-2013 09:50:40

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @T_nullclines_OpeningFcn, ...
                   'gui_OutputFcn',  @T_nullclines_OutputFcn, ...
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


% --- Executes just before T_nullclines is made visible.
function T_nullclines_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to T_nullclines (see VARARGIN)

% Choose default command line output for T_nullclines
handles.output = hObject;

Con     = { 400, ...            % N_tr
            800, ...            % N_rt
            800};               % N_rr

set(handles.Parametervalues,'Data',Con);

% Update handles structure
guidata(hObject, handles);

%add Toolbar for Zoom in / out and Pan


figureToolBar = uimenu('Label','Zoom Functions');
uimenu(figureToolBar,'Label','Zoom In','Callback','zoom on');
uimenu(figureToolBar,'Label','Zoom Out','Callback','zoom out');
uimenu(figureToolBar,'Label','Pan','Callback','pan on');

fig_update(handles)
% UIWAIT makes T_nullclines wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = T_nullclines_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in Parameter_set1.
function Parameter_set1_Callback(hObject, eventdata, handles)
% hObject    handle to Parameter_set1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Parameter_set1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Parameter_set1

Type_update1(handles);


% --- Executes during object creation, after setting all properties.
function Parameter_set1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Parameter_set1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on selection change in Parameter_set2.
function Parameter_set2_Callback(hObject, eventdata, handles)
% hObject    handle to Parameter_set2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Parameter_set2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Parameter_set2

Type_update2(handles);


% --- Executes during object creation, after setting all properties.
function Parameter_set2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Parameter_set2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function Parameterslider1_Callback(hObject, eventdata, handles)
% hObject    handle to Parameterslider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

Param_update1(handles);


% --- Executes during object creation, after setting all properties.
function Parameterslider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Parameterslider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Parameterslider2_Callback(hObject, eventdata, handles)
% hObject    handle to Parameterslider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

Param_update2(handles);



% --- Executes during object creation, after setting all properties.
function Parameterslider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Parameterslider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



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

% --- Update function for first Parameter
function Param_update1(handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

Pvalue = get(handles.Parameterslider1, 'Value');
Ptype1 = get(handles.Parameter_set1,   'String');
Ptype2 = get(handles.Parameter_set1,   'Value');
Param  = get(handles.Parametervalues,  'Data');
Param{Ptype2} = Pvalue;
string = [Ptype1(Ptype2), ' = ', num2str(Pvalue)];
set(handles.text1, 'String', string, 'Max', 1);
set(handles.Parametervalues, 'Data', Param, 'ColumnName', Ptype1);
fig_update(handles);

% --- Update function for first Parameter
function Param_update2(handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

Pvalue = get(handles.Parameterslider2, 'Value');
Ptype1 = get(handles.Parameter_set2,   'String');
Ptype2 = get(handles.Parameter_set2,   'Value');
Param  = get(handles.Parametervalues,  'Data');
Param{Ptype2} = Pvalue;
string = [Ptype1(Ptype2), ' = ', num2str(Pvalue)];
set(handles.text2, 'String', string, 'Max', 1);
set(handles.Parametervalues, 'Data', Param, 'ColumnName', Ptype1);
fig_update(handles);

% --- Update function for first Parameter
function Type_update1(handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


Pvalue = get(handles.Parametervalues,  'Data');
Ptype1 = get(handles.Parameter_set1,   'String');
Ptype2 = get(handles.Parameter_set1,   'Value');
string = [Ptype1(Ptype2), ' = ', num2str(Pvalue{Ptype2})];
set(handles.text1, 'String', string, 'Max', 1);
set(handles.Parameterslider1, 'Value', Pvalue{Ptype2});
fig_update(handles);

% --- Update function for first Parameter
function Type_update2(handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

Pvalue = get(handles.Parametervalues,  'Data');
Ptype1 = get(handles.Parameter_set2,   'String');
Ptype2 = get(handles.Parameter_set2,   'Value');
string = [Ptype1(Ptype2), ' = ', num2str(Pvalue{Ptype2})];
set(handles.text2, 'String', string, 'Max', 1);
set(handles.Parameterslider2, 'Value', Pvalue{Ptype2});
fig_update(handles);


% --- Executes when entered data in editable cell(s) in Parametervalues.
function Parametervalues_CellEditCallback(hObject, eventdata, handles) %#ok<DEFNU>
% hObject    handle to Parametervalues (see GCBO)
% eventdata  structure with the following fields (see UITABLE)
%	Indices: row and column indices of the cell(s) edited
%	PreviousData: previous data for the cell(s) edited
%	EditData: string(s) entered by the user
%	NewData: EditData or its converted form set on the Data property. Empty if Data was not changed
%	Error: error string when failed to convert EditData to appropriate value for Data
% handles    structure with handles and user data (see GUIDATA)

Param_update1(handles);
Param_update2(handles);

function fig_update(handles)

Param  = cell2mat(get(handles.Parametervalues,  'Data'));

Solver(Param, handles);
