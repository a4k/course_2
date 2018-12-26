#pragma once
#include <iostream>
#include "Factory.h"
#include "Polynom.h"
using namespace std;


class ControllerFactory: public Factory
{
public:
	Controller* createPolynom() {
		return new Polynom;
	}
	Controller* createElements() {
		return new Elements;
	};
};