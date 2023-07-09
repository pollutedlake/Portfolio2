#pragma once
#include "Character.h"

class Saladin : public Character
{
private:
	bitset<4> _state;
	POINT _tilePos;
	int _frame;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position);

	void setState(int state) {_state.reset(); _state.set(state, true);}
	void setTilePos(POINT tilePos) {_tilePos = tilePos;}

	POINT getTilePos() {return _tilePos;}

	Saladin() {}
	~Saladin() {}
};

