#pragma once
#include "Enemy.h"

class Soldier : public Enemy
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos);

	Soldier() {}
	virtual ~Soldier() {}
};

