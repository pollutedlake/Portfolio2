#include "Stdafx.h"
#include "Character.h"

HRESULT Character::init(void)
{
	_doing = false;
	_curWait = _wtp;
	_turn.reset();
	_turn.flip();
	_state.reset();
	_turnOrder.reset();
	_curMobility = _mobility;
	_damage = 0;
	_isAttack = false;
	_skillOrder.reset();
	_isDie = false;
	return S_OK;
}

void Character::release(void)
{

}

void Character::update(void)
{
	
}

void Character::render(HDC hdc, POINT position, POINT cameraPos)
{
}

void Character::setState(int state)
{
	_state.reset();
	_state |= state;
	if (_state.test(0))
	{
		x = _tilePos.x * 40 + 20;
		y  = _tilePos.y * 30 + 15;
	}
	_frame = 0;
}

void Character::setDir(int dir)
{
	_dir.reset();
	_dir.set(dir, true);
}

int Character::getTurnOrder(int charN)
{
	for (int i = 0; i < charN - 1; i++)
	{
		if (_turnOrder.test(i))
		{
			return i;
		}
	}
}

void Character::move()
{
	if (_route.size() > 0 && _curMobility > 0)
	{
		x = (_route.back().x * 40 + 20) * ((_frame % 11) / 10.f) + (_tilePos.x * 40 + 20) * ((10 - (_frame % 11)) / 10.f);
		y = (_route.back().y * 30 + 15) * ((_frame % 11) / 10.f) + (_tilePos.y * 30 + 15) * ((10 - (_frame % 11)) / 10.f);
		if (_tilePos.x - _route.back().x == 1)
		{
			_dir.reset();
			_dir.set(LEFT, true);
		}
		else if (_tilePos.x - _route.back().x == -1)
		{
			_dir.reset();
			_dir.set(RIGHT, true);
		}
		else if (_tilePos.y - _route.back().y == 1)
		{
			_dir.reset();
			_dir.set(UP, true);
		}
		else if (_tilePos.y - _route.back().y == -1)
		{
			_dir.reset();
			_dir.set(DOWN, true);
		}
		if (x == (_route.back().x * 40 + 20))
		{
			if (y == (_route.back().y * 30 + 15))
			{

				_tilePos.x = _route.back().x;
				_tilePos.y = _route.back().y;
				_route.pop_back();
				_curMobility--;
			}
		}
	}
	else
	{
		if(_state.test(ATTACK) && _route.empty())
		{
			if (_tilePos.x - _destTilePos.x > 0)
			{
				_dir.reset();
				_dir.set(LEFT, true);
			}
			else if (_tilePos.x - _destTilePos.x < 0)
			{
				_dir.reset();
				_dir.set(RIGHT, true);
			}
			else if (_tilePos.y - _destTilePos.y > 0)
			{
				_dir.reset();
				_dir.set(UP, true);
			}
			else if (_tilePos.y - _destTilePos.y < 0)
			{
				_dir.reset();
				_dir.set(DOWN, true);
			}
			setState(2);
		}
		else
		{
			_state.reset();
			_doing = false;
		}
		_curMobility = _mobility;
		if(_type == 0)
		{
			_turn.flip(0);
		}
		else
		{
			endTurn();
		}
		_route.clear();
	}
}

void Character::setXY(int tileWidth, int tileHeight)
{
	x = _tilePos.x * tileWidth + tileWidth / 2;
	y = _tilePos.y * tileHeight + tileHeight / 2;
}

bool Character::isDie()
{
	return _isDie;
}

int Character::getDamage()
{
	if (_damage == 0)
	{
		_damage = RND->getFromIntTo(30, 40);
	}
	return _damage;
}
