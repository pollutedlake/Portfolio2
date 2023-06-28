#include "Stdafx.h"
#include "ScenarioScene.h"

HRESULT ScenarioScene::init(void)
{
	_background = new GImage;
	_background->init("Resources/Images/BackGround/Scenario_BG.bmp", WINSIZE_X, WINSIZE_Y);
	return S_OK;
}

void ScenarioScene::update(void)
{
}

void ScenarioScene::release(void)
{
	SAFE_DELETE(_background);
}

void ScenarioScene::render(HDC hdc)
{
	_background->render(hdc);
}
