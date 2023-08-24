#pragma once
#include "Object.h"
class Obstacle : public Object
{
private:
	string _key;
	POINT _position;
	float _magnificationX;		// ≥–¿Ã
	float _magnificationY;		// ≥Ù¿Ã

public:
	void render(HDC hdc, POINT cameraPos);

	Obstacle(string key, POINT position, float magnificationX, float magnificationY, POINT tilePos) : _key(key), _position(position), 
	_magnificationX(magnificationX), _magnificationY(magnificationY) { _type = 2; _tilePos = tilePos; }
	~Obstacle() {};
};

