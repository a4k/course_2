#include "Board.h"



Board::Board()
{
	makeDefaultSettings();
	setHeader();
	setBody();

	create();
	createShips();
}


Board::~Board()
{
}

void Board::makeDefaultSettings() {

	createShipType(4, 1);
	createShipType(3, 2);
	createShipType(2, 3);
	createShipType(1, 4);
}

MESSAGE Board::listenAttack(int x, int y) {
	Cell* itemCell = findCell(x, y);

	if (itemCell) {
		if (itemCell->isStateEmpty()) {
			itemCell->setStateHit();
			return MESSAGE_ATTACK_BAD;
		} else if(itemCell->isStateShip()) {
			itemCell->setStateYesHit();
			Ship * ship = getShipByCell(x, y);
			if(ship->isSunken()) {
				makeHitAroundShip(ship);
				return MESSAGE_ATTACK_SUNKEN;
			}
			return MESSAGE_ATTACK_GOOD;
		}
		else {
			return ERROR_REPEAT_VALUE;
		}
	}

	return MESSAGE_ATTACK_BAD;
}

void Board::createShipType(int size, int col) {
	ShipType * shipType = new ShipType();
	shipType->col = col;
	shipType->size = size;
	shipTypes.push_back(shipType);
}

void Board::create() {
	for (int i = 0; i < BOARD_SIZE_Y; i++) {
		cells.push_back(vector<Cell*>());

		for (int j = 0; j < BOARD_SIZE_X; j++) {
			Cell * cell = new Cell();
			cell->setX(j);
			cell->setY(i);

			cells[cells.size() - 1].push_back(cell);
		}
	}
}

void Board::createShips() {
	for (int i = 0; i < shipTypes.size(); i++) {
		for (int j = 0; j < shipTypes[i]->col; j++) {
			createShip(shipTypes[i]->size);
		}
	}
	cout << "" << endl;
}

void Board::createShip(int size) {
	bool isSetup = false;
	while (!isSetup) {
		Ship * ship = new Ship();
	
		int x = rand() % BOARD_SIZE_X;
		int y = rand() % BOARD_SIZE_Y;
		bool isHoriz = (rand() % 2 == 0);

		int x2 = x;
		int y2 = y;

		bool rightCoord = true;
		if (x + size > BOARD_SIZE_X && isHoriz) rightCoord = false;
		if (y + size > BOARD_SIZE_Y && !isHoriz) rightCoord = false;
		if(isHoriz) ship->setHoriz();

		if (rightCoord) {
			for (int i = 0; i < size; i++) {
				if (isHoriz) x2 = x + i;
				else y2 = y + i;

				if (!isRightCoordinates(x2, y2)) {
					rightCoord = false;
					break;
				}
				else {
					addShipCoordinate(ship, x2, y2);
				}
			}
		}

		if (rightCoord) {
			
			vector<Cell*> shipCoordinates = ship->getCoordinates();
			int shipSize = shipCoordinates.size();
			Cell * itemCell = new Cell();
			if (shipSize > -1) {
				for (int i = 0; i < shipSize; i++) {
					itemCell = shipCoordinates[i];
					itemCell->setStateShip();
				}
				ships.push_back(ship);
				isSetup = true;
			}
		}
	}
}

void Board::addShipCoordinate(Ship * ship, int x, int y) {
	Cell * itemCell = new Cell();

	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++) {
			itemCell = cells[i][j];
			if (itemCell->getX() == x && itemCell->getY() == y) {
				ship->addCoordinate(itemCell);
				return;
			}
		}
	}

}

Ship * Board::getShipByCell(int x, int y) {
	Ship * ship = new Ship();
	bool isFound = false;
	for(int i = 0; i < ships.size(); i++) {
		Cell * cell = new Cell();
		vector<Cell*> coordinates = ships[i]->getCoordinates();
		for(int j = 0; j < coordinates.size(); j++) {
			if(coordinates[j]->getX() == x && coordinates[j]->getY() == y) {
				ship = ships[i];
				isFound = true;
				break;
			}
		}
		if(isFound) break;
	}
	return ship;
}

