#pragma once
#include "Character.h"
#include "Obstacle.h"
#include "Camera.h"

#define PLAYER 0
#define ENEMY 1
#define CANTMOVE 2
#define MOVABLE 3
//enum TileInfo
//{
//	PLAYER,
//	ENEMY,
//	CANTMOVE,
//	MOVABLE
//};

class TurnSystem2
{
private:
	vector<POINT> _movableTiles;
	vector<POINT> _attackableTiles;
	vector<Object*> _objectList;
	vector<Character*> _charList;
	Character* _curChar;
	Camera* _camera;
	HDC _tileCheckDC;
	int _frame;

	int _rowN;
	int _colN;

	bitset<4> _actionChoice;

public:
	HRESULT init(Camera* camera, HDC hdc, int rowN, int colN);
	void release(void);
	void update(POINT cursorTile);
	void render(HDC hdc);

	void addCharacter(Character* character, int dir, POINT tilePos, int turnOrder);
	void addObject(Object* object);
	int checkTile(POINT tilePos);
	void searchMovableTiles();
	bool checkAllDoingNot();

	TurnSystem2() {}
	~TurnSystem2() {}
};

