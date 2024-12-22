#pragma once
#include "Matrix.h"
#include "MatrixOperations.h"
#include <iterator>
#include <algorithm>
#include <map>

typedef map <string, Matrix*, less <string>> my_map;

class MenuManager
{
	my_map elements; //��� �������, � �������� ������ �������� (map ���� � ������
	//���� �������� � ����� ������� ���� � ���� ��������)
	MatrixOperations mo; //������, ����� ������� ����� �������� � ������� ��������
public:
	void add_matr(); //���������� �������
	void del_matr(); //�������� �������
	void print_all(); //����� ���� ������
	void menu();
	void one_matr(); //���� �������� � ����� ��������
	void two_matr(); //���� �������� � ����� ���������
	my_map::iterator get_matr(); //��������������� �-�
};

