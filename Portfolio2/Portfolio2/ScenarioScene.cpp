#include "Stdafx.h"
#include "ScenarioScene.h"

HRESULT ScenarioScene::init(void)
{
	_background = IMAGEMANAGER->findImage("ScenarioBG");
	_senarios = IMAGEMANAGER->findImage("Scenarios");
	_senariosY = 0;
	cout << (-5) % 3 << endl;
	return S_OK;
}

void ScenarioScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_senariosY--;
		cout << _senarios->getFrameHeight()<<endl;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_senariosY++;
	}
}

void ScenarioScene::release(void)
{

}

void ScenarioScene::render()
{
	_background->render(getMemDC());
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			_senarios->frameRender(getMemDC(), WINSIZE_X / 2 - _senarios->getFrameWidth() / 2 + 280 * (i - 1), 150 + 100 * j + _senariosY, i, j);
		}
	}
}
