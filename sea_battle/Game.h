#pragma once
#include <iostream>

#include "Player.h";
#include "Config.h";

using namespace std;

class Game
{
public:
	Game(Player *p1, Player *p2) : player1(p1), player2(p2), _isStepByPC(false) {};
	~Game();

	GAME_STATE start();
	GAME_STATE update();
	void finish();
	
	void setStepPC(bool);
	bool isNotMyStep();

	void setGameState(GAME_STATE);
	GAME_STATE getGameState();
		
private:
	Player * player1;
	Player * player2;
	bool _isStepByPC;
	GAME_STATE _gameState; 

};

