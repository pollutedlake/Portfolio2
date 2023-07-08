#include "Stdafx.h"
#include "BossBattleScene.h"

HRESULT BossBattleScene::init(void)
{
	_backGroundImg = IMAGEMANAGER->findImage("BossBattleBG");
	_tableImg = IMAGEMANAGER->findImage("Table");
	_camera = new Camera();
	_camera->init();
	return S_OK;
}

void BossBattleScene::release(void)
{
	_camera->release();
	SAFE_DELETE(_camera);
}

void BossBattleScene::update(void)
{
	
}

void BossBattleScene::render(void)
{
	_backGroundImg->render(getMemDC(), (WINSIZE_X - _backGroundImg->getWidth() * 1.5) / 2, (WINSIZE_Y - _backGroundImg->getHeight() * 1.5) / 2, _backGroundImg->getWidth() * 1.5, _backGroundImg->getHeight() * 1.5, 0, 0, _backGroundImg->getWidth(), _backGroundImg->getHeight());
}
