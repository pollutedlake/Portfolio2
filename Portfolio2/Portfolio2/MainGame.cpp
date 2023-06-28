#include "Stdafx.h"
#include "MainGame.h"
#include "TitleScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	IMAGEMANAGER->init();
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->changeScene("Title");
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render(memDC);

	this->getDoubleBuffer()->render(hdc, 0, 0);
}