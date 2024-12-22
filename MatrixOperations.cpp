#include "MatrixOperations.h"
#include <iostream>
#include <windows.h>
#include "Matrix.h"
using namespace std;

Matrix* MatrixOperations::addMat(Matrix* mat1, Matrix* mat2) {
	Matrix* res = zeroMatrix(mat1->get_rows(), mat1->get_cols());
	for (int i = 0; i < res->get_rows(); i++) {
		for (int j = 0; j < res->get_cols(); j++) {
			res->get_start()[i][j] += (mat1->get_start())[i][j] + (mat2->get_start())[i][j];
		}
	}
	return res;
}

Matrix* MatrixOperations::multiMat(Matrix* mat1, Matrix* mat2) {
	//nxm на mxp = nxp
	Matrix* res = zeroMatrix(mat1->get_rows(), mat2->get_cols());
	for (int i = 0; i < mat1->get_rows(); i++) {
		for (int j = 0; j < mat1->get_cols(); j++) {
			for (int k = 0; k < mat2->get_cols(); k++)
				res->get_start()[i][k] += (mat1->get_start())[i][j] * (mat2->get_start())[j][k];
			}
		}
	return res;
}

Matrix* MatrixOperations::vychMat(Matrix* mat1, Matrix* mat2) {
	Matrix* res = zeroMatrix(mat1->get_rows(), mat1->get_cols());
	for (int i = 0; i < res->get_rows(); i++) {
		for (int j = 0; j < res->get_cols(); j++) {
			res->get_start()[i][j] += (mat1->get_start())[i][j] - (mat2->get_start())[i][j];
		}
	}
	return res;
}

Matrix* MatrixOperations::transMat(Matrix* mat) {
	Matrix* Tmat = new Matrix(mat->get_cols(), mat->get_rows());
	for (int i = 0; i < mat->get_cols(); i++)
		for (int j = 0; j < mat->get_rows(); j++)
			Tmat->get_start()[i][j] = (mat->get_start())[j][i];
	return Tmat;
}

int MatrixOperations::sumDiag(Matrix* mat) {
	int sum = 0;
	for (int i = 0; i < mat->get_rows(); i++)
		sum += mat->get_start()[i][i];
	return sum;
}

int MatrixOperations::opred(Matrix* mat)
{
	//дл€ удобства обозначим размер матрицы и еЄ начало новыми переменными
	int** data = mat->get_start();
	int n = mat->get_cols();
	if (n == 1) return data[0][0];
	else
	{
		int res = 0;
		//будем считать определитель, умножа€ эл-ты верхней строки на соответствующие им миноры
		//счЄтчик k - те самые эл-ты верхней строки, recurs - миноры, i и j - счЄтчики дл€ изначальной матрицы,
		//r_j - счЄтчик дл€ recurs (увеличиваетс€ на каждом шагу вместе с j, кроме случа€ k==j, т.к. это
		// "вычЄркиваемый" столбец)
		for (int k = 0; k < n; k++)
		{
			Matrix recurs(n - 1, n - 1);
			for (int i = 1; i < n; i++)
			{
				int r_j = 0;
				for (int j = 0; j < n; j++)
				{
					if (j != k)
					{
						recurs.get_start()[i - 1][r_j] = data[i][j];
						r_j++;
					}
				}
			}
			int res_now = pow(-1, k + 2) * data[0][k] * opred(&recurs);
			res += res_now;
			//не забываем, что все эти матрицы с минорами захламл€ют пам€ть!
			recurs.clear();
		}
		return res;
	}
}

int MatrixOperations::min_el(Matrix* mat)
{
	int res = mat->get_start()[0][0];
	for (int i = 0; i < mat->get_rows(); i++)
		for (int j = 0; j < mat->get_cols(); j++)
			if (mat->get_start()[i][j] < res) res = mat->get_start()[i][j];
	return res;
}

int MatrixOperations::max_el(Matrix* mat)
{
	int res = mat->get_start()[0][0];
	for (int i = 0; i < mat->get_rows(); i++)
		for (int j = 0; j < mat->get_cols(); j++)
			if (mat->get_start()[i][j] > res) res = mat->get_start()[i][j];
	return res;
}

void MatrixOperations::multi_num(Matrix* mat, int n)
{
	for (int i = 0; i < mat->get_rows(); i++)
		for (int j = 0; j < mat->get_cols(); j++)
			mat->get_start()[i][j] *= n;
}