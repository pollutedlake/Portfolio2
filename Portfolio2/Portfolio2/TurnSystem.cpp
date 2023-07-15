#include "Stdafx.h"
#include "TurnSystem.h"

HRESULT TurnSystem::init(void)
{
	_actionChoice = false;
	_aStar = new AStar();
	_frame = 0;
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		if ((*it)->getTurnOrder(_charList.size()) == 0)
		{
			_curChar = (*it);
			break;
		}
	}
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		(*it)->setCurWait((*it)->getCurWait() - _curChar->getCurWait());
	}
	return S_OK;
}

void TurnSystem::update(int tileInfo[][60], int rowN, int colN, POINT cursorTile)
{
	_frame++;
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		(*it)->update();
	}

	if (!_curChar->isDoing())
	{	
		if(_curChar->getType() == 0)
		{
			tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = SALADIN;
		}
		else if (_curChar->getType() == 1)
		{
			tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = ENEMY;
		}
		if (!_curChar->canMove() && !_curChar->canAction())
		{
			nextTurn();
		}
		if(_curChar->getType() == 0)
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
					_attackTiles.push_back({curPos.x - 2, curPos.y});
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
								routes.push_back( _aStar->findRoute(_curChar->getTilePos(), { cursorTile.x - 2, cursorTile.y }, tileInfo, rowN, colN));
							}
							if (cursorTile.x < colN - 2 && (tileInfo[cursorTile.y][cursorTile.x + 2] == MOVABLE || tileInfo[cursorTile.y][cursorTile.x + 2] == SALADIN))
							{
								routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x + 2, cursorTile.y }, tileInfo, rowN, colN));
								//if ((route.size() > 0 && route.size() > temp.size()) || route.size() == 0)
								//{
								//	route = temp;
								//}
							}
							if (cursorTile.y > 1 && (tileInfo[cursorTile.y - 2][cursorTile.x] == MOVABLE || tileInfo[cursorTile.y - 2][cursorTile.x] == SALADIN))
							{
								routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x, cursorTile.y - 2 }, tileInfo, rowN, colN));
								//if ((route.size() > 0 && route.size() > temp.size()) || route.size() == 0)
								//{
								//	route = temp;
								//}
							}
							if (cursorTile.y < rowN - 2 && (tileInfo[cursorTile.y + 2][cursorTile.x] == MOVABLE || tileInfo[cursorTile.y + 2][cursorTile.x] == SALADIN))
							{
								routes.push_back(_aStar->findRoute(_curChar->getTilePos(), { cursorTile.x, cursorTile.y + 2 }, tileInfo, rowN, colN));
								//if ((route.size() > 0 && route.size() > temp.size()) || route.size() == 0)
								//{
								//	route = temp;
								//}
							}
							route = routes[0];
							for (auto it = routes.begin(); it != routes.end(); ++it)
							{
								if (route.size() > (*it).size())
								{
									route = (*it);
								}
							}
							if(route.size() > 0)
							{
								_curChar->setState(3);
							}
							else
							{
								_curChar->setState(2);
							}
							_curChar->setDoing(true);
							_curChar->setRoute(route);
							_curChar->setdestTilePos(cursorTile);
							tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
						}
						if (tileInfo[cursorTile.y][cursorTile.x] == SALADIN)
						{
							_actionChoice = true;
						}
						if (_actionChoice)
						{
							if (PtInRect(&_actionButtons[2], _ptMouse))
							{
								_actionChoice = false;
								nextTurn();
							}
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
								_curChar->setdestTilePos(cursorTile);
								//_curChar->setDir(RIGHT);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
							if ((cursorTile.x - _curChar->getTilePos().x == -2) && (cursorTile.y == _curChar->getTilePos().y))
							{
								_curChar->setdestTilePos(cursorTile);
								//_curChar->setDir(LEFT);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
							if ((cursorTile.y - _curChar->getTilePos().y == 2) && (cursorTile.x == _curChar->getTilePos().x))
							{
								_curChar->setdestTilePos(cursorTile);
								//_curChar->setDir(DOWN);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
							if ((cursorTile.y - _curChar->getTilePos().y == -2) && (cursorTile.x == _curChar->getTilePos().x))
							{
								_curChar->setdestTilePos(cursorTile);
								//_curChar->setDir(UP);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
						}
						if (tileInfo[cursorTile.y][cursorTile.x] == SALADIN)
						{
							_actionChoice = true;
						}
						if (_actionChoice)
						{
							if (PtInRect(&_actionButtons[2], _ptMouse))
							{
								_actionChoice = false;
								nextTurn();
							}
						}
					}
				}
			}
		}
		else if(_curChar->getType() == 1)
		{	
			if(_frame / 10 == 8)
			{
				_enemy = (Enemy*)_curChar;
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
				_curChar->setdestTilePos(player);
				tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
			}
		}
	}
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
		}
	}
}

