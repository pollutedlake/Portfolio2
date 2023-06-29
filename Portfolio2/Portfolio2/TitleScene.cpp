#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{

	_titleBG = IMAGEMANAGER->findImage("TitleBG");
	_titleName = IMAGEMANAGER->findImage("TitleName");
	_titleEFX2 = IMAGEMANAGER->findImage("TitleEFX2");
	_titleEFX1 = IMAGEMANAGER->findImage("TitleEFX1");
	_frame = 0;
	_deltaTime = 0;
	return S_OK;
}

void TitleScene::update(void)
{
	_deltaTime++;
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
}

void TitleScene::render(HDC hdc)
{
	_titleBG->render(hdc);
	if(_deltaTime <= 143)
	{
		_titleEFX1->frameRender(hdc, WINSIZE_X / 2 - _titleEFX1->getframeWidth() / 2, WINSIZE_Y / 2 - _titleEFX1->getframeHeight() / 2);
	}
	else
	{
		_titleEFX2->alphaFrameRender(hdc, WINSIZE_X / 2 - _titleEFX2->getframeWidth() / 2, WINSIZE_Y / 2 - _titleEFX2->getframeHeight() / 2, _frame % 6, (_frame / 6) % 6, 128);
		_titleName->render(hdc, WINSIZE_X / 2 - _titleName->getWidth() / 2, WINSIZE_Y / 2 - _titleName->getHeight() / 2, _titleName->getWidth(), _titleName->getHeight(), 0, 0, _titleName->getWidth(), _titleName->getHeight());
	}
}

void TitleScene::release(void)
{
	_titleBG->release();
	_titleName->release();
	_titleEFX1->release();
	_titleEFX2->release();
	SAFE_DELETE(_titleBG);
	SAFE_DELETE(_titleName);
	SAFE_DELETE(_titleEFX1);
	SAFE_DELETE(_titleEFX2);
}
