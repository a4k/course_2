#pragma once

#include <vector>

#include "Cell.h";
#include "Config.h";

using namespace std;

struct ShipType {
	int size;
	int col;
};

class Ship
{
private:
	bool _sunken;
	bool _horiz;
	vector<Cell*> coordinates;
public:
	Ship();
	~Ship();

	void addCoordinate(Cell*);
	vector<Cell*> getCoordinates();

	bool isHoriz();
	void setHoriz();

	bool isSunken();
	void checkSunken();
	void setSunken();
};

