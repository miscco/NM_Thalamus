% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Thalamus.cpp Thalamic_Column.cpp

function Plots(T)

if nargin == 0
    Con     	= [2;		% N_tr
               	   5.5;		% N_rt
                   5];		% N_rr    

    var_stim    = [ 0;          % strength of the stimulus in Hz (spikes per second)
                    0;          % time between   stimuli in s    
                    0;          % time until first stimuli in s
                    0];		% duration of the stimulus in ms
    T       	= 60;  		% duration of the simulation
end
[Vt, Vr] = Thalamus(T, Con, var_stim);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

figure(1)
subplot(211), plot(timeaxis,Vt)
title('Thalamic relay membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
subplot(212), plot(timeaxis,Vr)
title('Thalamic reticular membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')
%save('Thalamus.mat','Vt','Vr')
