// declaration

#pragma once
#include <iostream>
#include "Controller.h"
#include "Elements.h"
#include "../model/Struct.h"
#include "../store/DataStore.h"

using namespace std;

// ���������
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
	
    friend ostream &operator << (ostream &s, Polynom &c); // ������������� �������� ������
    friend istream &operator >> (istream &s, Polynom &c); // ������������� �������� �����

	/*
	int &operator()(int i)
    {
		int coef = getCoefElement(i);
        return coef;
    }
	/*

	/*
	void push(Core::polyData * data, int id); // �������� ���������
	void setPow(int id, int pow); // ���������� �������

	int createCId(); // �������� ID ������������

    Polynom();
    Polynom(int an);//����������� � �����������
    Polynom(const Polynom &); //�����������
    ~Polynom();//����������
    int getn(); //������� ��������� ������� ��������
    double getkoef(int); //������� ��������� ������������ ��� i-� �������
    Polynom operator+(const Polynom &);   //�������� �������� ���� ���������
    Polynom operator-(const Polynom &);   //�������� ��������� ���� ���������
    Polynom operator*(const Polynom &);// �������� ���������
    Polynom operator=(const Polynom &);   //�������� ������������
    Polynom derivative();//�����������
    Polynom integral();//��������
    friend ostream &operator<< (ostream &s, const Polynom &c); // ������������� �������� ������
    friend istream &operator >> (istream &s, Polynom &c); // ������������� �������� �����
    double &operator()(int i)
    {
        return koef[i];
    }

	*/


	//Complex();  // ����������� �� ���������
	//Complex(double re, double im);
	//Complex(double re);
	//Complex(Complex &b); // ����������� �����������
	//~Complex();

	// ������� � �������
	//void set(double re);


	//static void writeCount();

	// ������������� ��������
	//Complex operator+(Complex & second);
	//const Complex& operator=(const Complex & right);
	//friend ostream& operator<<(ostream & cout, Complex & a);
	//friend istream& operator>>(istream & cin, Complex & a);

};

