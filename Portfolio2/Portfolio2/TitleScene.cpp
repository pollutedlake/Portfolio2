#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{

	_titleBG = IMAGEMANAGER->findImage("TitleBG");
	_titleName = IMAGEMANAGER->findImage("TitleName");
	_titleEFX = IMAGEMANAGER->findImage("TitleEFX");
	_frame = 0;
	_deltaTime = 0;
	return S_OK;
}

void TitleScene::update(void)
{
	_deltaTime++;
	if (_deltaTime > 2)
	{
		_frame++;
		_deltaTime = 0;
	}
}

void TitleScene::render(HDC hdc)
{
	_titleBG->render(hdc);
	_titleEFX->alphaFrameRender(hdc, WINSIZE_X / 2 - _titleEFX->getframeWidth() / 2, WINSIZE_Y / 2 - _titleEFX->getframeHeight() / 2, _frame % 6, (_frame / 6) % 6, 128);
	_titleName->render(hdc, WINSIZE_X / 2 - _titleName->getWidth() / 2, WINSIZE_Y / 2 - _titleName->getHeight() / 2, _titleName->getWidth(), _titleName->getHeight(), 0, 0, _titleName->getWidth(), _titleName->getHeight());
}

void TitleScene::release(void)
{
	_titleBG->release();
	SAFE_DELETE(_titleBG);
}
