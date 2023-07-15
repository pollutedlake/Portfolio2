#pragma once
#include "Enemy.h"
class Vermont : public Enemy
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position);

	Vermont() {}
	virtual ~Vermont() {}
};

