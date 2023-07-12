#include "Stdafx.h"
#include "Vermont.h"

HRESULT Vermont::init(void)
{
	_frame = 0;
	return S_OK;
}

void Vermont::release(void)
{
}

void Vermont::update(void)
{
	_frame++;
	if(_state.test(MOVE))
	{
		if (_frame % 5 == 0)
		{
			move();
		}
	}
}

void Vermont::render(HDC hdc, POINT position)
{
	if (_state.test(IDLE))
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
			IMAGEMANAGER->findImage("VermontMoveLeft")->frameRender(hdc, position.x - 35, position.y - 10, (_frame / 5) % 6, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("VermontMoveRight")->frameRender(hdc, position.x, position.y - 10, (_frame / 5) % 6, 3);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("VermontMoveUp")->frameRender(hdc, position.x, position.y - 10, (_frame / 5) % 6, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("VermontMoveDown")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 6, 1);
		}
	}
	if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 40, position.y - 30, 0, LEFT);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, RIGHT);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("SaladinAttackUP")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 0);
		}
	}
}
