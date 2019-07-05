// PP_0.cpp: определяет точку входа для консольного приложения.
//
#include <locale>//setlocale
#include "stdafx.h"
#include<vector>
#include <Windows.h>//setconsoleCP
#include<iostream> //cout
#include <string>
#include <malloc.h>
#include <math.h> 
#include <ctime>
#include <algorithm>
#include <thread>
#include <fstream>
long long *xaF, *xbF;
long long *MPAR1;
long long *MPAR2;
long long *Bas, *Adr;
using namespace std;

long long IInsert(long long MaxNum = INT_MAX, string input = "") {//ввод числа типа long long от 1 до MaxNum
	string s;
	bool key = false;
	long long res;

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
		catch (const invalid_argument&) {
			cout << "Ошибка!Введено не число" << endl;
			return -1;
		}
		catch (const out_of_range&) {
			cout << "Число вне диапазона integer" << endl;
			return -1;
		}

	}

	do {

		getline(cin, s);

		long long i;
		if ((i = s.find(' ')) != std::string::npos) {
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
		long long i;
		if ((i = s.find(' ')) != std::string::npos) {
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


long long gcd(long long x, long long y)//функция сравнивает 2 числа, возвращает 1 если числа взимнопростые.
{
	return y ? gcd(y, x%y) : x;
}
long long* ReadBas() {//функция счтывает числа базиса, вернет массив элементов или NULL
	cout << "Введите базис числа, разделяя числа пробелом" << endl;
	string SBasNums = "";
	getline(cin, SBasNums);
	long long z;
	while ((z = SBasNums.find("  ")) != std::string::npos)//убираем лишние разделители
		SBasNums.erase(z, 1);
	if (SBasNums != "") {
		if (SBasNums[0] == ' ')//убираем пробелы в 1 и последнем символе строки если есть
			SBasNums.erase(0, 1);
		if (SBasNums[SBasNums.length() - 1] == ' ')
			SBasNums.erase(SBasNums.length() - 1, 1);//теперь все параметры гаранитрованно разделены 1 пробелом

		short SpaceCount = 0;
		long long wtf = SBasNums.length() - 1;
		for (long long i = 0; i < wtf; i++) {
			if (SBasNums[i] == ' ')
				SpaceCount++;
		}
		string *SArr1Basis;//массив с элементами типа string, содержащий значения базиса
		SArr1Basis = new string[SpaceCount + 1];
		for (long long i = 0; i < SpaceCount + 1; i++) {
			if (i != SpaceCount) {
				long long k = SBasNums.find(' ');
				SArr1Basis[i] = SBasNums.substr(0, k);
				SBasNums.erase(0, k + 1);
			}
			else {
				SArr1Basis[SpaceCount] = SBasNums;//вот тут осторожно. как передаётся?
			}
		}//     1    2 3456 7 8 910    теcт
		long long NumElements = SpaceCount + 1;
		long long *IArr1Basis;//массив для элементов базиса
		IArr1Basis = new long long[NumElements];
		for (long long i = 0; i < NumElements; i++) {
			IArr1Basis[i] = IInsert(INT_MAX, SArr1Basis[i]);//парсим
		}
		bool BasisCreated = true;

		for (long long i = 0; i < NumElements; i++)
		{
			if (IArr1Basis[i] == -1) {//проверяем все ли элементы были корректны
				cout << "Ошибка в записи: " << SArr1Basis[i] << endl;
				BasisCreated = false;
			}
		}
		if (BasisCreated == true) {//базис описан корректно
			for (long long i = 0; i < NumElements; i++) {//все элементы базиса также должны быть попарно взаимно просты.
				for (long long j = i; j < NumElements; j++) {
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

bool CmpParamsBasis(long long *Basis, long long Num1, long long Num2) {
	double MaxNums;
	long long n = _msize(Basis) / sizeof(long long);//количество элементов массива
	MaxNums = 1;
	for (long long i = 0; i < n; i++) {
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
void ShowBasis(long long *Basis) {
	if (Basis == NULL) {
		cout << "Базис не задан" << endl;
	}
	else {
		cout << "Текущий базис:" << endl;
		long long n = _msize(Basis) / sizeof(long long);//количество элементов массива
		cout << "(";
		for (long long i = 0; i < n; i++) {
			cout << Basis[i] << "; ";
		}
		cout << ")" << endl;
	}
}


long long* CreateModParams(long long *Basis, long long Num) {
	//функция берёт параметры из таблицы используемых чисел и помещает в отедльный массив с которым будет происходить работа
	// при переходе на динамику добавить проверку на NULL и освобождение памяти
	long long n = _msize(Basis) / sizeof(long long);//количество элементов массива
	long long *ModParam = new long long[n];
	for (long long i = 0; i < n; i++) {
		ModParam[i] = Num % Basis[i];
	}
	return ModParam;
}

void Add2(long long nstart,long long nend) {
	for (long long i = nstart; i <= nend; i++) {
		Adr[i] = (MPAR1[i] + MPAR2[i]) % Bas[i];
	}
}
void Add1(long long *ModParam1, long long *ModParam2, long long *Basis, long long *B) {
	MPAR1 = ModParam1;
	MPAR2 = ModParam2;
	Bas = Basis;
	Adr = B;
	long long n = _msize(Basis) / sizeof(long long);
	thread s1(Add2, 0, ((n / 4) - 1));
	thread s2(Add2, (n / 4), ((2*n / 4) - 1));
	thread s3(Add2, (2*n / 4), (3*n/4)-1);
	Add2((3*n / 4), n - 1);
	s1.join();
	s2.join();
	s3.join();
	B = Adr;
}
void Add(long long *ModParam1, long long *ModParam2, long long *Basis, long long *B) {
	long long n = _msize(Basis) / sizeof(long long);
	for (long long i = 0; i < n; i++) {
		B[i] = (ModParam1[i] + ModParam2[i]) % Basis[i];
	}
}

long long* CreateModParams1(long long *Basis, INT64 Num) {
	//функция берёт параметры из таблицы используемых чисел и помещает в отедльный массив с которым будет происходить работа
	// при переходе на динамику добавить проверку на NULL и освобождение памяти
	long long n = _msize(Basis) / sizeof(long long);//количество элементов массива

	long long *ModParam = new long long[n];
	for (INT64 i = 0; i < n; i++) {
		ModParam[i] = Num % Basis[i];
	}
	return ModParam;
}



//----------------------------------------------------------------------------------------------------------------------------------
bool MoreOrNot(string num1, string num2) {
	//num1 num2 > 0
	long long n1 = num1.length();
	long long n2 = num2.length();
	if (n1 > n2) {
		return true;
	}
	if (n1 < n2) {
		return false;
	}
	for (long long i = 0;i < n1;i++) {
		if ((num1[i] - '0') >(num2[i] - '0')) {
			return true;
		}
		if ((num1[i] - '0') <(num2[i] - '0')) {
			return false;
		}
	}
	return true;
}
string AMinB(string num1, string num2) {
	//подаём параметры в функцию только когда точно уверенны, что num1 > num2
	long long n1 = num1.length();
	long long n2 = num2.length();
	string s3;//result
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	long long ostatok = 0;
	for (long long i = 0;i < n2;i++) {
		long long sum = ((num1[i] - '0') - (num2[i] - '0') - ostatok);
		if (sum < 0) {
			sum += 10;
			ostatok = 1;
		}
		else {
			ostatok = 0;
		}
		s3.push_back(sum % 10 + '0');
	}
	for (long long i = n2;i < n1;i++) {
		long long sum = ((num1[i] - '0') - ostatok);
		if (sum < 0) {
			sum += 10;
			ostatok = 1;
		}
		else {
			ostatok = 0;
		}
		s3.push_back(sum % 10 + '0');
	}
	reverse(s3.begin(), s3.end());
	while (s3[0] == '0')
	{
		s3.erase(0, 1);
		if (s3 == "") {
			return "0";
		}
	}
	return s3;
}
string SumBF(string num1, string num2) {
	long long n1 = num1.length();
	long long n2 = num2.length();
	if (n1 > n2) {
		swap(num1, num2);//более длинная строка вторая
		swap(n1, n2);
	}
	string s3;//result
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	long long ostatok = 0;
	for (long long i = 0;i < n1;i++) {
		long long sum = ((num1[i] - '0') + (num2[i] - '0') + ostatok);
		s3.push_back(sum % 10 + '0');
		ostatok = sum / 10;
	}
	for (long long i = n1;i < n2;i++) {
		long long sum = ((num2[i] - '0') + ostatok);
		s3.push_back(sum % 10 + '0');
		ostatok = sum / 10;
	}
	if (ostatok) s3.push_back(ostatok + '0');
	reverse(s3.begin(), s3.end());
	return s3;
}
string MultBF(string num1, string num2) {
	long long n1 = num1.length();
	long long n2 = num2.length();
	if (n1 > n2) {
		swap(num1, num2);//более длинная строка вторая
		swap(n1, n2);
	}
	string s3 = "0";//result
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	long long ostatok = 0;
	//последняя цифра n1 это n1[0]
	//каждую n[i-uyu] перемножаем с каждым n2[k-ым]
	string promezhut = "";
	for (long long i = 0;i < n1;i++) {
		promezhut = "";
		for (long long j = 0;j < n2;j++) {
			long long sum = ((num1[i] - '0')*(num2[j] - '0') + ostatok);
			promezhut.push_back(sum % 10 + '0');
			ostatok = sum / 10;
		}
		if (ostatok != 0) {
			promezhut.push_back(ostatok + '0');
		}
		ostatok = 0;
		reverse(promezhut.begin(), promezhut.end());
		for (long long l = 0;l < i;l++) {
			promezhut.push_back('0');
		}
		s3 = SumBF(s3, promezhut);
	}

	return s3;
}
string* MultNASum(string num1, string num2, string *resultarea) {
	string i = "1";
	string *res = new string(num1);
	//cout << "WTF" << *res;
	while (i != num2) {
		*res = SumBF(*res, num1);
		i = SumBF(i, "1");
	}
	//cout << "WTF" << *res << endl;
	*resultarea = *res;
	delete res;
	//cout << *resultarea << "DFFGRLUKHFJE:FBR" << endl;
	return resultarea;
}
//----------------------------------------------------------------------------------------------------------------------------------
string FactLongLong(long long Num) {
	string aF = "1";
	for (long long i = 1;i <= Num;i++) {
		string *whereret = new string();
		aF = MultBF(aF, to_string(i));
		//aF = MultBF(aF, to_string(i));
	}
	return aF;
}
string RepeatFormulaLongLong(long long Num1, long long Num2) {
	clock_t startT = clock();

	//MultNASum("2", "4",whereret);
	string N1 = to_string(Num1);
	string N2 = to_string(Num2);
	string aF = "1";
	aF = FactLongLong(Num1);
	string bF = "1";
	bF = FactLongLong(Num2);
	string i = "1";
	string etoresult = SumBF(aF, bF);//a!=b!

	string res1;

	res1 = MultBF(aF, bF);//a!*b!
	res1 = SumBF(etoresult, res1);//a!*b! + a! + b!
	string resumn;
	resumn = MultBF(aF, aF);
	res1 = SumBF(res1, resumn);//a!*b! + a! + b! + a!*a!
	resumn = MultBF(bF, bF);
	res1 = SumBF(res1, resumn);//a!*b! + a! + b! + a!*a! + b!*b!
	clock_t endT = clock();
	cout << "Время работы в длинной арифметике: " << (double)(endT - startT) / CLOCKS_PER_SEC << endl;
	cout << res1 << "  : Дада это был res" << endl;
	return res1;
}

long long Retranslate(long long *Basis, long long *Result, long long Num1, long long Num2) {//вывод резуьтата работы в 10-ом виде

	long long n = _msize(Basis) / sizeof(long long);//количество элементов массива
	string result = RepeatFormulaLongLong(Num1, Num2);

	const long long base = 1000 * 1000 * 1000;
	bool flagCorrect = true;

	for (long long everyPinBas = 0;everyPinBas < n;everyPinBas++) {
		vector<long long> a;
		for (long long i = (long long)result.length(); i > 0; i -= 9)//заполнили вектор
			if (i < 9)
				a.push_back(atoi(result.substr(0, i).c_str()));
			else
				a.push_back(atoi(result.substr(i - 9, 9).c_str()));//закончили заполнять

		long long carry = 0;
		long long b = Basis[everyPinBas];
		for (long long i = (long long)a.size() - 1; i >= 0; --i) {
			long long cur = a[i] + carry * 1ll * base;
			a[i] = long long(cur / b);
			carry = long long(cur % b);
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();


		if (carry != Result[everyPinBas]) {
			flagCorrect = false;
		}
	}
	if (flagCorrect == true) {
		cout << "" << endl;
		cout << "Answer:  " << result << endl;
	}
	cout << "GG" << endl;
	return 0;
}


long long* Multy(long long *ModParam1, long long *ModParam2, long long *Basis, bool flagdelete, long long num) {
	long long n = _msize(Basis) / sizeof(long long);
	long long *B;
	long long *A = new long long[n];
	for (long long i = 0; i < n; i++) {
		A[i] = ModParam1[i];
	}
	long long i = 1;
	long long *currentparam;
	bool flag = false;
	currentparam = CreateModParams(Basis, i);
	for (long long j = 0; j < n; j++) {
		if (currentparam[j] != ModParam2[j]) {
			flag = true;
		}
	}
	delete[] currentparam;
	if (flag) {
		flag = false;
		while (!flag)
		{
			flag = true;
			i++;
			B = new long long[n];
			Add(A, ModParam1, Basis, B);
			delete[] A;
			A = B;
			currentparam = CreateModParams(Basis, i);
			for (long long j = 0; j < n; j++) {
				if (currentparam[j] != ModParam2[j]) {
					flag = false;
				}
			}
			delete[] currentparam;
		}
	}
	if (flagdelete == true) {
		delete[] ModParam1;
		delete[] ModParam2;
	}
	if (num == 1) {
		xaF = A;
	}
	if (num == 2) {
		xbF = A;
	}
	return A;
}

long long* Multy1(long long *ModParam1, long long *ModParam2, long long *Basis, bool flagdelete, long long num) {
	long long n = _msize(Basis) / sizeof(long long);
	long long *B;
	long long *A = new long long[n];
	for (long long i = 0; i < n; i++) {
		A[i] = ModParam1[i];
	}
	long long i = 1;
	long long *currentparam;
	bool flag = false;
	currentparam = CreateModParams(Basis, i);
	for (long long j = 0; j < n; j++) {
		if (currentparam[j] != ModParam2[j]) {
			flag = true;
		}
	}
	delete[] currentparam;
	if (flag) {
		flag = false;
		while (!flag)
		{
			flag = true;
			i++;
			B = new long long[n];
			Add1(A, ModParam1, Basis, B);
			delete[] A;
			A = B;
			currentparam = CreateModParams(Basis, i);
			for (long long j = 0; j < n; j++) {
				if (currentparam[j] != ModParam2[j]) {
					flag = false;
				}
			}
			delete[] currentparam;
		}
	}
	if (flagdelete == true) {
		delete[] ModParam1;
		delete[] ModParam2;
	}
	if (num == 1) {
		xaF = A;
	}
	if (num == 2) {
		xbF = A;
	}
	return A;
}
long long* Fact(long long *ModParam1, long long *Basis, long long num) {
	long long n = _msize(Basis) / sizeof(long long);
	long long *A = new long long[n];//результат умножения

	for (long long i = 0; i < n; i++) {
		A[i] = 1;
	}
	long long i = 1;
	long long *currentparam = NULL;
	bool flag = false;
	while (!flag)
	{
		flag = true;
		currentparam = CreateModParams(Basis, i);
		for (long long j = 0; j < n; j++) {
			if (currentparam[j] != ModParam1[j]) {
				flag = false;
			}
		}

		A = Multy(A, currentparam, Basis, true, 0);
		i++;
		//delete[] A;
		//A = B;
	}
	if (num == 1) {
		xaF = A;
	}
	if (num == 2) {
		xbF = A;
	}

	return A;
}

long long* Fact1(long long *ModParam1, long long *Basis, long long num) {
	long long n = _msize(Basis) / sizeof(long long);
	long long *A = new long long[n];//результат умножения

	for (long long i = 0; i < n; i++) {
		A[i] = 1;
	}
	long long i = 1;
	long long *currentparam = NULL;
	bool flag = false;
	while (!flag)
	{
		flag = true;
		currentparam = CreateModParams(Basis, i);
		for (long long j = 0; j < n; j++) {
			if (currentparam[j] != ModParam1[j]) {
				flag = false;
			}
		}

		A = Multy1(A, currentparam, Basis, true, 0);
		i++;
		//delete[] A;
		//A = B;
	}
	if (num == 1) {
		xaF = A;
	}
	if (num == 2) {
		xbF = A;
	}

	return A;
}


//long long* F(long long *ModParam1, long long *ModParam2, long long *Basis) {//Усложнить функцию
//	clock_t startT = clock();
//	long long n = _msize(Basis) / sizeof(long long);
//	
//	double start_time = clock();
//	//long long *aF = Fact(ModParam1, Basis);
//	long long *aF = new long long[n];
//	//Fact(ModParam1, Basis, std::cref(aF));
//	thread fact0(Fact, ModParam1, Basis, 1);
//	
//	long long *bF = new long long[n];
//	Fact(ModParam2, Basis, 2);
//	for (long long i = 0;i < n;i++) {
//		bF[i] = xbF[i];
//	}
//	fact0.join();
//	for (long long i = 0;i < n;i++) {
//		aF[i] = xaF[i];
//	}
//	long long *Result = new long long[n];//result = a!
//	for (long long i = 0;i < n;i++) {
//		Result[i] = aF[i];
//	}
//	long long *B = new long long[n];
//
//	
//	Add(Result, bF, Basis,B);//a!+b!
//	delete[] Result;
//	Result = B;
//
//	long long *Umnozh = Multy(aF, bF, Basis, false, 0);//a!*b!
//
//	B = new long long[n];
//	Add(Result, Umnozh, Basis, B);//a! + b! + a!*b!
//	delete[] Result;
//	Result = B;
//	delete[] Umnozh;
//	thread multaa(Multy, aF, aF, Basis, false, 1);
//	//Umnozh = Multy(aF, aF, Basis, false,true);//a!*a!
//	Umnozh = Multy( bF, bF, Basis, false,0);
//	B = new long long[n];
//	Add(Result, Umnozh, Basis, B);//a! + b! + a!*b! + b!*b!
//	delete[] Result;
//	Result = B;
//	delete[] Umnozh;
//
//	B = new long long[n];
//	multaa.join();
//	Add(Result, xaF, Basis, B);//a! + b! + a!*b! + a!*a! + b!*b!
//	delete[] Result;
//	Result = B;	
//	delete[] aF;
//	delete[] bF;
//	clock_t endT = clock();
//	cout <<"Время работы в СОК: "<< (double)(endT - startT) / CLOCKS_PER_SEC << endl;
//	return Result;
//}
long long* F(long long *ModParam1, long long *ModParam2, long long *Basis) {//Усложнить функцию
	clock_t startT = clock();
	long long n = _msize(Basis) / sizeof(long long);

	double start_time = clock();
	long long *aF = Fact(ModParam1, Basis, 0);
	long long *bF = Fact(ModParam2, Basis, 0);
	long long *Result = new long long[n];//result = a!
	for (long long i = 0;i < n;i++) {
		Result[i] = aF[i];
	}
	long long *B = new long long[n];
	Add(Result, bF, Basis, B);//a!+b!
	delete[] Result;
	Result = B;

	long long *Umnozh = Multy(aF, bF, Basis, false, 0);//a!*b!

	B = new long long[n];
	Add(Result, Umnozh, Basis, B);//a! + b! + a!*b!
	delete[] Result;
	Result = B;
	delete[] Umnozh;

	Umnozh = Multy(aF, aF, Basis, false, 0);//a!*a!

	B = new long long[n];
	Add(Result, Umnozh, Basis, B);//a! + b! + a!*b! + a!*a!
	delete[] Result;
	Result = B;
	delete[] Umnozh;

	Umnozh = Multy(bF, bF, Basis, false, 0);//b!*b!

	B = new long long[n];
	Add(Result, Umnozh, Basis, B);//a! + b! + a!*b! + a!*a! + b!*b!
	delete[] Result;
	Result = B;
	delete[] Umnozh;

	delete[] aF;
	delete[] bF;
	clock_t endT = clock();
	cout << "Время работы в СОК: " << (double)(endT - startT) / CLOCKS_PER_SEC << endl;
	return Result;
}

long long* F1(long long *ModParam1, long long *ModParam2, long long *Basis) {//Усложнить функцию
	clock_t startT = clock();
	long long n = _msize(Basis) / sizeof(long long);

	double start_time = clock();
	long long *aF = Fact1(ModParam1, Basis, 0);
	long long *bF = Fact1(ModParam2, Basis, 0);
	long long *Result = new long long[n];//result = a!
	for (long long i = 0;i < n;i++) {
		Result[i] = aF[i];
	}
	long long *B = new long long[n];
	Add1(Result, bF, Basis, B);//a!+b!
	delete[] Result;
	Result = B;

	long long *Umnozh = Multy1(aF, bF, Basis, false, 0);//a!*b!

	B = new long long[n];
	Add1(Result, Umnozh, Basis, B);//a! + b! + a!*b!
	delete[] Result;
	Result = B;
	delete[] Umnozh;

	Umnozh = Multy1(aF, aF, Basis, false, 0);//a!*a!

	B = new long long[n];
	Add1(Result, Umnozh, Basis, B);//a! + b! + a!*b! + a!*a!
	delete[] Result;
	Result = B;
	delete[] Umnozh;

	Umnozh = Multy1(bF, bF, Basis, false, 0);//b!*b!

	B = new long long[n];
	Add1(Result, Umnozh, Basis, B);//a! + b! + a!*b! + a!*a! + b!*b!
	delete[] Result;
	Result = B;
	delete[] Umnozh;

	delete[] aF;
	delete[] bF;
	clock_t endT = clock();
	cout << "Время работы в СОК параллельно: " << (double)(endT - startT) / CLOCKS_PER_SEC << endl;
	return Result;
}


bool CheckCommon(long long num) {
	for (long long i = 2; i <= sqrt(num); i++) {
		if (num % i == 0) {
			// вывести, что n  не простое, так как делится на i
			return false;
		}
	}
	// вывесьт что n простое.
	return true;
}
int main()
{	//возможно переветси все в double,но тогда как создавать таблицу трансляйций
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	bool EndApp = false;
	long long choise;

	double MaxNums = 0;
	long long *Basis = NULL, *testBas;
	long long *Res;
	long long Num1 = NULL, Num2 = NULL;//если сделать double,то остаток от деления придется искать циклом
									   //заменить DInsert и параметры в CMp и Create
									   //long long **TableAllowNums = NULL;
	long long *ModParam1 = NULL;
	long long *ModParam2 = NULL;
	string str0;
	long long j;
	ifstream fin("cppstudio.txt"); // открыли файл для чтения
	string a = "kek";
	std::cout << "Выберите действие" << endl;

	while (EndApp == false)
	{
		cout << "1 - задать базис" << endl;
		cout << "2 - ввести параметры" << endl;
		cout << "3 - вычислить" << endl;
		cout << "4 - выход" << endl;
		//cout << "5 - использовать дефолт" << endl; todo
		choise = IInsert(6);
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
				cout << "Базис не изменён" << endl;
				ShowBasis(Basis);
			}
			break;
		case 2:
			cout << "Введите первый параметр: ";
			Num1 = IInsert();
			cout << "Введите второй параметр: ";
			Num2 = IInsert();
			if (Basis != NULL) {
				//ShowBasis(Basis);
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
						//F(ModParam1, ModParam2, Basis);
						//Retranslate(Basis, F(ModParam1, ModParam2, Basis), Num1, Num2);
						F(ModParam1, ModParam2, Basis);
						F1(ModParam1, ModParam2, Basis);
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
		case 5:
			Basis = new long long[1000000];
			for (int i = 0;i < 1000000;i++) {
				fin >> a;
				Basis[i] = stoi(a);
			}
			fin.close(); // закрываем файл
			break;
		case 6:

			RepeatFormulaLongLong(4, 3);

			break;



		default:
			cout << "Попробуйте снова" << endl;
			break;
		}
	}
	return 0;
}

