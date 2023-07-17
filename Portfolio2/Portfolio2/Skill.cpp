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
	static Character* target;
	if(_order.test(0))
	{
		if (_frame == 1)
		{
			SOUNDMANAGER->playSoundFMOD("SkillCasting");
		}
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
			for (auto it = _charList.begin(); it != _charList.end(); ++it)
			{
				if ((*it)->getType() == 1) {
					continue;
				}
				IcePillar icePillar;
				icePillar._position = PointMake((*it)->getTilePos().x * 40, (*it)->getTilePos().y * 30);
				_icePillars.push_back(icePillar);
			}
		}
		for (auto it = _icePillars.begin(); it != _icePillars.end(); ++it)
		{
			if(_frame % 3 == 0)
			{
				if((*it)._frame < 15)
				{
					(*it)._frame++;
				}
			}
		}
		if ((_frame - 1) / 3 > 17)
		{
			_order = _order << 1;
			_curChar->setSkillOrder(2);
			_frame = 0;
			for (auto it = _charList.begin(); it != _charList.end();)
			{
				if ((*it)->getType() == 0)
				{
					_curChar->setDestTilePos((*it)->getTilePos());
					target = (*it);
					it = _charList.erase(it);
					break;
				}
				else
				{
					++it;
				}
			}
		}
	}
	else if (_order.test(2))
	{
		static int endFrame;
		_efxPos[IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX()].first = PointMake(_curChar->getX(), _curChar->getY());
		if (_frame % 3 == 0)
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
		static float angle;
		if (_frame == 1)
		{
			angle = atan2((float)_curChar->getDestTilePos().x * 40 + 20 - _curChar->getX(), (float)_curChar->getDestTilePos().y * 30 + 20 - _curChar->getY());
			endFrame = 0;
		}
		if(_frame % 3 == 0)
		{
			for (auto it = _icePillars.begin(); it != _icePillars.end();)
			{
				if ((*it)._frame > IMAGEMANAGER->findImage("VermontSkillEFX1")->getMaxFrameX())
				{
					it = _icePillars.erase(it);
				}
				else
				{
					if ((*it)._broken)
					{
						(*it)._frame++;
					}
					++it;
				}
			}
		}
		float curAngle = atan2((float)_curChar->getDestTilePos().x * 40 + 20 - _curChar->getX(), (float)_curChar->getDestTilePos().y * 30 + 20 - _curChar->getY());
		if (curAngle != angle && curAngle * angle <= 0)
		{
			if(endFrame == 0)
			{
				endFrame = _frame;
			}
			if (SamePoint(_curChar->getDestTilePos(), PointMake(_curChar->getTilePos().x, _curChar->getTilePos().y)))
			{
				_order = _order << 1;
				_curChar->setSkillOrder(3);
				_frame = 0;
			}
			if(endFrame + 20 < _frame && endFrame != 0)
			{
				for (auto it = _charList.begin(); it != _charList.end();)
				{
					if ((*it)->getType() == 0)
					{
						target->setDamage(100);
						target->setState(4);
						target = (*it);
						_curChar->setDestTilePos((*it)->getTilePos());
						_curChar->setSkillOrder(2);
						endFrame = 0;
						angle = atan2((float)_curChar->getDestTilePos().x * 40 + 20 - _curChar->getX(), (float)_curChar->getDestTilePos().y * 30 + 20 - _curChar->getY());
						it = _charList.erase(it);
						for (auto it2 = _icePillars.begin(); it2 != _icePillars.end(); ++it2)
						{
							if (!(*it2)._broken)
							{
								SOUNDMANAGER->playSoundFMOD("BreakIce");
								(*it2)._broken = true;
								break;
							}
						}
						break;
					}
					else
					{
						++it;
					}
					if (it == _charList.end() && _order.test(2))
					{
						_curChar->setDestTilePos(_curChar->getTilePos());
						target->setDamage(100);
						target->setState(4);
						_curChar->setSkillOrder(2);
						angle = atan2((float)_curChar->getDestTilePos().x * 40 + 20 - _curChar->getX(), (float)_curChar->getDestTilePos().y * 30 + 20 - _curChar->getY());
						if(_icePillars.size() > 0)
						{
							SOUNDMANAGER->playSoundFMOD("BreakIce");
						}
					}
				}
			}
		}
	}
	else if (_order.test(3))
	{
		_efxPos[IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX()].first = PointMake(_curChar->getX(), _curChar->getY());
		if (_frame % 3 == 0)
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
		if (_frame % 3 == 0)
		{
			for (auto it = _icePillars.begin(); it != _icePillars.end();)
			{
				if ((*it)._frame > IMAGEMANAGER->findImage("VermontSkillEFX1")->getMaxFrameX())
				{
					it = _icePillars.erase(it);
				}
				else
				{
					if ((*it)._broken)
					{
						(*it)._frame++;
					}
					++it;
				}
			}
		}
		if (SamePoint(_efxPos[_efxPos.size() - 1].first, _efxPos[0].first))
		{
			_isFinish = true;
			_curChar->setState(0);
			_curChar->setDir(DOWN);
			_curChar->endTurn();
			_curChar->setDoing(false);
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
		for (auto it = _icePillars.begin(); it != _icePillars.end(); ++it)
		{
			IMAGEMANAGER->findImage("VermontSkillEFX1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)._position.x) - 25,
				WINSIZE_Y / 2 - (cameraPos.y - (*it)._position.y) - 85, (*it)._frame, 0, 150);
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
		for (auto it = _icePillars.begin(); it != _icePillars.end(); ++it)
		{
			IMAGEMANAGER->findImage("VermontSkillEFX1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)._position.x) - 25,
				WINSIZE_Y / 2 - (cameraPos.y - (*it)._position.y) - 85, (*it)._frame, 0, 150);
		}
	}
	else if (_order.test(3))
	{
		for (int i = 0; i < _efxPos.size(); i++)
		{
			if(SamePoint(_efxPos[i].first, PointMake(_curChar->getX(), _curChar->getY())))
			{
				continue;
			}
			IMAGEMANAGER->findImage("VermontSkillEFX2")->alphaFrameRender(hdc,
				WINSIZE_X / 2 - (cameraPos.x - (_efxPos[i].first.x - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameWidth() / 2)),
				WINSIZE_Y / 2 - (cameraPos.y - (_efxPos[i].first.y - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameHeight() / 2 - 30)),
				IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() - i, 0, 20);
		}
		for (auto it = _icePillars.begin(); it != _icePillars.end(); ++it)
		{
			IMAGEMANAGER->findImage("VermontSkillEFX1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)._position.x) - 25,
				WINSIZE_Y / 2 - (cameraPos.y - (*it)._position.y) - 85, (*it)._frame, 0, 150);
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
