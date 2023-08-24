#include "Stdafx.h"
#include "TurnSystem.h"

HRESULT TurnSystem::init(void)
{
	_actionChoice = false;
	_skillChoice = false;
	_aStar = new AStar();
	_skill = new Skill();
	_skill->init();
	_isClear = false;
	_frame = 0;
	_actionChoice.reset();
	_actionChoice.set(0);
	_skillName = "";
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		if ((*it)->getTurnOrder(_charList.size()) == 0)
		{
			_curChar = (*it);
			break;
		}
	}
	int curWait = _curChar->getCurWait();
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		(*it)->setCurWait((*it)->getCurWait() - curWait);
	}
	return S_OK;
}

void TurnSystem::update(int tileInfo[][60], int rowN, int colN, POINT cursorTile)
{
	_frame++;
	for (auto it = _charList.begin(); it != _charList.end();)
	{
		if ((*it)->isDie())
		{
			tileInfo[(*it)->getTilePos().y][(*it)->getTilePos().x] = MOVABLE;
			for (auto it2 = _charList.begin(); it2 != _charList.end(); ++it2)
			{
				if ((*it)->getTurnOrder(_charList.size()) < (*it2)->getTurnOrder(_charList.size()))
				{
					(*it2)->moveTurnOrder();
				}
			}
			for (auto it2 = _objectList.begin(); it2 != _objectList.end();)
			{
				if (SamePoint((*it2)->getTilePos(), (*it)->getTilePos()))
				{
					it2 = _objectList.erase(it2);
					break;
				}
				else
				{
					++it2;
				}
			}
			//SAFE_DELETE(*it);
			//tileInfo[(*it)->getTilePos().y][(*it)->getTilePos().x] == MOVABLE;
			it = _charList.erase(it);
		}
		else
		{
			(*it)->update();
			++it;
		}
	}
	if (_isClear || _isFail)
	{
		if (_frame == 1)
		{
			SOUNDMANAGER->stopAllSoundFMOD();
			SOUNDMANAGER->playSoundFMOD("StageClear");
		}
		if (!SOUNDMANAGER->isPlaying() || KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->stopAllSoundFMOD();
			SCENEMANAGER->loadingScene();
		}
	}
	else
	{
		for (auto it = _charList.begin(); it != _charList.end();)
		{
			if ((*it)->getType() == 1)
			{
				break;
			}
			++it;
			if (it == _charList.end())
			{
				_isClear = true;
				_frame = 0;
				return;
			}
		}
		for (auto it = _charList.begin(); it != _charList.end();)
		{
			if ((*it)->getType() == 0)
			{
				break;
			}
			++it;
			if (it == _charList.end())
			{
				_isFail = true;
				_frame = 0;
				return;
			}
		}
		// 현재 캐릭터가 행동중이 아닐 때
		if (checkAllDoingNot())
		{
			if (_curChar->getType() == 0)
			{
				tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = SALADIN;
			}
			else if (_curChar->getType() == 1)
			{
				tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = ENEMY;
			}
			if (!_curChar->canMove() && !_curChar->canAction())
			{
				if (checkAllDoingNot())
				{
					nextTurn();
				}
			}
			if (_curChar->getType() == 0)
			{
				if (_curChar->canMove())
				{
					_player = (Saladin*)_curChar;
					_player->searchMovable(tileInfo, rowN, colN);
				}
				else
				{
					POINT curPos = _curChar->getTilePos();
					_attackTiles.clear();
					if (tileInfo[curPos.y][curPos.x - 2] == MOVABLE || tileInfo[curPos.y][curPos.x - 2] == ENEMY)
					{
						_attackTiles.push_back({ curPos.x - 2, curPos.y });
					}
					if (tileInfo[curPos.y][curPos.x + 2] == MOVABLE || tileInfo[curPos.y][curPos.x + 2] == ENEMY)
					{
						_attackTiles.push_back({ curPos.x + 2, curPos.y });
					}
					if (tileInfo[curPos.y - 2][curPos.x] == MOVABLE || tileInfo[curPos.y - 2][curPos.x] == ENEMY)
					{
						_attackTiles.push_back({ curPos.x, curPos.y - 2 });
					}
					if (tileInfo[curPos.y + 2][curPos.x] == MOVABLE || tileInfo[curPos.y + 2][curPos.x] == ENEMY)
					{
						_attackTiles.push_back({ curPos.x, curPos.y + 2 });
					}
				}
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (!_actionChoice.test(0))
					{
						if(_actionChoice.test(1))
						{
							if (PtInRect(&_actionButtons[0], _ptMouse))
							{
								_actionChoice = _actionChoice << 1;
							}
							if (PtInRect(&_actionButtons[2], _ptMouse))
							{
								_actionChoice.reset();
								_actionChoice.set(0);
								nextTurn();
							}
						}
						// 스킬 선택하고 스킬범위 받기
						else if(_actionChoice.test(2))
						{
							for (int i = 0; i < 3; i++)
							{
								if (PtInRect(&_skillButtons[i], _ptMouse))
								{
									_actionChoice = _actionChoice << 1;
									if (i == 0)
									{
										_skillName = "천지파열무";
									}
									else if (i == 1)
									{
										_skillName = "풍아열공참";
									}
									else if (i == 2)
									{
										_skillName = "혈랑마혼";
									}
									_skillableTiles = ((Saladin*)(_curChar))->getSkillableTiles(tileInfo, 90, 60, _skillName);
								}
							}
						}
						// 스킬 발동 영역 선택
						else if (_actionChoice.test(3))
						{
							_player = (Saladin*)_curChar;
							if (_player->getCurMP() == _player->getMaxMP())
							{
								if (!strcmp(_skillName, "풍아열공참"))
								{
									if (tileInfo[cursorTile.y][cursorTile.x] == ENEMY)
									{
										for (auto it = _skillableTiles.begin(); it != _skillableTiles.end(); ++it)
										{
											if (SamePoint(cursorTile, (*it)))
											{
												_curChar->setDestTilePos(cursorTile);
												_skill->start(_charList, _curChar, _skillName);
												_player->setState(8);
												_player->setXY(40, 30);
												_player->setDoing(true);
												_actionChoice.reset();
												_actionChoice.set(0);
												break;
											}
										}
									}
								}
								else if(!strcmp(_skillName, "천지파열무"))
								{
									vector<Character*> charList;
									for (auto it = _skillableTiles.begin(); it != _skillableTiles.end(); ++it)
									{
										for (int i = 0; i < _charList.size(); i++)
										{
											if (SamePoint((*it), _charList[i]->getTilePos()))
											{
												if (_charList[i]->getType() == 1)
												{
													charList.push_back(_charList[i]);
												}
											}
										}
									}
									if(charList.size() > 0)
									{
										_player->setState(8);
										_player->setXY(40, 30);
										_player->setDoing(true);
										_skill->start(charList, _curChar, _skillName);
										_actionChoice.reset();
										_actionChoice.set(0);
									}
								}
								else if (!strcmp(_skillName, "혈랑마혼"))
								{
									for (auto it = _skillableTiles.begin(); it != _skillableTiles.end(); ++it)
									{
										if (SamePoint(cursorTile, (*it)))
										{
											vector<Character*> charList;
											for (auto it = _charList.begin(); it != _charList.end(); ++it)
											{
												if ((*it)->getType() == 0)
												{
													continue;
												}
												if (cursorTile.y == _curChar->getTilePos().y)
												{
													if (abs((*it)->getTilePos().x - _curChar->getTilePos().x) < abs(cursorTile.x - _curChar->getTilePos().x) && 
														((*it)->getTilePos().x - _curChar->getTilePos().x) * (cursorTile.x - _curChar->getTilePos().x) > 0)
													{
														if (abs((*it)->getTilePos().y - _curChar->getTilePos().y) < 2)
														{
															charList.push_back((*it));
														}
													}
												}
												else
												{
													if (abs((*it)->getTilePos().y - _curChar->getTilePos().y) < abs(cursorTile.y - _curChar->getTilePos().y) &&
														((*it)->getTilePos().y - _curChar->getTilePos().y) * (cursorTile.y - _curChar->getTilePos().y) > 0)
													{
														if (abs((*it)->getTilePos().x - _curChar->getTilePos().x) < 2)
														{
															charList.push_back((*it));
														}
													}
												}
											}
											tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
											_curChar->setDestTilePos(cursorTile);
											_skill->start(charList, _curChar, _skillName);
											_player->setState(8);
											_player->setXY(40, 30);
											_player->setDoing(true);
											_actionChoice.reset();
											_actionChoice.set(0);
											break;
										}
									}
								}
							}
						}
					}
					else
					{
						if (_curChar->canMove())
						{
							if (_curChar->canAction())
							{
								if (tileInfo[cursorTile.y][cursorTile.x] == ENEMY)
								{
									vector<vector<POINT>> routes;
									vector<POINT> route;
									if (cursorTile.x > 1 && (tileInfo[cursorTile.y][cursorTile.x - 2] == MOVABLE || tileInfo[cursorTile.y][cursorTile.x - 2] == SALADIN))
									{
										routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x - 2, cursorTile.y }, tileInfo, rowN, colN));
									}
									if (cursorTile.x < colN - 2 && (tileInfo[cursorTile.y][cursorTile.x + 2] == MOVABLE || tileInfo[cursorTile.y][cursorTile.x + 2] == SALADIN))
									{
										routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x + 2, cursorTile.y }, tileInfo, rowN, colN));
									}
									if (cursorTile.y > 1 && (tileInfo[cursorTile.y - 2][cursorTile.x] == MOVABLE || tileInfo[cursorTile.y - 2][cursorTile.x] == SALADIN))
									{
										routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x, cursorTile.y - 2 }, tileInfo, rowN, colN));
									}
									if (cursorTile.y < rowN - 2 && (tileInfo[cursorTile.y + 2][cursorTile.x] == MOVABLE || tileInfo[cursorTile.y + 2][cursorTile.x] == SALADIN))
									{
										routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x, cursorTile.y + 2 }, tileInfo, rowN, colN));
									}
									route = routes[0];
									for (auto it = routes.begin(); it != routes.end(); ++it)
									{
										if (route.size() > (*it).size())
										{
											route = (*it);
										}
									}
									if (route.size() > 0)
									{
										_curChar->setState(3);
									}
									else
									{
										_curChar->setState(2);
									}
									_curChar->setDoing(true);
									_curChar->setRoute(route);
									_curChar->setDestTilePos(cursorTile);
									tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
								}
								if (tileInfo[cursorTile.y][cursorTile.x] == SALADIN)
								{
									_actionChoice = _actionChoice << 1;
								}
							}
							if (tileInfo[cursorTile.y][cursorTile.x] == MOVABLE)
							{
								_curChar->setState(1);
								_curChar->setDoing(true);
								_curChar->setRoute(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x, cursorTile.y }, tileInfo, rowN, colN));
								tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
							}
						}
						else
						{
							if (_curChar->canAction())
							{
								if (tileInfo[cursorTile.y][cursorTile.x] == ENEMY)
								{
									if ((cursorTile.x - _curChar->getTilePos().x == 2) && (cursorTile.y == _curChar->getTilePos().y))
									{
										_curChar->setDestTilePos(cursorTile);
										_curChar->setState(2);
										_curChar->setDoing(true);
									}
									if ((cursorTile.x - _curChar->getTilePos().x == -2) && (cursorTile.y == _curChar->getTilePos().y))
									{
										_curChar->setDestTilePos(cursorTile);
										_curChar->setState(2);
										_curChar->setDoing(true);
									}
									if ((cursorTile.y - _curChar->getTilePos().y == 2) && (cursorTile.x == _curChar->getTilePos().x))
									{
										_curChar->setDestTilePos(cursorTile);
										_curChar->setState(2);
										_curChar->setDoing(true);
									}
									if ((cursorTile.y - _curChar->getTilePos().y == -2) && (cursorTile.x == _curChar->getTilePos().x))
									{
										_curChar->setDestTilePos(cursorTile);
										_curChar->setState(2);
										_curChar->setDoing(true);
									}
								}
								if (tileInfo[cursorTile.y][cursorTile.x] == SALADIN)
								{
									_actionChoice = _actionChoice << 1;
								}
							}
						}
					}
				}
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					if(!_actionChoice.test(0))
					{
						_actionChoice = _actionChoice >> 1;
					}
				}
			}
			else if (_curChar->getType() == 1)
			{
				if (_frame / 10 == 8)
				{
					_enemy = (Enemy*)_curChar;
					if (_enemy->getCurMP() == _enemy->getMaxMP())
					{
						_enemy->setState(8);
						_enemy->setXY(40, 30);
						_enemy->setDoing(true);
						_skill->start(_charList, _curChar, "설화난영참");
					}
					else
					{
						_enemy->setState(3);
						_enemy->setDoing(true);
						POINT player = _enemy->findPlayer(tileInfo, rowN, colN);
						vector<vector<POINT>> routes;
						vector<POINT> route;
						if (player.x > 1 && (tileInfo[player.y][player.x - 2] == MOVABLE || (_enemy->getTilePos().x == player.x - 2 && _enemy->getTilePos().y == player.y)))
						{
							routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { player.x - 2, player.y }, tileInfo, rowN, colN));
						}
						if (player.x < colN - 2 && (tileInfo[player.y][player.x + 2] == MOVABLE || (_enemy->getTilePos().x == player.x + 2 && _enemy->getTilePos().y == player.y)))
						{
							routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { player.x + 2, player.y }, tileInfo, rowN, colN));
						}
						if (player.y > 1 && (tileInfo[player.y - 2][player.x] == MOVABLE || (_enemy->getTilePos().x == player.x && _enemy->getTilePos().y == player.y - 2)))
						{
							routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { player.x, player.y - 2 }, tileInfo, rowN, colN));
						}
						if (player.y < rowN - 2 && (tileInfo[player.y + 2][player.x] == MOVABLE || (_enemy->getTilePos().x == player.x && _enemy->getTilePos().y == player.y + 2)))
						{
							routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { player.x, player.y + 2 }, tileInfo, rowN, colN));
						}
						route = routes[0];
						for (auto it = routes.begin(); it != routes.end(); ++it)
						{
							if (route.size() > (*it).size())
							{
								route = (*it);
							}
						}
						_curChar->setRoute(route);
						_curChar->setDestTilePos(player);
						tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
					}
				}
			}
		}
		// 현재 캐릭터가 행동중일 때
		else
		{
			if (_curChar->isAttack())
			{
				Character* targetChar = nullptr;
				for (auto it = _charList.begin(); it != _charList.end(); ++it)
				{
					if (SamePoint((*it)->getTilePos(), _curChar->getDestTilePos()))
					{
						targetChar = (*it);
						break;
					}
				}
				targetChar->setState(4);
				targetChar->setDamage(_curChar->getDamage());
				targetChar->setDoing(true);
			}
			else if (_curChar->isSkill())
			{
				_skill->update();
			}
		}
	}
}

