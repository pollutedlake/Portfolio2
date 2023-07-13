#include "Stdafx.h"
#include "Saladin.h"

HRESULT Saladin::init(void)
{
	_frame = 0;
	_wtp = 10;
	_mobility = 10;
	_type = 0;
	Character::init();
	return S_OK;
}

void Saladin::release(void)
{

}

void Saladin::update(void)
{
	_frame++;
	if(_state.test(MOVE))
	{
		if (_frame % 5 == 0)
		{
			move();
		}
	}
	else if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX())
		{
			_state.reset();
			//setState(IDLE);
			setDoing(false);
			_turn.flip(1);
		}
		else if (_dir.test(RIGHT) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX())
		{
			_state.reset();
			//setState(IDLE);
			setDoing(false);
			_turn.flip(1);
		}
		else if (_dir.test(UP) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX())
		{
			_state.reset();
			//setState(IDLE);
			setDoing(false);
			_turn.flip(1);
		}
		else if (_dir.test(DOWN) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackDown")->getMaxFrameX())
		{
			_state.reset();
			//setState(IDLE);
			setDoing(false);
			_turn.flip(1);
		}
	}
}

void Saladin::render(HDC hdc, POINT position)
{
	if (_state.none())
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("SaladinIdleLeft")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 4, 0);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("SaladinIdleRight")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("SaladinIdleUp")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("SaladinIdleDown")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
		}
	}
	if (_state.test(MOVE))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 3);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 1);
		}
	}
	else if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, _frame / 10, LEFT);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20, 4 - _frame / 10, RIGHT);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60, _frame / 10, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, _frame / 10, 0);
		}
	}
}

//void Saladin::setState(int state)
//{
//	_state.reset(); 
//	_state.set(state, true);
//}
//
//void Saladin::setDir(int dir)
//{
//	_dir.reset();
//	_dir.set(dir, true);
//}
//
//void Saladin::move()
//{
//	if (_route.size() > 0)
//	{
//		_state.reset();
//		_state.set(MOVE, true);
//		if (_tilePos.x - _route.back().x == 1)
//		{
//			_dir.reset();
//			_dir.set(LEFT, true);
//		}
//		else if (_tilePos.x - _route.back().x == -1)
//		{
//			_dir.reset();
//			_dir.set(RIGHT, true);
//		}
//		else if (_tilePos.y - _route.back().y == 1)
//		{
//			_dir.reset();
//			_dir.set(UP, true);
//		}
//		else if (_tilePos.y - _route.back().y == -1)
//		{
//			_dir.reset();
//			_dir.set(DOWN, true);
//		}
//		else
//		{
//			_state.reset();
//			_state.set(IDLE, true);
//		}
//		_tilePos.x = _route.back().x;
//		_tilePos.y = _route.back().y;
//		_route.pop_back();
//	}
//	else
//	{
//		_state.reset();
//		_state.set(IDLE, true);
//	}
//}
