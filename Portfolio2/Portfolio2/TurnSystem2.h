#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include "Camera.h"
#include "Skill.h"

#define PLAYER 0
#define ENEMY 1
#define CANTMOVE 2
#define MOVABLE 3

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
	vector<POINT> _skillableTiles;

	vector<Object*> _objectList;
	vector<Character*> _charList;

	Character* _curChar;
	Enemy* _enemy;
	Camera* _camera;
	Skill* _skill;
	HDC _tileCheckDC;
	int _frame;

	int _rowN;
	int _colN;

	RECT _actionButtons[4];
	RECT _skillButtons[50];
	bitset<4> _actionChoice;
	char* _skillName;

	bool _isClear;
	bool _isFail;
	bool _start;

public:
	HRESULT init(Camera* camera, HDC hdc, int rowN, int colN);
	void release(void);
	void update(POINT cursorTile);
	void render(HDC hdc);

	Character* getCurChar() { return _curChar; }
	Character* findCharacter(POINT cursorPoint);

	void addCharacter(Character* character, int dir, POINT tilePos, int turnOrder);
	Player* deleteCharacter(string name);
	void addObject(Object* object);

	void sortObjectList();
	int checkTile(POINT tilePos);
	void searchMovableTiles();
	void searchSkillableTiles(char skillName[]);
	bool checkAllDoingNot();
	POINT findPlayer();
	void nextTurn();

	void setStart(bool start);

	vector<POINT> astar(POINT start, POINT dest); 
	int heuristic(POINT node, POINT dest);
	int distance(POINT start, POINT node);

	TurnSystem2() {}
	~TurnSystem2() {}
};