void TurnSystem::release(void)
{
	SAFE_DELETE(_aStar);
	_skill->release();
	SAFE_DELETE(_skill);
}

void TurnSystem::render(HDC hdc, int tileHeight, int tileWidth, POINT cameraPos)
{
	// 그림자
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		int x = NULL;
		int y = NULL;
		if ((*it)->isDoing())
		{
			x = (*it)->getX() - IMAGEMANAGER->findImage("Shadow")->getWidth() / 2;
			y = (*it)->getY() - IMAGEMANAGER->findImage("Shadow")->getWidth() / 2;
		}
		else
		{
			x = (*it)->getTilePos().x * TILEWIDTH + TILEWIDTH / 2 - IMAGEMANAGER->findImage("Shadow")->getWidth() / 2;
			y = (*it)->getTilePos().y * TILEHEIGHT + TILEHEIGHT / 2 - IMAGEMANAGER->findImage("Shadow")->getHeight() / 2;
		}
		IMAGEMANAGER->findImage("Shadow")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x), WINSIZE_Y / 2 - (cameraPos.y - y), 128);
	}
	// 현재 캐릭터가 플레이어일 때
	if (_curChar->getType() == 0)
	{
		if(!_curChar->isDoing())
		{
			if (_curChar->canMove())
			{
				_player = (Saladin*)_curChar;
				vector<POINT> tiles = _player->getMovableTiles();
				if (_actionChoice.test(3))
				{
					for (auto it = _skillableTiles.begin(); it != _skillableTiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("SkillableTile")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it).x * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (*it).y * tileHeight), tileWidth, tileHeight,
							0, 0, IMAGEMANAGER->findImage("SkillableTile")->getWidth(), IMAGEMANAGER->findImage("SkillableTile")->getHeight());
					}
				}
				else
				{
					for (auto it = tiles.begin(); it != tiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("MovableTile")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it).x * tileWidth),
							WINSIZE_Y / 2 - (cameraPos.y - (*it).y * tileHeight), tileWidth, tileHeight, 0, 0,
							IMAGEMANAGER->findImage("MovableTile")->getWidth(), IMAGEMANAGER->findImage("MovableTile")->getHeight(), 128);
					}
					tiles = _player->getAttackableTiles();
					for (auto it = tiles.begin(); it != tiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("AttackableTile")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it).x * tileWidth),
							WINSIZE_Y / 2 - (cameraPos.y - (*it).y * tileHeight), tileWidth, tileHeight, 0, 0,
							IMAGEMANAGER->findImage("AttackableTile")->getWidth(), IMAGEMANAGER->findImage("AttackableTile")->getHeight(), 128);
					}
				}
			}
			else 
			{
				if (_actionChoice.test(3))
				{
					for (auto it = _skillableTiles.begin(); it != _skillableTiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("SkillableTile")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it).x * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (*it).y * tileHeight), tileWidth, tileHeight,
							0, 0, IMAGEMANAGER->findImage("SkillableTile")->getWidth(), IMAGEMANAGER->findImage("SkillableTile")->getHeight());
					}
				}
				else if (_curChar->canAction())
				{
					for (auto it = _attackTiles.begin(); it != _attackTiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("AttackableTile")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it).x * tileWidth),
							WINSIZE_Y / 2 - (cameraPos.y - (*it).y * tileHeight), tileWidth, tileHeight, 0, 0,
							IMAGEMANAGER->findImage("AttackableTile")->getWidth(), IMAGEMANAGER->findImage("AttackableTile")->getHeight(), 128);
					}
				}
			}
		}
	}
	// y좌표에 따라 캐릭터들 정렬
	sortObjectList();
	// Object들 렌더
	for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
	{
		if ((*it)->getType() == 2)
		{
			Obstacle* obstacle = (Obstacle*)(*it);
			obstacle->render(hdc, cameraPos);
		}
		else if((*it)->getType() < 2)
		{
			Character* temp = (Character*)(*it);
			temp->render(hdc, { WINSIZE_X / 2 - (cameraPos.x - temp->getTilePos().x * tileWidth),
				WINSIZE_Y / 2 - (cameraPos.y - temp->getTilePos().y * tileHeight + tileHeight / 2 * 3) }, cameraPos);
		}
	}
	if (_isClear || _isFail)
	{
		IMAGEMANAGER->findImage("Black")->alphaRender(hdc, _frame * 10 > 128 ? 128 : _frame * 10);
		if (_frame * 10 > 128)
		{
			IMAGEMANAGER->findImage("BattleEnd")->alphaRender(hdc, 0, WINSIZE_Y / 2 - IMAGEMANAGER->findImage("BattleEnd")->getHeight() / 2, 128);
			IMAGEMANAGER->findImage("Scenario")->render(hdc, WINSIZE_X / 2 - IMAGEMANAGER->findImage("Scenario")->getWidth() - 20, WINSIZE_Y / 2 - IMAGEMANAGER->findImage("Scenario")->getHeight() / 2);
			IMAGEMANAGER->findImage("Clear")->render(hdc, WINSIZE_X / 2 + 20, WINSIZE_Y / 2 - IMAGEMANAGER->findImage("Clear")->getHeight() / 2);
		}
	}
	else
	{
		if (!_curChar->isDoing())
		{
			if (_curChar->getType() == 0)
			{
				IMAGEMANAGER->findImage("PlayerMarker")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - _curChar->getTilePos().x * tileWidth) + 15,
					WINSIZE_Y / 2 - (cameraPos.y - _curChar->getTilePos().y * tileHeight) - 70, (_frame / 5) % 8, 0);
			}
			else if (_curChar->getType() == 1)
			{
				IMAGEMANAGER->findImage("EnemyMarker")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - _curChar->getTilePos().x * tileWidth) + 15,
					WINSIZE_Y / 2 - (cameraPos.y - _curChar->getTilePos().y * tileHeight) - 70, (_frame / 5) % 8, 0);
			}
		}
		if (!_skill->isFinish())
		{
			_skill->render(hdc, { WINSIZE_X / 2 - (cameraPos.x - _curChar->getTilePos().x * tileWidth),
				WINSIZE_Y / 2 - (cameraPos.y - _curChar->getTilePos().y * tileHeight + tileHeight / 2 * 3) }, cameraPos, tileWidth, tileHeight);
		}
	}
	if (_actionChoice.test(1))
	{
		POINT curPos = _curChar->getTilePos();
		_actionButtons[0] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) - 80, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) - 30, 100, 30);
		_actionButtons[1] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) - 80, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) + 15, 100, 30);
		_actionButtons[2] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) + 120, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) - 30, 100, 30);
		_actionButtons[3] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) + 120, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) + 15, 100, 30);
		char* actionStr[4] = {"어빌리티", "아이템", "휴 식", "상 태"};
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_actionButtons[i], _ptMouse))
			{
				IMAGEMANAGER->findImage("ActionButtonActive")->render(hdc, _actionButtons[i].left, _actionButtons[i].top);
			}
			else
			{
				IMAGEMANAGER->findImage("ActionButton")->render(hdc, _actionButtons[i].left, _actionButtons[i].top);
			}
			IMAGEMANAGER->findImage("ActionIcon")->frameRender(hdc, _actionButtons[i].left + 10, _actionButtons[i].top, i, 0);
			FONTMANAGER->textOut(hdc, _actionButtons[i].left + 35 + 3 * (strlen(actionStr[0]) - strlen(actionStr[i])), _actionButtons[i].top + 5, "가을체", 15, 100, actionStr[i], strlen(actionStr[i]), RGB(255, 255, 255));
		}
	}
	if (_actionChoice.test(2))
	{
		for(int i = 0; i < 3; i++)
		{
			_skillButtons[i].left = WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 2) * tileWidth) + 5;
			_skillButtons[i].right = _skillButtons[i].left + 155;
			_skillButtons[i].top = WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 2) * tileHeight) + 5 + 23 * i;
			_skillButtons[i].bottom = _skillButtons[i].top + 20;
		}
		IMAGEMANAGER->findImage("TextBox")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 2) * tileWidth),
			WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 2) * tileHeight), 160, 100, 0, 0, 
			IMAGEMANAGER->findImage("TextBox")->getWidth(), IMAGEMANAGER->findImage("TextBox")->getHeight(), 128);
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_skillButtons[i], _ptMouse))
			{
				IMAGEMANAGER->findImage("SkillButtonActive")->alphaRender(hdc,_skillButtons[i].left, 
					_skillButtons[i].top, 150, 20, 0, 0, 
					IMAGEMANAGER->findImage("SkillButtonActive")->getWidth(), IMAGEMANAGER->findImage("SkillButtonActive")->getHeight(), 128);
			}
			IMAGEMANAGER->findImage("SkillIcon")->render(hdc, _skillButtons[i].left, _skillButtons[i].top);
		}
		char skillStr[258];
		wsprintf(skillStr, "천지파열무");
		FONTMANAGER->textOut(hdc, _skillButtons[0].left + 22, _skillButtons[0].top, "가을체", 18, 100, skillStr, strlen(skillStr), RGB(255, 255, 255));
		wsprintf(skillStr, "풍아열공참");
		FONTMANAGER->textOut(hdc, _skillButtons[1].left + 22, _skillButtons[1].top, "가을체", 18, 100, skillStr, strlen(skillStr), RGB(255, 255, 255));
		wsprintf(skillStr, "혈랑마혼");
		FONTMANAGER->textOut(hdc, _skillButtons[2].left + 22, _skillButtons[2].top, "가을체", 18, 100, skillStr, strlen(skillStr), RGB(255, 255, 255));
	}
}

