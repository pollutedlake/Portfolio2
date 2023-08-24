#include "Stdafx.h"
#include "ScenarioScene.h"

HRESULT ScenarioScene::init(void)
{
	_background = IMAGEMANAGER->findImage("ScenarioBG");
	_scenarios = IMAGEMANAGER->findImage("Scenarios");
	_scrollUp = IMAGEMANAGER->findImage("ScrollUp");
	_scrollDown = IMAGEMANAGER->findImage("ScrollDown");
	_scrollClick = IMAGEMANAGER->findImage("ScrollClick");
	_scrollNoClick = IMAGEMANAGER->findImage("ScrollNoClick");
	_mouseCursor = IMAGEMANAGER->findImage("MouseCursor");
	_scrollUpRC = { WINSIZE_X - 60, WINSIZE_Y / 2 - 148, (LONG)(WINSIZE_X - 60 + _scrollUp->getWidth() * 1.4), (LONG)(WINSIZE_Y / 2 - 148 + _scrollUp->getHeight() * 1.4) };
	_scrollDownRC = { WINSIZE_X - 60, WINSIZE_Y / 2 + 213, (LONG)(WINSIZE_X - 60 + _scrollDown->getWidth() * 1.4), (LONG)(WINSIZE_Y / 2 + 213 + _scrollDown->getHeight() * 1.4) };
	_scrollRC = { WINSIZE_X - 58, 250, (LONG)(WINSIZE_X - 58 + _scrollNoClick->getWidth() * 1.4), (LONG)(250 + _scrollNoClick->getHeight() * 1.4) };
	_scrollCenterY = 250.0f + _scrollNoClick->getHeight() * 1.4f / 2.0f;
	for (int i = 0; i < 81; i++)
	{
		_scenariosCenter[i] = { WINSIZE_X / 2 - _scenarios->getWidth() / 6 + _scenarios->getWidth() / 6 * (i % 3), 200 + _scenarios->getHeight() / 54 + _scenarios->getHeight() / 27 * (i / 3) };
	}
	_scenariosY = 0;
	_selectScenario = -1;
	_frame = 0;
	_isScrollClick = false;
	_fadeOut = false;
	return S_OK;
}

void ScenarioScene::update(void)
{
	SOUNDMANAGER->update();
	if (!_fadeOut)
	{
		if (!SOUNDMANAGER->isPlaying())
		{
			SOUNDMANAGER->playSoundFMOD("ScenarioScene");
		}
		_scrollRC = RectMakeCenter(WINSIZE_X - 58 + _scrollDown->getWidth() * 1.4 / 2.0f, _scrollCenterY, _scrollNoClick->getWidth() * 1.4, _scrollNoClick->getHeight() * 1.4);
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (_selectScenario == 75 || _selectScenario == 69)
			{
				if (_selectScenario <= DATAMANAGER->getMaxScenario())
				{
					SOUNDMANAGER->playSoundFMOD("Select");
					SOUNDMANAGER->stopSoundFMOD("ScenarioScene");
					DATAMANAGER->setScenario(_selectScenario);
					DATAMANAGER->setBattleIdx(0);
					DATAMANAGER->setSceneIdx(0);
					_fadeOut = true;
				}
			}
			if (PtInRect(&_scrollUpRC, _ptMouse))
			{
				if (_scenariosY > 0)
				{
					_scenariosY -= 5;
					_scrollCenterY -= 5.0f * 350.0f/(float)(_scenarios->getHeight() - 450);
				}

			}
			else if (PtInRect(&_scrollDownRC, _ptMouse))
			{
				if (_scenariosY < _scenarios->getHeight() - 450)
				{
					_scenariosY += 5;
					_scrollCenterY += 5.0f * 350.0f / (float)(_scenarios->getHeight() - 450);
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_scrollRC, _ptMouse))
			{
				_isScrollClick = true;
				_exPtMouse = _ptMouse;
			}
		}
		if (_isScrollClick)
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				_isScrollClick = false;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				if (_scrollCenterY >= 250.0f + _scrollNoClick->getHeight() * 1.4f / 2.0f && _scrollCenterY <= 600 - _scrollNoClick->getHeight() * 1.4f / 2.0f)
				{
					_scrollCenterY += _ptMouse.y - _exPtMouse.y;
					_scenariosY += ((float)(_scenarios->getHeight() - 450) / 350.0f) * (_ptMouse.y - _exPtMouse.y);
					if (_scenariosY < 0)
					{
						_scenariosY = 0;
					}
					if (_scenariosY > _scenarios->getHeight() - 450)
					{
						_scenariosY = _scenarios->getHeight() - 450;
					}
				}
				if (_scrollCenterY < 250.0f + _scrollNoClick->getHeight() * 1.4f / 2.0f)
				{
					_scrollCenterY = 250.0f + _scrollNoClick->getHeight() * 1.4f / 2.0f;
				}
				if (_scrollCenterY > 600 - _scrollNoClick->getHeight() * 1.4f / 2.0f)
				{
					_scrollCenterY = 600 - _scrollNoClick->getHeight() * 1.4f / 2.0f;
				}
			}
			_exPtMouse = _ptMouse;
		}
		for (int i = 0; i < 3; i++)
		{
			_scenariosCenter[i].y = 200 + _scenarios->getHeight() / 54 - _scenariosY;
		}
		for (int i = 3; i < 81; i++)
		{
			_scenariosCenter[i].y = _scenariosCenter[i - 3].y + _scenarios->getHeight() / 27;
		}
		for (int i = 0; i < 81; i++)
		{
			RECT temp = RectMakeCenter(_scenariosCenter[i].x, _scenariosCenter[i].y, _scenarios->getFrameWidth(), _scenarios->getFrameHeight());
			if (temp.bottom < 200)
			{
				continue;
			}
			else if (temp.top > 650)
			{
				continue;
			}
			else if (temp.top < 200 && temp.bottom > 200)
			{
				temp.top = 200;
			}
			else if (temp.top < 650 && temp.bottom > 650)
			{
				temp.bottom = 650;
			}
			if (PtInRect(&temp, _ptMouse))
			{
				_selectScenario = i;
				break;
			}
			_selectScenario = -1;
		}
	}
	else
	{
		_frame++;
		if (_frame > 50)
		{
			SCENEMANAGER->loadingScene();
		}
	}
}

