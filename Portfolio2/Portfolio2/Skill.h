#pragma once
#include "Character.h"
#include "Saladin.h"

struct IcePillar
{
	int _frame = -1;
	bool _broken = false;
	POINT _position;
};

class Skill
{
private:
	int _frame;
	int _startFrame;
	bool _isFinish;
	Character* _curChar;
	vector<Character*> _charList;
	bitset<4> _order;
	bitset<20> _orderOrder;
	vector<pair<POINT, POINT>> _efxPos;
	vector<pair<pair<float, float>, float>> _dust1Pos;
	vector<pair<pair<float, float>, float>> _dust2;
	vector<IcePillar> _icePillars;
	pair<int, bool> _crackedEarth[4][12];
	POINT _stonePos[4][12][5];
	vector<pair<int, int>> _volcano;
	vector<vector<pair<int, int>>> _bigStones;

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight);
	void release(void);
	int getOrder();

	bool isFinish() {return _isFinish;}
	void start(vector<Character*> charList, Character* curChar);
};

