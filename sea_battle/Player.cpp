#include "Player.h"


Player::~Player()
{
}

void Player::setEnemy(Player * enemy) {
	Enemy = enemy;
}

int Player::getPoints() {
	return _points;
}

void Player::setPoints(int count) {
	_points = count;
}

void Player::makeDefaultSettings() {
	_board = new Board();
	setHeader();
	setPoints(0);
}

MESSAGE Player::waitForCommand() {
	string x;
	string y;

	string input;
	bool isTrueCommand = false;

	while (!isTrueCommand) {
		cout << "Input coordinates (A1): ";

		if (cin >> input && input.size() >= 2) {
			x = toupper(input[0]);
			y = input[1];
			if(input.size() == 3) y = y + input[2];

			MESSAGE msg = attack(x, y);
			if (msg == ERROR_REPEAT_VALUE) {
				cout << "repeat attack on this cell" << endl;
			}
			else if(msg == MESSAGE_ATTACK_GOOD) isTrueCommand = true;
			else if(msg == MESSAGE_ATTACK_SUNKEN) isTrueCommand = true;
			else if(msg == MESSAGE_GAME_END) return MESSAGE_GAME_END;
			else return MESSAGE_GAME_CONTINUE;

		}
	}
}

MESSAGE Player::waitForCPU() {
	bool isTrueCommand = false;

	while (!isTrueCommand) {
		MESSAGE msg = attackAI();
		if (msg == ERROR_REPEAT_VALUE) {
			cout << "repeat attack on this cell" << endl;
		}
		else if(msg == MESSAGE_ATTACK_GOOD) isTrueCommand = true;
		else if(msg == MESSAGE_ATTACK_SUNKEN) isTrueCommand = true;
		else if(msg == MESSAGE_GAME_END) return MESSAGE_GAME_END;
		else return MESSAGE_GAME_CONTINUE;

	}
}

MESSAGE Player::attack(string x, string y) {
	int resultX = translateX(x);
	int resultY = translateY(y);
	return makeAttack(resultX, resultY);
}

MESSAGE Player::makeAttack(int x, int y) {
	MESSAGE msg = Enemy->listenAttack(x, y);
	Cell * itemCell = Enemy->_board->findCell(x, y);
	pushToHistory(itemCell);

	setPoints(Enemy->countBoardHit());

	if(getPoints() == POINTS_TO_END) {
		return MESSAGE_GAME_END;
	}

	return msg;
}

MESSAGE Player::listenAttack(int x, int y) {
	return _board->listenAttack(x, y);
}

MESSAGE Player::attackAI() {
	
	int x = 0;
	int y = 0;

	bool isAttack = false;
	bool isAttackFromChannel = false;
	MESSAGE msg = MESSAGE_ATTACK_BAD;

	while (!isAttack) {
		x = rand() % BOARD_SIZE_X;
		y = rand() % BOARD_SIZE_Y;
		isAttackFromChannel = false;

		if(!isEmptyChannel()) {
			int index = 0;
			Cell * itemCell = channel[index];
			x = itemCell->getX();
			y = itemCell->getY();
			channel.erase(channel.begin());
			isAttackFromChannel = true;
		}

		if (!isHistory(x, y)) {
			msg = makeAttack(x, y);
			isAttack = true;
		}
	}

	if(msg == MESSAGE_ATTACK_GOOD) {
		// save in next steps for cpu
		Cell * itemCell = NULL;
		bool isHoriz = false;

		if(isAttackFromChannel) {
			itemCell = history[history.size() - 1];
			if(itemCell->getY() == y) isHoriz = true;


			for(int i = 0; i < channel.size(); i++) {
				if(isHoriz) {
					if(channel[i]->getY() != y) channel.erase(channel.begin() + i);
				}
				else {
					if(channel[i]->getX() != x) channel.erase(channel.begin() + i);
				}
			}

			if(isHoriz) {
				if(!isHistory(x - 1, y)) {
					itemCell = Enemy->_board->findCell(x - 1, y);
					if(itemCell) pushToChannel(itemCell);
				}
				if(!isHistory(x + 1, y)) {
					itemCell = Enemy->_board->findCell(x + 1, y);
					if(itemCell) pushToChannel(itemCell);
				}
			}
			else {
				if(!isHistory(x, y - 1)) {
					itemCell = Enemy->_board->findCell(x, y - 1);
					if(itemCell) pushToChannel(itemCell);
				}
				if(!isHistory(x, y + 1)) {
					itemCell = Enemy->_board->findCell(x, y + 1);
					if(itemCell) pushToChannel(itemCell);
				}
			}
		}
		else {
			// left side
			itemCell = Enemy->_board->findCell(x - 1, y);
			if(itemCell) pushToChannel(itemCell);

			// middle side
			itemCell = Enemy->_board->findCell(x, y - 1);
			if(itemCell) pushToChannel(itemCell);
			itemCell = Enemy->_board->findCell(x, y + 1);
			if(itemCell) pushToChannel(itemCell);

			// right side
			itemCell = Enemy->_board->findCell(x + 1, y);
			if(itemCell) pushToChannel(itemCell);
		}



	}
	else if(msg == MESSAGE_ATTACK_SUNKEN) channel.clear();

	return msg;
}

bool Player::isHistory(int x, int y) {
	for(int i = 0; i < history.size(); i++) {
		Cell * itemCell = history[i];
		if(itemCell->getX() == x && itemCell->getY() == y) return true;
	}
	return false;
}

void Player::pushToHistory(Cell * cell) {
	history.push_back(cell);
}

bool Player::isEmptyChannel() {
	return channel.empty();
}

void Player::pushToChannel(Cell * cell) {
	channel.push_back(cell);
}

void Player::getBoard() {
	_board->print();
}

void Player::getBoardHidden() {
	_board->printEnemy();
}

void Player::getBoardEnemy() {
	Enemy->getBoardHidden();
}

int Player::countBoardHit() {
	return _board->countHit();
}


void Player::setHeader() {
	header.insert("A");
	header.insert("B");
	header.insert("C");
	header.insert("D");

	header.insert("E");
	header.insert("F");
	header.insert("G");
	header.insert("H");

	header.insert("I");
	header.insert("J");
}

int Player::translateX(string x) {
	int index = 0;

	auto myItem = header.begin();
	while (myItem != header.end()) {
		string title = *myItem;
		if (title == x) return index;
		index++;
		myItem++;
	}

	return index;
}

int Player::translateY(string y) {
	return stoi(y) - 1;
}