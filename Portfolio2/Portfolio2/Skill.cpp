#include "Stdafx.h"
#include "Skill.h"

HRESULT Skill::init(void)
{
	_frame = 0;
	_isFinish = true;
	_order.reset();
	return S_OK;
}

void Skill::update(void)
{
	_frame++;
	if(_order.test(0))
	{
		if ((_frame - 1) / 2 > IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX())
		{
			_order = _order << 1;
			_frame = 0;
		}
	}
}

void Skill::render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight)
{
	if(_order.test(0))
	{
		IMAGEMANAGER->findImage("SkillCasting")->alphaFrameRender(hdc, position.x - IMAGEMANAGER->findImage("SkillCasting")->getFrameWidth() / 2 + 10, 
		position.y - IMAGEMANAGER->findImage("SkillCasting")->getFrameHeight() / 2 + 30, (_frame - 1) / 2 % (IMAGEMANAGER->findImage("SkillCasting")->getMaxFrameX() +  1), 0, 200);
	}
	if (_order.test(1))
	{
		for (auto it = _charList.begin(); it != _charList.end(); ++it)
		{
			if ((*it)->getType() == 1) {
				continue;
			}
			IMAGEMANAGER->findImage("VermontSkillEFX1")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (*it)->getTilePos().x * tileWidth) - 25, 
				WINSIZE_Y / 2 - (cameraPos.y - (*it)->getTilePos().y * tileHeight) - 85, (_frame - 1) / 3 > 16 ? 15 : (_frame - 1) / 3, 0, 150);
		}
	}
}

void Skill::release(void)
{
}

int Skill::getOrder()
{
	for (int i = 0; i < _order.size(); i++)
	{
		if (_order.test(i))
		{
			return i;
		}
	}
}

void Skill::start(vector<Character*> charList)
{
	_frame = 0;
	_charList = charList;
	_order.set(0);
	_isFinish = false;
}
