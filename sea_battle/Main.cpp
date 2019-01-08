#include <iostream>
#include "Game.h";
#include "Player.h";

using namespace std;


int main() {
	srand(time(NULL));

	Player * p1 = new Player();
	Player * p2 = new Player();
	Game game(p1, p2);

	game.start();

	system("pause");
	return 0;
}