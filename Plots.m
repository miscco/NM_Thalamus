% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=c++11 -O3" Thalamus.cpp Thalamic_Column.cpp

function Plots(T)

if nargin == 0
    Con     	= [ 0.063;       % g_h
                    0.02;       % g_LK_t
                    3;          % N_tr
                    5;          % N_rt
                    30];		% N_rr 
               

    % stimulation parameters
    % first number is the mode of stimulation
    % 0 == none
    % 1 == periodic
    % 2 == phase dependend up state
    % 3 == phase dependend down state
    
    var_stim    = [ 0;           % mode of stimulation
                    25;          % strength of the stimulus      in Hz (spikes per second)
                    70;       	% duration of the stimulus      in ms
                    5;          % time between stimuli          in s    
                    1];         % time until stimuli after min 	in ms
    T       	= 30;  		% duration of the simulation
end
[Vt, Vr, ah] = Thalamus(T, Con, var_stim);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);
% 
% fs      = L/T;
% [Pxx,f] = pwelch(Vt-mean(Vt), 20*FS, 4*FS, [], fs,'onesided');
% n       = find(f<=60, 1, 'last' );

figure(1)
subplot(311), plot(timeaxis,Vt)
title('Thalamic relay membrane voltage'), xlabel('time in s'), ylabel('Vt [mV]')
subplot(312), plot(timeaxis,Vr)
title('Thalamic reticular membrane voltage'), xlabel('time in s'), ylabel('Vr [mV]')
subplot(313), plot(timeaxis,ah)
title('Thalamic relay I_h activation'), xlabel('time in s'), ylabel('m_h')
%save('Thalamus.mat','Vt','Vr')