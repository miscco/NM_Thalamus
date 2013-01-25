% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Cortical_Colum.cpp

function Plots(T, onset)

if nargin == 0
    T       = 120;      % duration of the simulation
    onset   = 5;
end

tic
[Ve, Vi ] = SteynRoss(T, onset);
toc

L        = max(size(Ve));
timeaxis = linspace(0,T,L);

figure(1)
subplot(211), plot(timeaxis,Ve)
title('Exitatory membrane voltage'), xlabel('time in s'), ylabel('Ve in mV')
subplot(212), plot(timeaxis,Vi)
title('Inhibitory membrane voltage'), xlabel('time in s'), ylabel('Vi in mV')


% fs      = L/T;
% NFFT    = 2^nextpow2(L);
% 
%  [Pxx,f]=pwelch(Ve-mean(Ve), 1024, 256, NFFT, fs,'onesided');
%  n       = find(f<=60, 1, 'last' );
%  
%  figure(2)
%  plot(f(1:n),Pxx(1:n))
%  title('Powerspectrum of Steyn-Ross model with pwelch'), xlabel('frequency in Hz'), ylabel('Power')
%  