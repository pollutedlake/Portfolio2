#include "Stdafx.h"
#include "BattleScene.h"

HRESULT BattleScene::init(void)
{
	BattleData* battleData = DATAMANAGER->findBattleData("형제", 0);
	wsprintf(_bgImg, "BattleSceneBG%d", battleData->_bgImgN);
	wsprintf(_checkBGImg, "검사용BattleSceneBG%d", battleData->_bgImgN);
	_camera = new Camera();
	_camera->init();
	_camera->setPosition({ IMAGEMANAGER->findImage(_bgImg)->getWidth() / 2, IMAGEMANAGER->findImage(_bgImg)->getHeight() / 2 });
	_camera->setLimitRight(IMAGEMANAGER->findImage(_bgImg)->getWidth() - WINSIZE_X / 2);
	_camera->setLimitBottom(IMAGEMANAGER->findImage(_bgImg)->getHeight() - WINSIZE_Y / 2);

	_turnSystem = new TurnSystem2();
	vector<CharacterData*> party = DATAMANAGER->getPartyData();
	for (auto it = party.begin(); it != party.end(); ++it)
	{
		if (!strcmp((*it)->_name.c_str(), "살라딘"))
		{
			Saladin* _saladin = new Saladin;
			_saladin->init();
			_turnSystem->addCharacter(_saladin, UP, { 13, 57 }, 0);
		}
	}
	for (auto it = battleData->_enemy.begin(); it != battleData->_enemy.end(); ++it)
	{
		Soldier* soldier = new Soldier;
		soldier->init(EnemyType(it->_type));
		_turnSystem->addCharacter(soldier, it->_dir, it->_tilePos, it->_turnOrder + 1);
		//soldier->setState(1);
	}
	_turnSystem->addObject(new Obstacle("Object1", {0, 1408}, 1, 1, {2, 53}));
	_turnSystem->addObject(new Obstacle("Object2", {720, 1408}, 1, 1, { 26, 52 }));
	_turnSystem->addObject(new Obstacle("Object3", {80, 632}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object4", {640, 632}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object5", {0, 1064}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object6", {640, 1064}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object7", {160, 1064}, 1, 1, { 10, 38 }));
	_turnSystem->addObject(new Obstacle("Object8", {320, 1465}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object9", {300, 1464}, 1, 1, { 9, 53 }));
	_turnSystem->init(_camera, IMAGEMANAGER->findImage(_checkBGImg)->getMemDC(), IMAGEMANAGER->findImage(_bgImg)->getHeight() / TILEHEIGHT, IMAGEMANAGER->findImage(_bgImg)->getWidth() / TILEWIDTH);

	_showMiniStatusFrame = 0;
	return S_OK;
}

void BattleScene::update(void)
{
	if (_frame == 0)
	{
		SOUNDMANAGER->playSoundFMOD("BattleSceneBG");
	}
	_frame++;
	_camera->update();
	_cameraPos = _camera->getPosition();

	//마우스커서가 위치한 타일 구하기
	_cursorTile.x = (_cameraPos.x - WINSIZE_X / 2 + _ptMouse.x) / TILEWIDTH;
	_cursorTile.y = (_cameraPos.y - WINSIZE_Y / 2 + _ptMouse.y) / TILEHEIGHT;
	_cursorTileLT = { _cursorTile.x * TILEWIDTH, _cursorTile.y * TILEHEIGHT };

	if (_turnSystem->checkTile(_cursorTile) < 2)
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

	_turnSystem->update(_cursorTile);

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_debug = !_debug;
	}
}

void BattleScene::release(void)
{
	_camera->release();
	SAFE_DELETE(_camera);
}

void BattleScene::render(void)
{
	IMAGEMANAGER->findImage(_bgImg)->render(getMemDC(), _camera->worldToCamera({ 0, 0 }).x, _camera->worldToCamera({ 0, 0 }).y);
	IMAGEMANAGER->findImage("CursorTile")->alphaFrameRender(getMemDC(), _camera->worldToCamera(_cursorTileLT).x, _camera->worldToCamera(_cursorTileLT).y, TILEWIDTH, TILEHEIGHT, (_frame / 5) % IMAGEMANAGER->findImage("CursorTile")->getMaxFrameX(), 0, 200);
	if (GetPixel(IMAGEMANAGER->findImage(_checkBGImg)->getMemDC(), _cursorTileLT.x + TILEWIDTH / 2, _cursorTileLT.y + TILEHEIGHT / 2) == RGB(255, 0, 255))
	{
		IMAGEMANAGER->findImage("CantMoveTile")->alphaFrameRender(getMemDC(), _camera->worldToCamera(_cursorTileLT).x, _camera->worldToCamera(_cursorTileLT).y,	
			TILEWIDTH, TILEHEIGHT, (_frame / 10) % (IMAGEMANAGER->findImage("CantMoveTile")->getMaxFrameX() + 1), 0, 200);
	}
	_turnSystem->render(getMemDC());
	// 적을 가리키고 있을 때
	if (_turnSystem->checkTile(_cursorTile) == ENEMY)
	{
		// 적 미니 스테이터스
		if (!_turnSystem->getCurChar()->isDoing())
		{
			POINT pt = { (_cursorTile.x) * TILEWIDTH, (_cursorTile.y - 2) * TILEHEIGHT + TILEHEIGHT / 2 };
			wsprintf(_text, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurHP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxHP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y, "가을체", 7, 500, _text, strlen(_text), RGB(255, 255, 255));
			IMAGEMANAGER->findImage("EnemyMiniStatus")->frameRender(getMemDC(), _camera->worldToCamera(pt).x, _camera->worldToCamera(pt).y, (_frame - _showMiniStatusFrame) / 5, 0);
			IMAGEMANAGER->findImage("HpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 7, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurHP() / _turnSystem->findCharacter(_cursorTile)->getMaxHP(), IMAGEMANAGER->findImage("HpBar")->getHeight() / 4,
				0, 0, IMAGEMANAGER->findImage("HpBar")->getWidth(), IMAGEMANAGER->findImage("HpBar")->getHeight());
			IMAGEMANAGER->findImage("MpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 18, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurMP() / _turnSystem->findCharacter(_cursorTile)->getMaxMP(), 4,
				0, 0, IMAGEMANAGER->findImage("MpBar")->getWidth(), IMAGEMANAGER->findImage("MpBar")->getHeight());
			wsprintf(_text, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurMP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxMP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y + 12, "가을체", 7, 500, _text, strlen(_text), RGB(255, 255, 255));
		}
		// 적 커서
		IMAGEMANAGER->findImage("AttackMouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	}
	else if(_turnSystem->checkTile(_cursorTile) == PLAYER)
	{
		// 플레이어 미니 스테이터스
		if (!_turnSystem->getCurChar()->isDoing())
		{
			POINT pt = { (_cursorTile.x) * TILEWIDTH, (_cursorTile.y - 2) * TILEHEIGHT + TILEHEIGHT / 2 };
			wsprintf(_text, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurHP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxHP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y, "가을체", 7, 500, _text, strlen(_text), RGB(255, 255, 255));
			IMAGEMANAGER->findImage("PlayerMiniStatus")->frameRender(getMemDC(), _camera->worldToCamera(pt).x, _camera->worldToCamera(pt).y, (_frame - _showMiniStatusFrame) / 5, 0);
			IMAGEMANAGER->findImage("HpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 7, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurHP() / _turnSystem->findCharacter(_cursorTile)->getMaxHP(), 4,
				0, 0, IMAGEMANAGER->findImage("HpBar")->getWidth(), IMAGEMANAGER->findImage("HpBar")->getHeight());
			IMAGEMANAGER->findImage("MpBar")->render(getMemDC(), _camera->worldToCamera(pt).x + 32, _camera->worldToCamera(pt).y + 18, 27.f * _turnSystem->findCharacter(_cursorTile)->getCurMP() / _turnSystem->findCharacter(_cursorTile)->getMaxMP(), 4,
				0, 0, IMAGEMANAGER->findImage("MpBar")->getWidth(), IMAGEMANAGER->findImage("MpBar")->getHeight());
			wsprintf(_text, "%d/%d", (int)_turnSystem->findCharacter(_cursorTile)->getCurMP(), (int)_turnSystem->findCharacter(_cursorTile)->getMaxMP());
			FONTMANAGER->textOut(getMemDC(), _camera->worldToCamera(pt).x + 36, _camera->worldToCamera(pt).y + 12, "가을체", 7, 500, _text, strlen(_text), RGB(255, 255, 255));
		}
	}
	if(_turnSystem->checkTile(_cursorTile) != ENEMY)
	{
		IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	}
	if (_debug)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hPen);
		for (int i = 0; i < IMAGEMANAGER->findImage(_bgImg)->getHeight() / TILEHEIGHT; i++)
		{
			LineMake(getMemDC(), _camera->worldToCamera({0, TILEHEIGHT * (i + 1) }).x, _camera->worldToCamera({ 0, TILEHEIGHT * (i + 1) }).y, 
				_camera->worldToCamera({ IMAGEMANAGER->findImage(_bgImg)->getWidth(), TILEHEIGHT * (i + 1) }).x, _camera->worldToCamera({ IMAGEMANAGER->findImage(_bgImg)->getWidth(), TILEHEIGHT * (i + 1) }).y);
		}
		for (int i = 0; i < IMAGEMANAGER->findImage(_bgImg)->getWidth() / TILEWIDTH; i++)
		{
			LineMake(getMemDC(), _camera->worldToCamera({ TILEWIDTH * (i + 1), 0 }).x, _camera->worldToCamera({ TILEWIDTH * (i + 1), 0 }).y,
				_camera->worldToCamera({ TILEWIDTH * (i + 1), IMAGEMANAGER->findImage(_bgImg)->getHeight() }).x, _camera->worldToCamera({ TILEWIDTH * (i + 1), IMAGEMANAGER->findImage(_bgImg)->getHeight() }).y);
		}
	}
	// 맵 정보
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
	IMAGEMANAGER->findImage("CurEld")->render(getMemDC(), eldBarX + eld / 10000 * IMAGEMANAGER->findImage("EldBar")->getWidth() - IMAGEMANAGER->findImage("CurEld")->getWidth() / 2,
		eldBarY + IMAGEMANAGER->findImage("EldBar")->getHeight() / 2 - IMAGEMANAGER->findImage("CurEld")->getHeight());
	char mapInfo[50];
	wsprintf(mapInfo, "자비단 돌입");
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 32 - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 / 2, 15, "가을체", 15, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "평 지");
	FONTMANAGER->textOut(getMemDC(), eldBarX + IMAGEMANAGER->findImage("EldBar")->getWidth() / 2 - 22,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight(), "가을체", 15, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%deld", eld);
	FONTMANAGER->textOut(getMemDC(), eldBarX + IMAGEMANAGER->findImage("EldIcon")->getWidth(), eldBarY + IMAGEMANAGER->findImage("EldBar")->getHeight() + 5, "가을체", 15, 0,
		mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _turnSystem->checkTile(_cursorTile) == CANTMOVE ? 1 : 0);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 5 + IMAGEMANAGER->findImage("MapCoordination")->getWidth() / 2 + 5,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight() + 2, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _cursorTile.x);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 5 + IMAGEMANAGER->findImage("MapCoordination")->getWidth() - 15,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight() / 2 - 5, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _cursorTile.y);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 + 2,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - 13, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
}
