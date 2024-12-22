#pragma once
#include "Matrix.h"


class MatrixOperations : public Matrix{
public:
	Matrix* addMat(Matrix* mat1, Matrix* mat2); //����� 2-� ������
	Matrix* vychMat(Matrix* mat1, Matrix* mat2); //�������� 2-� ������
	Matrix* multiMat(Matrix* mat1, Matrix* mat2); //������������ 2-� ������
	Matrix* transMat(Matrix* mat); //����������������
	int sumDiag(Matrix* mat); //����� ��-� ������� ��������� �������
	int opred(Matrix* mat); //������������
	int min_el(Matrix* mat); //��� ��-� �������
	int max_el(Matrix* mat); //���� ��-� �������
	void multi_num(Matrix* mat, int n); //���������� �� �����
	bool one_size(Matrix* mat1, Matrix* mat2) //��������� �� ������� ������
	{
		return (mat1->get_cols() == mat2->get_cols() && mat1->get_rows() == mat2->get_rows());
	}
	bool can_multi(Matrix* mat1, Matrix* mat2) //����� �� �������� ������� ���� �� �����
	{
		return mat1->get_cols() == mat2->get_rows();
	}
};