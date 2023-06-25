#include "Stdafx.h"
#include "MainGame.h"
#include "resource.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	title = new GImage;
	title->init("Resources/Images/Title.bmp", WINSIZE_X, WINSIZE_Y);
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(title);
}

void MainGame::update(void)
{
	GameNode::update();
	
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	title->render(memDC, 0, 0);

	this->getDoubleBuffer()->render(hdc, 0, 0);
}