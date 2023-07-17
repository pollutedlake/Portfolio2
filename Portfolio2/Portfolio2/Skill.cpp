#include "Stdafx.h"
#include "Skill.h"

HRESULT Skill::init(void)
{
	_frame = 0;
	_isFinish = true;
	_order.reset();
	return S_OK;
}

void Skill::update(void)
{
	_frame++;
	if(_order.test(0))
	{
		if ((_frame - 1) / 2 > IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX())
		{
			_order = _order << 1;
			_frame = 0;
			_curChar->setSkillOrder(1);
		}
	}
	else if (_order.test(1))
	{
		if (_frame == 1)
		{
			for(int i = 0; i < IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() + 1; i++)
			{
				_efxPos.push_back(make_pair(PointMake(_curChar->getX(), _curChar->getY()), PointMake(_curChar->getX(), _curChar->getY())));
			}
		}
		if ((_frame - 1) / 3 > 17)
		{
			_order = _order << 1;
			_curChar->setSkillOrder(2);
			_frame = 0;
			for (auto it = _charList.begin(); it != _charList.end(); ++it)
			{
				if ((*it)->getType() == 0)
				{
					_curChar->setDestTilePos((*it)->getTilePos());
					break;
				}
			}
		}
	}
	else if (_order.test(2))
	{
		_efxPos[IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX()].first = PointMake(_curChar->getX(), _curChar->getY());
		if (_frame % 2 == 0)
		{
			for (int i = 0; i < IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() + 1; i++)
			{
				_efxPos[i].second = _efxPos[i].first;
			}
		}
		for (int i = IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() - 1; i >= 0; i--)
		{
			_efxPos[i].first = _efxPos[i + 1].second;
		}
		
	}
}

void Skill::render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight)
{
	if(_order.test(0))
	{
		IMAGEMANAGER->findImage("SkillCasting")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SkillCasting")->getFrameWidth() / 2 + 10, 
		position.y - IMAGEMANAGER->findImage("SkillCasting")->getFrameHeight() / 2 + 30, (_frame - 1) / 2 % (IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX() +  1), 0, 200);
	}
	else if (_order.test(1))
	{
		for(int i = 0; i < _efxPos.size(); i++)
		{
			IMAGEMANAGER->findImage("VermontSkillEFX2")->alphaFrameRender(hdc, 
			WINSIZE_X / 2 - (cameraPos.x - (_efxPos[i].first.x - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameWidth() / 2)),
			WINSIZE_Y / 2 - (cameraPos.y - (_efxPos[i].first.y - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameHeight() / 2 - 30)), 
			IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() - i, 0, 20);
		}
		for (auto it = _charList.begin(); it != _charList.end(); ++it)
		{
			if ((*it)->getType() == 1) {
				continue;
			}
			IMAGEMANAGER->findImage("VermontSkillEFX1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)->getTilePos().x * tileWidth) - 25, 
				WINSIZE_Y / 2 - (cameraPos.y - (*it)->getTilePos().y * tileHeight) - 85, (_frame - 1) / 3 > 16 ? 15 : (_frame - 1) / 3, 0, 150);
		}
	}
	else if (_order.test(2))
	{
		for (int i = 0; i < _efxPos.size(); i++)
		{
			IMAGEMANAGER->findImage("VermontSkillEFX2")->alphaFrameRender(hdc,
				WINSIZE_X / 2 - (cameraPos.x - (_efxPos[i].first.x - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameWidth() / 2)),
				WINSIZE_Y / 2 - (cameraPos.y - (_efxPos[i].first.y - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameHeight() / 2 - 30)),
				IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() - i, 0, 20);
		}
		for (auto it = _charList.begin(); it != _charList.end(); ++it)
		{
			if ((*it)->getType() == 1)
			{
				continue;
			}
			IMAGEMANAGER->findImage("VermontSkillEFX1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)->getTilePos().x * tileWidth) - 25,
				WINSIZE_Y / 2 - (cameraPos.y - (*it)->getTilePos().y * tileHeight) - 85, 15, 0, 150);
		}
	}
}

void Skill::release(void)
{
}

int Skill::getOrder()
{
	for (int i = 0; i < _order.size(); i++)
	{
		if (_order.test(i))
		{
			return i;
		}
	}
}

void Skill::start(vector<Character*> charList, Character* curChar)
{
	_frame = 0;
	_charList = charList;
	_order.set(0);
	_isFinish = false;
	_curChar = curChar;
	_curChar->setSkillOrder(0);
}
