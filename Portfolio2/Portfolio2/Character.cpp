#include "Stdafx.h"
#include "Character.h"

HRESULT Character::init(void)
{
	return E_NOTIMPL;
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
	_state.set(state, true);
}

void Character::setDir(int dir)
{
	_dir.reset();
	_dir.set(dir, true);
}

void Character::move()
{
	if (_route.size() > 0)
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
	}
	else
	{
		_state.reset();
		_state.set(IDLE, true);
	}
}
