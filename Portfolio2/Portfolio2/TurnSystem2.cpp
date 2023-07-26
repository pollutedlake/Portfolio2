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
    }
    for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
    {
        if ((*it)->getType() != 2)
        {
            Character* character = (Character*)(*it);
            character->update();
        }
    }
    if (checkAllDoingNot())
    {
        if (_curChar->getType() == PLAYER)
        {
            if (_curChar->canMove())
            {
                searchMovableTiles();
            }
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

                }
                else
                {
                    if (_curChar->canMove())
                    {
                        if (_curChar->canAction())
                        {
                            if (checkTile(cursorTile) == ENEMY)
                            {
                                
                            }
                        }
                        if (checkTile(cursorTile) == MOVABLE)
                        {
                            _curChar->setState(1);
                            _curChar->setDoing(true);
                            //_curChar->setRoute()
                        }
                    }
                }
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
                        IMAGEMANAGER->findImage("MovableTile")->alphaRender(hdc, _camera->worldToCamera({(*it).x * TILEWIDTH, (*it).y * TILEHEIGHT}).x,
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
