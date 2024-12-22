#pragma once
#include <iostream>
#include <string>

using namespace std;

class Matrix {
private:
	int rows; // Количество строк
	int cols; // Количество столбцов
	int** data; // Двумерный массив для хранения элементов матрицы

	// Удаление существующей матрицы из памяти
public:
	// Конструктор по умолчанию
	Matrix() {}; // Конструктор по умолчанию
	Matrix(int rows, int cols); // Конструктор для создания матрицы заданного размера

	void randomize(int minVal, int maxVal); // Инициализация матрицы случайными числами
	void readFromInput();               // Считывание матрицы с клавиатуры
	void readFromFile(const std::string& filename); // Считывание матрицы из файла
	static Matrix* zeroMatrix(int rows, int cols);   // Создание нулевой матрицы
	static Matrix* identityMatrix(int size);          // Создание единичной матрицы
	Matrix copy() const;                        // Копирование матрицы
	void print() const;                        // Вывод матрицы на экран
	void writeToFile(const std::string& filename) const; // Запись матрицы в файл
	bool isZero() const;                       // Проверка, является ли матрица нулевой
	bool isIdentity() const;                   // Проверка, является ли матрица единичной
	bool isSymmetric() const;                  // Проверка, является ли матрица симметричной
	bool isSquare() const;                     // Проверка, является ли матрица квадратной
	//добавила для удобства работы с дальнейшими классами
	int** get_start() { return data; } //указатель на начало матрицы
	int get_rows() { return rows; }
	int get_cols() { return cols; }

	void clear();       // Удаление матрицы

	~Matrix();                          // Деструктор
};