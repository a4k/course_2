#include "Ship.h"


Ship::Ship()
{
	_sunken = false;
	_horiz = false;
}


Ship::~Ship()
{
}


void Ship::addCoordinate(Cell * cell) {
	coordinates.push_back(cell);
}
vector<Cell*> Ship::getCoordinates() {
	return coordinates;
}

void Ship::setHoriz() {
	_horiz = true;
}

bool Ship::isHoriz() {
	return _horiz;
}

bool Ship::isSunken() {
	checkSunken();
	return _sunken;
}

void Ship::checkSunken() {
	bool _isSunken = true;
	for(int i = 0; i < coordinates.size(); i++) {
		if(_isSunken) {
			if(coordinates[i]->isStateShip()) _isSunken = false;
		}
	}
	if(_isSunken) setSunken();
}

void Ship::setSunken() {
	_sunken = true;
}