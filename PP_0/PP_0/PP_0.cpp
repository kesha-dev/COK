// PP_0.cpp: определяет точку входа для консольного приложения.
//
#include <locale>//setlocale
#include "stdafx.h"
#include <Windows.h>//setconsoleCP
#include<iostream> //cout
#include <string>
#include <malloc.h>
#include <math.h> 
#include <ctime>
/*
todo: добавить динамическую память
	рабочий таймер
	перевести все типы на double
	добавить эталонные значения
*/


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
	if (SBasNums != "") {
		if (SBasNums[0] == ' ')//убираем пробелы в 1 и последнем символе строки если есть
			SBasNums.erase(0, 1);
		if (SBasNums[SBasNums.length() - 1] == ' ')
			SBasNums.erase(SBasNums.length() - 1, 1);//теперь все параметры гаранитрованно разделены 1 пробелом

		short SpaceCount = 0;
		int wtf = SBasNums.length() - 1;
		for (int i = 0;i < wtf;i++) {
			if (SBasNums[i] == ' ')
				SpaceCount++;
		}
		string *SArr1Basis;//массив с элементами типа string, содержащий значения базиса
		SArr1Basis = new string[SpaceCount + 1];
		for (int i = 0;i < SpaceCount + 1;i++) {
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
	else {//если введена пустая строка SBasNums ==""
		cout << "Введена пустая строка" << endl;
		return NULL;
	}
}

bool CmpParamsBasis(int *Basis, int Num1, int Num2) {
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
int* Add(int *ModParam1,int *ModParam2, int *Basis) {
	int n = _msize(Basis) / sizeof(int);
	int *A = new int[n];
	for (int i = 0;i < n;i++) {
		A[i] = (ModParam1[i] + ModParam2[i]) % Basis[i];
	}
	return A;
}
int* Multy(int *ModParam1,int *ModParam2, int *Basis) {
	int n = _msize(Basis) / sizeof(int);

	int *A = new int[n];
	for (int i = 0;i < n;i++) {
		A[i] = (ModParam1[i] * ModParam2[i]) % Basis[i];
	}
	return A;
}

int* CreateModParams(int *Basis, int Num) {
	//функция берёт параметры из таблицы используемых чисел и помещает в отедльный массив с которым будет происходить работа
	// при переходе на динамику добавить проверку на NULL и освобождение памяти
	double MaxNums = 1;
	int n = _msize(Basis) / sizeof(int);//количество элементов массива
	for (int i = 0; i < n;i++) {
		MaxNums *= Basis[i];
	}
	MaxNums--;
	int *ModParam = new int[n];
	for (int i = 0; i < n;i++) {
		ModParam[i] = Num % Basis[i];
	}
	return ModParam;
}

int* F(int *ModParam1,int *ModParam2, int *Basis) {//Усложнить функцию
	//F = (a+b)^3 = a^3 + 3*a^2b + 3ab^2 + b^3
	int n = _msize(Basis) / sizeof(int);
	int *Func = new int[n];
	double start_time = clock();
	int *A3 = Multy(Multy(ModParam1, ModParam1, Basis), ModParam1, Basis);
	int *B3 = Multy(Multy(ModParam2, ModParam2, Basis), ModParam2, Basis);
	int *A2B_3 = Multy(Multy(ModParam1, ModParam1, Basis), Multy(CreateModParams(Basis, 3), ModParam2, Basis), Basis);
	int *B2A_3 = Multy(Multy(ModParam2, ModParam2, Basis), Multy(CreateModParams(Basis, 3), ModParam1, Basis), Basis);

	int *X = Add(A3, B3, Basis);
	int *Y = Add(A2B_3, B2A_3, Basis);
	Func = Add(X,Y,Basis);
	double end_time = clock();
	double search_time = end_time - start_time;
	cout << "ВРемя работы: " << search_time << endl;
	cout << "В модулярной СС получено: (";
	for (int i = 0;i < n;i++) {
		cout << Func[i] << ";  ";
	}
	cout << ")" << endl;
	return Func;
}

//int** CreateTranslateTable(int **TableAllowNums, int *Basis) {
//	double MaxNums = 1;
//	int n = _msize(Basis) / sizeof(int);//количество элементов массива
//	for (int i = 0; i < n;i++) {
//		MaxNums *= Basis[i];
//	}
//	MaxNums--;
//
//	//массив сопоставляет числа с их представлением в модулярной СС.
//	//при переходе на динамику добавить сюда проверку на NULL и освобождение памяти
//	TableAllowNums = new int *[MaxNums];
//	for (int i = 0;i<MaxNums;i++) {
//		TableAllowNums[i] = new int[n];
//	}
//	for (int i = 0;i< MaxNums;i++) {
//		for (int j = 0;j<n;j++) {
//			TableAllowNums[i][j] = i % Basis[j];
//		}
//	}
//	return TableAllowNums;
//}
int Retranslate(int *Basis, int *Result) {//вывод резуьтата работы в 10-ом виде
	double MaxNums = 1;
	int n = _msize(Basis) / sizeof(int);//количество элементов массива
	for (int i = 0; i < n;i++) {
		MaxNums *= Basis[i];
	}
	MaxNums--;
	bool found;
	for (int i = 0;i < MaxNums;i++) {
		found = true;
		for (int j = 0; j < n;j++) {
			if ((i % Basis[j]) != Result[j]) {
				found = false;
			}
		}
		if (found) {
			cout << "Полученное число: " << i << endl;
			return i;
		}
	}
	return 0;
}
int main()
{	//возможно переветси все в double,но тогда как создавать таблицу трансляйций
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	bool EndApp = false;
	int choise;

	double MaxNums = 0;
	int *Basis = NULL, *testBas;
	int Num1 = NULL, Num2 = NULL;//если сделать double,то остаток от деления придется искать циклом
								//заменить DInsert и параметры в CMp и Create
	//int **TableAllowNums = NULL;
	int *ModParam1 = NULL;
	int *ModParam2 = NULL;
	std::cout << "Выберите действие" << endl;

	while (EndApp == false)
	{
		cout << "1 - задать базис" << endl;
		cout << "2 - ввести параметры" << endl;
		cout << "3 - вычислить" << endl;
		cout << "4 - выход" << endl;
		//cout << "5 - использовать дефолт" << endl; todo
		choise = IInsert(4);
		switch (choise)
		{
		case 1: 

			testBas = ReadBas();
			if (testBas != NULL) {
				Basis = testBas;//првоерить что передача происходит по значению
				cout << "Базис успешно задан" << endl;
				ShowBasis(Basis);
				CmpParamsBasis(Basis, Num1, Num2);
				//таблица трансляций не имеет смысла с параметрами типа double
				//TableAllowNums = CreateTranslateTable(TableAllowNums, Basis);//возможно стоит поставить параметр out, но это не точно
			}
			else {
				cout << "Базис не изменён"<<endl;
				ShowBasis(Basis);
			}
			break;
		case 2: 
			cout << "Введите первый параметр: ";
			Num1 = IInsert();
			cout << "Введите второй параметр: ";
			Num2 = IInsert();
			if (Basis != NULL) {
				ShowBasis(Basis);
				if (CmpParamsBasis(Basis, Num1, Num2)) {
					ModParam1 = CreateModParams(Basis, Num1);//управление памятью
					ModParam2 = CreateModParams(Basis, Num2);
				}
			}
			break;
		case 3:
			if (Basis != NULL) {
				if (Num1 != NULL) {
					if (CmpParamsBasis(Basis, Num1, Num2)) {
						Retranslate(Basis, F(ModParam1, ModParam2, Basis));
					}
				}
				else {
					cout << "НЕ указаны параметры" << endl;
				}
			}
			else {
				cout << "Базис не задан" << endl;
			}
			break;
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

