#include <cmath>
#include "Thalamic_Column.h"

// function that returns the firing rate of the exitatory population
double Thalamic_Column::get_Qt	(int N) const{
	_SWITCH((Vt)(h_T_t))
	double q = (Qt_max + var_h_T_t * Qt_burst)/ (1 + exp(-C * (var_Vt - theta_t) / sigma_t));
	return q;
}

// function that returns the firing rate of the exitatory population
double Thalamic_Column::get_Qr	(int N) const{
	_SWITCH((Vr))
	double q = (Qr_max + Qr_burst) / (1 + exp(-C * (var_Vr - theta_r) / sigma_r));
	return q;
}

// function that scales the input from TC to TC	has to be descending
double Thalamic_Column::psi_et	(int N) const{
	_SWITCH((Vt))
	double psi = (Vt_rev_e-var_Vt)/std::abs(Vt_rev_e-V_t0);
	return psi;
}

// function that scales the input from RE to TC has to be ascending
double Thalamic_Column::psi_it	(int N) const{
	_SWITCH((Vt))
	double psi =-(Vt_rev_i-var_Vt)/std::abs(Vt_rev_i-V_t0);
	return psi;
}

// function that scales the input from TC to RE	has to be descending
double Thalamic_Column::psi_er	(int N) const{
	_SWITCH((Vr))
	double psi = (Vr_rev_e-var_Vr)/std::abs(Vr_rev_e-V_r0);
	return psi;
}

// function that scales the input from RE to RE	has to be asscending
double Thalamic_Column::psi_ir	(int N) const{
	_SWITCH((Vr))
	double psi =-(Vr_rev_i-var_Vr)/std::abs(Vr_rev_i-V_r0);
	return psi;
}

// function that returns the instant activation of the T-type current
double Thalamic_Column::m_inf_t	(int N) const{
	_SWITCH((Vt))
	double m = 1/(1+exp(-(var_Vt+59)/6.2));
	return m;
}

// function that returns the instant activation of the T-type current
// by Destexhe 1994
double Thalamic_Column::m_inf_r	(int N) const{
	_SWITCH((Vr))
	double m = 1/(1+exp(-(var_Vr+52)/7.4));
	return m;
}

// function that returns the instant activation of the T-type current
double Thalamic_Column::h_inf_t	(int N) const{
	_SWITCH((Vt))
	double h = 1/(1+exp( (var_Vt+83)/4));
	return h;
}

// function that returns the instant activation of the T-type current
double Thalamic_Column::tau_h_t	(int N) const{
	_SWITCH((Vt))
	double tau = (30.8 + (211.4 + exp((var_Vt+115.2)/5)/(1+exp((var_Vt+86)/3.2))))/3.74;
	return tau;
}

// function that returns the instant activation of the T-type current
// by Destexhe 1994
double Thalamic_Column::h_inf_r	(int N) const{
	_SWITCH((Vr))
	double h = 1/(1+exp( (var_Vr+80)/5));
	return h;
}

// function that returns the instant activation of the T-type current
// by Destexhe 1994
double Thalamic_Column::tau_h_r	(int N) const{
	_SWITCH((Vr))
	double tau =  28.307 + 0.333/(exp((var_Vr+48)/4) + exp(-(var_Vr+407)/50));
	return tau;
}

// function that returns the T-type current
double Thalamic_Column::I_T_t	(int N) const{
	_SWITCH((Vt)(h_T_t))
	double I = gTt * m_inf_t(N) * m_inf_t(N) * var_h_T_t * (var_Vt - VT);
	return I;
}

// function that returns the T-type current
double Thalamic_Column::I_T_r	(int N) const{
	_SWITCH((Vr)(h_T_r))
	double I = gTr * m_inf_r(N) * m_inf_r(N) * var_h_T_r * (var_Vr - VT);
	return I;
}

// function that returns the instant activation of the T-type current
double Thalamic_Column::tau_m_h	(int N) const{
	_SWITCH((Vt))
	double tau = (20 + 1000/(exp((var_Vt + 71.5)/14.2) + exp(-(var_Vt + 89)/11.6)));
	return tau;
}

