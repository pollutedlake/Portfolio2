#include "../FrameWork/PCH/Stdafx.h"
#include "./Camera.h"

HRESULT Camera::init(void)
{
	_limitRC.left = WINSIZE_X / 2;
	_limitRC.top = WINSIZE_Y / 2;
	_speed = 10;
	return S_OK;
}

void Camera::release(void)
{
}

// 방향키 입력 또는 마우스로 카메라 이동
void Camera::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || _ptMouse.x > WINSIZE_X - 8)
	{
		_position.x += _speed;
		if (_position.x > _limitRC.right)
		{
			_position.x = _limitRC.right;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || _ptMouse.x < 8)
	{
		_position.x -= _speed;
		if (_position.x < _limitRC.left)
		{
			_position.x = _limitRC.left;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || _ptMouse.y > WINSIZE_Y  - 8)
	{
		_position.y += _speed;
		if (_position.y > _limitRC.bottom)
		{
			_position.y = _limitRC.bottom;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) || _ptMouse.y < 8)
	{
		_position.y -= _speed;
		if (_position.y < _limitRC.top)
		{
			_position.y = _limitRC.top;
		}
	}
	if (_position.x < _limitRC.left)
	{
		_position.x = _limitRC.left;
	}
	if (_position.x > _limitRC.right)
	{
		_position.x = _limitRC.right;
	}
	if (_position.y < _limitRC.top)
	{
		_position.y = _limitRC.top;
	}
	if (_position.y > _limitRC.bottom)
	{
		_position.y = _limitRC.bottom;
	}
}

void Camera::render(void)
{
}

void Camera::setPosition(POINT position)
{
	_position = position;
	if (_position.x < _limitRC.left)
	{
		_position.x = _limitRC.left;
	}
	if (_position.x > _limitRC.right)
	{
		_position.x = _limitRC.right;
	}
	if (_position.y < _limitRC.top)
	{
		_position.y = _limitRC.top;
	}
	if (_position.y > _limitRC.bottom)
	{
		_position.y = _limitRC.bottom;
	}
}

// 월드 좌표계에서 카메라 좌표계로 변환
POINT Camera::worldToCamera(POINT point)
{
	return PointMake(WINSIZE_X / 2 - (_position.x - point.x), WINSIZE_Y / 2 - (_position.y - point.y));
}
