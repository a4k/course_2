#pragma once


enum GAME_STATE { GAME_END, GAME_CONTINUE };
// ���� ���������, ���� ������������

enum MESSAGE {MESSAGE_ATTACK_BAD, MESSAGE_ATTACK_GOOD, MESSAGE_ATTACK_SUNKEN, MESSAGE_GAME_END, MESSAGE_GAME_CONTINUE, ERROR_REPEAT_VALUE};
// ���� ������, ��������� ��������, 

enum CellState { EMPTY, SHIP, NO_HIT, HIT, YES_HIT, SUNKEN };
// ������, ���� �������, �� ���������, ���������, ����� ���������, ������� �������,

const int BOARD_SIZE_X = 10;
const int BOARD_SIZE_Y = 10;
const int POINTS_TO_END = 10;

class Config
{
public:
	Config();
	~Config();
};

