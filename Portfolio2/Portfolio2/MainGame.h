#pragma once
#include "GameNode.h"
#include "SceneManager.h"

class MainGame : public GameNode
{
private:
	SceneManager* _sceneManager;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};