// PP_0.cpp: определяет точку входа для консольного приложения.
//
#include <locale>//setlocale
#include "stdafx.h"
#include <Windows.h>//setconsoleCP
#include<iostream> //cout
#include <string>
#include <malloc.h>
#include <math.h> 



using namespace std;

int IInsert(int MaxNum = INT_MAX, string input = "") {//ввод числа типа int от 1 до MaxNum
	string s;
	bool key = false;
	int res;

	if (input != "") {
		size_t check;
		try {
			res = stoi(input, &check);
			if (check == input.size()) {
				if ((res >= 1) && (res <= MaxNum))
				{
					return res;
				}
				else
				{
					cout << "Ошибка!Число вне диапазона" << endl;
					return  -1;
				}
			}
			else {
				cout << "Ошибка ввода" << endl;
				return -1;
			}
		}
		catch (const invalid_argument&) { cout << "Ошибка!Введено не число" << endl; 
		return -1;
		}
		catch (const out_of_range&) {
			cout << "Число вне диапазона integer" << endl;
			return -1;
		}
		
	}

	do {

		getline(cin, s);
		
		int i;
		if (int i = s.find(' ') != std::string::npos) {
			s.resize(i + 1);
		}
		while ((i = s.find(' ')) != std::string::npos)
			s.erase(i, 1);

		size_t check;
		try {
			res = stoi(s, &check);
			if (check == s.size()) {
				if ((res >= 1) && (res <= MaxNum))
				{
					key = true;
				}
				else
				{
					cout << "Вне диапазона количества элементов" << endl;
				}
			}
			else {
				cout << "Ошибка ввода" << endl;
			}
		}
		catch (const invalid_argument&) { cout << "Введено не число" << endl; cout << "Попробуйте снова" << endl; }
		catch (const out_of_range&) {
			cout << "Число вне диапазона integer" << endl; cout << "Попробуйте снова" << endl;
		}
	} while (key == false);
	return res;
}


double DInsert() {
	string s;
	bool key = false;
	double res;
	system("cls");
	cout << "Введите число: ";
	/*getline(cin, s);*/
	do {

		getline(cin, s);
		int i;
		if (int i = s.find(' ') != std::string::npos) {
			s.resize(i + 1);
		}
		while ((i = s.find(' ')) != std::string::npos)
			s.erase(i, 1);

		size_t check;
		try {
			res = stod(s, &check);
			if (check == s.size()) {
				if (res >= 0) {
					double a;
					if (modf(res, &a) == 0) {
						key = true;
					}
					else
					{
						cout << "Число должно быть целым" << endl;
					}
				}
				else {
					cout << "Используются только неотрицательные числа" << endl;
				}
			}
			else {
				cout << "Ошибка ввода" << endl;
			}
		}
		catch (const invalid_argument&) { cout << "Введено не число" << endl; cout << "Попробуйте снова" << endl; }
		catch (const out_of_range&) {
			cout << "Число вне диапазона double" << endl; cout << "Попробуйте снова" << endl;
		}
	} while (key != true);
	return res;
}


