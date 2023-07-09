#include "Stdafx.h"
#include "Saladin.h"

HRESULT Saladin::init(void)
{
	_frame = 0;
	return S_OK;
}

void Saladin::release(void)
{

}

void Saladin::update(void)
{
	_frame++;
}

void Saladin::render(HDC hdc, POINT position)
{
	if (_state.test(0))
	{
		IMAGEMANAGER->findImage("SaladinIdleLeft")->frameRender(hdc, position.x -10, position.y, (_frame / 5) % 4, 0);
	}
	if (_state.test(1))
	{
		IMAGEMANAGER->findImage("SaladinIdleRight")->frameRender(hdc, position.x - 10, position.y, (_frame / 5) % 4, 0);
	}
	if (_state.test(2))
	{
		IMAGEMANAGER->findImage("SaladinIdleUp")->frameRender(hdc, position.x - 10, position.y, (_frame / 5) % 4, 0);
	}
	if (_state.test(3))
	{
		IMAGEMANAGER->findImage("SaladinIdleDown")->frameRender(hdc, position.x - 10, position.y, (_frame / 5) % 4, 0);
	}
}
