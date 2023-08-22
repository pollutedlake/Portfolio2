#pragma once
#include "GameNode.h"

class Camera : public GameNode
{
private:
	POINT _position;	// 위치
	RECT _limitRC;		// 움직일 수 있는 RC
	int _speed;			// 움직이는 스피드

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPosition() {return _position;}

	void setPosition(POINT position);
	void setLimitRight(int limitRight) {_limitRC.right = limitRight;}
	void setLimitBottom(int limitBottom) {_limitRC.bottom = limitBottom;}
	
	// 월드 좌표계에서 카메라 좌표계로 변환
	POINT worldToCamera(POINT point);

	Camera() {}
	~Camera() {}
};

