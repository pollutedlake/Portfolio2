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

	Character* _saladin2 = new Saladin();
	_saladin2->init();
	_saladin2->setDir(UP);
	_saladin2->setTilePos({ 24, 45 });
	_saladin2->setTurnOder(2);
	_tileInfo[_saladin2->getTilePos().y][_saladin2->getTilePos().x] = SALADIN;

	Character * _saladin3 = new Saladin();
	_saladin3->init();
	_saladin3->setDir(DOWN);
	_saladin3->setTilePos({ 20, 35 });
	_saladin3->setTurnOder(3);
	_tileInfo[_saladin3->getTilePos().y][_saladin3->getTilePos().x] = SALADIN;

	Character* _saladin4 = new Saladin();
	_saladin4->init();
	_saladin4->setDir(LEFT);
	_saladin4->setTilePos({ 43, 52 });
	_saladin4->setTurnOder(4);
	_tileInfo[_saladin4->getTilePos().y][_saladin4->getTilePos().x] = SALADIN;

	Character* _saladin5 = new Saladin();
	_saladin5->init();
	_saladin5->setDir(RIGHT);
	_saladin5->setTilePos({ 15, 40 });
	_saladin5->setTurnOder(5);
	_tileInfo[_saladin5->getTilePos().y][_saladin5->getTilePos().x] = SALADIN;
	
	_vermont = new Vermont();
	_vermont->init();
	_vermont->setDir(RIGHT);
	_vermont->setTilePos({24, 40});
	_vermont->setTurnOder(1);
	_tileInfo[_vermont->getTilePos().y][_vermont->getTilePos().x] = ENEMY;

	_turnSystem = new TurnSystem();
	_turnSystem->addCharacter(_vermont);
	_turnSystem->addCharacter(_saladin);
	_turnSystem->addCharacter(_saladin2);
	_turnSystem->addCharacter(_saladin3);
	_turnSystem->addCharacter(_saladin4);
	_turnSystem->addCharacter(_saladin5);
	_turnSystem->addObject(_vermont);
	_turnSystem->addObject(_saladin);
	_turnSystem->addObject(_saladin2);
	_turnSystem->addObject(_saladin3);
	_turnSystem->addObject(_saladin4);
	_turnSystem->addObject(_saladin5);
	_turnSystem->addObject(new Obstacle("Table", {1110, 1180}, 1, 1.5, {29, 40}));
	_turnSystem->init();

	_frame = 0;
	_debug = false;
	_fade = false;
	_fadeStartFrame = 0;
	_showMiniStatusFrame = 0;

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

	if (_fade.none() && _vermont->isSkill())
	{
		_fade.set(0);
		_fadeStartFrame = _frame;
	}
	else if (_fade.test(0))
	{
		if ((_frame - _fadeStartFrame) * 10 > 255)
		{
			_fade = _fade << 1;
		}
	}
	else if (_fade.test(1) && !_vermont->isSkill())
	{
		_fade = _fade << 1;
	}
	else if (_fade.test(2))
	{
		if ((_frame - _fadeStartFrame) * 10 > 255)
		{
			_fade.reset();
		}
	}
	

	// 마우스커서가 위치한 타일 구하기
	_cursorTile.x = (_cameraPos.x - WINSIZE_X / 2 + _ptMouse.x) / TileWidth;
	_cursorTile.y = (_cameraPos.y - WINSIZE_Y / 2 + _ptMouse.y) / TileHeight;
	_turnSystem->update(_tileInfo, TileRowN, TileColN, _cursorTile);
	
	if (_tileInfo[_cursorTile.y][_cursorTile.x] == SALADIN || _tileInfo[_cursorTile.y][_cursorTile.x] == ENEMY)
	{
		if (_showMiniStatusFrame == 0)
		{
			_showMiniStatusFrame = _frame;
		}
	}
	else
	{
		_showMiniStatusFrame = 0;
	}

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
	if (_fade.test(0))
	{
		IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), (_frame - _fadeStartFrame) * 10 > 255 ? 255 : (_frame - _fadeStartFrame) * 10);
	}
	if (_fade.test(1))
	{
		//IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), 255);
	}
	if (_fade.test(2))
	{
		IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), 255 - (_frame - _fadeStartFrame) * 10 < 0 ? 0 : 255 - (_frame - _fadeStartFrame) * 10);
	}
	_turnSystem->render(getMemDC(), TileHeight, TileWidth, _cameraPos);
	char str[50];
	if (_tileInfo[_cursorTile.y][_cursorTile.x] == ENEMY)
	{
		if(!_turnSystem->getCurChar()->isDoing())
		{
			POINT pt = { (_cursorTile.x) * TileWidth, (_cursorTile.y - 2) * TileHeight + TileHeight / 2 };
			wsprintf(str, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurHP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxHP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y, "가을체", 7, 500, str, strlen(str), RGB(255, 255, 255));
			IMAGEMANAGER->findImage("EnemyMiniStatus")->frameRender(getMemDC(), _camera->worldToCamera(pt).x, _camera->worldToCamera(pt).y, (_frame - _showMiniStatusFrame) / 5, 0);
			IMAGEMANAGER->findImage("HpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 7, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurHP() / _turnSystem->findCharacter(_cursorTile)->getMaxHP(), IMAGEMANAGER->findImage("HpBar")->getHeight() / 4,
				0, 0, IMAGEMANAGER->findImage("HpBar")->getWidth(), IMAGEMANAGER->findImage("HpBar")->getHeight());
			IMAGEMANAGER->findImage("MpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 18, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurMP() / _turnSystem->findCharacter(_cursorTile)->getMaxMP(), 4,
				0, 0, IMAGEMANAGER->findImage("MpBar")->getWidth(), IMAGEMANAGER->findImage("MpBar")->getHeight());
			wsprintf(str, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurMP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxMP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y + 12, "가을체", 7, 500, str, strlen(str), RGB(255, 255, 255));
		}
		IMAGEMANAGER->findImage("AttackMouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	}
	else if (_tileInfo[_cursorTile.y][_cursorTile.x] == SALADIN)
	{
		if (!_turnSystem->getCurChar()->isDoing())
		{
			POINT pt = { (_cursorTile.x) * TileWidth, (_cursorTile.y - 2) * TileHeight + TileHeight / 2 };
			wsprintf(str, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurHP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxHP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y, "가을체", 7, 500, str, strlen(str), RGB(255, 255, 255));
			IMAGEMANAGER->findImage("PlayerMiniStatus")->frameRender(getMemDC(), _camera->worldToCamera(pt).x, _camera->worldToCamera(pt).y, (_frame - _showMiniStatusFrame) / 5, 0);
			IMAGEMANAGER->findImage("HpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 7, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurHP() / _turnSystem->findCharacter(_cursorTile)->getMaxHP(), 4,
				0, 0, IMAGEMANAGER->findImage("HpBar")->getWidth(), IMAGEMANAGER->findImage("HpBar")->getHeight());
			IMAGEMANAGER->findImage("MpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 18, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurMP() / _turnSystem->findCharacter(_cursorTile)->getMaxMP(), 4,
				0, 0, IMAGEMANAGER->findImage("MpBar")->getWidth(), IMAGEMANAGER->findImage("MpBar")->getHeight());
			wsprintf(str, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurMP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxMP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y + 12, "가을체", 7, 500, str, strlen(str), RGB(255, 255, 255));
		}
	}
	if(_tileInfo[_cursorTile.y][_cursorTile.x] != ENEMY)
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
