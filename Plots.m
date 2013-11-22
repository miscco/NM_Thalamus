% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Thalamus.cpp Thalamic_Colum.cpp

function Plots(T, onset)

if nargin == 0
    Con     = [20;             % N_tr
               80;             % N_rt
               80];            % N_rr    
    T       = 30;      % duration of the simulation
    onset   = 10;
end

[Vt, Vr] = Thalamus(Con, T, onset);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

figure(1)
subplot(211), plot(timeaxis,Vt)
title('Exitatory membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
subplot(212), plot(timeaxis,Vr)
title('Inhibitory membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')

fs      = L/T;
NFFT    = 2^nextpow2(L);

[Pxx,f] = pwelch(Vt-mean(Vt), [], [], [], fs,'onesided');
n       = find(f<=60, 1, 'last' );
 
figure(3)
plot(f(1:n),Pxx(1:n))
title('Powerspectrum of Steyn-Ross model with pwelch'), xlabel('frequency in Hz'), ylabel('Power')

%save('Thalamus.mat','Vt','Vr')