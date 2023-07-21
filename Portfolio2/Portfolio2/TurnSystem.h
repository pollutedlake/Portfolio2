#pragma once
//#include "Character.h"
#include "Enemy.h"
#include "Saladin.h"
#include "Obstacle.h"
#include "AStar.h"
#include "Skill.h"

#define CANTMOVE	0
#define MOVABLE		1
#define SALADIN		2
#define ENEMY		3

#define ACTION		0
#define MOVE		1

class TurnSystem
{
private:
	Character* _curChar;
	Enemy* _enemy;
	Saladin* _player;
	AStar* _aStar;
	vector<Character*> _charList;
	vector<Object*> _objectList;
	bitset<4> _actionChoice;
	bool _skillChoice;
	bool _skillRangeChoice;
	RECT _actionButtons[4];
	RECT _skillButtons[2];
	vector<POINT> _attackTiles;
	vector<POINT> _skillableTiles;
	int _frame;
	bool _isClear;
	bool _isFail;
	Skill* _skill;

public:
	HRESULT init(void);
	void update(int tileInfo[][60], int rowN, int colN, POINT cursorTile);
	void release(void);
	void render(HDC hdc, int tileHeight, int tileWidth, POINT cameraPos);

	Character* getCurChar() {return _curChar;}

	void addCharacter(Character* character);
	void addObject(Object* object);
	void nextTurn();
	void sortObjectList();
	Character* findCharacter(POINT cursorPoint);
	bool checkAllDoingNot();

	TurnSystem() {}
	~TurnSystem() {}

};

