#include "Cell.h"



Cell::Cell()
{
	x = 0;
	y = 0;
	state = EMPTY;
}


Cell::~Cell()
{
}

void Cell::setX(int x) {
	this->x = x;
}

void Cell::setY(int y) {
	this->y = y;
}


void Cell::setStateEmpty() {
	state = EMPTY;
}

void Cell::setStateShip() {
	state = SHIP;
}

void Cell::setStateNoHit() {
	state = NO_HIT;
}

void Cell::setStateYesHit() {
	state = YES_HIT;
}

void Cell::setStateHit() {
	state = HIT;
}

void Cell::setStateSunken() {
	state = SUNKEN;
}


int Cell::getX() {
	return this->x;
}

int Cell::getY() {
	return this->y;
}


bool Cell::isStateEmpty() {
	return (this->state == EMPTY);
}

bool Cell::isStateShip() {
	return (this->state == SHIP);
}

bool Cell::isStateNoHit() {
	return (this->state == NO_HIT);
}

bool Cell::isStateYesHit() {
	return (this->state == YES_HIT);
}

bool Cell::isStateHit() {
	return (this->state == HIT);
}

bool Cell::isStateSunken() {
	return (this->state == SUNKEN);
}