void TurnSystem::addCharacter(Character* character)
{
	_charList.push_back(character);
}

void TurnSystem::addObject(Object* object)
{
	_objectList.push_back(object);
}

void TurnSystem::nextTurn()
{
	_frame = 0;
	_curChar->setCurWait(_curChar->getWTP());
	int turnOrder = _charList.size() - 1;
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		if (_curChar->getCurWait() >= (*it)->getCurWait())
		{
			(*it)->moveTurnOrder();
		}
		else
		{
			if (turnOrder > (*it)->getTurnOrder(_charList.size()))
			{
				turnOrder = (*it)->getTurnOrder(_charList.size()) - 1;
			}
		}
	}
	_curChar->moveTurnOrder();
	_curChar->setTurnOder(turnOrder);
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		if ((*it)->getTurnOrder(_charList.size()) == 0)
		{
			_curChar = *it;
			break;
		}
	}
	int curWait = _curChar->getCurWait();
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		(*it)->setCurWait((*it)->getCurWait() - curWait);
	}
	_curChar->resetTurn();
}

void TurnSystem::sortObjectList()
{
	for (int i = 0; i < _objectList.size() - 1; i++)
	{
		for (int j = i + 1; j < _objectList.size(); j++)
		{
			if (_objectList[i]->getTilePos().y > _objectList[j]->getTilePos().y)
			{
				Object* temp;
				temp = _objectList[j];
				_objectList[j] = _objectList[i];
				_objectList[i] = temp;
			}
			else if (_objectList[i]->getTilePos().y == _objectList[j]->getTilePos().y)
			{
				if (_objectList[j]->getType() != 2)
				{
					Character* character = (Character*)_objectList[j];
					if (!character->isDoing())
					{
						Object* temp;
						temp = _objectList[j];
						_objectList[j] = _objectList[i];
						_objectList[i] = temp;
					}
					else
					{
						if (_objectList[i]->getTilePos().x > _objectList[j]->getTilePos().x)
						{
							Object* temp;
							temp = _objectList[j];
							_objectList[j] = _objectList[i];
							_objectList[i] = temp;
						}
					}
				}
			}
		}
	}
}

Character* TurnSystem::findCharacter(POINT cursorPoint)
{
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		if (SamePoint(cursorPoint, (*it)->getTilePos()))
		{
			return (*it);
		}
	}
}

bool TurnSystem::checkAllDoingNot()
{
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		if ((*it)->isDoing())
		{
			return false;
		}
	}
	return true;
}