void ScenarioScene::release(void)
{

}

void ScenarioScene::render()
{
	_background->render(getMemDC());
	_scenarios->render(getMemDC(), WINSIZE_X / 2 - _scenarios->getWidth() / 4, 200, _scenarios->getWidth() / 2, _scenariosY, _scenarios->getWidth() / 2, 450);
	_scrollUp->render(getMemDC(), _scrollUpRC.left, _scrollUpRC.top, _scrollUp->getWidth() * 1.4, _scrollUp->getHeight() * 1.4, 0, 0, _scrollUp->getWidth(), _scrollUp->getHeight());
	_scrollDown->render(getMemDC(), _scrollDownRC.left, _scrollDownRC.top, _scrollDown->getWidth() * 1.4, _scrollDown->getHeight() * 1.4, 0, 0, _scrollDown->getWidth(), _scrollDown->getHeight());
	_scrollNoClick->render(getMemDC(), WINSIZE_X - 58, _scrollCenterY - _scrollNoClick->getHeight() * 1.4 / 2.0f, _scrollNoClick->getWidth() * 1.4, _scrollNoClick->getHeight() * 1.4, 0, 0, _scrollNoClick->getWidth(), _scrollNoClick->getHeight());
	if (_isScrollClick)
	{
		_scrollClick->render(getMemDC(), WINSIZE_X - 58, _scrollCenterY - _scrollNoClick->getHeight() * 1.4 / 2.0f, _scrollClick->getWidth() * 1.4, _scrollClick->getHeight() * 1.4, 0, 0, _scrollClick->getWidth(), _scrollClick->getHeight());
	}
	if (_selectScenario != -1 && _selectScenario <= DATAMANAGER->getMaxScenario())
	{
		RECT temp = RectMakeCenter(_scenariosCenter[_selectScenario].x, _scenariosCenter[_selectScenario].y, _scenarios->getFrameWidth(), _scenarios->getFrameHeight());
		if (temp.top < 200 && temp.bottom > 200)
		{
			temp.top = 200;
		}
		else if (temp.top < 650 && temp.bottom > 650)
		{
			temp.bottom = 650;
		}
		_scenarios->render(getMemDC(), temp.left, temp.top,	_scenarios->getFrameWidth() * (_selectScenario % 3), 
			temp.top == 200 ? _scenarios->getFrameHeight() * (_selectScenario / 3 + 1) - (temp.bottom - temp.top) : _scenarios->getFrameHeight() * (_selectScenario / 3), 
			_scenarios->getFrameWidth(), temp.bottom - temp.top);
	}
	_mouseCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	SCENEMANAGER->fadeOutBlack(0, _frame, 50);
}
