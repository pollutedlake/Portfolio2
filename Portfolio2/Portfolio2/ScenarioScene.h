#pragma once
#include "GameNode.h"
class ScenarioScene : public GameNode
{
private:
	GImage* _background;
	GImage* _titleName;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(HDC hdc);

	ScenarioScene() {}
	~ScenarioScene() {}
};

