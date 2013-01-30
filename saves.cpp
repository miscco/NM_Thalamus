#include <iostream>
#include <vector>
#include "matio.h"
#include "Thalamic_Colum.h"
using std::vector;

// saving file for the c++ compilation

// saving the fluctuations of the populations
inline void get_data(int counter, Thalamic_Colum& Col, vector<double>& Ve, vector<double>& Vi) {
	Ve[counter] = Col.Ve[0];
	Vi[counter] = Col.Vi[0];
}

// closer of the variadic template
template<typename ...Args>
void save_matrix(mat_t*& mat) {Mat_Close(mat);};

// variadic template to save data_array "matrix" in a matlab file "mat"
template<typename ...Args>
void save_matrix(mat_t*& mat, vector<double>& matrix, const char* filename, Args& ...Arguments) {
	extern const int T;
	extern const int res;

	// generation of the explicit matrix in the matlab file
	matvar_t *matvar;

	// dimensions of the  data containers
	int dims[2] = {1,T*res};

	// writing the data of the array into the matlab matrix matvar
    matvar = Mat_VarCreate(filename,   MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dims, &matrix [0], 0);
    Mat_VarWrite( mat, matvar, 0);
    Mat_VarFree(matvar);

    // repeating for the other matrices
    save_matrix(mat, Arguments...);
}

// variadic template to save multiple inputs
template<typename ...Args>
void save_file(Args& ...Arguments) {

	// name of the data file
	const char* filename = "Steyn-Ross.mat";

	// removing old data file
	std::remove (filename);

	// saving the data
	std::cout << "saving the data!\n";

	// declaration of mat type
	mat_t *mat;

	//gernerating the file
	mat = Mat_Open(filename, MAT_ACC_RDWR);

	// saving the data into the mat file
	save_matrix(mat, Arguments...);
}
