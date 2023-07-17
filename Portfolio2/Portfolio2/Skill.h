#pragma once
#include "Character.h"

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
	bool _isFinish;
	Character* _curChar;
	vector<Character*> _charList;
	bitset<4> _order;
	vector<pair<POINT, POINT>> _efxPos;
	vector<IcePillar> _icePillars;

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight);
	void release(void);
	int getOrder();

	bool isFinish() {return _isFinish;}
	void start(vector<Character*> charList, Character* curChar);
};

