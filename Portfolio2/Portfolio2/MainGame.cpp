#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	_sceneManager = new SceneManager;
	_sceneManager->init();
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_sceneManager);
}

void MainGame::update(void)
{
	GameNode::update();
	_sceneManager->update();
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_sceneManager->render(memDC);

	this->getDoubleBuffer()->render(hdc, 0, 0);
}