// function that returns the instant activation of the T-type current
// by Destexhe 1994
double Thalamic_Column::m_inf_h	(int N) const{
	_SWITCH((Vt))
	double h = 1/(1+exp( (var_Vt+75)/5.5));
	return h;
}

// function that returns the T-type current
double Thalamic_Column::I_h		(int N) const{
	_SWITCH((Vt)(m_h)(m_h2))
	double I = gh * (var_m_h + g_inc * var_m_h2) * (var_Vt - E_h);
	return I;
}

// KCa current of RE population
double Thalamic_Column::I_KCa	(int N) const{
	_SWITCH((Vr)(m_KCa))
	double I = gKCa * pow(var_m_KCa, 2) * (var_Vr - E_KCa);
	return I;
}

// KCa current of RE population
double Thalamic_Column::I_CAN	(int N) const{
	_SWITCH((Vr)(m_CAN))
	double I = gCAN * pow(var_m_CAN, 2) * (var_Vr - E_CAN);
	return I;
}

// function that returns the noise to exitatory population for stochastic RK4
double Thalamic_Column::noise_xRK(int N, double u_1, double u_2) const{
	extern const double h;
	extern const vector<double> B1, B2;
	double n = s  / h * (B1[N-1] * u_1 + B2[N-1] * u_2);
	return n;
}

// function that returns the noise to inhibitory population for stochastic RK4
double Thalamic_Column::noise_xE	(double u) const{
	extern const double h;
	double n = s / h * u;
	return n;
}

// function that calculates the Nth RK term
void Thalamic_Column::set_RK		(int N, double u_t1, double u_t2) {
	extern const double dt;
	_SWITCH((Vt)(Vr)(Cat)(Car)(Phi_tt)(Phi_tr)(Phi_rt)(Phi_rr)(x_tt)(x_tr)(x_rt)(x_rr)(h_T_t)(h_T_r)(m_KCa)(m_CAN)(m_h)(m_h2)(P_h))
	Vt	  	[N] = dt/tau_t * (V_t0 - var_Vt + psi_et(N) * var_Phi_tt - psi_it(N) * var_Phi_rt - c * (I_T_t(N) + I_h(N)));
	Vr	  	[N] = dt/tau_r * (V_r0 - var_Vr + psi_er(N) * var_Phi_tr - psi_ir(N) * var_Phi_rr - c * (I_T_r(N)));
	Cat		[N] = dt*(alpha_Ca * I_T_t(N) - (var_Cat - Ca_0)/tau_Ca - n_P * k1 * pow(var_Cat, n_P) * (1 - var_P_h) + n_P * k2 * var_P_h);
	Car		[N] = dt*(alpha_Ca * I_T_r(N) - (var_Car - Ca_0)/tau_Ca);
	Phi_tt	[N] = dt*(var_x_tt);
	Phi_tr	[N] = dt*(var_x_tr);
	Phi_rt	[N] = dt*(var_x_rt);
	Phi_rr	[N] = dt*(var_x_rr);
	x_tt  	[N] = dt*(pow(gamma_t, 2) * (noise_xRK(N, u_t1, u_t2) 	- var_Phi_tt) - 2 * gamma_t * var_x_tt);
	x_tr  	[N] = dt*(pow(gamma_t, 2) * (N_tr * get_Qt(N)			- var_Phi_tr) - 2 * gamma_t * var_x_tr);
	x_rt  	[N] = dt*(pow(gamma_r, 2) * (N_rt * get_Qr(N) 			- var_Phi_rt) - 2 * gamma_r * var_x_rt);
	x_rr  	[N] = dt*(pow(gamma_r, 2) * (N_rr * get_Qr(N)		 	- var_Phi_rr) - 2 * gamma_r * var_x_rr);
	h_T_t 	[N] = dt*(h_inf_t(N) - var_h_T_t)/tau_h_t(N);
	h_T_r 	[N] = dt*(h_inf_r(N) - var_h_T_r)/tau_h_r(N);
	m_KCa 	[N] = dt*(48 * pow(var_Cat, 2) * (1 - var_m_KCa) - 0.03  * var_m_KCa);
	m_CAN 	[N] = dt*(20 * pow(var_Cat, 2) * (1 - var_m_CAN) - 0.005 * var_m_CAN);
	m_h 	[N] = dt*((m_inf_h(N) * (1 - var_m_h2) - var_m_h)/tau_m_h(N) - k3 * var_P_h * var_m_h + k4 * var_m_h2);
	m_h2 	[N] = dt*(k3   * var_P_h			 * 	    var_m_h  	- k4   * var_m_h2);
	P_h		[N] = dt*(k1   * pow(var_Cat, n_P) 	 * (1 - var_P_h) 	- k2   * var_P_h);
}

