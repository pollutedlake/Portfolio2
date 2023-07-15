#pragma once
#include "Character.h"

class Saladin : public Character
{
private:
	vector<POINT> _movableTiles;
	vector<POINT> _attackableTiles;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position);

	void searchMovable(int map[][60], int rowN, int colN);

	vector<POINT> getMovableTiles() {return _movableTiles;}
	vector<POINT> getAttackableTiles() {return _attackableTiles;}

	Saladin() {}
	virtual ~Saladin() {}
};

