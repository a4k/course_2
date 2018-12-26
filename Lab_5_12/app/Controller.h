#pragma once
#include <iostream>
using namespace std;


class Controller
{
public:

	Controller() {
		id_ = total_++;
	}

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void set(int id) = 0;
	virtual void setPow(int pow) = 0;
	virtual void setId(int id) = 0;
	virtual void setCoef(int coef) = 0;

	//virtual Struct::model get(int);
	virtual int getPow() = 0;
	virtual int getId() = 0;
	virtual int getCoef() = 0;
	
	virtual void create() = 0;
	virtual void update() = 0;
	virtual void print() = 0;

	virtual int getCount() = 0;

protected:
    int id_;
    static int total_;
};
int Controller::total_ = 0;