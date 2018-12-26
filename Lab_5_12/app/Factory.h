#pragma once
#include <iostream>
#include "Controller.h"
using namespace std;


class Factory
{
public:
	virtual Controller* createPolynom()=0;
	virtual Controller* createElements()=0;
};