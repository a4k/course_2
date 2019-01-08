#include "Game.h"


Game::~Game()
{
}

GAME_STATE Game::start() {
	player1->setEnemy(player2);
	player2->setEnemy(player1);

	update();
	
	return GAME_CONTINUE;
}

GAME_STATE Game::update() {
	system("cls");
	cout << "Your points: " << player1->getPoints() << ". Computer points: " << player2->getPoints() << endl;
	cout << "Yours board:" << endl;
	player1->getBoard();
	cout << "Computer board:" << endl;
	player1->getBoardEnemy();

	if(isNotMyStep()) {
		// cpu
		MESSAGE msg = player2->waitForCPU();
		if(msg == MESSAGE_GAME_CONTINUE) {
			setGameState(GAME_CONTINUE);
			setStepPC(false);
		}
		else if(msg == MESSAGE_GAME_END) {
			setGameState(GAME_END);
		}
	} else {
		// player
		MESSAGE msg = player1->waitForCommand();
		if(msg == MESSAGE_GAME_CONTINUE) {
			setGameState(GAME_CONTINUE);
			setStepPC(true);
		}
		else if(msg == MESSAGE_GAME_END) {
			setGameState(GAME_END);
		}
	}

	if(getGameState() == GAME_CONTINUE) update();
	if(getGameState() == GAME_END) finish();

	return getGameState();
}

void Game::finish() {
	system("cls");
	cout << "Your points: " << player1->getPoints() << ". Computer points: " << player2->getPoints() << endl;
	cout << "Yours board:" << endl;
	player1->getBoard();
	cout << "Computer board:" << endl;
	player1->getBoardEnemy();

	if(player1->getPoints() > player2->getPoints()) {
		cout << "You are won!" << endl;
	}
	else {
		cout << "You are lost.. PC is win." << endl;
	}

}


void Game::setStepPC(bool isStep) {
	_isStepByPC = isStep;
}

bool Game::isNotMyStep() {
	return _isStepByPC;
}

void Game::setGameState(GAME_STATE state) {
	_gameState = state;
}

GAME_STATE Game::getGameState() {
	return _gameState;
}