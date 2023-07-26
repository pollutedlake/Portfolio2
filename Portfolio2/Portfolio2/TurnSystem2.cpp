#include "Stdafx.h"
#include "TurnSystem2.h"

HRESULT TurnSystem2::init(Camera* camera, HDC hdc, int rowN, int colN)
{
    _camera = camera;
    _tileCheckDC = hdc;
    _rowN = rowN;
    _colN = colN;
    _actionChoice.reset();
    _actionChoice.set(0);
    _frame = 0;
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

void TurnSystem2::release(void)
{
}

void TurnSystem2::update(POINT cursorTile)
{
    _frame++;
    if (_frame == 1)
    {

    }
    for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
    {
        if ((*it)->getType() != 2)
        {
            Character* character = (Character*)(*it);
            character->update();
        }
    }
    // ��� ĳ���Ͱ� �ൿ���� �ƴ� ��
    if (checkAllDoingNot())
    {
        // ������ ���� ���� �ൿ�� ���� ���� �� ���� ��
		if (!_curChar->canMove() && !_curChar->canAction())
		{
			if (checkAllDoingNot())
			{
				nextTurn();
			}
		}
        // ���� ĳ���Ͱ� �÷��̾�
        if (_curChar->getType() == PLAYER)
        {
            // ������ �� ������ ������ �� �ִ� Ÿ�ϵ��� ã�´�.
            if (_curChar->canMove())
            {
                searchMovableTiles();
            }
            // ������ �� ������ �����¿� 2ĭ ������ Ÿ���� ������ �� �ִ� Ÿ���̰ų� ���� �ִ� Ÿ���̸� ���ݰ����� Ÿ��
            else
            {
                _attackableTiles.clear();
                if (checkTile({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y }) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y });
                }
                if (checkTile({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y }) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y });
                }
                if (checkTile({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y }) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y });
                }
                if (checkTile({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y }) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y });
                }
            }
            if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
            {
                if (!_actionChoice.test(0))
                {
					if (_actionChoice.test(1))
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
                }
                else
                {
                    // Player�� ������ ���� �ൿ�� �� ���� ���� ��
                    if (_curChar->canMove())
                    {
                        if (_curChar->canAction())
                        {
                            // Ŭ���� Ÿ�Ͽ� ���� ���� ��� �����¿� 2ĭ ������ �� �˻��ؼ� ���� ����� ��� ã��
                            if (checkTile(cursorTile) == ENEMY)
                            {
                                vector<vector<POINT>> routes;
                                vector<POINT> route;
                                if (cursorTile.x > 1 && checkTile({ cursorTile.x - 2, cursorTile.y }) % 3 == 0)
                                {
                                    routes.push_back(astar(_curChar->getTilePos(), {cursorTile.x - 2, cursorTile.y}));
                                }
								if (cursorTile.x < _colN - 2 && checkTile({ cursorTile.x + 2, cursorTile.y }) % 3 == 0)
								{
									routes.push_back(astar(_curChar->getTilePos(), { cursorTile.x + 2, cursorTile.y }));
								}
								if (cursorTile.y > 1 && checkTile({ cursorTile.x, cursorTile.y - 2 }) % 3 == 0)
								{
									routes.push_back(astar(_curChar->getTilePos(), { cursorTile.x, cursorTile.y - 2 }));
								}
								if (cursorTile.y < _rowN - 2 && checkTile({ cursorTile.x, cursorTile.y + 2 }) % 3 == 0)
								{
									routes.push_back(astar(_curChar->getTilePos(), { cursorTile.x, cursorTile.y + 2 }));
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
                            }
                            // ���� �÷��̾� ĳ���� Ÿ�� ���� �� �ൿ ���� UI ����
                            if (SamePoint(cursorTile, _curChar->getTilePos()))
                            {
                                _actionChoice = _actionChoice << 1;
                            }
                        }
                        // ������ �� �ִ� Ÿ���� �� ��� astar�� ���ϰ� �̵�
                        if (checkTile(cursorTile) == MOVABLE)
                        {
                            _curChar->setState(1);
                            _curChar->setDoing(true);
                            _curChar->setRoute(astar(_curChar->getTilePos(), cursorTile));
                        }
                    }
                    // ������ ���� ���� �ൿ�� ���� ���� ��
                    else
                    {
                        if (_curChar->canAction())
                        {
                            if (checkTile(cursorTile) == ENEMY)
                            {
								if (SamePoint(cursorTile, {_curChar->getTilePos().x + 2, _curChar->getTilePos().y}))
								{
									_curChar->setDestTilePos(cursorTile);
									_curChar->setState(2);
									_curChar->setDoing(true);
								}
								if (SamePoint(cursorTile, { _curChar->getTilePos().x - 2, _curChar->getTilePos().y }))
								{
									_curChar->setDestTilePos(cursorTile);
									_curChar->setState(2);
									_curChar->setDoing(true);
								}
								if (SamePoint(cursorTile, { _curChar->getTilePos().x, _curChar->getTilePos().y + 2}))
								{
									_curChar->setDestTilePos(cursorTile);
									_curChar->setState(2);
									_curChar->setDoing(true);
								}
								if (SamePoint(cursorTile, { _curChar->getTilePos().x, _curChar->getTilePos().y - 2}))
								{
									_curChar->setDestTilePos(cursorTile);
									_curChar->setState(2);
									_curChar->setDoing(true);
								}
                            }
							else if (checkTile(cursorTile) == PLAYER)
							{
								_actionChoice = _actionChoice << 1;
							}
                        }
                    }
                }
            }
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				if (!_actionChoice.test(0))
				{
					_actionChoice = _actionChoice >> 1;
				}
			}
        }
		else if (_curChar->getType() == ENEMY)
		{
			if (_frame / 10 == 8)
			{
				_curChar->setState(3);
				_curChar->setDoing(true);
				POINT player = findPlayer();
				vector<vector<POINT>> routes;
				vector<POINT> route;
				if (player.x > 1 && (checkTile({player.x - 2, player.y}) == MOVABLE || SamePoint(_curChar->getTilePos(), {player.x - 2, player.y})))
				{
					routes.push_back(astar(_curChar->getTilePos(), { player.x - 2, player.y }));
				}
				if (player.x < _colN - 2 && (checkTile({ player.x + 2, player.y }) == MOVABLE || SamePoint(_curChar->getTilePos(), {player.x + 2, player.y})))
				{
					routes.push_back(astar(_curChar->getTilePos(), { player.x + 2, player.y }));
				}
				if (player.y > 1 && (checkTile({ player.x, player.y - 2 }) == MOVABLE || SamePoint(_curChar->getTilePos(), {player.x, player.y - 2})))
				{
					routes.push_back(astar(_curChar->getTilePos(), { player.x, player.y - 2 }));
				}
				if (player.y < _rowN - 2 && (checkTile({ player.x, player.y + 2 }) == MOVABLE || SamePoint(_curChar->getTilePos(), {player.x, player.y + 2})))
				{
					routes.push_back(astar(_curChar->getTilePos(), { player.x, player.y + 2 }));
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
			}
		}
    }
}

