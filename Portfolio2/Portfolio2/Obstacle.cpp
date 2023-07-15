#include "Stdafx.h"
#include "Obstacle.h"

void Obstacle::render(HDC hdc, POINT cameraPos)
{
	IMAGEMANAGER->findImage(_key)->render(hdc, WINSIZE_X / 2 - (cameraPos.x - _position.x), WINSIZE_Y / 2 - (cameraPos.y - _position.y), 
	IMAGEMANAGER->findImage(_key)->getWidth() * _magnificationX, IMAGEMANAGER->findImage(_key)->getHeight() * _magnificationY,
		0, 0, IMAGEMANAGER->findImage(_key)->getWidth(), IMAGEMANAGER->findImage(_key)->getHeight());
}