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
	// ����Ʈ ��ų ��ȭ������
	if(_curChar->getType() == 1)
	{
		static Character* target;
		if(_order.test(0))
		{
			if (_frame == 1)
			{
				_startFrame = 0;
			}
			if (_frame * 10 > 255)
			{
				_startFrame++;
			}
			if (_startFrame == 1)
			{
				SOUNDMANAGER->playSoundFMOD("SkillCasting");
			}
			if ((_startFrame - 1) / 2 > IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX())
			{
				_order = _order << 1;
				_frame = 0;
				_curChar->setSkillOrder(1);
				_startFrame = 0;
			}
		}
		else if (_order.test(1))
		{
			static int count;
			static bool intersect;
			if (_frame == 1)
			{
				SOUNDMANAGER->playSoundFMOD("Blizzard");
				count = 0;
				intersect = false;
				for(auto it = _charList.begin(); it != _charList.end(); ++it)
				{
					if((*it)->getType() == 0)
					{
						for (int i = 0; i < 9; i++)
						{
							float angle = RND->getFromFloatTo(315.f + 30.f * i, 315.f + 30.f * (i + 1));
							float radius = RND->getFloat(10.0f);
							_dust1Pos.push_back(make_pair(make_pair((float)(*it)->getTilePos().x * 40.f + 20.f + radius * cos(angle / 180.0f * PI), 
							(float)(*it)->getTilePos().y * 30.f + 15.f + radius * sin(angle / 180.0f * PI)), angle));
						}
						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 3; j++)
							{
								_dust2.push_back(make_pair(make_pair((float)((*it)->getTilePos().x - 2 + i + j) * 40.f + 20.f, 
								(float)((*it)->getTilePos().y - i + j) * 30.f + 15.f), 270.f));
							}
						}
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 2; j++)
							{
								_dust2.push_back(make_pair(make_pair((float)((*it)->getTilePos().x - 1 + i + j) * 40.f + 20.f,
									(float)((*it)->getTilePos().y - i + j) * 30.f + 15.f), -90.f));
							}
						}
					}
				}
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
			for (int i = 0; i < _dust2.size(); i++)
			{
				if (_dust2[i].second > 0)
				{
					_dust2[i].second -= 2.f;
					if(_dust2[i].second < 90.f)
					{
						_dust2[i].second = 90.f;
					}
				}
				else if (_dust2[i].second < 0)
				{
					_dust2[i].second += 2.f;
					if (_dust2[i].second > 90.f)
					{
						_dust2[i].second = 90.f;
					}
				}
			}
			if (_frame % 45 == 0 && count < 3)
			{
				count++;
				if (count == 3)
				{
					_startFrame = _frame;
				}
				for (auto it = _charList.begin(); it != _charList.end(); ++it)
				{
					if ((*it)->getType() == 0)
					{
						for (int i = 0; i < 9; i++)
						{
							float angle = RND->getFromFloatTo(315.f + 30.f * i, 315.f + 30.f * (i + 1));
							float radius = RND->getFloat(10.0f);
							_dust1Pos.push_back(make_pair(make_pair((float)(*it)->getTilePos().x * 40.f + 20.f + radius * cos(angle / 180.0f * PI),
								(float)(*it)->getTilePos().y * 30.f + 15.f + radius * sin(angle / 180.0f * PI)), angle));
						}
						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 3; j++)
							{
								if(intersect)
								{ 
									_dust2.push_back(make_pair(make_pair((float)((*it)->getTilePos().x - 2 + i + j) * 40.f + 20.f,
										(float)((*it)->getTilePos().y - i + j) * 30.f + 15.f), 270.f));
								}
								else
								{
									_dust2.push_back(make_pair(make_pair((float)((*it)->getTilePos().x - 2 + i + j) * 40.f + 20.f,
										(float)((*it)->getTilePos().y - i + j) * 30.f + 15.f), -90.f));
								}
							}
						}
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 2; j++)
							{
								if(intersect)
								{
									_dust2.push_back(make_pair(make_pair((float)((*it)->getTilePos().x - 1 + i + j) * 40.f + 20.f,
										(float)((*it)->getTilePos().y - i + j) * 30.f + 15.f), -90.f));
								}
								else
								{
									_dust2.push_back(make_pair(make_pair((float)((*it)->getTilePos().x - 1 + i + j) * 40.f + 20.f,
										(float)((*it)->getTilePos().y - i + j) * 30.f + 15.f), 270.f));
								}
							}
						}
					}
				}
				intersect = !intersect;
			}
			if(_frame % 2 == 0)
			{
				for (int i = 0; i < _dust1Pos.size(); i++)
				{
					_dust1Pos[i].first.first += cos(_dust1Pos[i].second);
					_dust1Pos[i].first.second += sin(_dust1Pos[i].second);
				}
			}
			if(_startFrame != 0)
			{
				for (auto it = _icePillars.begin(); it != _icePillars.end(); ++it)
				{
					if((_frame - _startFrame) % 3 == 0)
					{
						if((*it)._frame < 15)
						{
							(*it)._frame++;
						}
					}
				}
			}
			if ((_frame - _startFrame ) / 3 > 17 && _startFrame != 0)
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
							target->setDoing(true);
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
								_icePillars[0]._broken = true;
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
	// ���� ��ų õ���Ŀ���
	else if (_curChar->getType() == 0)
	{
		if (_order.test(0))
		{
			if (_frame == 1)
			{
				_startFrame = 0;
			}
			if (_frame * 10 > 255)
			{
				_startFrame++;
			}
			if (_startFrame == 1)
			{
				SOUNDMANAGER->playSoundFMOD("SkillCasting");
			}
			if ((_startFrame - 1) / 2 > IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX())
			{
				_order = _order << 1;
				_frame = 0;
				_curChar->setSkillOrder(1);
				_startFrame = 0;
			}
		}
		else if (_order.test(1))
		{
			if (_frame == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 12; j++)
					{
						_crackedEarth[i][j] = RND->getInt(3);
					}
				}
			}
		}
	}
}