void TurnSystem2::render(HDC hdc)
{
	if (_curChar->getType() == 0)
	{
		if (!_curChar->isDoing())
		{
			if (_curChar->canMove())
			{
				if (_actionChoice.test(3))
				{

				}
				else
				{
					for (auto it = _movableTiles.begin(); it != _movableTiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("MovableTile")->alphaRender(hdc, _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).x,
							_camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).y, TILEWIDTH, TILEHEIGHT, 0, 0,
							IMAGEMANAGER->findImage("MovableTile")->getWidth(), IMAGEMANAGER->findImage("MovableTile")->getHeight(), 128);
					}
					for (auto it = _attackableTiles.begin(); it != _attackableTiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("AttackableTile")->alphaRender(hdc, _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).x,
							_camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).y, TILEWIDTH, TILEHEIGHT, 0, 0,
							IMAGEMANAGER->findImage("AttackableTile")->getWidth(), IMAGEMANAGER->findImage("AttackableTile")->getHeight(), 128);
					}
				}
			}
		}
	}
	// y ��ǥ�� ���� ĳ���͵� ����
	sortObjectList();
	// Object�� ����
	for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
	{
		if ((*it)->getType() == 2)
		{
			Obstacle* obstacle = (Obstacle*)(*it);
			obstacle->render(hdc, _camera->getPosition());
		}
		else
		{
			Character* character = (Character*)(*it);
			character->render(hdc, { _camera->worldToCamera({ (*it)->getTilePos().x * TILEWIDTH, (*it)->getTilePos().y * TILEHEIGHT - TILEHEIGHT / 2 * 3}).x,
				_camera->worldToCamera({ (*it)->getTilePos().x * TILEWIDTH, (*it)->getTilePos().y * TILEHEIGHT - TILEHEIGHT / 2 * 3}).y }, _camera->getPosition());
		}
	}
	if (_actionChoice.test(1))
	{
		POINT curPos = _curChar->getTilePos();
		_actionButtons[0] = RectMakeCenter(_camera->worldToCamera({(curPos.x - 2) * TILEWIDTH, (curPos.y - 1) * TILEHEIGHT}).x, 
			_camera->worldToCamera({ (curPos.x - 2) * TILEWIDTH, (curPos.y - 1) * TILEHEIGHT }).y, 100, 30);
		_actionButtons[1] = RectMakeCenter(_camera->worldToCamera({ (curPos.x - 2) * TILEWIDTH, curPos.y * TILEHEIGHT + TILEHEIGHT / 2 }).x,
			_camera->worldToCamera({ (curPos.x - 2) * TILEWIDTH, curPos.y * TILEHEIGHT + TILEHEIGHT / 2 }).y, 100, 30);
		_actionButtons[2] = RectMakeCenter(_camera->worldToCamera({ (curPos.x + 3) * TILEWIDTH, (curPos.y - 1) * TILEHEIGHT }).x,
			_camera->worldToCamera({ (curPos.x + 3) * TILEWIDTH, (curPos.y - 1) * TILEHEIGHT }).y, 100, 30);
		_actionButtons[3] = RectMakeCenter(_camera->worldToCamera({ (curPos.x + 3) * TILEWIDTH, curPos.y * TILEHEIGHT + TILEHEIGHT / 2 }).x,
			_camera->worldToCamera({ (curPos.x + 3) * TILEWIDTH, curPos.y * TILEHEIGHT + TILEHEIGHT / 2 }).y, 100, 30);
		char* actionStr[4] = { "�����Ƽ", "������", "�� ��", "�� ��" };
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
			FONTMANAGER->textOut(hdc, _actionButtons[i].left + 35 + 3 * (strlen(actionStr[0]) - strlen(actionStr[i])), _actionButtons[i].top + 5, "����ü", 15, 100, actionStr[i], strlen(actionStr[i]), RGB(255, 255, 255));
		}
	}
}

