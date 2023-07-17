#include "Stdafx.h"
#include "Vermont.h"

HRESULT Vermont::init(void)
{
	_frame = 0;
	_wtp = 10;
	_curWait = _wtp;
	_mobility = 5;
	_type = 1;
	Character::init();
	return S_OK;
}

void Vermont::release(void)
{
	Enemy::release();
}

void Vermont::update(void)
{
	_frame++;
	if (_state.test(MOVE))
	{
		move();
	}
	else if (_state.test(ATTACK))
	{
		if (_frame == 3)
		{
			SOUNDMANAGER->playEffectSoundWave("Resources/Sounds/SoundEffect/VermontAttack.wav");
			//SOUNDMANAGER->playSoundFMOD("VermontAttack");
		}
		if ((_frame / 10) % 4 == 2)
		{
			_isAttack = true;
		}
		else
		{
			_isAttack = false;
			_damage = 0;
		}
		if (_dir.test(LEFT) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackLeft")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(RIGHT) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackRight")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(UP) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackUp")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(DOWN) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackDown")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
	}
	else if (_state.test(DAMAGED))
	{
		if (_frame / 5 > 0)
		{
			_state.reset();
		}
	}
	else if (_state.test(SKILL))
	{
		if (_skillOrder.test(2))
		{
			static float angle;
			static float dist;
			static float moveDist;
			if(_frame == 1)
			{ 
				angle = atan2((float)_destTilePos.y * 30.f + 15.f - y, (float)_destTilePos.x * 40.f + 20.f - x);
				dist = sqrt(pow(((float)_destTilePos.x * 40.f + 20.f - x) * 1.1f, 2) + pow(((float)_destTilePos.y * 30.f + 15.f - y) * 1.1f, 2));
				if (SamePoint(_destTilePos, _tilePos))
				{
					dist = sqrt(pow(((float)_destTilePos.x * 40.f + 20.f - x), 2) + pow(((float)_destTilePos.y * 30.f + 15.f - y), 2));
				}
				moveDist = 0;
			}
			if (moveDist > dist / 10 && moveDist < dist / 10 + 10.f)
			{
				SOUNDMANAGER->playSoundFMOD("VermontSkillAttack");
			}
			if (abs((float)_destTilePos.y * 30.f + 15.f - y) > abs((float)_destTilePos.x * 40.f + 20.f - x))
			{
				if (sin(angle) < 0)
				{
					setDir(UP);
				}
				else
				{
					setDir(DOWN);
				}
			}
			else
			{
				if (cos(angle) < 0)
				{
					setDir(LEFT);
				}
				else
				{
					setDir(RIGHT);
				}
			}
			x += 10.f * cos(angle);
			y += 10.f * sin(angle);
			moveDist += 10.f;
			if (moveDist >= dist)
			{
				if (SamePoint(_destTilePos, _tilePos))
				{
					x = (float)_destTilePos.x * 40.f + 20.f;
					y = (float)_destTilePos.y * 30.f + 15.f;
				}
				else
				{
					x -= 10.f * cos(angle);
					y -= 10.f * sin(angle);
				}
			}
		}
		else if (_skillOrder.test(3))
		{
			
		}
	}
}

void Vermont::render(HDC hdc, POINT position, POINT cameraPos)
{
	if (_state.none())
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("VermontIdleLeft")->frameRender(hdc, position.x + 5, position.y - 10, (_frame / 5) % 5, 0);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("VermontIdleRight")->frameRender(hdc, position.x, position.y - 10, (_frame / 5) % 5, 0);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("VermontIdleUp")->frameRender(hdc, position.x + 10, position.y - 5, (_frame / 5) % 5, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("VermontIdleDown")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 5, 0);
		}
	}
	if (_state.test(MOVE))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("VermontMoveLeft")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 42, WINSIZE_Y / 2 - (cameraPos.y - y) - 70, (_frame / 5) % 6, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("VermontMoveRight")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_Y / 2 - (cameraPos.y - y) - 70, (_frame / 5) % 6, 3);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("VermontMoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_Y / 2 - (cameraPos.y - y) - 70, (_frame / 5) % 6, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("VermontMoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 30, WINSIZE_Y / 2 - (cameraPos.y - y) - 70, (_frame / 5) % 6, 1);
		}
	}
	else if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("VermontAttackLeft")->frameRender(hdc, position.x - 30, position.y - 40, (_frame / 10) % 4, 0);
			if((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackSideEffect")->alphaFrameRender(hdc, position.x - 60, position.y - 40, (_frame / 5) % 4, 0, 200);
			}
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("VermontAttackRight")->frameRender(hdc, position.x - 45, position.y - 40, 3 - (_frame / 10) % 4, 0);
			if ((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackSideEffect")->alphaFrameRender(hdc, position.x - 60, position.y - 40, 3 - (_frame / 5) % 4, 1, 200);
			}
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("VermontAttackUp")->frameRender(hdc, position.x - 20, position.y, (_frame / 10) % 4, 0);
			if ((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackUpEffect")->alphaFrameRender(hdc, position.x - 45, position.y - 35, (_frame / 5) % 4, 0, 200);
			}
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("VermontAttackDown")->frameRender(hdc, position.x - 35, position.y - 30, (_frame / 10) % 4, 0);
			if ((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 25, (_frame / 5) % 4, 0, 200);
			}
		}
	}
	else if (_state.test(DAMAGED))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("VermontDamagedLeft")->render(hdc, position.x, position.y);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("VermontDamagedRight")->render(hdc, position.x - 20, position.y);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("VermontDamagedUp")->render(hdc, position.x - 10, position.y);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("VermontDamagedDown")->render(hdc, position.x - 5, position.y);
		}
		char damageStr[50];
		wsprintf(damageStr, "%d", _damage);
		FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "°¡À»Ã¼", 20, 50, damageStr, strlen(damageStr), RGB(255, 0, 0));
	}
	else if (_state.test(SKILL))
	{
		if(_skillOrder.test(0))
		{
			IMAGEMANAGER->findImage("VermontSkillCasting")->render(hdc, position.x - 12, position.y - 5);
		}
		else if (_skillOrder.test(1))
		{
			IMAGEMANAGER->findImage("VermontIdleDown")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 5, 0);
		}
		else if (_skillOrder.test(2))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("VermontSkillLeft")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - (x - 20)) - 75, WINSIZE_Y / 2 - (cameraPos.y - (y - 60)));
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("VermontSkillRight")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - (x - 20)), WINSIZE_Y / 2 - (cameraPos.y - (y - 60 )));
			}
			else  if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("VermontSkillUp")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - (x - 20)) + 10, WINSIZE_Y / 2 - (cameraPos.y - (y - 60)) - 60);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("VermontSkillDown")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - (x - 20)) + 5, WINSIZE_Y / 2 - (cameraPos.y - (y - 60)));
			}
		}
		else if (_skillOrder.test(3))
		{
			IMAGEMANAGER->findImage("VermontIdleDown")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 5, 0);
		}
	}
}
