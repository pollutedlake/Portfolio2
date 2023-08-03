#include "Stdafx.h"
#include "BattleScene.h"

HRESULT BattleScene::init(void)
{
	BattleData* battleData = nullptr;
	switch (DATAMANAGER->getScenario())
	{
		case 69:
			battleData = DATAMANAGER->findBattleData("불사조", DATAMANAGER->getBattleIdx());
		break;
		case 75:
			battleData = DATAMANAGER->findBattleData("형제", DATAMANAGER->getBattleIdx());
		break;
	}
	wsprintf(_bgImg, "BattleSceneBG%d", battleData->_bgImgN);
	wsprintf(_checkBGImg, "검사용BattleSceneBG%d", battleData->_bgImgN);
	_camera = new Camera();
	_camera->init();
	_camera->setLimitRight(IMAGEMANAGER->findImage(_bgImg)->getWidth() - WINSIZE_X / 2);
	_camera->setLimitBottom(IMAGEMANAGER->findImage(_bgImg)->getHeight() - WINSIZE_Y / 2);
	_camera->setPosition({ IMAGEMANAGER->findImage(_bgImg)->getWidth() / 2, IMAGEMANAGER->findImage(_bgImg)->getHeight() / 2 });

	_turnSystem = new TurnSystem2();
	_party = DATAMANAGER->getPartyData();
	_launch = false;
	if (DATAMANAGER->isLoadGame())
	{
		_turnSystem->setCharList(DATAMANAGER->getLoadCharList());
		_launch = true;
		_turnSystem->setStart(true);
	}
	else
	{
		for (auto it = battleData->_enemy.begin(); it != battleData->_enemy.end(); ++it)
		{
			Soldier* soldier = new Soldier;
			soldier->init(EnemyType(it->_type));
			_turnSystem->addCharacter(soldier, it->_dir, it->_tilePos, it->_turnOrder);
			//soldier->setState(4);
		}
	}
	for (auto it = battleData->_object.begin(); it != battleData->_object.end(); ++it)
	{
		wsprintf(_text, "Object%d-%d", battleData->_bgImgN, it->_index);
		_turnSystem->addObject(new Obstacle(_text, it->_rcLT, it->_width, it->_height, it->_sortTile));
	}
	_turnSystem->init(_camera, IMAGEMANAGER->findImage(_checkBGImg)->getMemDC(), IMAGEMANAGER->findImage(_bgImg)->getHeight() / TILEHEIGHT, IMAGEMANAGER->findImage(_bgImg)->getWidth() / TILEWIDTH);
	DATAMANAGER->setLoadGame(false);

	for (int i = 0; i < _party.size(); i++)
	{
		_launchRT[i].first.left = 10 + (IMAGEMANAGER->findImage("살라딘Mini")->getWidth() + 6) * (i % 5);
		_launchRT[i].first.right = _launchRT[i].first.left + 4 + IMAGEMANAGER->findImage("살라딘Mini")->getWidth();
		_launchRT[i].first.top = 40 + (IMAGEMANAGER->findImage("살라딘Mini")->getHeight() + 6) * (i / 5);
		_launchRT[i].first.bottom = _launchRT[i].first.top + 4 + IMAGEMANAGER->findImage("살라딘Mini")->getHeight();
		_launchRT[i].second = false;
	}
	_launchTile = battleData->_launchTile;
	_showMiniStatusFrame = 0;
	_launchOrder.reset();
	_launchOrder.set(0);
	_frame = 0;
	return S_OK;
}