void TurnSystem2::addCharacter(Character* character, int dir, POINT tilePos, int turnOrder)
{
    character->setDir(dir);
    character->setTilePos(tilePos);
    character->setTurnOder(turnOrder);
    _charList.push_back(character);
    addObject(character);
}

void TurnSystem2::addObject(Object* object)
{
    _objectList.push_back(object);
}

void TurnSystem2::sortObjectList()
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
				}
			}
		}
	}
}

int TurnSystem2::checkTile(POINT tilePos)
{
    if (GetPixel(_tileCheckDC, tilePos.x * TILEWIDTH, tilePos.y * TILEHEIGHT) == RGB(255, 0, 255))
    {
        return CANTMOVE;
    }
    else
    {
        for (auto it = _charList.begin(); it != _charList.end(); ++it)
        {
            if (SamePoint((*it)->getTilePos(), tilePos))
            {
                return ((*it)->getType());
            }
        }
    }
    return MOVABLE;
}

void TurnSystem2::searchMovableTiles()
{
    _movableTiles.clear();
    _attackableTiles.clear();
    int mobility = _curChar->getMobility();
    POINT node = _curChar->getTilePos();
    queue<POINT> closedList;
    closedList.push(node);
    bitset<100> tileCheck[100];
    for (int i = 0; i < 100; i++)
    {
        tileCheck[i].reset();
    }
    tileCheck[node.y].set(node.x);
    while (mobility >= -1)
    {
        int leafN = closedList.size();
        while (leafN--)
        {
            node = closedList.front();
            if (node.x > 0 && checkTile({ node.x - 1, node.y }) == MOVABLE)
            {
                if(!tileCheck[node.y].test(node.x - 1))
                {
                    if (mobility >= 0)
                    {
                        closedList.push({node.x - 1, node.y});
                    }
                    else
                    {
                        _attackableTiles.push_back({node.x - 1, node.y});
                    }
                    tileCheck[node.y].set(node.x - 1);
                }
            }
            else if (node.x > 0 && checkTile({ node.x - 1, node.y }) == ENEMY)
            {
                if (!tileCheck[node.y].test(node.x - 1))
                {
                    _attackableTiles.push_back({node.x - 1, node.y});
                    tileCheck[node.y].set(node.x - 1);
                }
            }
            if (node.x < _colN - 1 && checkTile({ node.x + 1, node.y }) == MOVABLE)
            {
                if (!tileCheck[node.y].test(node.x + 1))
                {
                    if (mobility >= 0)
                    {
                        closedList.push({node.x + 1, node.y});
                    }
                    else
                    {
                        _attackableTiles.push_back({node.x + 1, node.y});
                    }
                    tileCheck[node.y].set(node.x + 1);
                }
            }
            else if (node.x < _colN - 1 && checkTile({ node.x + 1, node.y }) == ENEMY)
            {
                if (!tileCheck[node.y].test(node.x + 1))
                {
                    _attackableTiles.push_back({node.x + 1, node.y});
                    tileCheck[node.y].set(node.x + 1);
                }
            }
            if (node.y > 0 && checkTile({ node.x, node.y - 1 }) == MOVABLE)
            {
                if (!tileCheck[node.y - 1].test(node.x))
                {
                    if (mobility >= 0)
                    {
                        closedList.push(POINT{ node.x, node.y - 1 });
                    }
                    else
                    {
                        _attackableTiles.push_back({ node.x, node.y - 1 });
                    }
                    tileCheck[node.y - 1].set(node.x);
                }
            }
            else if (node.y > 0 && checkTile({ node.x, node.y - 1 }) == ENEMY)
            {
                if (!tileCheck[node.y].test(node.x - 1))
                {
                    _attackableTiles.push_back(POINT{ node.x, node.y - 1 });
                    tileCheck[node.y - 1].set(node.x);
                }
            }
            if (node.y < _rowN - 1 && checkTile({ node.x, node.y + 1 }) == MOVABLE)
            {
                if (!tileCheck[node.y + 1].test(node.x))
                {
                    if (mobility >= 0)
                    {
                        closedList.push(POINT{ node.x, node.y + 1 });
                    }
                    else
                    {
                        _attackableTiles.push_back({ node.x, node.y + 1 });
                    }
                    tileCheck[node.y + 1].set(node.x);
                }
            }
            else if (node.y < _rowN - 1 && checkTile({ node.x, node.y + 1 }) == ENEMY)
            {
                if (!tileCheck[node.y + 1].test(node.x))
                {
                    _attackableTiles.push_back(POINT{ node.x, node.y + 1 });
                    tileCheck[node.y + 1].set(node.x);
                }
            }
            closedList.pop();
            if (mobility >= 0)
            {
                _movableTiles.push_back(node);
            }
            else
            {
                _attackableTiles.push_back(node);
            }
        }
        mobility--;
    }
    while (!closedList.empty())
    {
        node = closedList.front();
        closedList.pop();
        _attackableTiles.push_back(node);
    }
}