// function that ads all the RK terms together
void Thalamic_Column::add_RK(double u_t) {
	extern const double h;
	Vt	  	[0] += (Vt		[1] + Vt		[2] * 2 + Vt		[3] * 2 + Vt		[4])/6;
	Vr	  	[0] += (Vr		[1] + Vr		[2] * 2 + Vr		[3] * 2 + Vr		[4])/6;
	Cat	  	[0] += (Cat		[1] + Cat		[2] * 2 + Cat		[3] * 2 + Cat		[4])/6;
	Car	  	[0] += (Car		[1] + Car		[2] * 2 + Car		[3] * 2 + Car		[4])/6;
	Phi_tt	[0] += (Phi_tt	[1] + Phi_tt	[2] * 2 + Phi_tt	[3] * 2 + Phi_tt	[4])/6;
	Phi_tr	[0] += (Phi_tr	[1] + Phi_tr	[2] * 2 + Phi_tr	[3] * 2 + Phi_tr	[4])/6;
	Phi_rt	[0] += (Phi_rt	[1] + Phi_rt	[2] * 2 + Phi_rt	[3] * 2 + Phi_rt	[4])/6;
	Phi_rr	[0] += (Phi_rr	[1] + Phi_rr	[2] * 2 + Phi_rr	[3] * 2 + Phi_rr	[4])/6;
	x_tt  	[0] += (x_tt	[1] + x_tt		[2] * 2 + x_tt		[3] * 2 + x_tt		[4])/6 + pow(gamma_t, 2) * s * h * u_t;
	x_tr  	[0] += (x_tr	[1] + x_tr		[2] * 2 + x_tr		[3] * 2 + x_tr		[4])/6;
	x_rt  	[0] += (x_rt	[1] + x_rt		[2] * 2 + x_rt		[3] * 2 + x_rt		[4])/6;
	x_rr  	[0] += (x_rr	[1] + x_rr		[2] * 2 + x_rr		[3] * 2 + x_rr		[4])/6;
	h_T_t 	[0] += (h_T_t	[1] + h_T_t		[2] * 2 + h_T_t		[3] * 2 + h_T_t		[4])/6;
	h_T_r 	[0] += (h_T_r	[1] + h_T_r		[2] * 2 + h_T_r		[3] * 2 + h_T_r		[4])/6;
	m_KCa	[0] += (m_KCa	[1] + m_KCa		[2] * 2 + m_KCa		[3] * 2 + m_KCa		[4])/6;
	m_CAN	[0] += (m_CAN	[1] + m_CAN		[2] * 2 + m_CAN		[3] * 2 + m_CAN		[4])/6;
	m_h	 	[0] += (m_h		[1] + m_h		[2] * 2 + m_h		[3] * 2 + m_h		[4])/6;
	m_h2	[0] += (m_h2	[1] + m_h2		[2] * 2 + m_h2		[3] * 2 + m_h2		[4])/6;
	P_h	 	[0] += (P_h		[1] + P_h		[2] * 2 + P_h		[3] * 2 + P_h		[4])/6;
}


