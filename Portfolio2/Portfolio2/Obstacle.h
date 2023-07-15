#pragma once
#include "Object.h"
class Obstacle : public Object
{
private:
	string _key;
	POINT _position;
	int _magnificationX;
	int _magnificationY;

public:
	void render(HDC hdc);

	Obstacle(string key, POINT position, int magnificationX, int magnificationY) : _key(key), _position(position), 
	_magnificationX(magnificationX), _magnificationY(magnificationY) { _type = 2; }
	~Obstacle() {};
};

