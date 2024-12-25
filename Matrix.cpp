#include <iostream>
#include <random>
#include <windows.h>
#include <iomanip>
#include "Matrix.h"
#include <fstream>
#include <iterator>

using namespace std;

int correct_file_input(int defaultt, ifstream &fin)
{
	int res = defaultt;
	string s_in;
	if (fin.eof())
	{
		cout << "В файле недостаточно информации! Недостающие значения будут заменены на " << defaultt << endl;
		return res;
	}
	fin >> s_in;
	try
	{
		res = stoi(s_in);
	}
	catch (...) { cout << "В файле записано некорректное значение! Оно будет заменено на " << defaultt << endl; }
	return res;
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
	data = new int* [rows];
	for (int i = 0; i < rows; ++i) {
		data[i] = new int[cols];
	}
}

void Matrix::randomize(int minVal, int maxVal) {
	srand(time(0));
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			data[i][j] = minVal + rand() / (RAND_MAX + 1.0) * (maxVal - minVal);
		}
	}
}

void Matrix::readFromInput() {
	std::cout << "Введите элементы матрицы (" << rows << "x" << cols << "):\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> data[i][j];
		}
	}
}

void Matrix::readFromFile(const std::string& filename) {
	clear();
	ifstream fin(filename);
	if (fin) {
		rows = correct_file_input(1, fin);
		cols = correct_file_input(1, fin);
		if (rows > 0 && cols > 0)
		{
			clear();
			data = new int* [rows];
			for (int i = 0; i < rows; i++)
			{
				data[i] = new int[cols];
				for (int j = 0; j < cols; j++)
					data[i][j] = 0;
			}
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					data[i][j] = correct_file_input(0, fin);
				}
			}
		}
		else
		{
			cout << "В файле записаны некорректные значения! Будет создана нулевая матрица 1х1" << endl;
			*this = *(zeroMatrix(1, 1));
		}
	}
	else
	{
		cout << "Не удалось открыть файл! Будет создана нулевая матрица 1х1" << endl;
		*this = *(zeroMatrix(1, 1));
	}
	fin.close();
}

Matrix* Matrix::zeroMatrix(int rows, int cols) {
	Matrix* res = new Matrix(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			res->data[i][j] = 0;
	return res;
}

Matrix* Matrix::identityMatrix(int size) {
	Matrix* mat = zeroMatrix(size, size);
	for (int i = 0; i < size; ++i) {
		mat->data[i][i] = 1;
	}
	return mat;
}

Matrix Matrix::copy() const {
	Matrix newMatrix(rows, cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			newMatrix.data[i][j] = data[i][j];
		}
	}
	return newMatrix;
}

void Matrix::print() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << setw(8) << data[i][j] << " ";
		}
		cout << "\n";
	}
}

void Matrix::writeToFile(const std::string& filename) const {
	ofstream out(filename);
	if (out) {

		out << rows << " " << cols << "\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				out << data[i][j] << " ";
			}
			out << "\n";
		}
	}
	else cout << "Не удалось открыть файл!" << endl;
	out.close();
}

bool Matrix::isZero() const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (data[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::isIdentity() const {
	if (rows != cols) return false;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if ((i == j && data[i][j] != 1) || (i != j && data[i][j] != 0)) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::isSymmetric() const {
	if (rows != cols) return false;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (data[i][j] != data[j][i]) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::isSquare() const {
	return rows == cols;
}

void Matrix::clear() {
	if (data) {
		for (int i = 0; i < rows; ++i) {
			delete[] data[i];
		}
		delete[] data;
		data = nullptr;
	}
}

Matrix::~Matrix() { clear(); }
