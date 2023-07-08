#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{

	_titleBG = IMAGEMANAGER->findImage("TitleBG");
	_titleName = IMAGEMANAGER->findImage("TitleName");
	_titleEFX2 = IMAGEMANAGER->findImage("TitleEFX2");
	_titleEFX1 = IMAGEMANAGER->findImage("TitleEFX1");
	_titleEFX3 = IMAGEMANAGER->findImage("TitleEFX3");
	_titleEFX4 = IMAGEMANAGER->findImage("TitleEFX4");
	_titleButtons = IMAGEMANAGER->findImage("TitleButtons");
	_cursor = IMAGEMANAGER->findImage("MouseCursor");
	_frame = 0;
	_deltaTime = 0;
	_activeButton = -1;
	_fadeOutStartFrame = 0;
	_fadeOut = false;
	for (int i = 0; i < 4; i++)
	{
		_buttonsRC[i] = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + _titleName->getHeight() / 2 + 50 + _titleButtons->getFrameHeight() * 3 / 2 * (i + 1), _titleButtons->getFrameWidth(), _titleButtons->getFrameHeight() * 3 / 2);
	}
	return S_OK;
}

void TitleScene::update(void)
{
	if (!SOUNDMANAGER->isPlaying() && !_fadeOut)
	{
		SOUNDMANAGER->playSoundFMOD("TitleScene");
	}
	_deltaTime++;
	_activeButton = -1;
	if(_deltaTime <= 286)
	{
		_titleEFX1->setFrameX((_deltaTime / 2) % 13);
		_titleEFX1->setFrameY(_deltaTime / 26);
	}
	else
	{
		if (_deltaTime % 5 == 0)
		{
			_frame++;
		}
	}
	if(!_fadeOut && _frame > 50)
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_buttonsRC[i], _ptMouse))
			{
				_activeButton = i;
				break;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			switch (_activeButton)
			{
			case 0:
				SOUNDMANAGER->stopSoundFMOD("TitleScene");
				SOUNDMANAGER->playSoundFMOD("TitleButton");
				_fadeOut = true;
				_fadeOutStartFrame = _frame;
				break;
			case 3:
				PostQuitMessage(0);
				break;
			}
		}
	}
	if(_fadeOut)
	{
		if (_frame > _fadeOutStartFrame + _titleEFX4->getMaxFrameX())
		{
			SCENEMANAGER->changeScene("Scenario");
		}
	}
}

void TitleScene::render(void)
{
	_titleBG->render(getMemDC());
	if(!_fadeOut)
	{
		if(_deltaTime <= 286)
		{
			_titleEFX1->frameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX1->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX1->getFrameHeight() / 2);
		}
		else
		{
			_titleEFX3->frameRender(getMemDC(), WINSIZE_X / 2 - 10, WINSIZE_Y / 2 - _titleEFX4->getHeight() + 25, _frame % _titleEFX3->getMaxFrameX(), 1);
			_titleEFX2->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX2->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX2->getFrameHeight() / 2, _frame % 6, (_frame / 6) % 6, 128);
			_titleName->alphaRender(getMemDC(), WINSIZE_X / 2 - _titleName->getWidth() / 2, WINSIZE_Y / 2 - _titleName->getHeight() / 2, _titleName->getWidth(), _titleName->getHeight(), 0, 0, _titleName->getWidth(), _titleName->getHeight(), _frame * 40 > 255 ? 255 : _frame * 5);
			if (_frame > 50)
			{
				for (int i = 0; i < 4; i++)
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
				_cursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frame % 7, 1);
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			_titleButtons->alphaFrameRender(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, 0, i, _frame == _fadeOutStartFrame ? 255 : 255 / ((_frame - _fadeOutStartFrame)));
		}
		SCENEMANAGER->fadeOutBlack(_fadeOutStartFrame, _frame, _fadeOutStartFrame + _titleEFX4->getMaxFrameX() / 3);
		_titleEFX4->frameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX4->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX4->getFrameHeight() / 2, _frame -_fadeOutStartFrame, 0);
	}
}

void TitleScene::release(void)
{

}