void Board::makeHitAroundShip(Ship * ship) {

	vector<Cell*> coordinates = ship->getCoordinates();
	bool isHoriz = ship->isHoriz();
	Cell * itemCell = NULL;

	for(int j = 0; j < coordinates.size(); j++) {
		int currentX = coordinates[j]->getX();
		int currentY = coordinates[j]->getY();
		bool isFirstCoordinate = (j == 0);
		bool isLastCoordinate = (j == coordinates.size() - 1);

		int preCoordinateX = currentX - 1;
		int postCoordinateX = currentX + 1;

		int preCoordinateY = currentY - 1;
		int postCoordinateY = currentY  + 1;


		if(isHoriz) {
			if(isFirstCoordinate) {
				itemCell = findCell(preCoordinateX, preCoordinateY);
				if(itemCell) itemCell->setStateHit();

				itemCell = findCell(preCoordinateX, currentY);
				if(itemCell) itemCell->setStateHit();
				
				itemCell = findCell(preCoordinateX, postCoordinateY);
				if(itemCell) itemCell->setStateHit();
			}
			if(isLastCoordinate) {
				itemCell = findCell(postCoordinateX, preCoordinateY);
				if(itemCell) itemCell->setStateHit();

				itemCell = findCell(postCoordinateX, currentY);
				if(itemCell) itemCell->setStateHit();
				
				itemCell = findCell(postCoordinateX, postCoordinateY);
				if(itemCell) itemCell->setStateHit();
			}

			itemCell = findCell(currentX, preCoordinateY);
			if(itemCell) itemCell->setStateHit();

			itemCell = findCell(currentX, postCoordinateY);
			if(itemCell) itemCell->setStateHit();

		}
		else {
			if(isFirstCoordinate) {
				itemCell = findCell(preCoordinateX, preCoordinateY);
				if(itemCell) itemCell->setStateHit();

				itemCell = findCell(currentX, preCoordinateY);
				if(itemCell) itemCell->setStateHit();
				
				itemCell = findCell(postCoordinateX, preCoordinateY);
				if(itemCell) itemCell->setStateHit();
			}
			if(isLastCoordinate) {
				itemCell = findCell(preCoordinateX, postCoordinateY);
				if(itemCell) itemCell->setStateHit();

				itemCell = findCell(currentX, postCoordinateY);
				if(itemCell) itemCell->setStateHit();
				
				itemCell = findCell(postCoordinateX, postCoordinateY);
				if(itemCell) itemCell->setStateHit();
			}

			itemCell = findCell(preCoordinateX, currentY);
			if(itemCell) itemCell->setStateHit();

			itemCell = findCell(postCoordinateX, currentY);
			if(itemCell) itemCell->setStateHit();
		}
	}
	return;
}

int Board::countHit() {
	int count = 0;
	for(int i = 0; i < ships.size(); i++) {
		if(ships[i]->isSunken()) count++;
	}
	return count;
}

Cell * Board::findCell(int x, int y) {
	Cell * itemCell = NULL;
	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++) {
			itemCell = cells[i][j];
			if (itemCell->getX() == x && itemCell->getY() == y) {
				return itemCell;
			}
		}
	}
	return itemCell;
}

bool Board::isRightCoordinates(int x, int y) {
	Cell * itemCell = new Cell();

	if (x >= BOARD_SIZE_X || x < 0) return false;
	if (y >= BOARD_SIZE_Y || y < 0) return false;

	for (int iy = 0; iy < cells.size(); iy++) {
		for (int ix = 0; ix < cells[iy].size(); ix++) {
			itemCell = cells[iy][ix];
			int currentX = itemCell->getX();
			int currentY = itemCell->getY();
			bool isEmpty = (itemCell->isStateEmpty());

			// check
			if ((currentY == y) ||
				(currentY == y - 1 && y != 0) ||
				(currentY == y + 1 && y != BOARD_SIZE_Y)
				) {
				if (currentX == x + 1 && x != BOARD_SIZE_X) {
					if (!isEmpty) return false;
				}
				else if (currentX == x - 1 && x != 0) {
					if (!isEmpty) return false;
				}
				else if (currentX == x) {
					if (!isEmpty) return false;
				}
			}
		}
	}

	return true;
}

void Board::setHeader() {
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

void Board::setBody() {
	for (int i = 1; i <= BOARD_SIZE_Y; i++) {
		body.insert(i);
	}
}

void Board::printHeader() {

	auto myItem = header.begin();
	cout << setw(3) << " ";
	while (myItem != header.end()) {
		string title = *myItem;
		cout << setw(3) << title;
		myItem++;
	}

	cout << endl;
}

void Board::print() {
	printHeader();
	auto myBody = body.begin();
	Cell * itemCell = new Cell();

	for (int iy = 0; iy < cells.size(); iy++) {
		int title = *myBody;
		cout << setw(3) << title;
		
		for (int ix = 0; ix < cells[iy].size(); ix++) {
			itemCell = cells[iy][ix];
			cout << setw(3);

			if (itemCell->isStateEmpty()) cout << "-";
			if (itemCell->isStateShip()) cout << "O";
			if (itemCell->isStateHit()) cout << "+";
			if (itemCell->isStateYesHit()) cout << "X";
			if (itemCell->isStateSunken()) cout << "X";
		}
		myBody++;
		cout << endl;
	}

}

void Board::printEnemy() {
	printHeader();
	auto myBody = body.begin();
	Cell * itemCell = new Cell();

	for (int iy = 0; iy < cells.size(); iy++) {
		int title = *myBody;
		cout << setw(3) << title;

		for (int ix = 0; ix < cells[iy].size(); ix++) {
			itemCell = cells[iy][ix];
			cout << setw(3);
			if (itemCell->isStateEmpty()) cout << "-";
			if (itemCell->isStateShip()) cout << "-";
			if (itemCell->isStateHit()) cout << "+";
			if (itemCell->isStateYesHit()) cout << "X";
			if (itemCell->isStateSunken()) cout << "O";
		}
		myBody++;
		cout << endl;
	}

}