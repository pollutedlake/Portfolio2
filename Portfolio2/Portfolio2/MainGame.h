// FMOD »ç¿ë
#pragma once
#include "GameNode.h"
#include "Resources.h"

class MainGame : public GameNode
{
private:
	Resources* _resources;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	MainGame() {}
	~MainGame() {}
};