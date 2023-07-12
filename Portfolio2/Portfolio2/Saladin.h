#pragma once
#include "Character.h"

class Saladin : public Character
{
//private:
//	bitset<3> _state;
//	POINT _tilePos;
//	int _frame;
//	vector<POINT> _route;
//	bitset<4> _dir;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position);

	//void setState(int state);
	//void setDir(int dir);
	//void setTilePos(POINT tilePos) {_tilePos = tilePos;}
	//void setRoute(vector<POINT> route) { _route = route; }
	/*void move();

	POINT getTilePos() {return _tilePos;}*/

	Saladin() {}
	~Saladin() {}
};

