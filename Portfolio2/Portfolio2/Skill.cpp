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
	// 버몬트 스킬 설화난영참
	if(_curChar->getType() == 1)
	{
		if (_frame % 30 == 0)
		{
			_snow.push_back({ RND->getInt(IMAGEMANAGER->findImage("BossBattleBG")->getWidth() * 1.5) - 6, -6 });
		}
		for (auto it = _snow.begin(); it != _snow.end();)
		{
			int pattern = RND->getInt(2);
			if (pattern == 0)
			{
				(*it).x -= 2;
			}
			else
			{
				(*it).x += 2;
			}
			(*it).y	+= 5;
			if ((*it).y > IMAGEMANAGER->findImage("BossBattleBG")->getHeight() * 1.5 + 6)
			{
				it = _snow.erase(it);
			}
			else
			{
				++it;
			}
		}
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
				_curChar->endTurn();
				//_curChar->setTurn(1, false);
				_curChar->setDir(DOWN);
				_curChar->setDoing(false);
			}
		}
	}
	// 살라딘 스킬 천지파열무
	else if (!strcmp(_skillName, "천지파열무"))
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
				_orderOrder.reset();
				_orderOrder.set(0);
			}
		}
		else if (_order.test(1))
		{
			if(_orderOrder.test(0))
			{
				if (_frame == 1)
				{
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 12; j++)
						{
							_crackedEarth[i][j].first = RND->getInt(3);
							_crackedEarth[i][j].second = false;
						}
					}
					for (int i = 0; i < 4; i++)
					{
						int count = 0;
						int num = RND->getFromIntTo(3, 9);
						while (count != num)
						{
							int index = RND->getFromIntTo(0, 11);
							if (!_crackedEarth[i][index].second)
							{
								_crackedEarth[i][index].second = true;
								count++;
							}
						}
					}
				}
				if ((_frame - 47) / 4 > IMAGEMANAGER->findImage("Eruption1LU")->getMaxFrameX())
				{
					_orderOrder = _orderOrder << 1;
					_frame = 0;
				}
			}
			else if(_orderOrder.test(1))
			{
				if (_frame == 1)
				{
					((Saladin*)_curChar)->setCameraShake(true);
				}
				if ((_frame == 1 || _frame == 25) || _frame == 50)
				{
					SOUNDMANAGER->playSoundFMOD("Magma");
				}
				if (_frame / 5 - 10 > IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX())
				{
					_orderOrder = _orderOrder << 1;
					_frame = 0;
				}
			}
			else if (_orderOrder.test(2))
			{
				if(_frame == 5)
				{
					SOUNDMANAGER->playSoundFMOD("CrackedEarth");
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 12; j++)
						{
							for (int k = 0; k < 5; k++)
							{
								_stonePos[i][j][k] = {RND->getInt(40), RND->getInt(30)};
							}
						}
					}
				}
				if (_frame - 15 - ((11 + 9) * 10) == IMAGEMANAGER->findImage("Explosion")->getMaxFrameX() + 1)
				{
					_orderOrder = _orderOrder << 1;
					_frame = 0;
					for (auto it = _charList.begin(); it != _charList.end(); ++it)
					{
						if ((*it)->getType() == 1)
						{
							_volcano.push_back(make_pair(RND->getInt(3), RND->getInt(3)));
						}
					}
				}
			}
			else if (_orderOrder.test(3))
			{
				if ((_frame - ((IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() + 2) * 5 + 20)) / 5 == 8)
				{
					_orderOrder.reset();
					_orderOrder.set(0);
					_order = _order << 1;
					_curChar->setSkillOrder(2);
					_frame = 0;
					((Saladin*)_curChar)->setCameraShake(false);
				}
			}
		}
		else if (_order.test(2))
		{
			if (_frame == 1)//3 * 2 - 8 + (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5)
			{
				for (auto it = _charList.begin(); it != _charList.end(); ++it)
				{
					if ((*it)->getType() == 1)
					{
						vector<pair<int, int>> stones;
						for (int i = 0; i < 5; i++)
						{
							pair<int, int> stone;
							stone.first = (*it)->getTilePos().x * 40 + 20 + 40 - RND->getInt(80);
							stone.second = (*it)->getTilePos().y * 30 + 15 - 120 - RND->getInt(150);
							stones.push_back(stone);
						}
						_bigStones.push_back(stones);
					}
				}
			}
			if (_frame == (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() - 7) * 5)
			{
				SOUNDMANAGER->playSoundFMOD("Explosion");
			}
			if ((_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 5 == 3)
			{
				((Saladin*)_curChar)->setCameraShake(true);
				for (auto it = _charList.begin(); it != _charList.end(); ++it)
				{
					if ((*it)->getType() == 1)
					{
						(*it)->setDamage(200);
						(*it)->setState(4);
					}
				}
			}
			if ((_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 5 > IMAGEMANAGER->findImage("Explosion3")->getMaxFrameX())
			{
				_order = _order << 1;
				_frame = 0;
			}
		}
		else if (_order.test(3))
		{
			if ((_frame - 45) / 5 - 4 > 4)
			{
				if (IMAGEMANAGER->findImage("RestoreEarth1LU")->getMaxFrameX() - (_frame - 90) / 5 == -1)
				{
					((Saladin*)_curChar)->setCameraShake(false);
				}
			}
			if (IMAGEMANAGER->findImage("RestoreEarth3LU")->getMaxFrameX() - (_frame - 90) / 5 + 11 < 0)
			{
				_curChar->setDir(DOWN);
				_curChar->setDoing(false);
				_isFinish = true;
			}
		}
	}
	else if (!strcmp(_skillName, "풍아열공참"))
	{
		if (_order.test(0))
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
				_orderOrder.reset();
				_startFrame = 0;
				_orderOrder.set(0);
			}
		}
		else if (_order.test(1))
		{
			_startFrame++;
			if ((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10 == 8)
			{
				_order = _order << 1;
				_frame = 0;
				_curChar->setSkillOrder(2);
				_orderOrder.reset();
				_orderOrder.set(0);
			}
			if (_frame  == 10 || _frame == 30)
			{
				_startFrame = 0;
			}
			if ((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10 < 8)
			{
				if (((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10) % 2 == 1)
				{
					_startFrame = 0;
				}
			}
		}
		else if (_order.test(2))
		{
			_startFrame++;
			if (_frame == 51)
			{
				SOUNDMANAGER->playSoundFMOD("FinalAttack");
			}
			if ((_frame - 50) / 5 > 5)
			{
				_order = _order << 1;
				_frame = 0;
				_curChar->setSkillOrder(3);
				_orderOrder.reset();
				_orderOrder.set(0);
			}
		}
		else if (_order.test(3))
		{
			if (_frame / 5 + 6 > IMAGEMANAGER->findImage("Cham")->getMaxFrameX())
			{
				_curChar->setDir(LEFT);
				_curChar->setDoing(false);
				_isFinish = true;
			}
		}
	}
}

void Skill::render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight)
{
	// 버몬트 스킬 설화난영참
	if (_curChar->getType() == 1)
	{
		for (auto it = _snow.begin(); it != _snow.end(); ++it)
		{
			IMAGEMANAGER->findImage("Snow")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it).x), WINSIZE_Y / 2 - (cameraPos.y - (*it).y));
		}
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
	// 살라딘 스킬 천지파열무
	else if (!strcmp(_skillName, "천지파열무"))
	{
		// 스킬 시전
		if (_order.test(0))
		{
			if (_startFrame > 0)
			{
				IMAGEMANAGER->findImage("SkillCasting")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SkillCasting")->getFrameWidth() / 2 + 10,
					position.y - IMAGEMANAGER->findImage("SkillCasting")->getFrameHeight() / 2 + 30, (_startFrame - 1) / 2, 0, 128);
			}
		}
		// 스킬 사전 준비
		else if (_order.test(1))
		{
			// 칼을 땅에 꽂고 빛나옴
			if (_orderOrder.test(0))
			{
				// 칼을 땅에 꽂은 후
				if (_frame / 4 > 11)
				{
					static int tempFrame;
					if (_frame == 48)
					{
						tempFrame = 0;
					}
					tempFrame++;
					IMAGEMANAGER->findImage("ShockWave")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x * tileWidth + tileWidth / 2 - IMAGEMANAGER->findImage("ShockWave")->getFrameWidth() / 2)),
						WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y * tileHeight + tileHeight / 2 - IMAGEMANAGER->findImage("ShockWave")->getFrameHeight() / 2)), tempFrame / 5, 0, 255 - tempFrame * 3);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 12; j++)
						{
							if (i == 0)
							{
								if (_crackedEarth[i][j].first == 0 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption1LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight) - IMAGEMANAGER->findImage("Eruption1LU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Eruption1LU")->getHeight(), IMAGEMANAGER->findImage("Eruption1LU")->getMaxFrameX() - (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 1 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption2LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight) - IMAGEMANAGER->findImage("Eruption2LU")->getHeight() + 29,
										tileWidth, IMAGEMANAGER->findImage("Eruption2LU")->getHeight(), IMAGEMANAGER->findImage("Eruption2LU")->getMaxFrameX() - (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 2 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption3LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight) - IMAGEMANAGER->findImage("Eruption3LU")->getHeight() + 29,
										tileWidth, IMAGEMANAGER->findImage("Eruption3LU")->getHeight(), IMAGEMANAGER->findImage("Eruption3LU")->getMaxFrameX() - (tempFrame / 4), 0, 200);
								}
							}
							else if (i == 1)
							{
								if (_crackedEarth[i][j].first == 0 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption1RU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight) - IMAGEMANAGER->findImage("Eruption1RU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Eruption1RU")->getHeight(), (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 1 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption2RU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight) - IMAGEMANAGER->findImage("Eruption2RU")->getHeight() + 29,
										tileWidth, IMAGEMANAGER->findImage("Eruption2RU")->getHeight(), (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 2 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption3RU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight) - IMAGEMANAGER->findImage("Eruption3RU")->getHeight() + 29,
										tileWidth, IMAGEMANAGER->findImage("Eruption3RU")->getHeight(), (tempFrame / 4), 0, 200);
								}
							}
							else if (i == 2)
							{
								if (_crackedEarth[i][j].first == 0 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption1RU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight) - IMAGEMANAGER->findImage("Eruption1RU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Eruption1RU")->getHeight(), (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 1 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption2RU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight) - IMAGEMANAGER->findImage("Eruption2RU")->getHeight() + 29,
										tileWidth, IMAGEMANAGER->findImage("Eruption2RU")->getHeight(), (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 2 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption3RU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - j) * tileHeight) - IMAGEMANAGER->findImage("Eruption3RU")->getHeight() + 29,
										tileWidth, IMAGEMANAGER->findImage("Eruption3RU")->getHeight(), (tempFrame / 4), 0, 200);
								}
							}
							else if (i == 3)
							{
								if (_crackedEarth[i][j].first == 0 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption1LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight) - IMAGEMANAGER->findImage("Eruption1LU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Eruption1LU")->getHeight(), IMAGEMANAGER->findImage("Eruption1LU")->getMaxFrameX() - (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 1 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption2LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight) - IMAGEMANAGER->findImage("Eruption2LU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Eruption2LU")->getHeight(), IMAGEMANAGER->findImage("Eruption2LU")->getMaxFrameX() - (tempFrame / 4), 0, 200);
								}
								else if (_crackedEarth[i][j].first == 2 && _crackedEarth[i][j].second)
								{
									IMAGEMANAGER->findImage("Eruption3LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + j) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + j) * tileHeight) - IMAGEMANAGER->findImage("Eruption3LU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Eruption3LU")->getHeight(), IMAGEMANAGER->findImage("Eruption3LU")->getMaxFrameX() - (tempFrame / 4), 0, 200);
								}
							}
						}
					}
				}
			}
			// 마그마 왼아래, 오른위, 왼위/오른아래 순으로 나옴
			else if (_orderOrder.test(1))
			{
				for (int i = 0; i < 12; i++)
				{
					if (_crackedEarth[1][i].first == 0)
					{
						if(_frame / 5 < IMAGEMANAGER->findImage("Magma1RU")->getMaxFrameX() + 1)
						{
							IMAGEMANAGER->findImage("Magma1RU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma1RU")->getHeight() + 34,
								tileWidth, IMAGEMANAGER->findImage("Magma1RU")->getHeight(), _frame / 5, 0, 128);
						}
					}
					else if (_crackedEarth[1][i].first == 1)
					{
						if (_frame / 5 < IMAGEMANAGER->findImage("Magma2RU")->getMaxFrameX() + 1)
						{
							IMAGEMANAGER->findImage("Magma2RU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma2RU")->getHeight() + 63,
								tileWidth, IMAGEMANAGER->findImage("Magma2RU")->getFrameHeight(), _frame / 5, 0, 128);
						}
					}
					else if (_crackedEarth[1][i].first == 2)
					{
						if (_frame / 5 < IMAGEMANAGER->findImage("Magma2RU")->getMaxFrameX() + 1)
						{
							IMAGEMANAGER->findImage("Magma3RU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma3RU")->getHeight() + 31,
								tileWidth, IMAGEMANAGER->findImage("Magma3RU")->getHeight(), _frame / 5, 0, 128);
						}
					}
				}
				if (_frame / 5 > 4)
				{
					for (int i = 0; i < 12; i++)
					{
						if (_crackedEarth[2][i].first == 0)
						{
							if(_frame / 5 - 5 < IMAGEMANAGER->findImage("Magma1RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma1RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma1RU")->getHeight() + 34,
									tileWidth, IMAGEMANAGER->findImage("Magma1RU")->getHeight(), _frame / 5 - 5, 0, 128);
							}
						}
						else if (_crackedEarth[2][i].first == 1)
						{
							if (_frame / 5 - 5 < IMAGEMANAGER->findImage("Magma2RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma2RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma2RU")->getHeight() + 63,
									tileWidth, IMAGEMANAGER->findImage("Magma2RU")->getFrameHeight(), _frame / 5 - 5, 0, 128);
							}
						}
						else if (_crackedEarth[2][i].first == 2)
						{
							if (_frame / 5 - 5 < IMAGEMANAGER->findImage("Magma3RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma3RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma3RU")->getHeight() + 31,
									tileWidth, IMAGEMANAGER->findImage("Magma3RU")->getHeight(), _frame / 5 - 5, 0, 128);
							}
						}
					}
				}
				if (_frame / 5 - 5 > 4)
				{
					for (int i = 0; i < 12; i++)
					{
						if (_crackedEarth[0][i].first == 0)
						{
							IMAGEMANAGER->findImage("Magma1LU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma1LU")->getHeight() + 34,
								tileWidth, IMAGEMANAGER->findImage("Magma1LU")->getHeight(), IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() - (_frame / 5 - 10), 0, 128);
						}
						else if (_crackedEarth[0][i].first == 1)
						{
							IMAGEMANAGER->findImage("Magma2LU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma2LU")->getHeight() + 63,
								tileWidth, IMAGEMANAGER->findImage("Magma2LU")->getFrameHeight(), IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() - (_frame / 5 - 10), 0, 128);
						}
						else if (_crackedEarth[0][i].first == 2)
						{
							IMAGEMANAGER->findImage("Magma3LU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma3LU")->getHeight() + 31,
								tileWidth, IMAGEMANAGER->findImage("Magma3LU")->getHeight(), IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() - (_frame / 5 - 10), 0, 128);
						}
						if (_crackedEarth[3][i].first == 0)
						{
							IMAGEMANAGER->findImage("Magma1LU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma1LU")->getHeight() + 34,
								tileWidth, IMAGEMANAGER->findImage("Magma1LU")->getHeight(), IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() - (_frame / 5 - 10), 0, 128);
						}
						else if (_crackedEarth[3][i].first == 1)
						{
							IMAGEMANAGER->findImage("Magma2LU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma2LU")->getHeight() + 63,
								tileWidth, IMAGEMANAGER->findImage("Magma2LU")->getFrameHeight(), IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() - (_frame / 5 - 10), 0, 128);
						}
						else if (_crackedEarth[3][i].first == 2)
						{
							IMAGEMANAGER->findImage("Magma3LU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma3LU")->getHeight() + 31,
								tileWidth, IMAGEMANAGER->findImage("Magma3LU")->getHeight(), IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() - (_frame / 5 - 10), 0, 128);
						}
					}
				}
			}
			// 땅갈라지고 터지면서 마그마 돌 나옴
			else if (_orderOrder.test(2))
			{
				for (int i = 0; i < 12; i++)
				{
					if(_frame / 10 > i)
					{
						if (_crackedEarth[1][i].first == 0)
						{
							IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
								tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
							if((_frame - (i + 1) * 10) / 5 < IMAGEMANAGER->findImage("Magma1RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma1RU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma1RU")->getFrameHeight() + 34,
									tileWidth, IMAGEMANAGER->findImage("Magma1RU")->getFrameHeight(), (_frame - (i + 1) * 10) / 5, 0);
							}
						}
						else if (_crackedEarth[1][i].first == 1)
						{
							IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
								tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
							if ((_frame - (i + 1) * 10) / 5 < IMAGEMANAGER->findImage("Magma2RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma2RU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma2RU")->getHeight() + 63,
									tileWidth, IMAGEMANAGER->findImage("Magma2RU")->getFrameHeight(), (_frame - (i + 1) * 10) / 5, 0);
							}
						}
						else if (_crackedEarth[1][i].first == 2)
						{
							IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
								tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
							if ((_frame - (i + 1) * 10) / 5 < IMAGEMANAGER->findImage("Magma3RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma3RU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma3RU")->getHeight() + 31,
									tileWidth, IMAGEMANAGER->findImage("Magma3RU")->getHeight(), (_frame - (i + 1) * 5) / 10, 0);
							}
						}
					}
					if((_frame - (i + 1) * 10) / 5 > 3)
					{
						if(_crackedEarth[1][i].first % 2 == 0)
						{
							if ((_frame - (20 + (i + 1) * 10)) / 3 < IMAGEMANAGER->findImage("Explosion")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Explosion")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) - 60, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Explosion")->getFrameHeight() + 60,
									IMAGEMANAGER->findImage("Explosion")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion")->getFrameHeight(), (_frame - (20 + (i + 1) * 10)) / 3, 0);
							}
						}
						else
						{
							if((_frame - (20 + (i + 1) * 10)) / 3 < IMAGEMANAGER->findImage("Explosion2")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Explosion2")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) - 35, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - 50,
									IMAGEMANAGER->findImage("Explosion2")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion2")->getFrameHeight(), (_frame - (20 + (i + 1) * 10)) / 3, 0);
							}
						}
						if((_frame - (20 + (i + 1) * 10)) * 2 < 60.f)
						{
							for(int j = 0; j < 5; j++)
							{
								IMAGEMANAGER->findImage("Stone1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth - _stonePos[1][i][j].x), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight - _stonePos[1][i][j].y + 60) - (_frame - (20 + (i + 1) * 10)) * 2,
									IMAGEMANAGER->findImage("Stone1")->getFrameWidth(), IMAGEMANAGER->findImage("Stone1")->getFrameHeight(), ((_frame / 5 - i - j) * 19 % 17) % (IMAGEMANAGER->findImage("Stone1")->getMaxFrameX() + 1), 0, 
									255 - 0);
							}
						}
					}
					if (_frame / 10 > 3)
					{
						if(_frame / 10 - 4 > i)
						{
							if (_crackedEarth[2][i].first == 0)
							{
								IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
								if((_frame - (i + 5) * 10) / 5 < IMAGEMANAGER->findImage("Magma1RU")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Magma1RU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma1RU")->getHeight() + 34,
										tileWidth, IMAGEMANAGER->findImage("Magma1RU")->getHeight(), (_frame - (i + 5) * 10) / 5, 0);
								}
							}
							else if (_crackedEarth[2][i].first == 1)
							{
								IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
								if ((_frame - (i + 5) * 10) / 5 < IMAGEMANAGER->findImage("Magma2RU")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Magma2RU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma2RU")->getHeight() + 63,
										tileWidth, IMAGEMANAGER->findImage("Magma2RU")->getFrameHeight(), (_frame - (i + 5) * 10) / 5, 0);
								}
							}
							else if (_crackedEarth[2][i].first == 2)
							{
								IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
								if ((_frame - (i + 5) * 10) / 5 < IMAGEMANAGER->findImage("Magma3RU")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Magma3RU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma3RU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Magma3RU")->getHeight(), (_frame - (i + 5) * 10) / 5, 0);
								}
							}
						}
						if ((_frame - (i + 5) * 10) / 5 > 3)
						{
							if (_crackedEarth[1][i].first % 2 == 0)
							{
								if ((_frame - (20 + (i + 5) * 10)) / 3 < IMAGEMANAGER->findImage("Explosion")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Explosion")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) - 60, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Explosion")->getFrameHeight() + 60,
										IMAGEMANAGER->findImage("Explosion")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion")->getFrameHeight(), (_frame - (20 + (i + 5) * 10)) / 3, 0);
								}
							}
							else
							{
								if ((_frame - (20 + (i + 5) * 10)) / 3 < IMAGEMANAGER->findImage("Explosion2")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Explosion2")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) - 35, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - 50,
										IMAGEMANAGER->findImage("Explosion2")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion2")->getFrameHeight(), (_frame - (20 + (i + 5) * 10)) / 3, 0);
								}
							}
							if ((_frame - (20 + (i + 5) * 10)) * 2 < 60.f)
							{
								for (int j = 0; j < 5; j++)
								{
									IMAGEMANAGER->findImage("Stone1")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth - _stonePos[2][i][j].x), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight - _stonePos[2][i][j].y + 60) - (_frame - (20 + (i + 5) * 10)) * 2,
										IMAGEMANAGER->findImage("Stone1")->getFrameWidth(), IMAGEMANAGER->findImage("Stone1")->getFrameHeight(), ((_frame / 5 - i - j) * 19 % 17) % (IMAGEMANAGER->findImage("Stone1")->getMaxFrameX() + 1), 0);
								}
							}
						}
					}
					if (_frame / 10 - 4 > 3)
					{
						if(_frame / 10 - 8 > i)
						{
							if (_crackedEarth[0][i].first == 0)
							{
								IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
								if(IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma1LU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma1LU")->getHeight() + 34,
										tileWidth, IMAGEMANAGER->findImage("Magma1LU")->getHeight(), IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5, 0);
								}
							}
							else if (_crackedEarth[0][i].first == 1)
							{
								IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
								if(IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma2LU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma2LU")->getHeight() + 63,
										tileWidth, IMAGEMANAGER->findImage("Magma2LU")->getFrameHeight(), IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5, 0);
								}
							}
							else if (_crackedEarth[0][i].first == 2)
							{
								IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
								if(IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma3LU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Magma3LU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Magma3LU")->getHeight(), IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5, 0);
								}
							}
							if (_crackedEarth[3][i].first == 0)
							{
								IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
								if (IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma1LU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma1LU")->getHeight() + 34,
										tileWidth, IMAGEMANAGER->findImage("Magma1LU")->getHeight(), IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5, 0);
								}
							}
							else if (_crackedEarth[3][i].first == 1)
							{
								IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
								if (IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma2LU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma2LU")->getHeight() + 63,
										tileWidth, IMAGEMANAGER->findImage("Magma2LU")->getFrameHeight(), IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5, 0);
								}
							}
							else if (_crackedEarth[3][i].first == 2)
							{
								IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
									tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
								if (IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma3LU")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Magma3LU")->getHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Magma3LU")->getHeight(), IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() - (_frame - (i + 9) * 10) / 5, 0);
								}
							}
						}
						if (11 - (_frame - (i + 9) * 10) / 5 < 9)
						{
							if(_crackedEarth[0][i].first % 2 == 0)
							{
								if(_frame - 15 - ((i + 9) * 10) < IMAGEMANAGER->findImage("Explosion")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Explosion")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) - 60, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - IMAGEMANAGER->findImage("Explosion")->getFrameHeight() + 60,
										IMAGEMANAGER->findImage("Explosion")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion")->getFrameHeight(), _frame - 15 - ((i + 9) * 10), 0);
								}
							}
							else
							{
								if (_frame - 15 - ((i + 9) * 10) < IMAGEMANAGER->findImage("Explosion2")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Explosion2")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth) - 35, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight) - 50,
										IMAGEMANAGER->findImage("Explosion2")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion2")->getFrameHeight(), _frame - 15 - ((i + 9) * 10), 0);
								}
							}
							if(_crackedEarth[3][i].first % 2 == 0)
							{
								if (_frame - 15 - ((i + 9) * 10) < IMAGEMANAGER->findImage("Explosion")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Explosion")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) - 60, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Explosion")->getFrameHeight() + 60,
										IMAGEMANAGER->findImage("Explosion")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion")->getFrameHeight(), _frame - 15 - ((i + 9) * 10), 0);
								}
							}
							else
							{
								if (_frame - 15 - ((i + 9) * 10) < IMAGEMANAGER->findImage("Explosion2")->getMaxFrameX() + 1)
								{
									IMAGEMANAGER->findImage("Explosion2")->frameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth) - 60, WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight) - IMAGEMANAGER->findImage("Explosion2")->getFrameHeight() + 60,
										IMAGEMANAGER->findImage("Explosion2")->getFrameWidth(), IMAGEMANAGER->findImage("Explosion2")->getFrameHeight(), _frame - 15 - ((i + 9) * 10), 0);
								}
							}
							if ((_frame - 15 - (i + 9) * 10) * 2 < 60.f)
							{
								for (int j = 0; j < 5; j++)
								{
									IMAGEMANAGER->findImage("Stone1")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth - _stonePos[3][i][j].x), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight - _stonePos[3][i][j].y + 60) - (_frame - 15 - (i + 9) * 10) * 2,
										IMAGEMANAGER->findImage("Stone1")->getFrameWidth(), IMAGEMANAGER->findImage("Stone1")->getFrameHeight(), ((_frame / 5 - i - j) * 19 % 17) % (IMAGEMANAGER->findImage("Stone1")->getMaxFrameX() + 1), 0);
									IMAGEMANAGER->findImage("Stone1")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth - _stonePos[0][i][j].x), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight - _stonePos[0][i][j].y + 60) - (_frame - 15 - (i + 9) * 10) * 2,
										IMAGEMANAGER->findImage("Stone1")->getFrameWidth(), IMAGEMANAGER->findImage("Stone1")->getFrameHeight(), ((_frame / 5 - i - j) * 19 % 17) % (IMAGEMANAGER->findImage("Stone1")->getMaxFrameX() + 1), 0);
								}
							}
						}
					}
				}
			}
			// 적 밑에 마그마 두번 x자로 생기고 빛나옴
			else if (_orderOrder.test(3))
			{
				for (int i = 0; i < 12; i++)
				{
					if (_crackedEarth[1][i].first == 0)
					{
						IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
					}
					else if (_crackedEarth[1][i].first == 1)
					{
						IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
					}
					else if (_crackedEarth[1][i].first == 2)
					{
						IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
					}
					if (_crackedEarth[2][i].first == 0)
					{
						IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
					}
					else if (_crackedEarth[2][i].first == 1)
					{
						IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
					}
					else if (_crackedEarth[2][i].first == 2)
					{
						IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
					}
					if (_crackedEarth[0][i].first == 0)
					{
						IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
					}
					else if (_crackedEarth[0][i].first == 1)
					{
						IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
					}
					else if (_crackedEarth[0][i].first == 2)
					{
						IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
					}
					if (_crackedEarth[3][i].first == 0)
					{
						IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
					}
					else if (_crackedEarth[3][i].first == 1)
					{
						IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
					}
					else if (_crackedEarth[3][i].first == 2)
					{
						IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
					}
				}
				static int index;
				if (_frame == 0)
				{
					index = 0;
				}
				for (auto it = _charList.begin(); it != _charList.end(); ++it)
				{
					if ((*it)->getType() == 1)
					{
						if(_volcano[index].second == 0)
						{
							if(_frame / 5 < IMAGEMANAGER->findImage("Magma1RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma1RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Magma1RU")->getFrameHeight() + 34,
									tileWidth, IMAGEMANAGER->findImage("Magma1RU")->getFrameHeight(), _frame / 5, 0, 128);
							}
						}
						else if (_volcano[index].second == 1)
						{
							if (_frame / 5 < IMAGEMANAGER->findImage("Magma2RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma2RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Magma2RU")->getFrameHeight() + 63,
									tileWidth, IMAGEMANAGER->findImage("Magma2RU")->getFrameHeight(), _frame / 5, 0, 128);
							}
						}
						else if (_volcano[index].second == 2)
						{
							if (_frame / 5 < IMAGEMANAGER->findImage("Magma3RU")->getMaxFrameX() + 1)
							{
								IMAGEMANAGER->findImage("Magma3RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x) * tileWidth) + 1, WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Magma3RU")->getFrameHeight() + 31,
									tileWidth, IMAGEMANAGER->findImage("Magma3RU")->getFrameHeight(), _frame / 5, 0, 128);
							}
						}
						if (_frame / 5 > 3)
						{
							if (_volcano[index].first == 0)
							{
								if (IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() + 1 - (_frame - 20) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma1LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Magma1LU")->getFrameHeight() + 34,
										tileWidth, IMAGEMANAGER->findImage("Magma1LU")->getFrameHeight(), IMAGEMANAGER->findImage("Magma1LU")->getMaxFrameX() + 1 - (_frame - 20) / 5, 0, 128);
								}
							}
							else if (_volcano[index].first == 1)
							{
								if (IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() + 1 - (_frame - 20) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma2LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Magma2LU")->getFrameHeight() + 64,
										tileWidth, IMAGEMANAGER->findImage("Magma2LU")->getFrameHeight(), IMAGEMANAGER->findImage("Magma2LU")->getMaxFrameX() + 1 - (_frame - 20) / 5, 0, 128);
								}
							}
							else if (_volcano[index].first == 2)
							{
								if (IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() + 1 - (_frame - 20) / 5 > -1)
								{
									IMAGEMANAGER->findImage("Magma3LU")->alphaFrameRender(hdc,
										WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Magma3LU")->getFrameHeight() + 31,
										tileWidth, IMAGEMANAGER->findImage("Magma3LU")->getFrameHeight(), IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() + 1 - (_frame - 20) / 5, 0, 128);
								}
							}
						}
						if (IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() + 1 - (_frame - 20) / 5 < 0)
						{
							if (_volcano[index].second == 0)
							{
								IMAGEMANAGER->findImage("Eruption1RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth)), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Eruption1RU")->getHeight() + 31,
									tileWidth, IMAGEMANAGER->findImage("Eruption1RU")->getHeight(), (_frame - ((IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() + 2) * 5 + 20)) / 5, 0, 200);
							}
							else if (_volcano[index].second == 1)
							{
								IMAGEMANAGER->findImage("Eruption2RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth)), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Eruption2RU")->getHeight() + 29,
									tileWidth, IMAGEMANAGER->findImage("Eruption2RU")->getHeight(), (_frame - ((IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() + 2) * 5 + 20)) / 5, 0, 200);
							}
							else if (_volcano[index].second == 2)
							{
								IMAGEMANAGER->findImage("Eruption3RU")->alphaFrameRender(hdc,
									WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth)), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Eruption3RU")->getHeight() + 29,
									tileWidth, IMAGEMANAGER->findImage("Eruption3RU")->getHeight(), (_frame - ((IMAGEMANAGER->findImage("Magma3LU")->getMaxFrameX() + 2) * 5 + 20)) / 5, 0, 200);
							}
						}
						index++;
					}
				}
				index = 0;
			}
		}
		// 터지면서 데미지 들어가기
		else if (_order.test(2))
		{
			for (int i = 0; i < 12; i++)
			{
				if (_crackedEarth[1][i].first == 0)
				{
					IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
				}
				else if (_crackedEarth[1][i].first == 1)
				{
					IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
				}
				else if (_crackedEarth[1][i].first == 2)
				{
					IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i) % 12, 0);
				}
				if (_crackedEarth[2][i].first == 0)
				{
					IMAGEMANAGER->findImage("CrackedEarth1RU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
				}
				else if (_crackedEarth[2][i].first == 1)
				{
					IMAGEMANAGER->findImage("CrackedEarth2RU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
				}
				else if (_crackedEarth[2][i].first == 2)
				{
					IMAGEMANAGER->findImage("CrackedEarth3RU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 4) % 12, 0);
				}
				if (_crackedEarth[0][i].first == 0)
				{
					IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
				}
				else if (_crackedEarth[0][i].first == 1)
				{
					IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
				}
				else if (_crackedEarth[0][i].first == 2)
				{
					IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
				}
				if (_crackedEarth[3][i].first == 0)
				{
					IMAGEMANAGER->findImage("CrackedEarth1LU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
				}
				else if (_crackedEarth[3][i].first == 1)
				{
					IMAGEMANAGER->findImage("CrackedEarth2LU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
				}
				else if (_crackedEarth[3][i].first == 2)
				{
					IMAGEMANAGER->findImage("CrackedEarth3LU")->frameRender(hdc,
						WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
						tileWidth, tileHeight, ((_frame / 5) - i - 8) % 12, 0);
				}
			}
			static int index;
			if (_frame == 0)
			{
				index = 0;
			}
			for (auto it = _charList.begin(); it != _charList.end(); ++it)
			{
				if ((*it)->getType() == 1)
				{
					if (_volcano[index].second == 0)
					{
						if(8 + (_frame) / 5 < IMAGEMANAGER->findImage("Eruption1RU")->getMaxFrameX() + 1)
						{
							IMAGEMANAGER->findImage("Eruption1RU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth)), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Eruption1RU")->getHeight() + 31,
								tileWidth, IMAGEMANAGER->findImage("Eruption1RU")->getHeight(), 8 + (_frame) / 5, 0, 200);
						}
					}
					else if (_volcano[index].second == 1)
					{
						if (8 + (_frame) / 5 < IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1)
						{
							IMAGEMANAGER->findImage("Eruption2RU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth)), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Eruption2RU")->getHeight() + 29,
								tileWidth, IMAGEMANAGER->findImage("Eruption2RU")->getHeight(), 8 + (_frame) / 5, 0, 200);
						}
					}
					else if (_volcano[index].second == 2)
					{
						if (8 + (_frame) / 5 < IMAGEMANAGER->findImage("Eruption3RU")->getMaxFrameX() + 1)
						{
							IMAGEMANAGER->findImage("Eruption3RU")->alphaFrameRender(hdc,
								WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth)), WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y) * tileHeight) - IMAGEMANAGER->findImage("Eruption3RU")->getHeight() + 29,
								tileWidth, IMAGEMANAGER->findImage("Eruption3RU")->getHeight(), 8 + (_frame ) / 5, 0, 200);
						}
					}
					if ((_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 3 > 0 && (_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 3 < 2)
					{
						IMAGEMANAGER->findImage("Red")->alphaRender(hdc, 128);
					}
					if ((_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 3 > 2)
					{
						for (auto it = _bigStones.begin(); it != _bigStones.end(); ++it)
						{
							for (int i = 0; i < 5; i++)
							{
								if ((_frame - (3 * 3 - 8 + 32 * 5)) * 2 < 50)
								{
									IMAGEMANAGER->findImage("Stone2")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)[i].first),
										WINSIZE_Y / 2 - (cameraPos.y - (*it)[i].second) - (_frame - (3 * 3 - 8 + 32 * 5)) * 2,
										((_frame - 3 * 3 - 8 + 32 * 5) / 5 - i * 19 / 3 % 17) % 15, 0, 255);
								}
							}
						}
						IMAGEMANAGER->findImage("Volcano")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth + tileWidth / 2)) - IMAGEMANAGER->findImage("Volcano")->getFrameWidth() / 2,
							WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y * tileHeight + tileHeight / 2)) - IMAGEMANAGER->findImage("Volcano")->getFrameHeight() / 2,
							((_frame - 3 * 2 - 8 + (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5) / 10) % 4, 0);
					}
					if (8 + _frame / 5 > IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX())
					{
						if ((_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 5 < IMAGEMANAGER->findImage("Explosion3")->getMaxFrameX() + 1)
						{
							IMAGEMANAGER->findImage("Explosion3")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)->getTilePos().x * tileWidth) - 105, WINSIZE_Y / 2 - (cameraPos.y - (*it)->getTilePos().y * tileHeight) - 150,
								(_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 3, 0, 
								255 - 255 / (IMAGEMANAGER->findImage("Explosion3")->getMaxFrameX() + 1) * ((_frame - (IMAGEMANAGER->findImage("Eruption2RU")->getMaxFrameX() + 1) * 5 + 8) / 3));
						}
					}
					index++;
				}
			}
			index = 0;
		}
		// 땅 복구
		else if (_order.test(3))
		{
			for (int i = 0; i < 12; i++)
			{
				if (_crackedEarth[1][i].first == 0)
				{
					if (_frame / 5 - i < IMAGEMANAGER->findImage("RestoreEarth1RU")->getMaxFrameX() + 1)
					{
						IMAGEMANAGER->findImage("RestoreEarth1RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, _frame / 5 - i, 0);
					}
				}
				else if (_crackedEarth[1][i].first == 1)
				{
					if (_frame / 5 - i < IMAGEMANAGER->findImage("RestoreEarth2RU")->getMaxFrameX() + 1)
					{
						IMAGEMANAGER->findImage("RestoreEarth2RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, _frame / 5 - i, 0);
					}
				}
				else if (_crackedEarth[1][i].first == 2)
				{
					if (_frame / 5 - i < IMAGEMANAGER->findImage("RestoreEarth2RU")->getMaxFrameX() + 1)
					{
						IMAGEMANAGER->findImage("RestoreEarth3RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, _frame / 5 - i, 0);
					}
				}
			}
			for (int i = 0; i < 12; i++)
			{
				if (_crackedEarth[2][i].first == 0)
				{
					if ((_frame - 45) / 5 - i < IMAGEMANAGER->findImage("RestoreEarth1RU")->getMaxFrameX() + 1)
					{
						IMAGEMANAGER->findImage("RestoreEarth1RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, _frame / 5 - 4 > 4 ? (_frame - 45) / 5 - i : 0, 0);
					}
				}
				else if (_crackedEarth[2][i].first == 1)
				{
					if ((_frame - 45) / 5 - i < IMAGEMANAGER->findImage("RestoreEarth2RU")->getMaxFrameX() + 1)
					{
						IMAGEMANAGER->findImage("RestoreEarth2RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, _frame / 5 - 4 > 4 ? (_frame - 45) / 5 - i : 0, 0);
					}
				}
				else if (_crackedEarth[2][i].first == 2)
				{
					if ((_frame - 45) / 5 - i < IMAGEMANAGER->findImage("RestoreEarth3RU")->getMaxFrameX() + 1)
					{
						IMAGEMANAGER->findImage("RestoreEarth3RU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, _frame / 5 - 4 > 4 ? (_frame - 45) / 5 - i : 0, 0);
					}
				}
			}
			for (int i = 0; i < 12; i++)
			{
				if (_crackedEarth[0][i].first == 0)
				{
					if (IMAGEMANAGER->findImage("RestoreEarth1LU")->getMaxFrameX() - (_frame - 90) / 5 + i > -1)
					{
						IMAGEMANAGER->findImage("RestoreEarth1LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, (_frame - 45) / 5 - 4 > 4 ? IMAGEMANAGER->findImage("RestoreEarth1LU")->getMaxFrameX() - (_frame - 90) / 5 + i : IMAGEMANAGER->findImage("RestoreEarth1LU")->getMaxFrameX(), 0);
					}
				}
				else if (_crackedEarth[0][i].first == 1)
				{
					if (IMAGEMANAGER->findImage("RestoreEarth2LU")->getMaxFrameX() - (_frame - 90) / 5 + i > -1)
					{
						IMAGEMANAGER->findImage("RestoreEarth2LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, (_frame - 45) / 5 - 4 > 4 ? IMAGEMANAGER->findImage("RestoreEarth2LU")->getMaxFrameX() - (_frame - 90) / 5 + i : IMAGEMANAGER->findImage("RestoreEarth2LU")->getMaxFrameX(), 0);
					}
				}
				else if (_crackedEarth[0][i].first == 2)
				{
					if (IMAGEMANAGER->findImage("RestoreEarth3LU")->getMaxFrameX() - (_frame - 90) / 5 + i > -1)
					{
						IMAGEMANAGER->findImage("RestoreEarth3LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x - 1 - i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y - 1 - i) * tileHeight),
							tileWidth, tileHeight, (_frame - 45) / 5 - 4 > 4 ? IMAGEMANAGER->findImage("RestoreEarth3LU")->getMaxFrameX() - (_frame - 90) / 5 + i : IMAGEMANAGER->findImage("RestoreEarth3LU")->getMaxFrameX(), 0);
					}
				}
				if (_crackedEarth[3][i].first == 0)
				{
					if (IMAGEMANAGER->findImage("RestoreEarth1LU")->getMaxFrameX() - (_frame - 90) / 5 + i > -1)
					{
						IMAGEMANAGER->findImage("RestoreEarth1LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, (_frame - 45) / 5 - 4 > 4 ? IMAGEMANAGER->findImage("RestoreEarth1LU")->getMaxFrameX() - (_frame - 90) / 5 + i : IMAGEMANAGER->findImage("RestoreEarth1LU")->getMaxFrameX(), 0);
					}
				}
				else if (_crackedEarth[3][i].first == 1)
				{
					if (IMAGEMANAGER->findImage("RestoreEarth2LU")->getMaxFrameX() - (_frame - 90) / 5 + i > -1)
					{
						IMAGEMANAGER->findImage("RestoreEarth2LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, (_frame - 45) / 5 - 4 > 4 ? IMAGEMANAGER->findImage("RestoreEarth2LU")->getMaxFrameX() - (_frame - 90) / 5 + i : IMAGEMANAGER->findImage("RestoreEarth2LU")->getMaxFrameX(), 0);
					}
				}
				else if (_crackedEarth[3][i].first == 2)
				{
					if (IMAGEMANAGER->findImage("RestoreEarth3LU")->getMaxFrameX() - (_frame - 90) / 5 + i > -1)
					{
						IMAGEMANAGER->findImage("RestoreEarth3LU")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - (_curChar->getTilePos().x + 1 + i) * tileWidth), WINSIZE_Y / 2 - (cameraPos.y - (_curChar->getTilePos().y + 1 + i) * tileHeight),
							tileWidth, tileHeight, (_frame - 45) / 5 - 4 > 4 ? IMAGEMANAGER->findImage("RestoreEarth3LU")->getMaxFrameX() - (_frame - 90) / 5 + i : IMAGEMANAGER->findImage("RestoreEarth3LU")->getMaxFrameX(), 0);
					}
				}
			}
			for (auto it = _charList.begin(); it != _charList.end(); ++it)
			{
				if ((*it)->getType() == 1)
				{
					if (_frame / 10 < IMAGEMANAGER->findImage("Volcano")->getMaxFrameX())
					{
						IMAGEMANAGER->findImage("Volcano")->frameRender(hdc,
							WINSIZE_X / 2 - (cameraPos.x - ((*it)->getTilePos().x * tileWidth + tileWidth / 2)) - IMAGEMANAGER->findImage("Volcano")->getFrameWidth() / 2,
							WINSIZE_Y / 2 - (cameraPos.y - ((*it)->getTilePos().y * tileHeight + tileHeight / 2)) - IMAGEMANAGER->findImage("Volcano")->getFrameHeight() / 2,
							_frame / 10, 0);
					}
				}
			}
		}
	}
	else if (!strcmp(_skillName, "풍아열공참"))
	{
		if (_order.test(0))
		{
			IMAGEMANAGER->findImage("SkillCasting")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SkillCasting")->getFrameWidth() / 2 + 10,
				position.y - IMAGEMANAGER->findImage("SkillCasting")->getFrameHeight() / 2 + 30, (_frame - 1) / 2, 0, 128);
		}
		else if (_order.test(1))
		{
			if(_startFrame - 1 < IMAGEMANAGER->findImage("SlashLight")->getMaxFrameX() + 1)
			{
				IMAGEMANAGER->findImage("SlashLight")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SlashLight")->getFrameWidth() / 2 - 60,
					position.y - IMAGEMANAGER->findImage("SlashLight")->getFrameHeight() / 2 + 30, _startFrame - 1, 0, 200);
			}
		}
		else if (_order.test(2))
		{
			if(_frame > 50)
			{
				IMAGEMANAGER->findImage("Cham")->frameRender(hdc, position.x - 170, position.y - 120, (_frame - 50) / 5, 0);
			}
			if (_startFrame - 1 < IMAGEMANAGER->findImage("SlashLight")->getMaxFrameX() + 1)
			{
				IMAGEMANAGER->findImage("SlashLight")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SlashLight")->getFrameWidth() / 2 - 60,
					position.y - IMAGEMANAGER->findImage("SlashLight")->getFrameHeight() / 2 + 30, _startFrame - 1, 0, 200);
			}
		}
		else if (_order.test(3))
		{
			IMAGEMANAGER->findImage("Cham")->frameRender(hdc, position.x - 170, position.y - 120, _frame / 5 + 6, 0);
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
	return  -1;
}

void Skill::start(vector<Character*> charList, Character* curChar, char* skillName)
{
	_frame = 0;
	_charList = charList;
	_order.reset();
	_order.set(0);
	_orderOrder.reset();
	_isFinish = false;
	_curChar = curChar;
	_curChar->setSkillOrder(0);
	_efxPos.clear();
	_icePillars.clear();
	_dust1Pos.clear();
	_dust2.clear();
	_volcano.clear();
	_bigStones.clear();
	_startFrame = 0;
	_snow.clear();
	_skillName = skillName;
	_curChar->setSkillName(_skillName);
}
