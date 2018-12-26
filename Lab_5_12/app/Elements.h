// declaration

#pragma once
#include <iostream>
#include "../model/Struct.h"
#include "../store/DataStore.h"
#include "Controller.h"
using namespace std;

// Многочлен
class Elements: public Controller
{
private:
	Struct::model eElement, * lElement;
	DataStore<Struct::model, 32> elements;
	int count;


public:

	Elements();
	~Elements();

	void set(int id);
	void setPow(int pow);
	void setId(int id);
	void setCoef(int coef);


	Struct::model get(int);
	int getPow();
	int getId();
	int getCoef();

	void create();
	void update();

	int getCount();

	void print();

};