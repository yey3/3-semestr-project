#pragma once
#include "Matrix.h"
#include "MatrixOperations.h"
#include <iterator>
#include <algorithm>
#include <map>

typedef map <string, Matrix*, less <string>> my_map;

class MenuManager
{
	my_map elements; //все матрицы, с которыми сейчас работаем (map чтоб у матриц
	//были названия и юзеру удобнее было с ними работать)
	MatrixOperations mo; //объект, через который будем работать с классом операций
public:
	void add_matr(); //добавление матрицы
	void del_matr(); //удаление матрицы
	void print_all(); //вывод всех матриц
	void menu();
	void one_matr(); //меню действий с одной матрицей
	void two_matr(); //меню действий с двумя матрицами
	my_map::iterator get_matr(); //вспомогательная ф-я
};

