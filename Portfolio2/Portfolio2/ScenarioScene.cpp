#include "Stdafx.h"
#include "ScenarioScene.h"

HRESULT ScenarioScene::init(void)
{
	_background = IMAGEMANAGER->findImage("ScenarioBG");
	_senarios = IMAGEMANAGER->findImage("Scenarios");
	_scrollUp = IMAGEMANAGER->findImage("ScrollUp");
	_scrollDown = IMAGEMANAGER->findImage("ScrollDown");
	_senariosY = 0;
	return S_OK;
}

void ScenarioScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if(_senariosY < _senarios->getHeight() - 450)
		{
			_senariosY++;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if(_senariosY > 0)
		{
			_senariosY--;
		}
	}
}

void ScenarioScene::release(void)
{

}

void ScenarioScene::render()
{
	_background->render(getMemDC());
	_senarios->render(getMemDC(), WINSIZE_X / 2 - _senarios->getWidth() / 4, 200, _senarios->getWidth() / 2, _senariosY, _senarios->getWidth() / 2, 450);
	_scrollUp->render(getMemDC(), WINSIZE_X - 100, WINSIZE_Y / 2);
	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			_senarios->frameRender(getMemDC(), WINSIZE_X / 2 - _senarios->getFrameWidth() / 2 + 280 * (i - 1), 150 + _senarios->getFrameHeight() * j + _senariosY, i, j);
		}
	}*/
}
