#include "Stdafx.h"
#include "TurnSystem2.h"

HRESULT TurnSystem2::init(Camera* camera)
{
    _camera = camera;
    return S_OK;
}

void TurnSystem2::release(void)
{
}

void TurnSystem2::update(void)
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
}

void TurnSystem2::render(HDC hdc)
{
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
    character->init();
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
