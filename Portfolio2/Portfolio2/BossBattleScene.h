#pragma once
#include "GameNode.h"
#include "Camera.h"

class BossBattleScene : public GameNode
{
private:
	GImage* _backGroundImg;
	GImage* _tableImg;
	Camera* _camera;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossBattleScene() {}
	~BossBattleScene() {}
};

