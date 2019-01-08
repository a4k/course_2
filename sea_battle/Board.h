#pragma once

#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>
#include <set>
#include <string>

#include "Cell.h";
#include "Ship.h";
#include "Config.h";

using namespace std;


class Board
{
private:
	vector< vector<Cell*>> cells;
	vector<Ship*> ships;
	vector<ShipType*> shipTypes;

	set<string> header;
	set<int> body;

public:
	Board();
	~Board();

	void makeDefaultSettings();

	MESSAGE listenAttack(int x, int y);

	void create();
	void createShips();
	void createShipType(int size, int col);
	void createShip(int size);
	void addShipCoordinate(Ship *, int x, int y);
	Ship * getShipByCell(int x, int y);

	bool isRightCoordinates(int x, int y);

	void makeHitAroundShip(Ship *);
	int countHit();
	Cell * findCell(int x, int y);

	void setHeader();
	void setBody();

	void printHeader();
	void print();
	void printEnemy();
};

