#include "Stdafx.h"
#include "TurnSystem.h"

HRESULT TurnSystem::init(void)
{
	_aStar = new AStar();
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
	return S_OK;
}

void TurnSystem::update(int tileInfo[][60], int rowN, int colN, POINT cursorTile)
{
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		(*it)->update();
	}

	if (!_curChar->isDoing())
	{	
		//cout << _curChar->getTilePos().x << "\t" <<_curChar->getTilePos().y<<endl;
		if(_curChar->getType() == 0)
		{
			tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = SALADIN;
		}
		else
		{
			tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = ENEMY;
		}
		if (!_curChar->canMove() && !_curChar->canAction())
		{
			nextTurn();
		}
		if(_curChar->getType() == 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_curChar->canMove())
				{
					if (_curChar->canAction())
					{
						if (tileInfo[cursorTile.y][cursorTile.x] == ENEMY)
						{
							_curChar->setState(3);
							_curChar->setDoing(true);
							vector<POINT> route;
							vector<POINT> temp;
							//POINT dest;
							if (cursorTile.x > 1 && (tileInfo[cursorTile.y][cursorTile.x - 2] == MOVABLE || tileInfo[cursorTile.y][cursorTile.x - 2] == SALADIN))
							{
								route = _aStar->findRoute(_curChar->getTilePos(), { cursorTile.x - 2, cursorTile.y }, tileInfo, rowN, colN);
								//dest = { cursorTile.x - 2, cursorTile.y };
							}
							if (cursorTile.x < colN - 2 && (tileInfo[cursorTile.y][cursorTile.x + 2] == MOVABLE || tileInfo[cursorTile.y][cursorTile.x + 2] == SALADIN))
							{
								temp = _aStar->findRoute(_curChar->getTilePos(), { cursorTile.x + 2, cursorTile.y }, tileInfo, rowN, colN);
								if (route.size() > 0 && route.size() > temp.size())
								{
									route = temp;
									//dest = { cursorTile.x + 2, cursorTile.y };
								}
							}
							if (cursorTile.y > 1 && (tileInfo[cursorTile.y - 2][cursorTile.x] == MOVABLE || tileInfo[cursorTile.y - 2][cursorTile.x] == SALADIN))
							{
								temp = _aStar->findRoute(_curChar->getTilePos(), { cursorTile.x, cursorTile.y - 2 }, tileInfo, rowN, colN);
								if (route.size() > 0 && route.size() > temp.size())
								{
									route = temp;
									//dest = { cursorTile.x, cursorTile.y - 2 };
								}
							}
							if (cursorTile.y < rowN - 2 && (tileInfo[cursorTile.y + 2][cursorTile.x] == MOVABLE || tileInfo[cursorTile.y + 2][cursorTile.x] == SALADIN))
							{
								temp = _aStar->findRoute(_curChar->getTilePos(), { cursorTile.x, cursorTile.y + 2 }, tileInfo, rowN, colN);
								if (route.size() > 0 && route.size() > temp.size())
								{
									route = temp;
									//dest = { cursorTile.x, cursorTile.y + 2 };
								}
							}
							_curChar->setRoute(route);
							_curChar->setdestTilePos(cursorTile);
							tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
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
								_curChar->setDir(RIGHT);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
							if ((cursorTile.x - _curChar->getTilePos().x == -2) && (cursorTile.y == _curChar->getTilePos().y))
							{
								_curChar->setDir(LEFT);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
							if ((cursorTile.y - _curChar->getTilePos().y == 2) && (cursorTile.x == _curChar->getTilePos().x))
							{
								_curChar->setDir(DOWN);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
							if ((cursorTile.y - _curChar->getTilePos().y == -2) && (cursorTile.x == _curChar->getTilePos().x))
							{
								_curChar->setDir(UP);
								_curChar->setState(2);
								_curChar->setDoing(true);
							}
						}
						else
						{
							nextTurn();
						}
					}
				}
			}
		}
		else
		{
			_enemy = (Enemy*)_curChar;
			_enemy->setState(3);
			_enemy->setDoing(true);
			POINT player = _enemy->findPlayer(tileInfo, rowN, colN);
			vector<POINT> route;
			vector<POINT> temp;
			if (player.x > 1 && (tileInfo[player.y][player.x - 2] == MOVABLE || (_enemy->getTilePos().x == player.x - 2 && _enemy->getTilePos().y == player.y)))
			{
				route = _aStar->findRoute(_curChar->getTilePos(), { player.x - 2, player.y }, tileInfo, rowN, colN);
				//dest = { player.x - 2, player.y };
			}
			if (player.x < colN - 2 && (tileInfo[player.y][player.x + 2] == MOVABLE || (_enemy->getTilePos().x == player.x + 2 && _enemy->getTilePos().y == player.y)))
			{
				temp = _aStar->findRoute(_curChar->getTilePos(), { player.x + 2, player.y }, tileInfo, rowN, colN);
				if (route.size() > temp.size() || route.size() == 0)
				{
					route = temp;
					//dest = { player.x + 2, player.y };
				}
			}
			if (player.y > 1 && (tileInfo[player.y - 2][player.x] == MOVABLE || (_enemy->getTilePos().x == player.x && _enemy->getTilePos().y == player.y - 2)))
			{
				temp = _aStar->findRoute(_curChar->getTilePos(), { player.x, player.y - 2 }, tileInfo, rowN, colN);
				if (route.size() > temp.size() || route.size() == 0)
				{
					route = temp;
					//dest = { player.x, player.y - 2 };
				}
			}
			if (player.y < rowN - 2 && (tileInfo[player.y + 2][player.x] == MOVABLE || (_enemy->getTilePos().x == player.x && _enemy->getTilePos().y == player.y + 2)))
			{
				temp = _aStar->findRoute(_curChar->getTilePos(), { player.x, player.y + 2 }, tileInfo, rowN, colN);
				if (route.size() > temp.size() || route.size() == 0)
				{
					route = temp;
					//dest = { player.x, player.y + 2 };
				}
			}
			_curChar->setRoute(route);
			_curChar->setdestTilePos(player);
			tileInfo[_curChar->getTilePos().y][_curChar->getTilePos().x] = MOVABLE;
		}
	}
	//_movableTiles = _curChar->searchMovable(tileInfo, rowN, colN);
}

void TurnSystem::release(void)
{
	SAFE_DELETE(_aStar);
}

void TurnSystem::render(HDC hdc, int tileHeight, int tileWidth, POINT cameraPos)
{
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		(*it)->render(hdc, { WINSIZE_X / 2 - (cameraPos.x - (*it)->getTilePos().x * tileWidth),
	WINSIZE_Y / 2 - (cameraPos.y - (*it)->getTilePos().y * tileHeight + tileHeight / 2 * 3) });
	}
}

void TurnSystem::addCharacter(Character* character)
{
	_charList.push_back(character);
}

void TurnSystem::nextTurn()
{
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
