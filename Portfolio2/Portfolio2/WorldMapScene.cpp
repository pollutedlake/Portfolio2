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
		_buttonsRC[i] = RectMakeCenter(WINSIZE_X - IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5 / 2 - 30,
			20 + IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 / 2 + (IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 + 10) * i,
			IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5);
	}
	_buttonsRC[4] = RectMakeCenter(WINSIZE_X - IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5 / 2 - 30,
		20 + IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 / 2 + (IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5 + 10) * 4 + 30,
		IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5);
	_buttonStr[0] = "이 동";
	_buttonStr[1] = "진 입";
	_buttonStr[2] = "상 태";
	_buttonStr[3] = "교 환";
	_buttonStr[4] = "턴종료";

	_state.reset();
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
	_nextMoveRC = RectMakeCenter(WINSIZE_X / 2 - (_cameraPos.x - 200) + IMAGEMANAGER->findImage("WorldMapMoveMarker")->getFrameWidth() / 4,
		WINSIZE_Y / 2 - (_cameraPos.y - 320) + IMAGEMANAGER->findImage("WorldMapMoveMarker")->getFrameHeight() / 4,
		IMAGEMANAGER->findImage("WorldMapMoveMarker")->getFrameWidth() / 2, IMAGEMANAGER->findImage("WorldMapMoveMarker")->getFrameHeight() / 2);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_buttonsRC[0], _ptMouse))
		{
			_state.set(0);
		}
		if (PtInRect(&_buttonsRC[1], _ptMouse))
		{
			SOUNDMANAGER->stopAllSoundFMOD();
			SCENEMANAGER->changeScene("Shop");
		}
		if (_state.test(0) && PtInRect(&_nextMoveRC, _ptMouse))
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
		if(PtInRect(&_buttonsRC[i], _ptMouse))
		{
			IMAGEMANAGER->findImage("ActionButtonActive")->render(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, IMAGEMANAGER->findImage("ActionButtonActive")->getWidth()*1.5, IMAGEMANAGER->findImage("ActionButtonActive")->getHeight()*1.5,
			0, 0, IMAGEMANAGER->findImage("ActionButtonActive")->getWidth(), IMAGEMANAGER->findImage("ActionButtonActive")->getHeight());
		}
		else
		{
			IMAGEMANAGER->findImage("ActionButton")->render(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, IMAGEMANAGER->findImage("ActionButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("ActionButton")->getHeight() * 1.5,
				0, 0, IMAGEMANAGER->findImage("ActionButton")->getWidth(), IMAGEMANAGER->findImage("ActionButton")->getHeight());
		}
		FONTMANAGER->textOut(getMemDC(), (_buttonsRC[i].right + _buttonsRC[i].left) / 2 - 30, (_buttonsRC[i].bottom + _buttonsRC[i].top) / 2 - 25 / 2,
			"가을체", 25, 50, _buttonStr[i], strlen(_buttonStr[i]), RGB(255, 255, 255));
	}
	if (_state.test(0))
	{
		IMAGEMANAGER->findImage("WorldMapMoveMarker")->frameRender(getMemDC(), _nextMoveRC.left, _nextMoveRC.top, 
			IMAGEMANAGER->findImage("WorldMapMoveMarker")->getFrameWidth() / 2, IMAGEMANAGER->findImage("WorldMapMoveMarker")->getFrameHeight() / 2, _frame % 28, 0);
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(56, 196, 140));
		HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hPen);
		LineMake(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 310), WINSIZE_Y / 2 - (_cameraPos.y - 170) + IMAGEMANAGER->findImage("WorldMapFlag")->getHeight(), 
			(_nextMoveRC.left + _nextMoveRC.right) / 2, (_nextMoveRC.top + _nextMoveRC.bottom) / 2);
		SelectObject(getMemDC(), hOldPen);
		DeleteObject(hPen);
	}

	IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
}

void WorldMapScene::release(void)
{
	_camera->release();
	SAFE_DELETE(_camera);
}
