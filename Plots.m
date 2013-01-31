% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Thalamic_Colum.cpp

function Plots(T, onset)

if nargin == 0
    Con     = [400;             % N_ti
               800;             % N_it
               800];            % N_ii    
    T       = 10;      % duration of the simulation
    onset   = 5;
end

[Ve, Vi, Phi_ee, Phi_ei, Phi_ie, Phi_ii, I_T] = SteynRoss(Con, T, onset);

L        = max(size(Ve));
timeaxis = linspace(0,T,L);

figure(1)
subplot(311), plot(timeaxis,Ve)
title('Exitatory membrane voltage'), xlabel('time in s'), ylabel('Ve in mV')
subplot(312), plot(timeaxis,Vi)
title('Inhibitory membrane voltage'), xlabel('time in s'), ylabel('Vi in mV')
subplot(313), plot(timeaxis,I_T)
title('T-type current'), xlabel('time in s'), ylabel('I_T in muA')

% figure(2)
% subplot(411), plot(timeaxis,Phi_ee)
% title('exitatory  to exitatory  PSP'), xlabel('time in s'), ylabel('Phi_{ee} in mV')
% subplot(412), plot(timeaxis,Phi_ei)
% title('exitatory  to inhibitory PSP'), xlabel('time in s'), ylabel('Phi_{ei} in mV')
% subplot(413), plot(timeaxis,Phi_ie)
% title('inhibitory to exitatory  PSP'), xlabel('time in s'), ylabel('Phi_{ie} in mV')
% subplot(414), plot(timeaxis,Phi_ii)
% title('inhibitory to inhibitory PSP'), xlabel('time in s'), ylabel('Phi_{ii} in mV')

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