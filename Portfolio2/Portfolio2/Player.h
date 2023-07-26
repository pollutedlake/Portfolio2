#pragma once
#include "Character.h"
class Player : public Character
{
private:
	vector<POINT> _movableTiles;
	vector<POINT> _attackableTiles;
	vector<POINT> _skillableTiles;
	bool _cameraShake;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos);

	Player() {}
	~Player() {}
};