bool TurnSystem2::checkAllDoingNot()
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

POINT TurnSystem2::findPlayer()
{
	POINT node = _curChar->getTilePos();
	queue<POINT> closedList;
	closedList.push(node);
	bitset<100> tileCheck[100];
	for (int i = 0; i < 100; i++)
	{
		tileCheck[i].reset();
	}
	tileCheck[node.y].set(node.x);
	while (true)
	{
		int leafN = closedList.size();
		while (leafN--)
		{
			node = closedList.front();
			if (node.x > 0 && checkTile({node.x - 1, node.y}) == MOVABLE)
			{
				if (!tileCheck[node.y].test(node.x - 1))
				{
					closedList.push(POINT{ node.x - 1, node.y });
					tileCheck[node.y].set(node.x - 1);
				}
			}
			else if (node.x > 0 && checkTile({ node.x - 1, node.y }) == PLAYER)
			{
				return { node.x - 1, node.y };
			}
			if (node.x < _colN - 1 && checkTile({ node.x + 1, node.y }) == MOVABLE)
			{
				if (!tileCheck[node.y].test(node.x + 1))
				{
					closedList.push(POINT{ node.x + 1, node.y });
					tileCheck[node.y].set(node.x + 1);
				}
			}
			else if (node.x > 0 && checkTile({ node.x + 1, node.y }) == PLAYER)
			{
				return { node.x + 1, node.y };
			}
			if (node.y > 0 && checkTile({ node.x + 1, node.y }) == MOVABLE)
			{
				if (!tileCheck[node.y - 1].test(node.x))
				{
					closedList.push(POINT{ node.x, node.y - 1 });
					tileCheck[node.y - 1].set(node.x);
				}
			}
			else if (node.x > 0 && checkTile({ node.x + 1, node.y }) == PLAYER)
			{
				return { node.x, node.y - 1 };
			}
			if (node.y < _rowN - 1 && checkTile({ node.x + 1, node.y }) == MOVABLE)
			{
				if (!tileCheck[node.y + 1].test(node.x))
				{
					closedList.push(POINT{ node.x, node.y + 1 });
					tileCheck[node.y + 1].set(node.x);
				}
			}
			else if (node.x > 0 && checkTile({ node.x + 1, node.y }) == PLAYER)
			{
				return { node.x, node.y + 1 };
			}
			closedList.pop();
		}
	}
	return POINT();
}

