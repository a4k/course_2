﻿/*
  Задача:
 Интерфейсные методы для полей (set, get);
 перегрузка как минимум одной операции над объектами класса (операция
указана в таблице); допускается определять дополнительные
операции;
 перегрузка операций потокового ввода и вывода для объектов этого
класса или определение соответствующих методов ввода/вывода значений
объектов класса;
 перегрузка операции присваивания;
 конструктор (перегруженный, как минимум в двух реализациях) и деструктор;
 статические поля и методы;
 виртуальные методы;
Желательные ограничения:
 абстрактный класс, чистые виртуальные методы;
 дружественность;
 шаблон класса.

Многочлены.
Бровкович Никита. ПИ в дизайне.
2 курс.
*/

#include <iostream>
#include <iomanip>
#include <locale.h>
#include "app/Polynom.h"
using namespace std;

void main()
{
	
	setlocale(LC_ALL,"Russian");

	Polynom A;
	//Polynom B;
	//Polynom C;


	// Новый многочлен
	//cin >> A;
	//cout << A;

	cout << endl;
	cout << endl;
	/*

	// Новый многочлен
	cin >> B;
	cout << B;

	cout << endl;
	cout << endl;


	C = A;
	cout << C;

	cout << endl;
	cout << endl;
	*/

	/*
	int n;
	cout << "Введите степень многочлена p:" << '\n';
	cin >> n;
	//p.create();
	//p.print();

	cout << "Введите коэфициенты полинома p:" << '\n';
    cin >> p;
	cout << p;

	*/
	/*
	int n, m;
    cout << "Введите степень полинома A и степень полинома B:" << '\n';
    cin >> n >> m;
    Polynom A(n), B(m), D, K, Y;
    cout << "Введите коэфициенты полинома A:" << '\n';
    cin >> A;
    cout << "Введите коэфициенты полинома B:" << '\n';
    cin >> B;
    cout << setw(17) << "Многочлен А:" << setw(5) << A << '\n';
    cout << setw(17) << "Многочлен B:" << setw(5) << B << '\n';
    cout << setw(17) << "Многочлен D=A+B:" << setw(5) << (D = A + B) << '\n';
    cout << setw(17) << "Многочлен K=A-B:" << setw(5) << (K = A - B) << '\n';
    cout << setw(17) << "Производная от A:" << setw(5)<< A.derivative() << '\n';
    cout << setw(17) << "Интеграл от A:" << setw(5) <<"C"<< A.integral()<< '\n';
    cout << setw(17) << "Многочлен Y=A*B:" << setw(5) << (Y = A*B)<< '\n';
	*/

	system("pause");  
}