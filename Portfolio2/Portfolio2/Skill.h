#pragma once
#include "Character.h"


class Skill
{
private:
	int _frame;
	bool _isFinish;
	vector<Character*> _charList;
	bitset<3> _order;

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight);
	void release(void);
	int getOrder();

	bool isFinish() {return _isFinish;}
	void start(vector<Character*> charList);
};

