#pragma once
#include "GameNode.h"
#include "Camera.h"

class WorldMapScene	: public GameNode
{
private:
	bitset<4> _state;
	int _frame;
	Camera* _camera;
	POINT _cameraPos;
	RECT _buttonsRC[5];
	RECT _nextMoveRC;
	char* _buttonStr[5];

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	WorldMapScene() {}
	~WorldMapScene() {}
};

