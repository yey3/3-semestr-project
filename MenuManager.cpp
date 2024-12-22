#include "MenuManager.h"
#include "Matrix.h"
#include "MatrixOperations.h"
#include <iterator>
#include <algorithm>
#include <map>
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
//макрос для обозначения конца case (чтоб он не выводил сразу внешнее меню, а сначала дал посмотреть юзеру на
// результат работу)
#define end_of_case system("pause"); break;

void MenuManager::menu()
{
	short c = 1;
	//продолжаем выдавать меню, пока юзер не выберет пункт "выход из программы"
	while (c != 5)
	{
		if (!elements.empty())
		{
			cout << "Список матриц: " << endl;
			print_all();
		}
		else cout << "Пока что не введено ни одной матрицы" << endl;
		cout << "Выберите номер действия: " << endl <<
			"1 Ввод матрицы" << endl <<
			"2 Удаление матрицы" << endl <<
			"3 Переход в меню операций с одной матрицей" << endl <<
			"4 Переход в меню операций с двумя матрицами" << endl <<
			"5 Выход из программы" << endl;

		cin >> c;
		switch (c)
		{
			case 1:
			{
				add_matr();
				break;
			}
			case 2:
			{
				del_matr();
				break;
			}
			case 3:
			{
				one_matr();
				break;
			}
			case 4:
			{
				two_matr();
				break;
			}
			case 5:
			{
				cout << "Приятно было иметь с вами дело:)";
				break;
			}
			default:
			{
				cout << "Значение не соответствует ни одной из выбранной команд!" << endl;
				break;
			}
		}
	}
}

