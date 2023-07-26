#pragma once
#include "Character.h"
#include "Enemy.h"
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
struct cmp2 
{
	bool operator()(pair<POINT, int> node1, pair<POINT, int> node2)
	{
		if (node1.second > node2.second)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class TurnSystem2
{
private:
	priority_queue<pair<POINT, int>, vector<pair<POINT, int>>, cmp2> _closedList;
	vector<POINT> _route;

	vector<POINT> _movableTiles;
	vector<POINT> _attackableTiles;

	vector<Object*> _objectList;
	vector<Character*> _charList;

	Character* _curChar;
	Enemy* _enemy;
	Camera* _camera;
	HDC _tileCheckDC;
	int _frame;

	int _rowN;
	int _colN;

	RECT _actionButtons[4];
	bitset<4> _actionChoice;

public:
	HRESULT init(Camera* camera, HDC hdc, int rowN, int colN);
	void release(void);
	void update(POINT cursorTile);
	void render(HDC hdc);

	void addCharacter(Character* character, int dir, POINT tilePos, int turnOrder);
	void addObject(Object* object);
	void sortObjectList();
	int checkTile(POINT tilePos);
	void searchMovableTiles();
	bool checkAllDoingNot();
	POINT findPlayer();
	void nextTurn();

	vector<POINT> astar(POINT start, POINT dest); 
	int heuristic(POINT node, POINT dest);
	int distance(POINT start, POINT node);

	TurnSystem2() {}
	~TurnSystem2() {}
};