void TurnSystem::release(void)
{
	SAFE_DELETE(_aStar);
}

void TurnSystem::render(HDC hdc, int tileHeight, int tileWidth, POINT cameraPos)
{
	if (_curChar->getType() == 0)
	{
		if(!_curChar->isDoing())
		{
			if (_curChar->canMove())
			{
				_player = (Saladin*)_curChar;
				vector<POINT> tiles = _player->getMovableTiles();
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
			else 
			{
				if (_curChar->canAction())
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
	sortObjectList();
	for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
	{
		if ((*it)->getType() == 2)
		{
			Obstacle* obstacle = (Obstacle*)(*it);
			obstacle->render(hdc, cameraPos);
		}
		else
		{
			Character* temp = (Character*)(*it);
			temp->render(hdc, { WINSIZE_X / 2 - (cameraPos.x - temp->getTilePos().x * tileWidth),
				WINSIZE_Y / 2 - (cameraPos.y - temp->getTilePos().y * tileHeight + tileHeight / 2 * 3) });
		}
	}
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
	if (_actionChoice)
	{
		POINT curPos = _curChar->getTilePos();
		_actionButtons[0] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) - 80, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) - 30, 100, 30);
		_actionButtons[1] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) - 80, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) + 15, 100, 30);
		_actionButtons[2] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) + 120, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) - 30, 100, 30);
		_actionButtons[3] = RectMakeCenter(WINSIZE_X / 2 - (cameraPos.x - curPos.x * tileWidth) + 120, WINSIZE_Y / 2 - (cameraPos.y - curPos.y * tileHeight) + 15, 100, 30);
		char* actionStr[4] = {"어빌리티", "아이템", "휴 식", "상 태"};
		for (int i = 0; i < 4; i++)
		{
			IMAGEMANAGER->findImage("ActionButton")->render(hdc, _actionButtons[i].left, _actionButtons[i].top);
			IMAGEMANAGER->findImage("ActionIcon")->frameRender(hdc, _actionButtons[i].left + 10, _actionButtons[i].top, i, 0);
			FONTMANAGER->textOut(hdc, _actionButtons[i].left + 35, _actionButtons[i].top + 5, "가을체", 15, 100, actionStr[i], strlen(actionStr[i]), RGB(255, 255, 255));
		}
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
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		(*it)->setCurWait((*it)->getCurWait() - _curChar->getCurWait());
	}
	_curChar->resetTurn();
}

void TurnSystem::sortObjectList()
{
	for (int i = 0; i < _objectList.size() - 1; i++)
	{
		int y = _objectList[i]->getTilePos().y;
		for (int j = i + 1; j < _objectList.size(); j++)
		{
			if (y > _objectList[j]->getTilePos().y)
			{
				Object* temp;
				temp = _objectList[j];
				_objectList[j] = _objectList[i];
				_objectList[i] = temp;
			}
			else if (y == _objectList[j]->getTilePos().y)
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
				}
			}
		}
	}
}