void BattleScene::update(void)
{
	if (_frame == 0)
	{
		wsprintf(_text, "BattleSceneBG%d", DATAMANAGER->getBattleIdx() + 1);
		SOUNDMANAGER->playSoundFMOD(_text);
	}
	_frame++;
	_camera->update();
	SOUNDMANAGER->update();
	_cameraPos = _camera->getPosition();

	if (_turnSystem->getCurChar()->isSkill())
	{
		_camera->setPosition({ (LONG)(_turnSystem->getCurChar()->getX()), (LONG)(_turnSystem->getCurChar()->getY()) });
		Player* saladin = (Player*)_turnSystem->getCurChar();
		if (saladin->isCameraShake())
		{
			_camera->setPosition({ _camera->getPosition().x - RND->getInt(20), _camera->getPosition().y - RND->getInt(20) });
		}
	}

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

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_launch)
		{
			if (_launchOrder.test(0))
			{
				for (int i = 0; i < _party.size(); i++)
				{
					if (PtInRect(&_launchRT[i].first, _ptMouse))
					{
						_launchOrder = _launchOrder << 1;
						_exPtMouse = _ptMouse;
						_launchButton[0] = { _exPtMouse.x + 5, _exPtMouse.y + 5, _exPtMouse.x + 125, _exPtMouse.y + 20 };
						_launchButton[1] = { _exPtMouse.x + 5, _exPtMouse.y + 25, _exPtMouse.x + 125, _exPtMouse.y + 45 };
						_launchButton[2] = { _exPtMouse.x + 5, _exPtMouse.y + 125, _exPtMouse.x + 125, _exPtMouse.y + 145 };
						_launchButton[3] = { _exPtMouse.x + 5, _exPtMouse.y + 145, _exPtMouse.x + 125, _exPtMouse.y + 165 };
						_selectCharIndex = i;
					}
				}
			}
			else if (_launchOrder.test(1))
			{
				if (PtInRect(&_launchButton[0], _ptMouse) && !_launchRT[_selectCharIndex].second)
				{
					_launchOrder = _launchOrder << 1;
				}
				else if (PtInRect(&_launchButton[1], _ptMouse) && _launchRT[_selectCharIndex].second)
				{
					_launchOrder = _launchOrder >> 1;
					_launchRT[_selectCharIndex].second = false;
					Player* player = _turnSystem->deleteCharacter(_party[_selectCharIndex]->_name.c_str());
					SAFE_DELETE(player);
				}
				else if (PtInRect(&_launchButton[2], _ptMouse))
				{
					_launchOrder = _launchOrder >> 1;
					for (auto it = _party.begin(); it != _party.end(); ++it)
					{
						_launchRT[_selectCharIndex].second = false;
						Player* player = _turnSystem->deleteCharacter((*it)->_name.c_str());
						if(player != nullptr)
						{
							SAFE_DELETE(player);
						}
					}
					for (auto it = _party.begin(); it != _party.end(); ++it)
					{
						int random = RND->getInt(_launchTile.size());
						while (_turnSystem->checkTile(_launchTile[random]) != MOVABLE)
						{
							random = RND->getInt(_launchTile.size());
						}
						Player* _player = new Player((*it)->_name.c_str(), (*it)->_skill);
						_player->init();
						_turnSystem->addCharacter(_player, UP, _launchTile[random], NULL);
						_launchRT[it - _party.begin()].second = true;
					}
				}
				else if (PtInRect(&_launchButton[3], _ptMouse))
				{
					_launch = true;
					_turnSystem->setStart(true);
				}
				else
				{
					_launchOrder = _launchOrder >> 1;
				}
			}
			else if (_launchOrder.test(2))
			{
				for (auto it = _launchTile.begin(); it != _launchTile.end(); ++it)
				{
					if (PtInRect(&RectMakeCenter(_camera->worldToCamera({ (*it).x * TILEWIDTH + TILEWIDTH / 2, (*it).y * TILEHEIGHT + TILEHEIGHT / 2 }).x,
						_camera->worldToCamera({ (*it).x * TILEWIDTH + TILEWIDTH / 2, (*it).y * TILEHEIGHT + TILEHEIGHT / 2 }).y, TILEWIDTH, TILEHEIGHT), _ptMouse))
					{
						if(_turnSystem->checkTile((*it)) == MOVABLE)
						{
							Player* _player = new Player(_party[_selectCharIndex]->_name.c_str(), _party[_selectCharIndex]->_skill);
							_player->init();
							_turnSystem->addCharacter(_player, UP, *it, NULL);
							//_player->setState(2);
							_launchRT[_selectCharIndex].second = true;
							_launchOrder.reset();
							_launchOrder.set(0);
						}
					}
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_debug = !_debug;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SOUNDMANAGER->stopAllSoundFMOD();
		SCENEMANAGER->loadingScene();
		DATAMANAGER->setBattleIdx(DATAMANAGER->getBattleIdx() + 1);
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
	if(_launch)
	{
		IMAGEMANAGER->findImage("CursorTile")->alphaFrameRender(getMemDC(), _camera->worldToCamera(_cursorTileLT).x, _camera->worldToCamera(_cursorTileLT).y, TILEWIDTH, TILEHEIGHT, (_frame / 5) % IMAGEMANAGER->findImage("CursorTile")->getMaxFrameX(), 0, 200);
		if (GetPixel(IMAGEMANAGER->findImage(_checkBGImg)->getMemDC(), _cursorTileLT.x + TILEWIDTH / 2, _cursorTileLT.y + TILEHEIGHT / 2) == RGB(255, 0, 255))
		{
			IMAGEMANAGER->findImage("CantMoveTile")->alphaFrameRender(getMemDC(), _camera->worldToCamera(_cursorTileLT).x, _camera->worldToCamera(_cursorTileLT).y,
				TILEWIDTH, TILEHEIGHT, (_frame / 10) % (IMAGEMANAGER->findImage("CantMoveTile")->getMaxFrameX() + 1), 0, 200);
		}
	}
	// 파티 배치
	if (!_launch)
	{
		bool launchTile = false;
	//	// 출전시킬 수 있는 타일
		for (auto it = _launchTile.begin(); it != _launchTile.end(); ++it)
		{
			IMAGEMANAGER->findImage("LaunchTile")->alphaRender(getMemDC(), _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).x, _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).y, 127);
			// 출전시킬 수 있는 타일에 마우스 올리면 커서 바뀜
			if (PtInRect(&RectMakeCenter(_camera->worldToCamera({ (*it).x * TILEWIDTH + TILEWIDTH / 2, (*it).y * TILEHEIGHT + TILEHEIGHT / 2 }).x,
				_camera->worldToCamera({ (*it).x * TILEWIDTH + TILEWIDTH / 2, (*it).y * TILEHEIGHT + TILEHEIGHT / 2 }).y, TILEWIDTH, TILEHEIGHT), _ptMouse))
			{
				IMAGEMANAGER->findImage("FingerCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 5, 0);
				launchTile = true;
			}
		}
		_turnSystem->render(getMemDC());
		DIALOGMANAGER->makeTextBox(getMemDC(), 5, 5, WINSIZE_X / 2 - 50, 100, 200);
		FONTMANAGER->textOut(getMemDC(), 10, 10, "가을체", 20, 100, "출전할 캐릭터를 선택하세요.", strlen("출전할 캐릭터를 선택하세요."), RGB(164, 215, 242));
		for (auto it = _party.begin(); it != _party.end(); ++it)
		{
			wsprintf(_text, (*it)->_name.c_str());
			strcat_s(_text, "Mini");
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
			FillRect(getMemDC(), &_launchRT[(it - _party.begin())].first, hBrush);
			IMAGEMANAGER->findImage(_text)->render(getMemDC(), _launchRT[it - _party.begin()].first.left + 2, _launchRT[it - _party.begin()].first.top + 2);
			if (_launchRT[it - _party.begin()].second)
			{
				IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), _launchRT[it - _party.begin()].first.left, _launchRT[it - _party.begin()].first.top, _launchRT[it - _party.begin()].first.right - _launchRT[it - _party.begin()].first.left,
					_launchRT[it - _party.begin()].first.bottom - _launchRT[it - _party.begin()].first.top, 0, 0, IMAGEMANAGER->findImage("Black")->getWidth(), IMAGEMANAGER->findImage("Black")->getHeight(), 128);
				SetTextAlign(getMemDC(), TA_CENTER);
				FONTMANAGER->textOut(getMemDC(), (_launchRT[it - _party.begin()].first.right + _launchRT[it - _party.begin()].first.left) / 2, _launchRT[it - _party.begin()].first.bottom - 30, "가을체", 20, 100, "Entry", strlen("Entry"), RGB(255, 0, 0));
				SetTextAlign(getMemDC(), TA_LEFT);
			}
			DeleteObject(hBrush);
		}
		if (_launchOrder.test(1))
		{
			DIALOGMANAGER->makeTextBox(getMemDC(), _exPtMouse.x, _exPtMouse.y, 130, 170, 200);
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&_launchButton[i], _ptMouse))
				{
					if (i < 2 && i != _launchRT[_selectCharIndex].second)
					{
						continue;
					}
					IMAGEMANAGER->findImage("SkillButtonActive")->render(getMemDC(), _launchButton[i].left, _launchButton[i].top, _launchButton[i].right - _launchButton[i].left, _launchButton[i].bottom - _launchButton[i].top,
						0, 0, IMAGEMANAGER->findImage("SkillButtonActive")->getWidth(), IMAGEMANAGER->findImage("SkillButtonActive")->getHeight());
				}
			}
			SetTextAlign(getMemDC(), TA_CENTER);
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 5, "가을체", 15, 100, "출전", strlen("출전"), _launchRT[_selectCharIndex].second ? RGB(139, 140, 141) : RGB(255, 255, 255));
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 25, "가을체", 15, 100, "출전 취소", strlen("출전 취소"), _launchRT[_selectCharIndex].second ? RGB(255, 255, 255) : RGB(139, 140, 141));
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 45, "가을체", 15, 100, "용병 배치", strlen("용병 배치"), RGB(139, 140, 141));
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 65, "가을체", 15, 100, "용병 배치 취소", strlen("용병 배치 취소"), RGB(139, 140, 141));
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 85, "가을체", 15, 100, "탑승", strlen("탑승"), RGB(139, 140, 141));
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 105, "가을체", 15, 100, "탑승 취소", strlen("탑승 취소"), RGB(139, 140, 141));
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 125, "가을체", 15, 100, "자동 배치", strlen("자동 배치"), RGB(255, 255, 255));
			FONTMANAGER->textOut(getMemDC(), _exPtMouse.x + 65, _exPtMouse.y + 145, "가을체", 15, 100, "배치 종료", strlen("배치 종료"), RGB(255, 255, 255));
			SetTextAlign(getMemDC(), TA_LEFT);
		}
		if (!launchTile)
		{
			IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
		}
	}
	else
	{
		_turnSystem->render(getMemDC());
		if (_turnSystem->checkTile(_cursorTile) != ENEMY)
		{
			IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
		}
	}
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
		SelectObject(getMemDC(), hOldPen);
		DeleteObject(hPen);
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
