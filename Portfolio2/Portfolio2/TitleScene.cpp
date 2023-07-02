#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{

	_titleBG = IMAGEMANAGER->findImage("TitleBG");
	_titleName = IMAGEMANAGER->findImage("TitleName");
	_titleEFX2 = IMAGEMANAGER->findImage("TitleEFX2");
	_titleEFX1 = IMAGEMANAGER->findImage("TitleEFX1");
	_titleButtons = IMAGEMANAGER->findImage("TitleButtons");
	_frame = 0;
	_deltaTime = 0;
	_activeButton = -1;
	for (int i = 0; i < 4; i++)
	{
		_buttonsRC[i] = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + _titleName->getHeight() / 2 + 50 + _titleButtons->getFrameHeight() * 3 / 2 * (i + 1), _titleButtons->getFrameWidth(), _titleButtons->getFrameHeight() * 3 / 2);
	}
	return S_OK;
}

void TitleScene::update(void)
{
	_deltaTime++;
	_activeButton = -1;
	if(_deltaTime <= 143)
	{
		_titleEFX1->setFrameX(_deltaTime % 13);
		_titleEFX1->setFrameY(_deltaTime / 13);
	}
	else
	{
		if (_deltaTime % 5 == 0)
		{
			_frame++;
		}
	}
	for(int i = 0; i < 4; i++)
	{
		if (PtInRect(&_buttonsRC[i], _ptMouse))
		{
			_activeButton = i;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		switch(_activeButton)
		{
		case 0:
			SCENEMANAGER->changeScene("Scenario");
			break;
		case 3:
			PostQuitMessage(0);
			break;
		}
	}
}

void TitleScene::render(void)
{
	_titleBG->render(getMemDC());
	if(_deltaTime <= 143)
	{
		_titleEFX1->frameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX1->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX1->getFrameHeight() / 2);
	}
	else
	{
		_titleEFX2->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX2->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX2->getFrameHeight() / 2, _frame % 6, (_frame / 6) % 6, 128);
		_titleName->render(getMemDC(), WINSIZE_X / 2 - _titleName->getWidth() / 2, WINSIZE_Y / 2 - _titleName->getHeight() / 2, _titleName->getWidth(), _titleName->getHeight(), 0, 0, _titleName->getWidth(), _titleName->getHeight());
		for(int i = 0; i < 4; i++)
		{
			if (_activeButton == i)
			{
				_titleButtons->frameRender(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, _titleButtons->getFrameWidth(), _titleButtons->getFrameHeight(), 0, i);
			}
			else
			{
				_titleButtons->frameRender(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, _titleButtons->getFrameWidth(), _titleButtons->getFrameHeight(), 1, i);
			}
		}
	}
}

void TitleScene::release(void)
{

}
