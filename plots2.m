clear
load('Steyn-Ross.mat')

L       = max(size(Ve));
T       = 120;  
fs      = L/T;
NFFT    = 2^nextpow2(L);
timeaxis = linspace(0,T,L);

figure(1)
plot(timeaxis,Ve)
xlabel('time in s')
ylabel('Ve in mV')
title('exitatory membrane voltage')

% [Pxx,f]=pwelch(Ve-mean(Ve), 1024, 256, NFFT, fs,'onesided');
% n       = find(f<=60, 1, 'last' );
% 
% figure(2)
% plot(f(1:n),Pxx(1:n))
% xlabel('frequency in Hz')
% ylabel('Power')
% title('Powerspectrum of Steyn-Ross model with pwelch')