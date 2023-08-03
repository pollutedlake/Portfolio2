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

	Character* _nakama = new PlayerSoldier();
	_nakama->init();
	_nakama->setDir(UP);
	_nakama->setTilePos({ 24, 45 });
	_nakama->setTurnOder(2);
	_tileInfo[_nakama->getTilePos().y][_nakama->getTilePos().x] = SALADIN;

	Character * _nakama2 = new PlayerSoldier();
	_nakama2->init();
	_nakama2->setDir(DOWN);
	_nakama2->setTilePos({ 20, 35 });
	_nakama2->setTurnOder(3);
	_tileInfo[_nakama2->getTilePos().y][_nakama2->getTilePos().x] = SALADIN;

	Character* _nakama3 = new PlayerSoldier();
	_nakama3->init();
	_nakama3->setDir(LEFT);
	_nakama3->setTilePos({ 43, 52 });
	_nakama3->setTurnOder(4);
	_tileInfo[_nakama3->getTilePos().y][_nakama3->getTilePos().x] = SALADIN;

	Character* _nakama4 = new PlayerSoldier();
	_nakama4->init();
	_nakama4->setDir(RIGHT);
	_nakama4->setTilePos({ 15, 40 });
	_nakama4->setTurnOder(5);
	_tileInfo[_nakama4->getTilePos().y][_nakama4->getTilePos().x] = SALADIN;

	Character* _nakama5 = new PlayerSoldier();
	_nakama5->init();
	_nakama5->setDir(DOWN);
	_nakama5->setTilePos({ 24, 36 });
	_nakama5->setTurnOder(23);
	_tileInfo[_nakama5->getTilePos().y][_nakama5->getTilePos().x] = SALADIN;

	Character* _nakama6 = new PlayerSoldier();
	_nakama6->init();
	_nakama6->setDir(DOWN);
	_nakama6->setTilePos({ 24, 38 });
	_nakama6->setTurnOder(24);
	_tileInfo[_nakama6->getTilePos().y][_nakama6->getTilePos().x] = SALADIN;

	Character* _nakama7 = new PlayerSoldier();
	_nakama7->init();
	_nakama7->setDir(LEFT);
	_nakama7->setTilePos({ 32, 50 });
	_nakama7->setTurnOder(25);
	_tileInfo[_nakama7->getTilePos().y][_nakama7->getTilePos().x] = SALADIN;

	Character* _nakama8 = new PlayerSoldier();
	_nakama8->init();
	_nakama8->setDir(UP);
	_nakama8->setTilePos({ 15, 53 });
	_nakama8->setTurnOder(26);
	_tileInfo[_nakama8->getTilePos().y][_nakama8->getTilePos().x] = SALADIN;
	
	_vermont = new Vermont();
	_vermont->init();
	_vermont->setDir(RIGHT);
	_vermont->setTilePos({24, 40});
	_vermont->setTurnOder(1);
	_tileInfo[_vermont->getTilePos().y][_vermont->getTilePos().x] = ENEMY;

	Character* _enemySoldier = new Soldier();
	((Soldier*)(_enemySoldier))->init(EnemyType::SOLDIER4);
	_enemySoldier->setDir(UP);
	_enemySoldier->setTilePos({ 32, 42 });
	_enemySoldier->setTurnOder(6);
	_tileInfo[_enemySoldier->getTilePos().y][_enemySoldier->getTilePos().x] = ENEMY;

	Character* _enemySoldier2 = new Soldier();
	((Soldier*)(_enemySoldier2))->init(EnemyType::SOLDIER4);
	_enemySoldier2->setDir(UP);
	_enemySoldier2->setTilePos({ 32, 43 });
	_enemySoldier2->setTurnOder(7);
	_tileInfo[_enemySoldier2->getTilePos().y][_enemySoldier2->getTilePos().x] = ENEMY;

	Character* _vermont5 = new Soldier();
	((Soldier*)(_vermont5))->init(EnemyType::SOLDIER4);
	_vermont5->setDir(UP);
	_vermont5->setTilePos({ 32, 45 });
	_vermont5->setTurnOder(9);
	_tileInfo[_vermont5->getTilePos().y][_vermont5->getTilePos().x] = ENEMY;

	Character* _vermont4 = new Soldier();
	((Soldier*)(_vermont4))->init(EnemyType::SOLDIER4);
	_vermont4->setDir(UP);
	_vermont4->setTilePos({ 32, 44 });
	_vermont4->setTurnOder(8);
	_tileInfo[_vermont4->getTilePos().y][_vermont4->getTilePos().x] = ENEMY;

	Character* _vermont6 = new Soldier();
	((Soldier*)(_vermont6))->init(EnemyType::SOLDIER4);
	_vermont6->setDir(DOWN);
	_vermont6->setTilePos({ 31, 46 });
	_vermont6->setTurnOder(8);
	_tileInfo[_vermont6->getTilePos().y][_vermont6->getTilePos().x] = ENEMY;

	Character* _vermont7 = new Soldier();
	((Soldier*)(_vermont7))->init(EnemyType::SOLDIER4);
	_vermont7->setDir(RIGHT);
	_vermont7->setTilePos({ 30, 47 });
	_vermont7->setTurnOder(10);
	_tileInfo[_vermont7->getTilePos().y][_vermont7->getTilePos().x] = ENEMY;

	Character* _vermont8 = new Soldier();
	((Soldier*)(_vermont8))->init(EnemyType::SOLDIER4);
	_vermont8->setDir(RIGHT);
	_vermont8->setTilePos({ 31, 40 });
	_vermont8->setTurnOder(11);
	_tileInfo[_vermont8->getTilePos().y][_vermont8->getTilePos().x] = ENEMY;

	Character* _vermont9 = new Soldier();
	((Soldier*)(_vermont9))->init(EnemyType::SOLDIER4);
	_vermont9->setDir(RIGHT);
	_vermont9->setTilePos({ 30, 41 });
	_vermont9->setTurnOder(12);
	_tileInfo[_vermont9->getTilePos().y][_vermont9->getTilePos().x] = ENEMY;

	Character* _vermont10 = new Soldier();
	((Soldier*)(_vermont10))->init(EnemyType::SOLDIER4);
	_vermont10->setDir(RIGHT);
	_vermont10->setTilePos({ 30, 42 });
	_vermont10->setTurnOder(13);
	_tileInfo[_vermont10->getTilePos().y][_vermont10->getTilePos().x] = ENEMY;

	Character* _vermont11 = new Soldier();
	((Soldier*)(_vermont11))->init(EnemyType::SOLDIER4);
	_vermont11->setDir(DOWN);
	_vermont11->setTilePos({ 37, 42 });
	_vermont11->setTurnOder(14);
	_tileInfo[_vermont11->getTilePos().y][_vermont11->getTilePos().x] = ENEMY;

	Character* _vermont12 = new Soldier();
	((Soldier*)(_vermont12))->init(EnemyType::SOLDIER4);
	_vermont12->setDir(LEFT);
	_vermont12->setTilePos({ 34, 39 });
	_vermont12->setTurnOder(15);
	_tileInfo[_vermont12->getTilePos().y][_vermont12->getTilePos().x] = ENEMY;

	Character* _vermont13 = new Soldier();
	((Soldier*)(_vermont13))->init(EnemyType::SOLDIER4);
	_vermont13->setDir(DOWN);
	_vermont13->setTilePos({ 34, 38 });
	_vermont13->setTurnOder(16);
	_tileInfo[_vermont13->getTilePos().y][_vermont13->getTilePos().x] = ENEMY;

	Character* _vermont14 = new Soldier();
	((Soldier*)(_vermont14))->init(EnemyType::SOLDIER4);
	_vermont14->setDir(DOWN);
	_vermont14->setTilePos({ 33, 38 });
	_vermont14->setTurnOder(17);
	_tileInfo[_vermont14->getTilePos().y][_vermont14->getTilePos().x] = ENEMY;

	Character* _vermont15 = new Soldier();
	((Soldier*)(_vermont15))->init(EnemyType::SOLDIER4);
	_vermont15->setDir(DOWN);
	_vermont15->setTilePos({ 32, 38 });
	_vermont15->setTurnOder(18);
	_tileInfo[_vermont15->getTilePos().y][_vermont15->getTilePos().x] = ENEMY;

	Character* _vermont16 = new Soldier();
	((Soldier*)(_vermont16))->init(EnemyType::SOLDIER4);
	_vermont16->setDir(DOWN);
	_vermont16->setTilePos({ 32, 37 });
	_vermont16->setTurnOder(19);
	_tileInfo[_vermont16->getTilePos().y][_vermont16->getTilePos().x] = ENEMY;

	Character* _vermont17 = new Soldier();
	((Soldier*)(_vermont17))->init(EnemyType::SOLDIER4);
	_vermont17->setDir(DOWN);
	_vermont17->setTilePos({ 32, 36 });
	_vermont17->setTurnOder(20);
	_tileInfo[_vermont17->getTilePos().y][_vermont17->getTilePos().x] = ENEMY;

	Character* _vermont18 = new Soldier();
	((Soldier*)(_vermont18))->init(EnemyType::SOLDIER4);
	_vermont18->setDir(DOWN);
	_vermont18->setTilePos({ 33, 36 });
	_vermont18->setTurnOder(21);
	_tileInfo[_vermont18->getTilePos().y][_vermont18->getTilePos().x] = ENEMY;

	Character* _vermont19 = new Soldier();
	((Soldier*)(_vermont19))->init(EnemyType::SOLDIER4);
	_vermont19->setDir(DOWN);
	_vermont19->setTilePos({ 32, 34 });
	_vermont19->setTurnOder(22);
	_tileInfo[_vermont19->getTilePos().y][_vermont19->getTilePos().x] = ENEMY;

	Character* _vermont20 = new Soldier();
	((Soldier*)(_vermont20))->init(EnemyType::SOLDIER4);
	_vermont20->setDir(LEFT);
	_vermont20->setTilePos({ 37, 43 });
	_vermont20->setTurnOder(22);
	_tileInfo[_vermont20->getTilePos().y][_vermont20->getTilePos().x] = ENEMY;

	Character* _vermont21 = new Soldier();
	((Soldier*)(_vermont21))->init(EnemyType::SOLDIER4);
	_vermont21->setDir(LEFT);
	_vermont21->setTilePos({ 37, 41 });
	_vermont21->setTurnOder(22);
	_tileInfo[_vermont21->getTilePos().y][_vermont21->getTilePos().x] = ENEMY;

	_turnSystem = new TurnSystem();
	_turnSystem->addCharacter(_saladin);
	_turnSystem->addCharacter(_vermont);
	_turnSystem->addCharacter(_nakama);
	_turnSystem->addCharacter(_nakama2);
	_turnSystem->addCharacter(_nakama3);
	_turnSystem->addCharacter(_nakama4);
	_turnSystem->addCharacter(_nakama5);
	_turnSystem->addCharacter(_nakama6);
	_turnSystem->addCharacter(_nakama7);
	_turnSystem->addCharacter(_nakama8);
	_turnSystem->addCharacter(_enemySoldier);
	_turnSystem->addCharacter(_enemySoldier2);
	_turnSystem->addCharacter(_vermont4);
	_turnSystem->addCharacter(_vermont5);
	_turnSystem->addCharacter(_vermont6);
	_turnSystem->addCharacter(_vermont7);
	_turnSystem->addCharacter(_vermont8);
	_turnSystem->addCharacter(_vermont9);
	_turnSystem->addCharacter(_vermont10);
	_turnSystem->addCharacter(_vermont11);
	_turnSystem->addCharacter(_vermont12);
	_turnSystem->addCharacter(_vermont13);
	_turnSystem->addCharacter(_vermont14);
	_turnSystem->addCharacter(_vermont15);
	_turnSystem->addCharacter(_vermont16);
	_turnSystem->addCharacter(_vermont17);
	_turnSystem->addCharacter(_vermont18);
	_turnSystem->addCharacter(_vermont19);
	_turnSystem->addCharacter(_vermont20);
	_turnSystem->addCharacter(_vermont21);
	_turnSystem->addObject(_vermont);
	_turnSystem->addObject(_enemySoldier);
	_turnSystem->addObject(_enemySoldier2);
	_turnSystem->addObject(_vermont4);
	_turnSystem->addObject(_vermont5);
	_turnSystem->addObject(_vermont6);
	_turnSystem->addObject(_vermont7);
	_turnSystem->addObject(_vermont8);
	_turnSystem->addObject(_vermont9);
	_turnSystem->addObject(_vermont10);
	_turnSystem->addObject(_vermont11);
	_turnSystem->addObject(_vermont12);
	_turnSystem->addObject(_vermont13);
	_turnSystem->addObject(_vermont14);
	_turnSystem->addObject(_vermont15);
	_turnSystem->addObject(_vermont16);
	_turnSystem->addObject(_vermont17);
	_turnSystem->addObject(_vermont18);
	_turnSystem->addObject(_vermont19);
	_turnSystem->addObject(_vermont20);
	_turnSystem->addObject(_vermont21);
	_turnSystem->addObject(_saladin);
	_turnSystem->addObject(_nakama);
	_turnSystem->addObject(_nakama2);
	_turnSystem->addObject(_nakama3);
	_turnSystem->addObject(_nakama4);
	_turnSystem->addObject(_nakama5);
	_turnSystem->addObject(_nakama6);
	_turnSystem->addObject(_nakama7);
	_turnSystem->addObject(_nakama8);
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
	SOUNDMANAGER->update();
	_cameraPos = _camera->getPosition();
	_frame++;
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_debug = !_debug;
	}

	if (_fade.none() && (_vermont->isSkill() || _saladin->isSkill()))
	{
		_fade.set(0);
		_fadeStartFrame = _frame;
	}
	else if (_fade.test(0))
	{
		if ((_frame - _fadeStartFrame) * 10 > 230)
		{
			_fade = _fade << 1;
		}
	}
	else if (_fade.test(1) && (!_vermont->isSkill() && !_saladin->isSkill()))
	{
		_fade = _fade << 1;
	}
	else if (_fade.test(2))
	{
		if ((_frame - _fadeStartFrame) * 10 > 230)
		{
			_fade.reset();
		}
	}

	if (_saladin->isSkill() || _vermont->isSkill())
	{
		_camera->setPosition({(LONG)(_turnSystem->getCurChar()->getX()), (LONG)(_turnSystem->getCurChar()->getY())});
		Saladin* saladin = (Saladin*)_saladin;
		if (saladin->isCameraShake())
		{
			_camera->setPosition({ _camera->getPosition().x - RND->getInt(20), _camera->getPosition().y - RND->getInt(20) });
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
		SCENEMANAGER->loadingScene();
	}
}

void BossBattleScene::render(void)
{
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
		IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), (_frame - _fadeStartFrame) * 10 > 230 ? 230 : (_frame - _fadeStartFrame) * 10);
	}
	if (_fade.test(1))
	{
		IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), 230);
	}
	if (_fade.test(2))
	{
		IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), 230 - (_frame - _fadeStartFrame) * 10 < 0 ? 0 : 230 - (_frame - _fadeStartFrame) * 10);
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