void TurnSystem2::nextTurn()
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

vector<POINT> TurnSystem2::astar(POINT start, POINT dest)
{
	if (SamePoint(start, dest))
	{
		_route.clear();
		return _route;
	}
    int _distance[100][100];
    POINT _exNode[100][100];
	for (int i = 0; i < _rowN; i++)
	{
		for (int j = 0; j < _colN; j++)
		{
			_distance[i][j] = 999999;
		}
	}
	while (!_closedList.empty())
	{
		_closedList.pop();
	}
	_route.clear();
	_closedList.push(make_pair(start, heuristic(start, dest)));
	_distance[start.y][start.x] = heuristic(start, dest);
	while (!_closedList.empty())
	{
		POINT node = _closedList.top().first;
		if (SamePoint(node, dest))
		{
			break;
		}
		POINT next;
		if (node.x != 0)
		{
			next.x = node.x - 1;
			next.y = node.y;
			if (checkTile(next) == MOVABLE)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
                    _exNode[next.y][next.x] = node;
				}
			}
		}
		if (node.x != _colN - 1)
		{
			next.x = node.x + 1;
			next.y = node.y;
			if (checkTile(next) == MOVABLE)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		if (node.y != 0)
		{
			next.x = node.x;
			next.y = node.y - 1;
			if (checkTile(next) == MOVABLE)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		if (node.y != _rowN - 1)
		{
			next.x = node.x;
			next.y = node.y + 1;
			if (checkTile(next) == MOVABLE)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		_closedList.pop();
	}
	_route.push_back(dest);
	POINT temp = { dest.x, dest.y };
	while (distance(temp, start) != 0)
	{
		temp = _exNode[temp.y][temp.x];
		_route.push_back(temp);
		if (distance(temp, start) == 0)
		{
			_route.pop_back();
		}
	}
    return _route;
}

int TurnSystem2::heuristic(POINT node, POINT dest)
{
    return (abs(node.x - dest.x) + abs(node.y - dest.y)) * 10;
}

int TurnSystem2::distance(POINT start, POINT node)
{
	node.x -= start.x;
	node.y -= start.y;
	if (node.x == 0)
	{
		if (node.y == 0)
		{
			return 0;
		}
		else
		{
			return 10;
		}
	}
	if (node.y == 0)
	{
		return 10;
	}
	return 14;
}
