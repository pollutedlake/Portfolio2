#pragma once
#include "Character.h"
class Enemy : public Character
{
	
public:
	POINT findPlayer(int tileInfo[][60], int rowN, int colN);

	Enemy() {}
	~Enemy() {}
};

