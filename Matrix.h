#pragma once
#include <iostream>
#include <string>

using namespace std;

class Matrix {
private:
	int rows; // ���������� �����
	int cols; // ���������� ��������
	int** data; // ��������� ������ ��� �������� ��������� �������

	// �������� ������������ ������� �� ������
public:
	// ����������� �� ���������
	Matrix() {}; // ����������� �� ���������
	Matrix(int rows, int cols); // ����������� ��� �������� ������� ��������� �������

	void randomize(int minVal, int maxVal); // ������������� ������� ���������� �������
	void readFromInput();               // ���������� ������� � ����������
	void readFromFile(const std::string& filename); // ���������� ������� �� �����
	static Matrix* zeroMatrix(int rows, int cols);   // �������� ������� �������
	static Matrix* identityMatrix(int size);          // �������� ��������� �������
	Matrix copy() const;                        // ����������� �������
	void print() const;                        // ����� ������� �� �����
	void writeToFile(const std::string& filename) const; // ������ ������� � ����
	bool isZero() const;                       // ��������, �������� �� ������� �������
	bool isIdentity() const;                   // ��������, �������� �� ������� ���������
	bool isSymmetric() const;                  // ��������, �������� �� ������� ������������
	bool isSquare() const;                     // ��������, �������� �� ������� ����������
	//�������� ��� �������� ������ � ����������� ��������
	int** get_start() { return data; } //��������� �� ������ �������
	int get_rows() { return rows; }
	int get_cols() { return cols; }

	void clear();       // �������� �������

	~Matrix();                          // ����������
};