#include "Stdafx.h"
#include "ScenarioScene.h"

HRESULT ScenarioScene::init(void)
{
	_background = IMAGEMANAGER->findImage("ScenarioBG");
	_senarios = IMAGEMANAGER->findImage("Scenarios");
	_scrollUp = IMAGEMANAGER->findImage("ScrollUp");
	_scrollDown = IMAGEMANAGER->findImage("ScrollDown");
	_scrollUpRC = { WINSIZE_X - 60, WINSIZE_Y / 2 - 148, (LONG)(WINSIZE_X - 60 + _scrollUp->getWidth() * 1.4), (LONG)(WINSIZE_Y / 2 - 148 + _scrollUp->getHeight() * 1.4) };
	_scrollDownRC = { WINSIZE_X - 60, WINSIZE_Y / 2 + 213, (LONG)(WINSIZE_X - 60 + _scrollDown->getWidth() * 1.4), (LONG)(WINSIZE_Y / 2 + 213 + _scrollDown->getHeight() * 1.4) };
	_senariosY = 0;
	return S_OK;
}

void ScenarioScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_scrollUpRC, _ptMouse))
		{
			if (_senariosY < _senarios->getHeight() - 450)
			{
				_senariosY += 5;
			}
		}
		else if (PtInRect(&_scrollDownRC, _ptMouse))
		{
			if (_senariosY > 0)
			{
				_senariosY -= 5;
			}
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
	_scrollUp->render(getMemDC(), _scrollUpRC.left, _scrollUpRC.top, _scrollUp->getWidth() * 1.4, _scrollUp->getHeight() * 1.4, 0, 0, _scrollUp->getWidth(), _scrollUp->getHeight());
	_scrollDown->render(getMemDC(), _scrollDownRC.left, _scrollDownRC.top, _scrollDown->getWidth() * 1.4, _scrollDown->getHeight() * 1.4, 0, 0, _scrollDown->getWidth(), _scrollDown->getHeight());
	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			_senarios->frameRender(getMemDC(), WINSIZE_X / 2 - _senarios->getFrameWidth() / 2 + 280 * (i - 1), 150 + _senarios->getFrameHeight() * j + _senariosY, i, j);
		}
	}*/
}
