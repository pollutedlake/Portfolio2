#pragma once
#include "GameNode.h"
#include "Camera.h"

class WorldMapScene	: public GameNode
{
private:
	int _frame;
	Camera* _camera;
	POINT _cameraPos;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	WorldMapScene() {}
	~WorldMapScene() {}
};

