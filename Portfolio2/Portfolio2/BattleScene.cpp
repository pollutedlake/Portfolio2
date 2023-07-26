#include "Stdafx.h"
#include "BattleScene.h"

HRESULT BattleScene::init(void)
{
	_camera = new Camera();
	_camera->init();
	_camera->setPosition({ IMAGEMANAGER->findImage("BattleSceneBG")->getWidth() / 2, IMAGEMANAGER->findImage("BattleSceneBG")->getHeight() / 2 });
	_camera->setLimitRight(IMAGEMANAGER->findImage("BattleSceneBG")->getWidth() - WINSIZE_X / 2);
	_camera->setLimitBottom(IMAGEMANAGER->findImage("BattleSceneBG")->getHeight() - WINSIZE_Y / 2);

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
	Soldier* _soldier = new Soldier{};
	_soldier->init(EnemyType::SOLDIER4);
	_turnSystem->addCharacter(_soldier, DOWN, { 8, 45 }, 1);
	Soldier* _soldier2 = new Soldier{};
	_soldier2->init(EnemyType::SOLDIER4);
	_turnSystem->addCharacter(_soldier2, DOWN, { 18, 46 }, 2);
	Soldier* _soldier3 = new Soldier{};
	_soldier3->init(EnemyType::SOLDIER4);
	_turnSystem->addCharacter(_soldier3, DOWN, { 13, 41 }, 3);
	_turnSystem->addObject(new Obstacle("Object1", {0, 1408}, 1, 1, {0, 0}));
	_turnSystem->addObject(new Obstacle("Object2", {720, 1408}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object3", {80, 632}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object4", {640, 632}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object5", {0, 1064}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object6", {640, 1064}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object7", {160, 1064}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object8", {320, 1465}, 1, 1, { 0, 0 }));
	_turnSystem->addObject(new Obstacle("Object9", {300, 1464}, 1, 1, { 0, 0 }));
	_turnSystem->init(_camera, IMAGEMANAGER->findImage("검사용BattleSceneBG")->getMemDC(), IMAGEMANAGER->findImage("검사용BattleSceneBG")->getHeight() / TILEHEIGHT, IMAGEMANAGER->findImage("BattleSceneBG")->getWidth() / TILEWIDTH);

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
	IMAGEMANAGER->findImage("BattleSceneBG")->render(getMemDC(), _camera->worldToCamera({ 0, 0 }).x, _camera->worldToCamera({ 0, 0 }).y);
	IMAGEMANAGER->findImage("CursorTile")->alphaFrameRender(getMemDC(), _camera->worldToCamera(_cursorTileLT).x, _camera->worldToCamera(_cursorTileLT).y, TILEWIDTH, TILEHEIGHT, (_frame / 5) % IMAGEMANAGER->findImage("CursorTile")->getMaxFrameX(), 0, 200);
	if (GetPixel(IMAGEMANAGER->findImage("검사용BattleSceneBG")->getMemDC(), _cameraPos.x - WINSIZE_X / 2 + _ptMouse.x, _cameraPos.y - WINSIZE_Y / 2 + _ptMouse.y) == RGB(255, 0, 255))
	{
		IMAGEMANAGER->findImage("CantMoveTile")->alphaFrameRender(getMemDC(), _camera->worldToCamera(_cursorTileLT).x, _camera->worldToCamera(_cursorTileLT).y,	
			TILEWIDTH, TILEHEIGHT, (_frame / 10) % (IMAGEMANAGER->findImage("CantMoveTile")->getMaxFrameX() + 1), 0, 200);
	}
	_turnSystem->render(getMemDC());
	if (_debug)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hPen);
		for (int i = 0; i < IMAGEMANAGER->findImage("BattleSceneBG")->getHeight() / TILEHEIGHT; i++)
		{
			LineMake(getMemDC(), _camera->worldToCamera({0, TILEHEIGHT * (i + 1) }).x, _camera->worldToCamera({ 0, TILEHEIGHT * (i + 1) }).y, 
				_camera->worldToCamera({ IMAGEMANAGER->findImage("BattleSceneBG")->getWidth(), TILEHEIGHT * (i + 1) }).x, _camera->worldToCamera({ IMAGEMANAGER->findImage("BattleSceneBG")->getWidth(), TILEHEIGHT * (i + 1) }).y);
		}
		for (int i = 0; i < IMAGEMANAGER->findImage("BattleSceneBG")->getWidth() / TILEWIDTH; i++)
		{
			LineMake(getMemDC(), _camera->worldToCamera({ TILEWIDTH * (i + 1), 0 }).x, _camera->worldToCamera({ TILEWIDTH * (i + 1), 0 }).y,
				_camera->worldToCamera({ TILEWIDTH * (i + 1), IMAGEMANAGER->findImage("BattleSceneBG")->getHeight() }).x, _camera->worldToCamera({ TILEWIDTH * (i + 1), IMAGEMANAGER->findImage("BattleSceneBG")->getHeight() }).y);
		}
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
	IMAGEMANAGER->findImage("CurEld")->render(getMemDC(), eldBarX + eld / 10000 * IMAGEMANAGER->findImage("EldBar")->getWidth() - IMAGEMANAGER->findImage("CurEld")->getWidth() / 2,
		eldBarY + IMAGEMANAGER->findImage("EldBar")->getHeight() / 2 - IMAGEMANAGER->findImage("CurEld")->getHeight());
	IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	char mapInfo[50];
	wsprintf(mapInfo, "자비단 돌입");
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 32 - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 / 2, 15, "가을체", 15, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "평 지");
	FONTMANAGER->textOut(getMemDC(), eldBarX + IMAGEMANAGER->findImage("EldBar")->getWidth() / 2 - 22,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight(), "가을체", 15, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%deld", eld);
	FONTMANAGER->textOut(getMemDC(), eldBarX + IMAGEMANAGER->findImage("EldIcon")->getWidth(), eldBarY + IMAGEMANAGER->findImage("EldBar")->getHeight() + 5, "가을체", 15, 0,
		mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	//wsprintf(mapInfo, "%d", _tileInfo[_cursorTile.y][_cursorTile.x] == CANTMOVE ? 1 : 0);
	wsprintf(mapInfo, "%d", 0);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 5 + IMAGEMANAGER->findImage("MapCoordination")->getWidth() / 2 + 5,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight() + 2, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _cursorTile.x);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 - 5 + IMAGEMANAGER->findImage("MapCoordination")->getWidth() - 15,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - IMAGEMANAGER->findImage("MapCoordination")->getHeight() / 2 - 5, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
	wsprintf(mapInfo, "%d", _cursorTile.y);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("TextBox")->getWidth() * 0.7 + 2,
		5 + IMAGEMANAGER->findImage("TextBox")->getHeight() * 0.7 - 13, "가을체", 13, 0, mapInfo, strlen(mapInfo), RGB(255, 255, 255));
}