int gcd(int x, int y)//функция сравнивает 2 числа, возвращает 1 если числа взимнопростые.
{
	return y ? gcd(y, x%y) : x;
}
int* ReadBas() {//функция счтывает числа базиса, вернет массив элементов или NULL
	cout << "Введите базис числа, разделяя числа пробелом" << endl;
	string SBasNums = "";
	getline(cin, SBasNums);
	int z;
	while ((z = SBasNums.find("  ")) != std::string::npos)//убираем лишние разделители
		SBasNums.erase(z, 1);
	if (SBasNums[0] == ' ')//убираем пробелы в 1 и последнем символе строки если есть
		SBasNums.erase(0, 1);
	if (SBasNums[SBasNums.length() - 1] == ' ')
		SBasNums.erase(SBasNums.length() - 1, 1);//теперь все параметры гаранитрованно разделены 1 пробелом
	short SpaceCount = 0;
	for (int i = 0;i < SBasNums.length() - 1;i++) {
		if (SBasNums[i] == ' ')
			SpaceCount++;
	}
	string *SArr1Basis;//массив с элементами типа string, содержащий значения базиса
	SArr1Basis = new string[SpaceCount + 1];
	for (int i = 0;i < SpaceCount+1;i++) {
		if (i != SpaceCount) {
			int k = SBasNums.find(' ');
			SArr1Basis[i] = SBasNums.substr(0, k);
			SBasNums.erase(0, k + 1);
		}
		else {
			SArr1Basis[SpaceCount] = SBasNums;//вот тут осторожно. как передаётся?
		}
	}//     1    2 3456 7 8 910    теcт
	int NumElements = SpaceCount + 1;
	int *IArr1Basis;//массив для элементов базиса
	IArr1Basis = new int[NumElements];
	for (int i = 0; i < NumElements;i++) {
		IArr1Basis[i] = IInsert(INT_MAX, SArr1Basis[i]);//парсим
	}
	bool BasisCreated = true;

	for (int i = 0; i < NumElements;i++)
	{
		if (IArr1Basis[i] == -1) {//проверяем все ли элементы были корректны
			cout << "Ошибка в записи: " << SArr1Basis[i] << endl;
			BasisCreated = false;
		}
	}
		if (BasisCreated == true) {//базис описан корректно
			for (int i = 0; i < NumElements;i++) {//все элементы базиса также должны быть попарно взаимно просты.
				for (int j = i; j < NumElements;j++) {
					if (i == j) {
						//сравнивать с собой не нужно, но если добавить в цикле +1 то можно и за границы массива уйти
					}
					else {
						if (gcd(IArr1Basis[i], IArr1Basis[j]) != 1) {
							BasisCreated = false;
							cout << "Числа " << IArr1Basis[i] << " и " << IArr1Basis[j] << " не являются взаимнопростыми" << endl;
						}
					}
				}
			}
			if (BasisCreated) {//все числа оказались взаимно простыми
				return IArr1Basis;
			}
			else {//найдены не взаимно простые числа
				return NULL;
			}
		}
		else {//некорректно описан базис
			return NULL;
		}
	}

bool CmpParamsBasis(int *Basis, double Num1, double Num2) {
	double MaxNums;
	int n = _msize(Basis) / sizeof(int);//количество элементов массива
	MaxNums = 1;
	for (int i = 0; i < n;i++) {
		MaxNums *= Basis[i];
	}
	MaxNums--;
	cout << "Диапазон значений базиса: [0; " << MaxNums << "]" << endl;
	if ((Num1 != NULL) && (Num2 != NULL)) {
		if ((Num1 <= MaxNums) && (Num2 <= MaxNums)) {
			cout << "Параметры \n" << Num1 << "\n" << Num2 << "\n удовлетворяют заданному базису" << endl;
			return true;
		}
		else
		{
			cout << "Не все текущие параметры\n" << Num1 << "\n" << Num2 << "удовлетворяют заданному базису" << endl;
			return false;
		}
	}
	else {
		cout << "необходимо задать параметры" << endl;
	}
}
void ShowBasis(int *Basis) {
	if (Basis == NULL) {
		cout << "Базис не задан" << endl;
	}
	else {
		cout << "Текущий базис:" << endl;
		int n = _msize(Basis) / sizeof(int);//количество элементов массива
		cout << "(";
		for (int i = 0; i < n;i++) {
			cout << Basis[i] << "; ";
		}
		cout << ")" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	bool EndApp = false;
	double MaxNums = 0;
	int *Basis = NULL, *testBas;
	double Num1 = NULL, Num2 = NULL;
	int choise;
	std::cout << "Выберите действие" << endl;

	while (EndApp == false)
	{
		cout << "1 - задать базис" << endl;
		cout << "2 - ввести параметры" << endl;
		cout << "3 - вычислить" << endl;
		cout << "4 - выход" << endl;
		//cout << "5 - использовать дефолт" << endl; todo
		choise = IInsert(4);
		cout << choise << endl;
		switch (choise)
		{
		case 1: 

			testBas = ReadBas();
			if (testBas != NULL) {
				Basis = testBas;//првоерить что передача происходит по значению
				cout << "Базис успешно задан" << endl;
				ShowBasis(Basis);
				CmpParamsBasis(Basis, Num1, Num2);
			}
			else {
				cout << "Базис не изменён"<<endl;
				ShowBasis(Basis);
			}
			break;
		case 2: 
			Num1 = DInsert();
			Num2 = DInsert();
			ShowBasis(Basis);
			CmpParamsBasis(Basis, Num1, Num2);
			break;
		case 3: break;
		case 4: 
			EndApp = true; 
			break;
		default:
			cout << "Попробуйте снова" << endl;
			break;
		}
	}
    return 0;
}

