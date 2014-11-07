% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=c++11 -O3" Thalamus.cpp Thalamic_Column.cpp

function Plots(T)

if nargin == 0
    Con     	= [ 0.062;       % g_h
                    0.02;       % g_LK_t
                    3;          % N_tr
                    4;          % N_rt
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
[Vt, Vr] = Thalamus(T, Con, var_stim);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

fs      = L/T;
[Pxx,f] = pwelch(Vt-mean(Vt), [], [], [], fs,'onesided');
n       = find(f<=60, 1, 'last' );

figure(1)
subplot(311), plot(timeaxis,Vt)
title('Thalamic relay membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
subplot(312), plot(timeaxis,Vr)
title('Thalamic reticular membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')
subplot(313), plot(f(1:n),Pxx(1:n))
title('Powerspectrum of Steyn-Ross model with pwelch'), xlabel('frequency in Hz'), ylabel('Power')
save('Thalamus.mat','Vt','Vr')
