#include "Stdafx.h"
#include "WorldMapScene.h"

HRESULT WorldMapScene::init(void)
{
	_frame = 0;
	_camera = new Camera();
	_camera->init();
	_camera->setPosition({(LONG)(IMAGEMANAGER->findImage("WorldMap")->getWidth() / 2), (LONG)(IMAGEMANAGER->findImage("WorldMap")->getHeight() / 2)});
	_camera->setLimitRight(IMAGEMANAGER->findImage("WorldMap")->getWidth() - WINSIZE_X / 2);
	_camera->setLimitBottom(IMAGEMANAGER->findImage("WorldMap")->getHeight() - WINSIZE_Y / 2);

	for (int i = 0; i < 4; i++)
	{
		_buttons[i] = RectMakeCenter(WINSIZE_X - IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5 / 2 - 30, 
			20 + IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 / 2 + (IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 + 10) * i,
			IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5);
	}
	_buttons[4] = RectMakeCenter(WINSIZE_X - IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5 / 2 - 30,
		20 + IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 / 2 + (IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 + 10) * 4 + 30,
		IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5);
	_buttonStr[0] = "이 동";
	_buttonStr[1] = "진 입";
	_buttonStr[2] = "상 태";
	_buttonStr[3] = "교 환";
	_buttonStr[4] = "턴종료";
	return S_OK;
}

void WorldMapScene::update(void)
{
	if (_frame == 0 && !SOUNDMANAGER->isPlaying())
	{
		SOUNDMANAGER->playSoundFMOD("WorldMapBG");
	}
	_camera->update();
	_cameraPos = _camera->getPosition();
	_frame++;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_buttons[0], _ptMouse))
		{

		}
		if (PtInRect(&_buttons[1], _ptMouse))
		{
			SOUNDMANAGER->stopAllSoundFMOD();
			SCENEMANAGER->changeScene("Story");
		}
	}
}

void WorldMapScene::render(void)
{
	IMAGEMANAGER->findImage("WorldMap")->render(getMemDC(), WINSIZE_X / 2 - _cameraPos.x, WINSIZE_Y / 2 - _cameraPos.y);
	IMAGEMANAGER->findImage("WorldMapMarker")->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 255), WINSIZE_Y / 2 - (_cameraPos.y - 210), (_frame / 5) % 10, 0, 128);
	IMAGEMANAGER->findImage("SaladinMark")->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 295), WINSIZE_Y / 2 - (_cameraPos.y - 230));
	IMAGEMANAGER->findImage("WorldMapFlag")->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 310), WINSIZE_Y / 2 - (_cameraPos.y - 170));
	IMAGEMANAGER->findImage("WorldMapTeam")->frameRender(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 320 - IMAGEMANAGER->findImage("WorldMapSaladin")->getWidth()), 
		WINSIZE_Y / 2 - (_cameraPos.y - 187), (_frame / 5) % 5, 0);
	IMAGEMANAGER->findImage("WorldMapSaladin")->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 320), WINSIZE_Y / 2 - (_cameraPos.y - 187));
	char str[50];
	wsprintf(str, "1 팀");
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 375), WINSIZE_Y / 2 - (_cameraPos.y - 188), "가을체", 15, 50, str, strlen(str), RGB(255, 255, 255));
	wsprintf(str, "투르 칼리프령");
	IMAGEMANAGER->findImage("WorldMapInfo")->render(getMemDC());
	FONTMANAGER->textOut(getMemDC(), 40, 50, "가을체", 23, 50, str, strlen(str), RGB(255, 255, 255));
	wsprintf(str, "1283년 30일");
	FONTMANAGER->textOut(getMemDC(), 140, 85, "가을체", 15, 50, str, strlen(str), RGB(255, 255, 255));
	for (int i = 0; i < 5; i++)
	{
		if(PtInRect(&_buttons[i], _ptMouse))
		{
			IMAGEMANAGER->findImage("ActionButtonActive")->render(getMemDC(), _buttons[i].left, _buttons[i].top, IMAGEMANAGER->findImage("ActionButtonActive")->getWidth()*1.5, IMAGEMANAGER->findImage("ActionButtonActive")->getHeight()*1.5,
			0, 0, IMAGEMANAGER->findImage("ActionButtonActive")->getWidth(), IMAGEMANAGER->findImage("ActionButtonActive")->getHeight());
		}
		else
		{
			IMAGEMANAGER->findImage("ActionButton")->render(getMemDC(), _buttons[i].left, _buttons[i].top, IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5,
				0, 0, IMAGEMANAGER->findImage("ActionButton")->getWidth(), IMAGEMANAGER->findImage("ActionButton")->getHeight());
		}
		FONTMANAGER->textOut(getMemDC(), (_buttons[i].right + _buttons[i].left) / 2 - 30, (_buttons[i].bottom + _buttons[i].top) / 2 - 25 / 2,
			"가을체", 25, 50, _buttonStr[i], strlen(_buttonStr[i]), RGB(255, 255, 255));
	}

	IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
}

void WorldMapScene::release(void)
{
	_camera->release();
	SAFE_DELETE(_camera);
}
