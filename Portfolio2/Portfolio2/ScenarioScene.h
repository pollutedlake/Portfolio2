#pragma once
#include "GameNode.h"
class ScenarioScene : public GameNode
{
private:
	GImage* _background;
	GImage* _senarios;
	int _senariosY;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	ScenarioScene() {}
	~ScenarioScene() {}
};

