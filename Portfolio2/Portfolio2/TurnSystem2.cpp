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
	_isClear = false;
	_isFail = false;
	_skill = new Skill;
	_skill->init();
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
    // 모든 캐릭터가 행동중이 아닐 때
    if (checkAllDoingNot())
    {
        // 움직일 수도 없고 행동할 수도 없을 때 다음 턴
		if (!_curChar->canMove() && !_curChar->canAction())
		{
			if (checkAllDoingNot())
			{
				nextTurn();
			}
		}
        // 현재 캐릭터가 플레이어
        if (_curChar->getType() == PLAYER)
        {
            // 움직일 수 있으면 움직일 수 있는 타일들을 찾는다.
            if (_curChar->canMove())
            {
                searchMovableTiles();
            }
            // 움직일 수 없으면 상하좌우 2칸 떨어진 타일이 움직일 수 있는 타일이거나 적이 있는 타일이면 공격가능한 타일
            else
            {
                _attackableTiles.clear();
                if (checkTile({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y }) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x - 2, _curChar->getTilePos().y });
                }
                if (checkTile({ _curChar->getTilePos().x + 2, _curChar->getTilePos().y }) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x + 2, _curChar->getTilePos().y });
                }
                if (checkTile({ _curChar->getTilePos().x, _curChar->getTilePos().y - 2}) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x, _curChar->getTilePos().y - 2});
                }
                if (checkTile({ _curChar->getTilePos().x, _curChar->getTilePos().y + 2}) % 2 == 1)
                {
                    _attackableTiles.push_back({ _curChar->getTilePos().x, _curChar->getTilePos().y + 2});
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
							for (int i = 0; i < 3; i++)
							{
								_skillButtons[i].left = _camera->worldToCamera({ (_curChar->getTilePos().x + 2) * TILEWIDTH + 5, (_curChar->getTilePos().y - 2) * TILEHEIGHT + 5 + 23 * i }).x;
								_skillButtons[i].right = _skillButtons[i].left + 155;
								_skillButtons[i].top = _camera->worldToCamera({ (_curChar->getTilePos().x + 2) * TILEWIDTH + 5, (_curChar->getTilePos().y - 2) * TILEHEIGHT + 5 + 23 * i }).y;
								_skillButtons[i].bottom = _skillButtons[i].top + 20;
							}
						}
						if (PtInRect(&_actionButtons[2], _ptMouse))
						{
							_actionChoice.reset();
							_actionChoice.set(0);
							nextTurn();
						}
					}
					// 스킬 선택하고 스킬 범위 받기
					else if (_actionChoice.test(2))
					{
						for (int i = 0; i < 3; i++)
						{
							if (PtInRect(&_skillButtons[i], _ptMouse))
							{
								_actionChoice = _actionChoice << 1;
								//if (i == 0)
								//{
								//	_skillName = "천지파열무";
								//}
								//else if (i == 1)
								//{
								//	_skillName = "풍아열공참";
								//}
								//else if (i == 2)
								//{
								//	_skillName = "혈랑마혼";
								//}
								//_skillableTiles = ((Saladin*)(_curChar))->getSkillableTiles(tileInfo, 90, 60, _skillName);
							}
						}
					}
					else if (_actionChoice.test(3))
					{

					}
                }
                else
                {
                    // Player가 움직일 수도 행동을 할 수도 있을 때
                    if (_curChar->canMove())
                    {
                        if (_curChar->canAction())
                        {
                            // 클릭한 타일에 적이 있을 경우 상하좌우 2칸 떨어진 곳 검사해서 가장 가까운 경로 찾기
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
                            // 현재 플레이어 캐릭터 타일 선택 시 행동 고르는 UI 생성
                            if (SamePoint(cursorTile, _curChar->getTilePos()))
                            {
                                _actionChoice = _actionChoice << 1;
                            }
                        }
                        // 움직일 수 있는 타일일 시 경로 astar로 구하고 이동
                        if (checkTile(cursorTile) == MOVABLE)
                        {
                            _curChar->setState(1);
                            _curChar->setDoing(true);
                            _curChar->setRoute(astar(_curChar->getTilePos(), cursorTile));
                        }
                    }
                    // 움직일 수는 없고 행동할 수는 있을 때
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
			// 행동 선택 되돌리기
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				if (!_actionChoice.test(0))
				{
					_actionChoice = _actionChoice >> 1;
				}
			}
        }
		// 적의 행동패턴
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
					for (auto it = _skillableTiles.begin(); it != _skillableTiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("SkillableTile")->render(hdc, _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).x, _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).y, TILEWIDTH, TILEHEIGHT,
							0, 0, IMAGEMANAGER->findImage("SkillableTile")->getWidth(), IMAGEMANAGER->findImage("SkillableTile")->getHeight());
					}
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
			else
			{
				if (_actionChoice.test(3))
				{
					for (auto it = _skillableTiles.begin(); it != _skillableTiles.end(); ++it)
					{
						IMAGEMANAGER->findImage("SkillableTile")->render(hdc, _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).x, _camera->worldToCamera({ (*it).x * TILEWIDTH, (*it).y * TILEHEIGHT }).y, TILEWIDTH, TILEHEIGHT,
							0, 0, IMAGEMANAGER->findImage("SkillableTile")->getWidth(), IMAGEMANAGER->findImage("SkillableTile")->getHeight());
					}
				}
				else if (_curChar->canAction())
				{
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
	// y 좌표에 따라 캐릭터들 정렬
	sortObjectList();
	// Object들 렌더
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
				IMAGEMANAGER->findImage("PlayerMarker")->frameRender(hdc, _camera->worldToCamera({ _curChar->getTilePos().x * TILEWIDTH + 15, _curChar->getTilePos().y * TILEHEIGHT - 70 }).x, 
					_camera->worldToCamera({ _curChar->getTilePos().x * TILEWIDTH + 15, _curChar->getTilePos().y * TILEHEIGHT - 70 }).y, (_frame / 5) % 8, 0);
			}
			else if (_curChar->getType() == 1)
			{
				IMAGEMANAGER->findImage("EnemyMarker")->frameRender(hdc, _camera->worldToCamera({ _curChar->getTilePos().x * TILEWIDTH + 15, _curChar->getTilePos().y * TILEHEIGHT - 70 }).x,
					_camera->worldToCamera({ _curChar->getTilePos().x * TILEWIDTH + 15, _curChar->getTilePos().y * TILEHEIGHT - 70 }).y, (_frame / 5) % 8, 0);
			}
		}
		if (!_skill->isFinish())
		{
			_skill->render(hdc, _camera->worldToCamera({ _curChar->getTilePos().x * TILEWIDTH, _curChar->getTilePos().y * TILEHEIGHT + TILEHEIGHT / 2 * 3 }), _camera->getPosition(), TILEWIDTH, TILEHEIGHT);
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
		char* actionStr[4] = { "어빌리티", "아이템", "휴 식", "상 태" };
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
	// 스킬 선택창
	else if (_actionChoice.test(2))
	{
		DIALOGMANAGER->makeTextBox(hdc, _camera->worldToCamera({ (_curChar->getTilePos().x + 2) * TILEWIDTH,  (_curChar->getTilePos().y - 2) * TILEHEIGHT }).x,
			_camera->worldToCamera({ (_curChar->getTilePos().x + 2) * TILEWIDTH,  (_curChar->getTilePos().y - 2) * TILEHEIGHT }).y, 160, 100, 128);
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_skillButtons[i], _ptMouse))
			{
				IMAGEMANAGER->findImage("SkillButtonActive")->alphaRender(hdc, _skillButtons[i].left,
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

Character* TurnSystem2::findCharacter(POINT cursorPoint)
{
	for (auto it = _charList.begin(); it != _charList.end(); ++it)
	{
		if (SamePoint(cursorPoint, (*it)->getTilePos()))
		{
			return (*it);
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
    if (GetPixel(_tileCheckDC, tilePos.x * TILEWIDTH + TILEWIDTH / 2, tilePos.y * TILEHEIGHT + TILEHEIGHT / 2) == RGB(255, 0, 255))
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
                if (!tileCheck[node.y - 1].test(node.x))
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
