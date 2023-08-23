#pragma once
#include "../FrameWork/GameNode/GameNode.h"
class ScenarioScene : public GameNode
{
private:
	GImage* _background;
	GImage* _scenarios;
	GImage* _scrollUp;
	GImage* _scrollDown;
	GImage* _scrollNoClick;
	GImage* _scrollClick;
	GImage* _mouseCursor;

	RECT _scrollUpRC;
	RECT _scrollDownRC;
	RECT _scrollRC;
	POINT _scenariosCenter[81];
	RECT _scenarioRC[81];

	float _scenariosY;
	bool _isScrollClick;
	float _scrollCenterY;
	POINT _exPtMouse;
	int _selectScenario;
	bool _fadeOut;
	int _frame;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	ScenarioScene() {}
	~ScenarioScene() {}
};