void MenuManager::add_matr()
{
	short c = -1;
	//продолжаем работу функции, пока юзер не введёт корректное значение
	while (c < 1 || c > 8)
	{
		cout << "Введите номер способа создания новой матрицы:" << endl <<
			"1 Инициализация случайными числами из диапазона" << endl <<
			"2 Ввод с клавиатуры" << endl <<
			"3 Считывание из файла" << endl <<
			"4 Создание нулевой матрицы" << endl <<
			"5 Создание единичной матрицы" << endl <<
			"6 Копирование существующей матрицы" << endl <<
			"7 Транспонирование существующей матрицы" << endl <<
			"8 Отменить создание матрицы" << endl;
		cin >> c;
		switch (c)
		{
			case 1:
			{
				cout << "Введите размеры матрицы и диапазон чисел для генерации эл-тов: ";
				int rows = 1, cols = 1, minV = 0, maxV = 0;
				cin >> rows >> cols >> minV >> maxV;
				Matrix* matr = new Matrix(rows, cols);
				matr->randomize(minV, maxV);
				cout << "Введите название для матрицы: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 2:
			{
				cout << "Введите размеры матрицы: ";
				int rows = 1, cols = 1;
				cin >> rows >> cols;
				Matrix* matr = new Matrix(rows, cols);
				matr->readFromInput();
				cout << "Введите название для матрицы: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 3:
			{
				cout << "Введите название файла: ";
				string filename;
				cin >> filename;
				Matrix* matr = new Matrix;
				matr->readFromFile(filename);
				cout << "Введите название для матрицы: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 4:
			{
				cout << "Введите размеры матрицы: ";
				int rows = 1, cols = 1;
				cin >> rows >> cols;
				Matrix* matr = mo.zeroMatrix(rows, cols);
				cout << "Введите название для матрицы: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 5:
			{
				cout << "Введите размер матрицы: ";
				int size = 1;
				cin >> size;
				Matrix* matr = mo.identityMatrix(size);
				cout << "Введите название для матрицы: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 6:
			{
				my_map::iterator to_copy = get_matr();
				Matrix matr = (to_copy->second)->copy();
				cout << "Введите название для матрицы: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, &matr));
				end_of_case
			}
			case 7:
			{
				my_map::iterator to_trans = get_matr();
				Matrix* matr = mo.transMat(to_trans->second);
				cout << "Введите название для матрицы: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 8:
			{
				break;
			}
			default:
			{
				cout << "Значение не соответствует ни одной из выбранной команд! Введите корректное число";
				break;
			}
		}
	}
}

void MenuManager::print_all()
{
	for (auto i = elements.begin(); i != elements.end(); i++)
	{
		cout << i->first << endl;
		i->second->print();
		cout << endl;
	}
}

void MenuManager::del_matr()
{
	my_map::iterator to_del = get_matr();
	to_del->second->clear();
	elements.erase(to_del->first);
}

my_map::iterator MenuManager::get_matr()
{
	cout << "Выберите матрицу для работы и введите её название: " << endl;
	print_all();
	string name;
	cin >> name;
	my_map::iterator to_work = elements.find(name);
	while (to_work == elements.end())
	{
		cout << "Не найдена матрица с таким названием! Введите корректное значение: " << endl;
		cin >> name;
		to_work = elements.find(name);
	}
	return to_work;
}

void MenuManager::one_matr()
{
	short c = -1;
	//продолжаем работу функции, пока юзер не введёт корректное значение
	while (c < 1 || c > 11)
	{
		cout << "Введите номер действия: " << endl <<
			"1 Запись матрицы в файл" << endl <<
			"2 Проверка, является ли матрица нулевой" << endl <<
			"3 Проверка, является ли матрица единичной" << endl <<
			"4 Проверка, является ли матрица симметричной" << endl <<
			"5 Проверка, является ли матрица квадратной" << endl <<
			"6 Сумма эл-тов главной диагонали матрицы" << endl <<
			"7 Определитель матрицы" << endl <<
			"8 Минимальный эл-т матрицы" << endl <<
			"9 Максимальный эл-т матрицы" << endl <<
			"10 Домножение матрицы на число" << endl <<
			"11 Выход в главное меню" << endl;
		cin >> c;
		switch (c)
		{
			case 1:
			{
				my_map::iterator to_work = get_matr();
				cout << "Введите название файла для записи: ";
				string filename;
				cin >> filename;
				to_work->second->writeToFile(filename);
				end_of_case
			}
			case 2: 
			{
				my_map::iterator to_work = get_matr();
				cout << "Матрица " << to_work->first;
				if (!to_work->second->isZero()) cout << " не";
				cout << " нулевая" << endl;
				end_of_case
			}
			case 3:
			{
				my_map::iterator to_work = get_matr();
				cout << "Матрица " << to_work->first;
				if (!to_work->second->isIdentity()) cout << " не";
				cout << " единичная" << endl;
				end_of_case
			}
			case 4:
			{
				my_map::iterator to_work = get_matr();
				cout << "Матрица " << to_work->first;
				if (!to_work->second->isSymmetric()) cout << " не";
				cout << " симметричная" << endl;
				end_of_case
			}
			case 5:
			{
				my_map::iterator to_work = get_matr();
				cout << "Матрица " << to_work->first;
				if (!to_work->second->isSquare()) cout << " не";
				cout << " квадратная" << endl;
				end_of_case
			}
			case 6:
			{
				my_map::iterator to_work = get_matr();
				if(to_work->second->isSquare())
				{
					cout << "Сумма эл-тов главной диагонали матрицы " << to_work->first << " равна " <<
						mo.sumDiag(to_work->second);
				}
				else
				{
					cout << "Функция определена только для квадратных матриц!";
				}
				end_of_case
			}
			case 7:
			{
				my_map::iterator to_work = get_matr();
				if (to_work->second->isSquare())
					cout << "Определитель матрицы " << to_work->first << " равен " << mo.opred(to_work->second) << endl;
				else
					cout << "Функция определена только для квадратных матриц!";
				end_of_case
			}
			case 8:
			{
				my_map::iterator to_work = get_matr();
				cout << "Минимальный эл-т матрицы " << to_work->first << " равен " << mo.min_el(to_work->second);
				end_of_case
			}
			case 9:
			{
				my_map::iterator to_work = get_matr();
				cout << "Максимальный эл-т матрицы " << to_work->first << " равен " << mo.max_el(to_work->second);
				end_of_case
			}
			case 10:
			{
				my_map::iterator to_work = get_matr();
				cout << "Введите число для домножения на него матрицы: ";
				int a;
				cin >> a;
				mo.multi_num(to_work->second, a);
				end_of_case
			}
			case 11: break;
			default:
			{
				cout << "Значение не соответствует ни одной из выбранной команд! Введите корректное число";
				end_of_case
			}
		}
	}
}

void MenuManager::two_matr()
{
	short c = -1;
	//продолжаем работу функции, пока юзер не введёт корректное значение
	while (c < 1 || c > 5)
	{
		cout << "Введите номер действия: " << endl <<
			"1 Сумма двух матриц" << endl <<
			"2 Разность двух матриц" << endl <<
			"3 Произведение двух матриц" << endl <<
			"4 Одинаковы ли размеры двух матриц" << endl <<
			"5 Выход в главное меню" << endl;
		cin >> c;
		switch (c)
		{
			case 1:
			{
				my_map::iterator to_work1 = get_matr();
				my_map::iterator to_work2 = get_matr();
				if (mo.one_size(to_work1->second, to_work2->second))
				{
					Matrix* matr = mo.addMat(to_work1->second, to_work2->second);
					cout << "Полученная в результате сложения матрица (будет добавлена в матрицы для работы):" << endl;
					matr->print();
					string name = to_work1->first + "+" + to_work2->first;
					elements.insert(pair<string, Matrix*>(name, matr));
				}
				else cout << "Функция определена только для матриц одного размера!" << endl;
				end_of_case
			}
			case 2:
			{
				my_map::iterator to_work1 = get_matr();
				my_map::iterator to_work2 = get_matr();
				if (mo.one_size(to_work1->second, to_work2->second))
				{
					Matrix* matr = mo.vychMat(to_work1->second, to_work2->second);
					cout << "Полученная в результате вычитания матрица (будет добавлена в матрицы для работы):" << endl;
					matr->print();
					string name = to_work1->first + "-" + to_work2->first;
					elements.insert(pair<string, Matrix*>(name, matr));
				}
				else cout << "Функция определена только для матриц одного размера!" << endl;
				end_of_case
			}
			case 3:
			{
				my_map::iterator to_work1 = get_matr();
				my_map::iterator to_work2 = get_matr();
				if (mo.can_multi(to_work1->second, to_work2->second))
				{
					Matrix* matr = mo.multiMat(to_work1->second, to_work2->second);
					cout << "Полученная в результате произведения матрица (будет добавлена в матрицы для работы):" << endl;
					matr->print();
					string name = to_work1->first + "*" + to_work2->first;
					elements.insert(pair<string, Matrix*>(name, matr));
				}
				else cout << "У выбранных матриц неподходящие размеры!" << endl;
				end_of_case
			}
			case 4:
			{
				my_map::iterator to_work1 = get_matr();
				my_map::iterator to_work2 = get_matr();
				cout << "Размеры матриц " << to_work1->first << " и " << to_work2->first;
				if (!mo.one_size(to_work1->second, to_work2->second)) cout << " не";
				cout << " равны" << endl;
				end_of_case
			}
			case 5: break;
			default:
			{
				cout << "Значение не соответствует ни одной из выбранной команд! Введите корректное число";
				end_of_case
			}
		}
	}
}
