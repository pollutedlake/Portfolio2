#include "Stdafx.h"
#include "MainGame.h"
#include "TitleScene.h"
#include "ScenarioScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);
	IMAGEMANAGER->init();
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Scenario", new ScenarioScene);
	SCENEMANAGER->changeScene("Scenario");
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

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();

	this->getBackBuffer()->render(getHDC(), 0, 0);
}