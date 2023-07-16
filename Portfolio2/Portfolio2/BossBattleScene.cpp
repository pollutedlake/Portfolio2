#include "Stdafx.h"
#include "BossBattleScene.h"

HRESULT BossBattleScene::init(void)
{
	_backGroundImg = IMAGEMANAGER->findImage("BossBattleBG");
	_tableImg = IMAGEMANAGER->findImage("Table");
	_mouseCursorImg = IMAGEMANAGER->findImage("MouseCursor");
	_camera = new Camera();
	_camera->init();
	_camera->setPosition({(LONG)(_backGroundImg->getWidth() * 1.5 / 2), (LONG)(_backGroundImg->getHeight() * 1.5 / 2)});
	_camera->setLimitRight(_backGroundImg->getWidth() * 1.5 - WINSIZE_X / 2);
	_camera->setLimitBottom(_backGroundImg->getHeight() * 1.5 - WINSIZE_Y / 2);

	_saladin = new Saladin();
	_saladin->init();
	_saladin->setDir(LEFT);
	_saladin->setTilePos({33, 40});
	_saladin->setTurnOder(0);
	_tileInfo[_saladin->getTilePos().y][_saladin->getTilePos().x] = SALADIN;

	_vermont = new Vermont();
	_vermont->init();
	_vermont->setDir(RIGHT);
	_vermont->setTilePos({24, 40});
	_vermont->setTurnOder(1);
	_tileInfo[_vermont->getTilePos().y][_vermont->getTilePos().x] = ENEMY;

	_turnSystem = new TurnSystem();
	_turnSystem->addCharacter(_vermont);
	_turnSystem->addCharacter(_saladin);
	_turnSystem->addObject(_vermont);
	_turnSystem->addObject(_saladin);
	_turnSystem->addObject(new Obstacle("Table", {1110, 1180}, 1, 1.5, {29, 40}));
	_turnSystem->init();

	_frame = 0;
	_debug = false;

	return S_OK;
}

void BossBattleScene::release(void)
{
	_camera->release();
	_saladin->release();
	_turnSystem->release();
	SAFE_DELETE(_camera);
	SAFE_DELETE(_saladin);
	SAFE_DELETE(_turnSystem);
}

void BossBattleScene::update(void)
{
	if (_frame == 0)
	{
		SOUNDMANAGER->playSoundFMOD("BossBattle");
	}
	_camera->update();
	_cameraPos = _camera->getPosition();
	_frame++;
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_debug = !_debug;
	}

	// 마우스커서가 위치한 타일 구하기
	_cursorTile.x = (_cameraPos.x - WINSIZE_X / 2 + _ptMouse.x) / TileWidth;
	_cursorTile.y = (_cameraPos.y - WINSIZE_Y / 2 + _ptMouse.y) / TileHeight;
	_turnSystem->update(_tileInfo, TileRowN, TileColN, _cursorTile);
	
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SOUNDMANAGER->stopAllSoundFMOD();
		SCENEMANAGER->changeScene("Ending");
	}
}

