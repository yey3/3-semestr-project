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
//������ ��� ����������� ����� case (���� �� �� ������� ����� ������� ����, � ������� ��� ���������� ����� ��
// ��������� ������)
#define end_of_case system("pause"); break;

void MenuManager::menu()
{
	short c = 1;
	//���������� �������� ����, ���� ���� �� ������� ����� "����� �� ���������"
	while (c != 5)
	{
		if (!elements.empty())
		{
			cout << "������ ������: " << endl;
			print_all();
		}
		else cout << "���� ��� �� ������� �� ����� �������" << endl;
		cout << "�������� ����� ��������: " << endl <<
			"1 ���� �������" << endl <<
			"2 �������� �������" << endl <<
			"3 ������� � ���� �������� � ����� ��������" << endl <<
			"4 ������� � ���� �������� � ����� ���������" << endl <<
			"5 ����� �� ���������" << endl;

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
				cout << "������� ���� ����� � ���� ����:)";
				break;
			}
			default:
			{
				cout << "�������� �� ������������� �� ����� �� ��������� ������!" << endl;
				break;
			}
		}
	}
}

void MenuManager::add_matr()
{
	short c = -1;
	//���������� ������ �������, ���� ���� �� ����� ���������� ��������
	while (c < 1 || c > 8)
	{
		cout << "������� ����� ������� �������� ����� �������:" << endl <<
			"1 ������������� ���������� ������� �� ���������" << endl <<
			"2 ���� � ����������" << endl <<
			"3 ���������� �� �����" << endl <<
			"4 �������� ������� �������" << endl <<
			"5 �������� ��������� �������" << endl <<
			"6 ����������� ������������ �������" << endl <<
			"7 ���������������� ������������ �������" << endl <<
			"8 �������� �������� �������" << endl;
		cin >> c;
		switch (c)
		{
			case 1:
			{
				cout << "������� ������� ������� � �������� ����� ��� ��������� ��-���: ";
				int rows = 1, cols = 1, minV = 0, maxV = 0;
				cin >> rows >> cols >> minV >> maxV;
				Matrix* matr = new Matrix(rows, cols);
				matr->randomize(minV, maxV);
				cout << "������� �������� ��� �������: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 2:
			{
				cout << "������� ������� �������: ";
				int rows = 1, cols = 1;
				cin >> rows >> cols;
				Matrix* matr = new Matrix(rows, cols);
				matr->readFromInput();
				cout << "������� �������� ��� �������: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 3:
			{
				cout << "������� �������� �����: ";
				string filename;
				cin >> filename;
				Matrix* matr = new Matrix;
				matr->readFromFile(filename);
				cout << "������� �������� ��� �������: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 4:
			{
				cout << "������� ������� �������: ";
				int rows = 1, cols = 1;
				cin >> rows >> cols;
				Matrix* matr = mo.zeroMatrix(rows, cols);
				cout << "������� �������� ��� �������: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 5:
			{
				cout << "������� ������ �������: ";
				int size = 1;
				cin >> size;
				Matrix* matr = mo.identityMatrix(size);
				cout << "������� �������� ��� �������: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, matr));
				end_of_case
			}
			case 6:
			{
				my_map::iterator to_copy = get_matr();
				Matrix matr = (to_copy->second)->copy();
				cout << "������� �������� ��� �������: ";
				string s;
				cin >> s;
				elements.insert(pair<string, Matrix*>(s, &matr));
				end_of_case
			}
			case 7:
			{
				my_map::iterator to_trans = get_matr();
				Matrix* matr = mo.transMat(to_trans->second);
				cout << "������� �������� ��� �������: ";
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
				cout << "�������� �� ������������� �� ����� �� ��������� ������! ������� ���������� �����";
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
	cout << "�������� ������� ��� ������ � ������� � ��������: " << endl;
	print_all();
	string name;
	cin >> name;
	my_map::iterator to_work = elements.find(name);
	while (to_work == elements.end())
	{
		cout << "�� ������� ������� � ����� ���������! ������� ���������� ��������: " << endl;
		cin >> name;
		to_work = elements.find(name);
	}
	return to_work;
}

void MenuManager::one_matr()
{
	short c = -1;
	//���������� ������ �������, ���� ���� �� ����� ���������� ��������
	while (c < 1 || c > 11)
	{
		cout << "������� ����� ��������: " << endl <<
			"1 ������ ������� � ����" << endl <<
			"2 ��������, �������� �� ������� �������" << endl <<
			"3 ��������, �������� �� ������� ���������" << endl <<
			"4 ��������, �������� �� ������� ������������" << endl <<
			"5 ��������, �������� �� ������� ����������" << endl <<
			"6 ����� ��-��� ������� ��������� �������" << endl <<
			"7 ������������ �������" << endl <<
			"8 ����������� ��-� �������" << endl <<
			"9 ������������ ��-� �������" << endl <<
			"10 ���������� ������� �� �����" << endl <<
			"11 ����� � ������� ����" << endl;
		cin >> c;
		switch (c)
		{
			case 1:
			{
				my_map::iterator to_work = get_matr();
				cout << "������� �������� ����� ��� ������: ";
				string filename;
				cin >> filename;
				to_work->second->writeToFile(filename);
				end_of_case
			}
			case 2: 
			{
				my_map::iterator to_work = get_matr();
				cout << "������� " << to_work->first;
				if (!to_work->second->isZero()) cout << " ��";
				cout << " �������" << endl;
				end_of_case
			}
			case 3:
			{
				my_map::iterator to_work = get_matr();
				cout << "������� " << to_work->first;
				if (!to_work->second->isIdentity()) cout << " ��";
				cout << " ���������" << endl;
				end_of_case
			}
			case 4:
			{
				my_map::iterator to_work = get_matr();
				cout << "������� " << to_work->first;
				if (!to_work->second->isSymmetric()) cout << " ��";
				cout << " ������������" << endl;
				end_of_case
			}
			case 5:
			{
				my_map::iterator to_work = get_matr();
				cout << "������� " << to_work->first;
				if (!to_work->second->isSquare()) cout << " ��";
				cout << " ����������" << endl;
				end_of_case
			}
			case 6:
			{
				my_map::iterator to_work = get_matr();
				if(to_work->second->isSquare())
				{
					cout << "����� ��-��� ������� ��������� ������� " << to_work->first << " ����� " <<
						mo.sumDiag(to_work->second);
				}
				else
				{
					cout << "������� ���������� ������ ��� ���������� ������!";
				}
				end_of_case
			}
			case 7:
			{
				my_map::iterator to_work = get_matr();
				if (to_work->second->isSquare())
					cout << "������������ ������� " << to_work->first << " ����� " << mo.opred(to_work->second) << endl;
				else
					cout << "������� ���������� ������ ��� ���������� ������!";
				end_of_case
			}
			case 8:
			{
				my_map::iterator to_work = get_matr();
				cout << "����������� ��-� ������� " << to_work->first << " ����� " << mo.min_el(to_work->second);
				end_of_case
			}
			case 9:
			{
				my_map::iterator to_work = get_matr();
				cout << "������������ ��-� ������� " << to_work->first << " ����� " << mo.max_el(to_work->second);
				end_of_case
			}
			case 10:
			{
				my_map::iterator to_work = get_matr();
				cout << "������� ����� ��� ���������� �� ���� �������: ";
				int a;
				cin >> a;
				mo.multi_num(to_work->second, a);
				end_of_case
			}
			case 11: break;
			default:
			{
				cout << "�������� �� ������������� �� ����� �� ��������� ������! ������� ���������� �����";
				end_of_case
			}
		}
	}
}

void MenuManager::two_matr()
{
	short c = -1;
	//���������� ������ �������, ���� ���� �� ����� ���������� ��������
	while (c < 1 || c > 5)
	{
		cout << "������� ����� ��������: " << endl <<
			"1 ����� ���� ������" << endl <<
			"2 �������� ���� ������" << endl <<
			"3 ������������ ���� ������" << endl <<
			"4 ��������� �� ������� ���� ������" << endl <<
			"5 ����� � ������� ����" << endl;
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
					cout << "���������� � ���������� �������� ������� (����� ��������� � ������� ��� ������):" << endl;
					matr->print();
					string name = to_work1->first + "+" + to_work2->first;
					elements.insert(pair<string, Matrix*>(name, matr));
				}
				else cout << "������� ���������� ������ ��� ������ ������ �������!" << endl;
				end_of_case
			}
			case 2:
			{
				my_map::iterator to_work1 = get_matr();
				my_map::iterator to_work2 = get_matr();
				if (mo.one_size(to_work1->second, to_work2->second))
				{
					Matrix* matr = mo.vychMat(to_work1->second, to_work2->second);
					cout << "���������� � ���������� ��������� ������� (����� ��������� � ������� ��� ������):" << endl;
					matr->print();
					string name = to_work1->first + "-" + to_work2->first;
					elements.insert(pair<string, Matrix*>(name, matr));
				}
				else cout << "������� ���������� ������ ��� ������ ������ �������!" << endl;
				end_of_case
			}
			case 3:
			{
				my_map::iterator to_work1 = get_matr();
				my_map::iterator to_work2 = get_matr();
				if (mo.can_multi(to_work1->second, to_work2->second))
				{
					Matrix* matr = mo.multiMat(to_work1->second, to_work2->second);
					cout << "���������� � ���������� ������������ ������� (����� ��������� � ������� ��� ������):" << endl;
					matr->print();
					string name = to_work1->first + "*" + to_work2->first;
					elements.insert(pair<string, Matrix*>(name, matr));
				}
				else cout << "� ��������� ������ ������������ �������!" << endl;
				end_of_case
			}
			case 4:
			{
				my_map::iterator to_work1 = get_matr();
				my_map::iterator to_work2 = get_matr();
				cout << "������� ������ " << to_work1->first << " � " << to_work2->first;
				if (!mo.one_size(to_work1->second, to_work2->second)) cout << " ��";
				cout << " �����" << endl;
				end_of_case
			}
			case 5: break;
			default:
			{
				cout << "�������� �� ������������� �� ����� �� ��������� ������! ������� ���������� �����";
				end_of_case
			}
		}
	}
}
