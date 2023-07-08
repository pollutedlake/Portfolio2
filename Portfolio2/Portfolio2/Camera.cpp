#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
	return S_OK;
}

void Camera::release(void)
{
}

void Camera::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || _ptMouse.x - 8 > WINSIZE_X)
	{
		_position.x += _speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || _ptMouse.x < 8)
	{
		_position.x -= _speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || _ptMouse.y - 8 > WINSIZE_Y)
	{
		_position.y += _speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) || _ptMouse.y < 8)
	{
		_position.y -= _speed;
	}
}

void Camera::render(void)
{
}