void BossBattleScene::render(void)
{
	//IMAGEMANAGER->findImage("SkillCasting")->frameRender(getMemDC(), 0, 0, (_frame / 2 % IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX() + 1), 0);
	//IMAGEMANAGER->findImage("SkillCasting")->alphaFrameRenderEFX(getMemDC(), 200, 0, _frame / 2 % (IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX() + 1), 0, 255);
	_backGroundImg->render(getMemDC(), WINSIZE_X / 2 - _cameraPos.x, WINSIZE_Y / 2 - _cameraPos.y, _backGroundImg->getWidth() * 1.5, _backGroundImg->getHeight() * 1.5, 0, 0, _backGroundImg->getWidth(), _backGroundImg->getHeight());
	IMAGEMANAGER->findImage("CursorTile")->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - _cursorTile.x * TileWidth),
		WINSIZE_Y / 2 - (_cameraPos.y - _cursorTile.y * TileHeight), TileWidth, TileHeight, (_frame / 5) % IMAGEMANAGER->findImage("CursorTile")->getMaxFrameX(), 0, 200);
	if (_tileInfo[_cursorTile.y][_cursorTile.x] == CANTMOVE)
	{
		IMAGEMANAGER->findImage("CantMoveTile")->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - _cursorTile.x * TileWidth),
			WINSIZE_Y / 2 - (_cameraPos.y - _cursorTile.y * TileHeight), TileWidth, TileHeight, (_frame / 10) % (IMAGEMANAGER->findImage("CantMoveTile")->getMaxFrameX() + 1), 0, 200);
	}
	_turnSystem->render(getMemDC(), TileHeight, TileWidth, _cameraPos);
	//_tableImg->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 1110), WINSIZE_Y / 2 - (_cameraPos.y - 1180), _tableImg->getWidth(), _tableImg->getHeight() * 1.5, 0, 0, _tableImg->getWidth(), _tableImg->getHeight());
	if (_tileInfo[_cursorTile.y][_cursorTile.x] == ENEMY)
	{
		IMAGEMANAGER->findImage("AttackMouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	}
	else
	{
		_mouseCursorImg->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	}
	if (_debug)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hPen);
		for (int i = 0; i < TileRowN; i++)
		{
			LineMake(getMemDC(), WINSIZE_X / 2 - _cameraPos.x, WINSIZE_Y / 2 - (_cameraPos.y - TileHeight * (i + 1)), WINSIZE_X / 2 - (_cameraPos.x - 2400), WINSIZE_Y / 2 - (_cameraPos.y - TileHeight * (i + 1)));
		}
		for (int i = 0; i < TileColN; i++)
		{
			LineMake(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - TileWidth * (i + 1)), WINSIZE_Y / 2 - _cameraPos.y, WINSIZE_X / 2 - (_cameraPos.x - TileWidth * (i + 1)), WINSIZE_Y / 2 - (_cameraPos.y - 2700));
		}
		SelectObject(getMemDC(), hOldPen);
		DeleteObject(hPen);
		RECT saladinRect;
		saladinRect.left = WINSIZE_X / 2 - (_cameraPos.x - _saladin->getTilePos().x * TileWidth);
		saladinRect.right = WINSIZE_X / 2 - (_cameraPos.x - (_saladin->getTilePos().x + 1) * TileWidth);
		saladinRect.top = WINSIZE_Y / 2 - (_cameraPos.y - _saladin->getTilePos().y * TileHeight);
		saladinRect.bottom = WINSIZE_Y / 2 - (_cameraPos.y - (_saladin->getTilePos().y + 1) * TileHeight);
		for (int i = 0; i < TileRowN; i++)
		{
			for (int j = 0; j < TileColN; j++)
			{
				RECT rt;
				rt.left = WINSIZE_X / 2 - (_cameraPos.x - j * TileWidth);
				rt.right = WINSIZE_X / 2 - (_cameraPos.x - (j + 1) * TileWidth);
				rt.top = WINSIZE_Y / 2 - (_cameraPos.y - i * TileHeight);
				rt.bottom = WINSIZE_Y / 2 - (_cameraPos.y - (i + 1) * TileHeight);
				if(_tileInfo[i][j] == 0)
				{
					FillRect(getMemDC(), &rt, HBRUSH(RGB(0, 255, 0)));
				}
			}
		}
		FillRect(getMemDC(), &saladinRect, HBRUSH(RGB(255, 0, 0)));
	}
	IMAGEMANAGER->findImage("TextBox")->alphaRender(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 10, 10, 
		IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7, IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7, 
		0, 0, IMAGEMANAGER->findImage("TextBox")->getWidth(), IMAGEMANAGER->findImage("TextBox")->getHeight(), 200);
	IMAGEMANAGER->findImage("MapCoordination")->render(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 5,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight());
	int eldBarX = WINSIZE_X - (IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getWidth() - 5 + IMAGEMANAGER->findImage("EldBar")->getWidth()) / 2 - 10;
	int eldBarY = 5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - (IMAGEMANAGER->findImage("MapCoordination")->getHeight() + IMAGEMANAGER->findImage("EldBar")->getHeight()) / 2;
	IMAGEMANAGER->findImage("EldBar")->render(getMemDC(), eldBarX, eldBarY);
	IMAGEMANAGER->findImage("EldIcon")->render(getMemDC(), eldBarX, eldBarY + IMAGEMANAGER->findImage("EldBar")->getHeight());
	int eld = 0;
	IMAGEMANAGER->findImage("CurEld")->render(getMemDC(), eldBarX + eld/10000 * IMAGEMANAGER->findImage("EldBar")->getWidth() - IMAGEMANAGER->findImage("CurEld")->getWidth() / 2,
		eldBarY + IMAGEMANAGER->findImage("EldBar")->getHeight() / 2 - IMAGEMANAGER->findImage("CurEld")->getHeight());
	char mapInfo[50];
	wsprintf(mapInfo, "형제여!");
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 32 - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 / 2, 15, "가을체", 15, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "평 지");
	FONTMANAGER->textOut(getMemDC(), eldBarX + IMAGEMANAGER->findImage("EldBar")->getWidth() / 2 - 22,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight(), "가을체", 15, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%deld", eld);
	FONTMANAGER->textOut(getMemDC(), eldBarX + IMAGEMANAGER->findImage("EldIcon")->getWidth(), eldBarY + IMAGEMANAGER->findImage("EldBar")->getHeight() + 5, "가을체", 15, 0,
		mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _tileInfo[_cursorTile.y][_cursorTile.x] == CANTMOVE ? 1 : 0);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 5 + IMAGEMANAGER->findImage("MapCoordination")->getWidth() / 2 + 5,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight() + 2, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _cursorTile.x);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 5 + IMAGEMANAGER->findImage("MapCoordination")->getWidth() - 15,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight() / 2 - 5, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _cursorTile.y);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 + 2,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - 13, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
}
