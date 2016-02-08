% mex command is given by: 
% mex CXXFLAGS="\$CXXFLAGS -std=c++11 -O3" Thalamus_mex.cpp Thalamic_Column.cpp

function Plots(T)

if nargin == 0
    Con     	= [ 0.01;       % g_h
                    0.05];      % g_LK

    T       	= 30;  		% duration of the simulation
end
[Vt, Vr, ah] = Thalamus_mex(T, Con, var_stim);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

% Plot the data
figure(1)
subplot(311), plot(timeaxis,Vt)
title('Thalamic relay membrane voltage'), xlabel('time in s'), ylabel('Vt [mV]')
subplot(312), plot(timeaxis,Vr)
title('Thalamic reticular membrane voltage'), xlabel('time in s'), ylabel('Vr [mV]')
subplot(313), plot(timeaxis,ah)
title('Thalamic relay I_h activation'), xlabel('time in s'), ylabel('m_h')
