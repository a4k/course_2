// declaration

#pragma once
#include <iostream>
#include "Controller.h"
#include "Elements.h"
#include "../model/Struct.h"
#include "../store/DataStore.h"

using namespace std;

// Многочлен
class Polynom: public Controller
{
private:
	Elements E;
	int count;
	int lenPolynoms;
public:

	Struct::model ePolynom, * lPolynom;
	


	Polynom();
	Polynom(int pow);
	~Polynom();


	void setPow(int pow);
	void setId(int id);


	int getPow();
	int getId();
	
	Polynom operator + (Polynom & second);
	const Polynom& operator = (Polynom &t);
	
    friend ostream &operator << (ostream &s, Polynom &c); // перегруженный оператор вывода
    friend istream &operator >> (istream &s, Polynom &c); // перегруженный оператор ввода

	/*
	int &operator()(int i)
    {
		int coef = getCoefElement(i);
        return coef;
    }
	/*

	/*
	void push(Core::polyData * data, int id); // Вставить многочлен
	void setPow(int id, int pow); // Установить степень

	int createCId(); // создание ID коэффициента

    Polynom();
    Polynom(int an);//конструктор с параметрами
    Polynom(const Polynom &); //копирования
    ~Polynom();//деструктор
    int getn(); //функция получения степени полинома
    double getkoef(int); //функция получения коэффициента при i-й степени
    Polynom operator+(const Polynom &);   //оператор сложения двух полиномов
    Polynom operator-(const Polynom &);   //оператор вычитания двух полиномов
    Polynom operator*(const Polynom &);// оператор умножения
    Polynom operator=(const Polynom &);   //оператор присваивания
    Polynom derivative();//производная
    Polynom integral();//интеграл
    friend ostream &operator<< (ostream &s, const Polynom &c); // перегруженный оператор вывода
    friend istream &operator >> (istream &s, Polynom &c); // перегруженный оператор ввода
    double &operator()(int i)
    {
        return koef[i];
    }

	*/


	//Complex();  // Конструктор по умолчанию
	//Complex(double re, double im);
	//Complex(double re);
	//Complex(Complex &b); // Конструктор копирования
	//~Complex();

	// Сеттеры и геттеры
	//void set(double re);


	//static void writeCount();

	// Перегруженные операции
	//Complex operator+(Complex & second);
	//const Complex& operator=(const Complex & right);
	//friend ostream& operator<<(ostream & cout, Complex & a);
	//friend istream& operator>>(istream & cin, Complex & a);

};

