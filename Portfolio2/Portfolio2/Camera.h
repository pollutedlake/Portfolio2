#pragma once
#include "GameNode.h"

class Camera : public GameNode
{
private:
	POINT _position;
	RECT _limitRC;
	int _speed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPosition() {return _position;}

	void setPosition(POINT position) {_position = position;}
	void setLimitRight(int limitRight) {_limitRC.right = limitRight;}
	void setLimitBottom(int limitBottom) {_limitRC.bottom = limitBottom;}

	Camera() {}
	~Camera() {}
};

