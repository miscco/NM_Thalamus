Con     = [10;             % N_tr
                10;             % N_rt
                50];            % N_rr    
T       = 10;      % duration of the simulation
onset   = 5;

[Vt,~] = Thalamus(Con, T, onset);

L        = max(size(Vt));
timeaxis = linspace(0,T,L);

figure(1)
plot(timeaxis, Vt);
title('Membrane voltage of the thalamic relay population')
xlabel('time in s')
ylabel('V in mV')

tightfig();
savefig('Spindle', 'png')