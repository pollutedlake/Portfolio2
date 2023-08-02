#pragma once
#include "Enemy.h"

enum class EnemyType
{
	SOLDIER1,
	SOLDIER2,
	SOLDIER3,
	SOLDIER4,
	SOLDIER5,
	SOLDIER6,
	SOLDIER7,
	SOLDIER8,
	SOLDIER9,
	SOLDIER10
};

class Soldier : public Enemy
{
private:
	EnemyType _enemyType;
public:
	HRESULT init(EnemyType enemyType);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos);

	Soldier() {}
	virtual ~Soldier() {}
};

