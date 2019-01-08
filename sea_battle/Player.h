#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Config.h";
#include "Board.h";
#include "Cell.h";


using namespace std;

class Player
{
private:
	vector<Cell*> history;
	vector<Cell*> channel;

	int _points;
	
	set<string> header;

	Player * Enemy;
	Board * _board;

public:
	Player() {makeDefaultSettings();};
	~Player();

	void setEnemy(Player * enemy);
	void makeDefaultSettings();
	MESSAGE waitForCommand();
	MESSAGE waitForCPU();

	int getPoints();
	void setPoints(int count);

	MESSAGE attack(string x, string y);
	MESSAGE listenAttack(int x, int y);
	MESSAGE makeAttack(int x, int y);
	MESSAGE attackAI();

	bool isHistory(int x, int y);
	void pushToHistory(Cell *);

	bool isEmptyChannel();
	void pushToChannel(Cell *);


	void getBoard();
	void getBoardHidden();
	void getBoardEnemy();
	int countBoardHit();

	void setHeader();
	int translateX(string x);
	int translateY(string y);
};

