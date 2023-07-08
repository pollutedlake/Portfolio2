#pragma once
#include "GameNode.h"

class Camera : public GameNode
{
private:
	POINT _position;
	int _speed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPosition() {return _position;}

	void setPosition(POINT position) {_position = position;}

	Camera() {}
	~Camera() {}
};

