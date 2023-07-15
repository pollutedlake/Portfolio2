#include "Stdafx.h"
#include "Obstacle.h"

void Obstacle::render(HDC hdc)
{
	IMAGEMANAGER->findImage(_key)->render(hdc, _position.x, _position.y, IMAGEMANAGER->findImage(_key)->getWidth() * _magnificationX, IMAGEMANAGER->findImage(_key)->getHeight() * _magnificationY,
		0, 0, IMAGEMANAGER->findImage(_key)->getWidth(), IMAGEMANAGER->findImage(_key)->getHeight());
}