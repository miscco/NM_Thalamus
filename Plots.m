% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=c++11" Thalamus.cpp Thalamic_Column.cpp

function Plots(T)

if nargin == 0
    Con     	= [ 6;      % sigma
                    4;		% N_tr
                    4;		% N_rt
                    20];		% N_rr 
               

    % stimulation parameters
    % first number is the mode of stimulation
    % 0 == none
    % 1 == periodic
    % 2 == phase dependend up state
    % 3 == phase dependend down state
    
    var_stim    = [ 0;           % mode of stimulation
                    50;          % strength of the stimulus      in Hz (spikes per second)
                    120;       	% duration of the stimulus      in ms
                    7;          % time between stimuli          in s    
                    1];         % time until stimuli after min 	in ms
    T       	= 30;  		% duration of the simulation
end
[Vt, Vr, I_t, I_h] = Thalamus(T, Con, var_stim);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

Fs      = L/T;
[Pxx,f] = pwelch(Vt-mean(Vt), hamming(4*Fs), 2*Fs, [], Fs,'ConfidenceLevel', 0.9, 'power');
n       = find(f<=60, 1, 'last' );

figure(1)
subplot(311), plot(timeaxis,Vt)
title('Thalamic relay membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
subplot(312), plot(timeaxis,Vr)
title('Thalamic reticular membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')
subplot(313), plot(f(1:n),Pxx(1:n))
title('Powerspectrum of Steyn-Ross model with pwelch'), xlabel('frequency in Hz'), ylabel('Power')
%save('Thalamus.mat','Vt','Vr')
% 
% figure(2)
% subplot(311), plot(timeaxis,Vt)
% title('Thalamic relay membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
% subplot(312), plot(timeaxis,I_t)
% title('Thalamic reticular membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')
% subplot(313), plot(timeaxis,I_h)
% title('Thalamic reticular membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')