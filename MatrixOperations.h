#pragma once
#include "Matrix.h"


class MatrixOperations : public Matrix{
public:
	Matrix* addMat(Matrix* mat1, Matrix* mat2); //сумма 2-х матриц
	Matrix* vychMat(Matrix* mat1, Matrix* mat2); //разность 2-х матриц
	Matrix* multiMat(Matrix* mat1, Matrix* mat2); //произведение 2-х матриц
	Matrix* transMat(Matrix* mat); //транспонирование
	int sumDiag(Matrix* mat); //сумма эл-в главной диагонали матрицы
	int opred(Matrix* mat); //определитель
	int min_el(Matrix* mat); //мин эл-т матрицы
	int max_el(Matrix* mat); //макс эл-т матрицы
	void multi_num(Matrix* mat, int n); //домножение на число
	bool one_size(Matrix* mat1, Matrix* mat2) //одинаковы ли размеры матриц
	{
		return (mat1->get_cols() == mat2->get_cols() && mat1->get_rows() == mat2->get_rows());
	}
	bool can_multi(Matrix* mat1, Matrix* mat2) //можно ли умножить матрицы друг на друга
	{
		return mat1->get_cols() == mat2->get_rows();
	}
};