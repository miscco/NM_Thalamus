% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Thalamus.cpp Thalamic_Colum.cpp

function Plots(T, onset)

if nargin == 0
    Con     = [400;             % N_tr
               800;             % N_rt
               800];            % N_rr    
    T       = 20;      % duration of the simulation
    onset   = 5;
end

[Vt, Vr, Ca, Phi_tt, Phi_tr, Phi_rt, Phi_rr, h_T_t, h_T_r, I_T_t, I_T_r] = Thalamus(Con, T, onset);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

% figure(1)
% subplot(211), plot(timeaxis,Vt)
% title('Exitatory membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
% subplot(212), plot(timeaxis,Vr)
% title('Inhibitory membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')

figure(1)
subplot(411), plot(timeaxis,Vt)
title('Exitatory membrane voltage'),  xlabel('time in s'), ylabel('Vt in mV')
subplot(412), plot(timeaxis,Vr)
title('Inhibitory membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')
subplot(413), plot(timeaxis,Ca)
title('Calcium Concentration'),       xlabel('time in s'), ylabel('Ca in muM')
subplot(414), plot(timeaxis,I_T_r)
title('T-type current'),              xlabel('time in s'), ylabel('I_T in muA')
% 
% figure(2)
% subplot(411), plot(timeaxis,Phi_tt)
% title('exitatory  to exitatory  PSP'), xlabel('time in s'), ylabel('Phi_{tt} in mV')
% subplot(412), plot(timeaxis,Phi_tr)
% title('exitatory  to inhibitory PSP'), xlabel('time in s'), ylabel('Phi_{tr} in mV')
% subplot(413), plot(timeaxis,Phi_rt)
% title('inhibitory to exitatory  PSP'), xlabel('time in s'), ylabel('Phi_{rt} in mV')
% subplot(414), plot(timeaxis,Phi_rr)
% title('inhibitory to inhibitory PSP'), xlabel('time in s'), ylabel('Phi_{rr} in mV')

fs      = L/T;
NFFT    = 2^nextpow2(L);

[Pxx,f] = pwelch(Vt-mean(Vt), 1024, 256, NFFT, fs,'onesided');
n       = find(f<=60, 1, 'last' );
 
figure(2)
plot(f(1:n),Pxx(1:n))
title('Powerspectrum of Steyn-Ross model with pwelch'), xlabel('frequency in Hz'), ylabel('Power')