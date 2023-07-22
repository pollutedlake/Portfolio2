#include "Stdafx.h"
#include "Soldier.h"

HRESULT Soldier::init(void)
{
	_frame = 0;
	_wtp = 999999;
	_mobility = 5;
	_type = 1;
	_maxHP = 50.f;
	_curHP = _maxHP;
	_maxMP = 100.f;
	_curMP = 0;
	Character::init();
	return S_OK;
}

void Soldier::release(void)
{
	Enemy::release();
}

void Soldier::update(void)
{
	_frame++;
	if (_state.test(MOVE))
	{
		move();
	}
	else if (_state.test(ATTACK))
	{
		
	}
	else if (_state.test(DAMAGED))
	{
		if (_frame / 5 > 0)
		{
			_curHP -= _damage;
			if (_curHP < 0)
			{
				_curHP = 0;
				setState(pow(2, DIE));
			}
			else
			{
				_state.reset();
				setDoing(false);
			}
		}
	}
	else if (_state.test(SKILL))
	{
		
	}
	else if (_state.test(DIE))
	{
		if (255 - 255 / 30 * _frame < 0)
		{
			_isDie = true;
		}
	}
}

void Soldier::render(HDC hdc, POINT position, POINT cameraPos)
{
	if (_state.none())
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 20, position.y - 30, (_frame / 10) % 3, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 20, position.y - 30, (_frame / 10) % 3, 4);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 25, position.y - 25, (_frame / 10) % 3, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 25, position.y - 25, (_frame / 10) % 3, 6);
		}
	}
	if (_state.test(MOVE))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 30, (_frame / 5) % 6, 3);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 30, (_frame / 5) % 6, 5);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_Y / 2 - (cameraPos.y - y) - 25, (_frame / 5) % 6, 1);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_Y / 2 - (cameraPos.y - y) - 25, (_frame / 5) % 6, 7);
		}
	}
	else if (_state.test(ATTACK))
	{
		
	}
	else if (_state.test(DAMAGED))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 20, position.y - 30, 0, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 20, position.y - 30, 0, 4);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 25, position.y - 25, 0, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Enemy")->frameRender(hdc, position.x - 25, position.y - 25, 0, 6);
		}
		char damageStr[50];
		wsprintf(damageStr, "%d", _damage);
		FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "°¡À»Ã¼", 20, 50, damageStr, strlen(damageStr), RGB(255, 0, 0));
	}
	else if (_state.test(SKILL))
	{
		
	}
	else if (_state.test(DIE))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 20, position.y - 30, 0, 2, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 20, position.y - 30, 0, 4, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 25, position.y - 25, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 25, position.y - 25, 0, 6, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
	}
}
