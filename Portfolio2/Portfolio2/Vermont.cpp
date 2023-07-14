#include "Stdafx.h"
#include "Vermont.h"

HRESULT Vermont::init(void)
{
	_frame = 0;
	_wtp = 10;
	_curWait = _wtp;
	_mobility = 5;
	_type = 1;
	Character::init();
	return S_OK;
}

void Vermont::release(void)
{
}

void Vermont::update(void)
{
	_frame++;
	if (_state.test(MOVE))
	{
		if (_frame % 5 == 0)
		{
			move();
		}
	}
	else if (_state.test(ATTACK))
	{	
		if (_frame == 3)
		{
			SOUNDMANAGER->playEffectSoundWave("Resources/Sounds/SoundEffect/VermontAttack.wav");
			//SOUNDMANAGER->playSoundFMOD("VermontAttack");
		}
		if (_dir.test(LEFT) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackLeft")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(RIGHT) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackRight")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(UP) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackUp")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(DOWN) && _frame / 10 > IMAGEMANAGER->findImage("VermontAttackDown")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
	}
}

void Vermont::render(HDC hdc, POINT position)
{
	//IMAGEMANAGER->findImage("VermontAttackDown")->frameRender(hdc, position.x - 35, position.y - 30, 2, 0);
	//IMAGEMANAGER->findImage("VermontAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 25, 0, 0, 200);
	if (_state.none())
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
	else if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("VermontAttackLeft")->frameRender(hdc, position.x - 30, position.y - 40, (_frame / 10) % 4, 0);
			if((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackSideEffect")->alphaFrameRender(hdc, position.x - 60, position.y - 40, (_frame / 5) % 4, 0, 200);
			}
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("VermontAttackRight")->frameRender(hdc, position.x - 45, position.y - 40, 3 - (_frame / 10) % 4, 0);
			if ((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackSideEffect")->alphaFrameRender(hdc, position.x - 60, position.y - 40, 3 - (_frame / 5) % 4, 1, 200);
			}
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("VermontAttackUp")->frameRender(hdc, position.x - 20, position.y, (_frame / 10) % 4, 0);
			if ((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackUpEffect")->alphaFrameRender(hdc, position.x - 45, position.y - 35, (_frame / 5) % 4, 0, 200);
			}
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("VermontAttackDown")->frameRender(hdc, position.x - 35, position.y - 30, (_frame / 10) % 4, 0);
			if ((_frame / 10) % 4 > 1)
			{
				IMAGEMANAGER->findImage("VermontAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 25, (_frame / 5) % 4, 0, 200);
			}
		}
	}
}