void Skill::render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight)
{
	// ����Ʈ ��ų ��ȭ������
	if (_curChar->getType() == 1)
	{
		if(_order.test(0))
		{
			if (_startFrame > 0)
			{
				IMAGEMANAGER->findImage("SkillCasting")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SkillCasting")->getFrameWidth() / 2 + 10,
					position.y - IMAGEMANAGER->findImage("SkillCasting")->getFrameHeight() / 2 + 30, (_startFrame - 1) / 2, 0, 128);
			}
		}
		else if (_order.test(1))
		{
			for (int i = 0; i < _dust2.size(); i++)
			{
				IMAGEMANAGER->findImage("VermontSkillEFX3")->alphaFrameRender(hdc, 
				WINSIZE_X / 2 - (cameraPos.x - _dust2[i].first.first) - 30 + 15 * cos(_dust2[i].second / 180.f * PI),
				WINSIZE_Y / 2 - (cameraPos.y - _dust2[i].first.second) - 45 + 15 * sin(_dust2[i].second / 180.f * PI),
					(_frame - 1) / 10, 0, 32);
			}

			if ((_frame - 1) / 10 < 8)
			{
				for (int i = 0; i < _dust1Pos.size(); i++)
				{
					IMAGEMANAGER->findImage("VermontSkillEFX4")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - _dust1Pos[i].first.first) - 15,
						WINSIZE_Y / 2 - (cameraPos.y - _dust1Pos[i].first.second) - 15, (_frame - 1) / 10, 0, 80);
				}
			}
			for(int i = 0; i < _efxPos.size(); i++)
			{
				IMAGEMANAGER->findImage("VermontSkillEFX2")->alphaFrameRender(hdc, 
				WINSIZE_X / 2 - (cameraPos.x - (_efxPos[i].first.x - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameWidth() / 2)),
				WINSIZE_Y / 2 - (cameraPos.y - (_efxPos[i].first.y - IMAGEMANAGER->findImage("VermontSkillEFX2")->getFrameHeight() / 2 - 30)), 
				IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() - i, 0, 35);
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
					IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() - i, 0, 35);
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
					IMAGEMANAGER->findImage("VermontSkillEFX2")->getMaxFrameX() - i, 0, 35);
			}
			for (auto it = _icePillars.begin(); it != _icePillars.end(); ++it)
			{
				IMAGEMANAGER->findImage("VermontSkillEFX1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)._position.x) - 25,
					WINSIZE_Y / 2 - (cameraPos.y - (*it)._position.y) - 85, (*it)._frame, 0, 150);
			}
		}
	}
	// ���� ��ų õ���Ŀ���
	else if (_curChar->getType() == 0)
	{
		if (_order.test(0))
		{
			if (_startFrame > 0)
			{
				IMAGEMANAGER->findImage("SkillCasting")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SkillCasting")->getFrameWidth() / 2 + 10,
					position.y - IMAGEMANAGER->findImage("SkillCasting")->getFrameHeight() / 2 + 30, (_startFrame - 1) / 2, 0, 128);
			}
		}
		else if (_order.test(1))
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 12; j++)
				{	
					if(i == 0)
					{
						if (_crackedEarth[i][j] == 0)
						{
							IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight),
							tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 1)
						{
							IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 2)
						{
							IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
					}
					else if (i == 1)
					{
						if (_crackedEarth[i][j] == 0)
						{
							IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 1)
						{
							IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 2)
						{
							IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
					}
					else if (i == 2)
					{
						if (_crackedEarth[i][j] == 0)
						{
							IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 1)
						{
							IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 2)
						{
							IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
					}
					else if (i == 3)
					{
						if (_crackedEarth[i][j] == 0)
						{
							IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 1)
						{
							IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
						else if (_crackedEarth[i][j] == 2)
						{
							IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight),
								tileWidth, tileHeight, (_frame / 5) % 12, 0);
						}
					}
				}
			}
		}
		else if (_order.test(2))
		{
			for(auto it = _charList.begin(); it != _charList.end(); ++it)
			{
				if((*it)->getType() == 1)
				{
					IMAGEMANAGER->findImage("Volcano")->frameRender(hdc, 
						WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * 40 + 20)) - IMAGEMANAGER->findImage("Volcano")->getFrameWidth() / 2,
						WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y * 30 + 15)) - IMAGEMANAGER->findImage("Volcano")->getFrameHeight() / 2,
						(_frame / 10) % 4, 0);
				}
			}
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
