#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{

	_titleBG = new GImage;
	_startGame = new GImage;
	_loadGame = new GImage;
	_tutorial = new GImage;
	_exit = new GImage;
	_titleBG->init("Resources/Images/BackGround/Title.bmp", WINSIZE_X, WINSIZE_Y);
	_startGame -> init("Resources/Images/BackGround/StartGame.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	_loadGame->init("Resources/Images/BackGround/LoadGame.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(252, 0, 0));
	_tutorial->init("Resources/Images/BackGround/Tutorial.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(252, 0, 0));
	_exit->init("Resources/Images/BackGround/Exit.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(252, 0, 0));
	_startGameRC = RectMake(WINSIZE_X / 2 - 100, WINSIZE_Y / 2 + 100, 200, 30);
	_loadGameRC = RectMake(WINSIZE_X / 2 - 100, WINSIZE_Y / 2 + 150, 200, 30);
	_tutorialRC = RectMake(WINSIZE_X / 2 - 75, WINSIZE_Y / 2 + 200, 150, 30);
	_exitRC = RectMake(WINSIZE_X / 2 - 25, WINSIZE_Y / 2 + 250, 50, 30);
	return S_OK;
}

void TitleScene::update(void)
{
	if (PtInRect(&_startGameRC, _ptMouse))
	{

	}
	else
	{

	}
	if (PtInRect(&_loadGameRC, _ptMouse))
	{

	}
	else
	{

	}
	if (PtInRect(&_tutorialRC, _ptMouse))
	{

	}
	else
	{

	}
	if (PtInRect(&_exitRC, _ptMouse))
	{

	}
	else
	{

	}
}

void TitleScene::render(HDC hdc)
{
	_titleBG->render(hdc);
	_startGame->render(hdc, _startGameRC.left, _startGameRC.top, 200, 30, 0, 0, WINSIZE_X, WINSIZE_Y);
	_loadGame->render(hdc, _loadGameRC.left, _loadGameRC.top, 200, 30, 0, 0, WINSIZE_X, WINSIZE_Y);
	_tutorial->render(hdc, _tutorialRC.left, _tutorialRC.top, 150, 30, 0, 0, WINSIZE_X, WINSIZE_Y);
	_exit->render(hdc, _exitRC.left, _exitRC.top, 50, 30, 0, 0, WINSIZE_X, WINSIZE_Y);
}

void TitleScene::release(void)
{
	SAFE_DELETE(_titleBG);
	SAFE_DELETE(_startGame);
	SAFE_DELETE(_loadGame);
	SAFE_DELETE(_tutorial);
	SAFE_DELETE(_exit);
}
