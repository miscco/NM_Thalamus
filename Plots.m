% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Thalamus.cpp Thalamic_Colum.cpp

function Plots(T, onset)

if nargin == 0
    Con     = [400;             % N_tr
               400;             % N_rt
               400];            % N_rr    
    T       = 20;      % duration of the simulation
    onset   = 5;
end

[Vt, Vr, Cat, Car, I_T_t, I_T_r, I_h] = Thalamus(Con, T, onset);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

% figure(1)
% subplot(211), plot(timeaxis,Vt)
% title('Exitatory membrane voltage'), xlabel('time in s'), ylabel('Vt in mV')
% subplot(212), plot(timeaxis,Vr)
% title('Inhibitory membrane voltage'), xlabel('time in s'), ylabel('Vr in mV')

figure(1)
subplot(411), plot(timeaxis, Vt)
title('Thalamic relay membrane voltage'),  xlabel('time in s'), ylabel('V_{t} in mV')
subplot(412), plot(timeaxis, Vr)
title('Thalamic reticular membrane voltage'),  xlabel('time in s'), ylabel('V_{r} in mV')
subplot(413), plot(timeaxis, Cat)
title('TC Ca concentration'),                 xlabel('time in s'), ylabel('Ca in \muM')
subplot(414), plot(timeaxis, Car)
title('RE Ca concentration'),                 xlabel('time in s'), ylabel('Ca in \muM')

%exportfig(gcf, 'TC_delta.png', 'Format', 'png', 'height', 11, 'Color', 'rgb', 'FontMode', 'fixed', 'FontSize', 22)
% 
% figure(2)
% subplot(311), plot(timeaxis,I_T_t)
% title('TC I_T current '),   xlabel('time in s'), ylabel('I_T in \muA cm^{-2}')
% subplot(312), plot(timeaxis,I_CAN_t)
% title('TC I_{CAN} current '), xlabel('time in s'), ylabel('I_{CAN} in \muA cm^{-2}')
% subplot(313), plot(timeaxis,I_KCa_t)
% title('TC I_{KCa} current '), xlabel('time in s'), ylabel('I_{KCa} in \muA cm^{-2}')


fs      = L/T;
NFFT    = 2^nextpow2(L);

[Pxx,f] = pwelch(Vt-mean(Vt), 1024, 256, NFFT, fs,'onesided');
n       = find(f<=60, 1, 'last' );
 
figure(3)
plot(f(1:n),Pxx(1:n))
title('Powerspectrum of Steyn-Ross model with pwelch'), xlabel('frequency in Hz'), ylabel('Power')