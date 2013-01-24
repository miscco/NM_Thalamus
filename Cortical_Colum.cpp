#include <cmath>
#include "Cortical_Colum.h"

// function that returns the firing rate of the exitatory population
double Cortical_Colum::get_Qe	(int N) const{
	_SWITCH((Ve))
	double q = Ne * Qe_max / (1 + exp(-C * (var_Ve * theta_e) / sigma_e));
	return q;
}

// function that returns the firing rate of the exitatory population
double Cortical_Colum::get_Qi	(int N) const{
	_SWITCH((Vi))
	double q = Ni * Qi_max / (1 + exp(-C * (var_Vi * theta_i) / sigma_i));
	return q;
}

// function that scales the input
double Cortical_Colum::psi_ee	(int N) const{
	_SWITCH((Ve))
	double psi = (V_rev_e-var_Ve)/(V_rev_e-V_e0);
	return psi;
}

// function that scales the input
double Cortical_Colum::psi_ei	(int N) const{
	_SWITCH((Vi))
	double psi = (V_rev_e-var_Vi)/(V_rev_e-V_i0);
	return psi;
}

// function that scales the input
double Cortical_Colum::psi_ie	(int N) const{
	_SWITCH((Ve))
	double psi = (V_rev_i-var_Ve)/(V_rev_i-V_e0);
	return psi;
}

// function that scales the input
double Cortical_Colum::psi_ii	(int N) const{
	_SWITCH((Vi))
	double psi = (V_rev_i-var_Vi)/(V_rev_i-V_i0);
	return psi;
}

// function that returns the noise to exitatory population for stochastic RK4
double Cortical_Colum::noise_xRK(int N, double u_1, double u_2) const{
	extern const double h;
	extern const vector<double> B1, B2;
	double n = s  / h * (B1[N-1] * u_1 + B2[N-1] * u_2);
	return n;
}

// function that returns the noise to inhibitory population for stochastic RK4
double Cortical_Colum::noise_xE	(double u) const{
	extern const double h;
	double n = s / h * u;
	return n;
}

// function that calculates the Nth RK term
void Cortical_Colum::set_RK		(int N, double u_e1, double u_e2, double u_i1, double u_i2) {
	extern const double dt;
	_SWITCH((Ve)(Vi)(Phi_ee)(Phi_ei)(Phi_ie)(Phi_ii)(x_ee)(x_ei)(x_ie)(x_ii))
	Ve	  [N] = dt/tau_e * (V_e0 - var_Ve + rho_e * psi_ee(N) * var_Phi_ee + rho_i * psi_ie(N) * var_Phi_ie);
	Vi	  [N] = dt/tau_i * (V_i0 - var_Vi + rho_e * psi_ei(N) * var_Phi_ei + rho_i * psi_ii(N) * var_Phi_ii);
	Phi_ee[N] = dt*(var_x_ee);
	Phi_ei[N] = dt*(var_x_ei);
	Phi_ie[N] = dt*(var_x_ie);
	Phi_ii[N] = dt*(var_x_ii);
	x_ee  [N] = dt*(pow(gamma_ee, 2) * (get_Qe(N) + noise_xRK(N, u_e1, u_e2) - var_Phi_ee) - 2 * gamma_ee * var_x_ee);
	x_ei  [N] = dt*(pow(gamma_ei, 2) * (get_Qe(N) + noise_xRK(N, u_i1, u_i2) - var_Phi_ei) - 2 * gamma_ei * var_x_ei);
	x_ie  [N] = dt*(pow(gamma_ie, 2) * (get_Qi(N) 			  			   	 - var_Phi_ie) - 2 * gamma_ie * var_x_ie);
	x_ii  [N] = dt*(pow(gamma_ii, 2) * (get_Qi(N)		 	  			 	 - var_Phi_ii) - 2 * gamma_ii * var_x_ii);
}

// function that ads all the RK terms together
void Cortical_Colum::add_RK(double u_e1, double u_i1) {
	extern const double h;
	Ve	  [0] += (Ve	[1] + Ve	[2] * 2 + Ve	[3] * 2 + Ve	[4])/6;
	Vi	  [0] += (Vi	[1] + Vi	[2] * 2 + Vi	[3] * 2 + Vi	[4])/6;
	Phi_ee[0] += (Phi_ee[1] + Phi_ee[2] * 2 + Phi_ee[3] * 2 + Phi_ee[4])/6;
	Phi_ei[0] += (Phi_ei[1] + Phi_ei[2] * 2 + Phi_ei[3] * 2 + Phi_ei[4])/6;
	Phi_ie[0] += (Phi_ie[1] + Phi_ie[2] * 2 + Phi_ie[3] * 2 + Phi_ie[4])/6;
	Phi_ii[0] += (Phi_ii[1] + Phi_ii[2] * 2 + Phi_ii[3] * 2 + Phi_ii[4])/6;
	x_ee  [0] += (x_ee	[1] + x_ee	[2] * 2 + x_ee	[3] * 2 + x_ee	[4])/6 + s * h * u_e1;
	x_ei  [0] += (x_ei	[1] + x_ei	[2] * 2 + x_ei	[3] * 2 + x_ei	[4])/6 + s * h * u_i1;
	x_ie  [0] += (x_ie	[1] + x_ie	[2] * 2 + x_ie	[3] * 2 + x_ie	[4])/6;
	x_ii  [0] += (x_ii	[1] + x_ii	[2] * 2 + x_ii	[3] * 2 + x_ii	[4])/6;
}

// function that uses Euler-Maruyama scheme to solve SODE
void Cortical_Colum::set_Euler(double u_e, double u_i) {
	extern const double dt;
	Ve	  [0] += dt/tau_e * (V_e0 - Ve[0] + rho_e * psi_ee(0) * Phi_ee[0] + rho_i * psi_ie(0) * Phi_ie[0]);
	Vi	  [0] += dt/tau_i * (V_i0 - Vi[0] + rho_e * psi_ei(0) * Phi_ei[0] + rho_i * psi_ii(0) * Phi_ii[0]);
	Phi_ee[0] += dt*(x_ee[0]);
	Phi_ei[0] += dt*(x_ei[0]);
	Phi_ie[0] += dt*(x_ie[0]);
	Phi_ii[0] += dt*(x_ii[0]);
	x_ee  [0] += dt*(pow(gamma_ee, 2) * (get_Qe(0) + noise_xE(u_e) - Phi_ee[0]) - 2 * gamma_ee * x_ee[0]);
	x_ei  [0] += dt*(pow(gamma_ei, 2) * (get_Qe(0) + noise_xE(u_i) - Phi_ei[0]) - 2 * gamma_ei * x_ei[0]);
	x_ie  [0] += dt*(pow(gamma_ie, 2) * (get_Qi(0) 			       - Phi_ie[0]) - 2 * gamma_ie * x_ie[0]);
	x_ii  [0] += dt*(pow(gamma_ii, 2) * (get_Qi(0)		 	  	   - Phi_ii[0]) - 2 * gamma_ii * x_ii[0]);
}
