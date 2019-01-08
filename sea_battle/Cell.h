#pragma once
#include "Config.h";

class Cell
{
private:
	int x;
	int y;
	CellState state;
public:
	Cell();
	~Cell();

	void setX(int);
	void setY(int);

	void setStateEmpty();
	void setStateShip();
	void setStateNoHit();
	void setStateYesHit();
	void setStateHit();
	void setStateSunken();

	int getX();
	int getY();

	bool isStateEmpty();
	bool isStateShip();
	bool isStateNoHit();
	bool isStateYesHit();
	bool isStateHit();
	bool isStateSunken();
};

