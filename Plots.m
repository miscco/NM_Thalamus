% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Thalamus.cpp Thalamic_Colum.cpp

function Plots(T, onset)

if nargin == 0
    Con     = [10;             % N_tr
               15;             % N_rt
               30];            % N_rr    
    T       = 30;      % duration of the simulation
    onset   = 10;
end

[Vt, Vr, Ca, Phi_tr, Phi_rt, I_T_t, I_T_r, I_h] = Thalamus(Con, T, onset);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

figure(1)
subplot(211), plot(timeaxis,Vt)
title('Exitatory membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
subplot(212), plot(timeaxis,Vr)
title('Inhibitory membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')

% figure(1)
% subplot(411), plot(timeaxis, Vt)
% title('Thalamic relay membrane voltage'),  xlabel('time in s'), ylabel('V_{t} in mV')
% subplot(412), plot(timeaxis, Vr)
% title('Thalamic reticular membrane voltage'),  xlabel('time in s'), ylabel('V_{r} in mV')
% subplot(413), plot(timeaxis, Cat)
% title('TC Ca concentration'),                 xlabel('time in s'), ylabel('Ca in \muM')
% subplot(414), plot(timeaxis, Car)
% title('RE Ca concentration'),                 xlabel('time in s'), ylabel('Ca in \muM')

%exportfig(gcf, 'TC_delta.png', 'Format', 'png', 'height', 11, 'Color', 'rgb', 'FontMode', 'fixed', 'FontSize', 22)
% 
% figure(2)
% subplot(411), plot(timeaxis,I_T_r)
% title('RE I_{T} current '),   xlabel('time in s'), ylabel('I_{T}   in \muA cm^{-2}')
% subplot(412), plot(timeaxis,I_CAN)
% title('RE I_{CAN} current '), xlabel('time in s'), ylabel('I_{CAN} in \muA cm^{-2}')
% subplot(413), plot(timeaxis,I_KCa)
% title('RE I_{KCa} current '), xlabel('time in s'), ylabel('I_{KCa} in \muA cm^{-2}')
% subplot(414), plot(timeaxis,Phi_tr)
% title('TC input to RE'),      xlabel('time in s'), ylabel('\Phi_{tr} in \muA cm^{-2}')
% 
% figure(4)
% subplot(311), plot(timeaxis,I_T_t)
% title('TC I_{T} current '), xlabel('time in s'), ylabel('I_{T} in \muA cm^{-2}')
% subplot(312), plot(timeaxis,I_h)
% title('TC I_{h} current '), xlabel('time in s'), ylabel('I_{h} in \muA cm^{-2}')
% subplot(313), plot(timeaxis,Phi_rt)
% title('RE input to TC'),    xlabel('time in s'), ylabel('\Phi_{rt} in \muA cm^{-2}')
% 
fs      = L/T;
NFFT    = 2^nextpow2(L);

[Pxx,f] = pwelch(Vt-mean(Vt), [], [], [], fs,'onesided');
n       = find(f<=60, 1, 'last' );
 
figure(3)
plot(f(1:n),Pxx(1:n))
title('Powerspectrum of Steyn-Ross model with pwelch'), xlabel('frequency in Hz'), ylabel('Power')

%save('Thalamus.mat','Vt','Vr')