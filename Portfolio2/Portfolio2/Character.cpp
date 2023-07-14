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
	return S_OK;
}

void Character::release(void)
{
}

void Character::update(void)
{

}

void Character::render(HDC hdc, POINT position)
{
}

void Character::setState(int state)
{
	_state.reset();
	_state |= state;
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
		_tilePos.x = _route.back().x;
		_tilePos.y = _route.back().y;
		_route.pop_back();
		_curMobility--;
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

