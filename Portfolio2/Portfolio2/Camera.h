#pragma once
#include "GameNode.h"

class Camera : public GameNode
{
private:
	POINT _position;	// ��ġ
	RECT _limitRC;		// ������ �� �ִ� RC
	int _speed;			// �����̴� ���ǵ�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPosition() {return _position;}

	//	��ġ ����
	void setPosition(POINT position);
	// ������ ���� ����
	void setLimitRight(int limitRight) {_limitRC.right = limitRight;}
	// ���� ���� ����
	void setLimitBottom(int limitBottom) {_limitRC.bottom = limitBottom;}
	
	// ���� ��ǥ�迡�� ī�޶� ��ǥ��� ��ȯ
	POINT worldToCamera(POINT point);

	Camera() {}
	~Camera() {}
};

