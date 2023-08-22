#include "../../../FrameWork/PCH/Stdafx.h"
#include "./Player.h"

HRESULT Player::init(void)
{
	_frame = 0;
	_wtp = 10;
	_mobility = 7;
	_type = 0;
	_maxHP = 500.f;
	_curHP = _maxHP;
	_maxMP = 100.f;
	_curMP = _maxMP;
	Character::init();
	return S_OK;
}

void Player::release(void)
{
	Character::release();
}

void Player::update(void)
{
	_frame++;
	if (_isRide)
	{
		if (_state.test(MOVE))
		{
			move();
		}
		else if (_state.test(ATTACK))
		{
			if (_frame == 1)
			{
				SOUNDMANAGER->playSoundFMOD("AjdahakaAttack");
				_isAttack = true;
			}
			else
			{
				_isAttack = false;
				_damage = 0;
			}
			if (_frame / 2 > 23)
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_frame / 5 > 0)
			{
				_curHP -= _damage;
				if (_curHP <= 0)
				{
					_curHP = 0;
					setState(pow(2, DIE));
				}
				else
				{
					_state.reset();
					setDoing(false);
				}
			}
		}
		else if (_state.test(DIE))
		{
			_isRide = false;
			_curHP = _maxMP;
			_state.reset();
			setDoing(false);
		}
	}
	else
	{
		if (!strcmp(_playerName.c_str(), "ªÏ∂ÛµÚ"))
	{
		if (_state.test(MOVE))
		{
			move();
		}
		else if (_state.test(ATTACK))
		{
			if (_frame == 2)
			{
				SOUNDMANAGER->playEffectSoundWave("Resources/Sounds/SoundEffect/SaladinAttack.wav");
			}
			if ((_frame / 10 == 1) || (_frame / 10 == 3))
			{
				_isAttack = true;
			}
			else
			{
				_isAttack = false;
				_damage = 0;
			}
			if (_destTilePos.x - _tilePos.x > 0)
			{
				_dir.reset();
				_dir.set(RIGHT);
			}
			else if (_destTilePos.x - _tilePos.x < 0)
			{
				_dir.reset();
				_dir.set(LEFT);
			}
			else
			{
				if (_destTilePos.y - _tilePos.y > 0)
				{
					_dir.reset();
					_dir.set(DOWN);
				}
				else if (_destTilePos.y - _tilePos.y < 0)
				{
					_dir.reset();
					_dir.set(UP);
				}
			}
			if (_dir.test(LEFT) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
			else if (_dir.test(RIGHT) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
			else if (_dir.test(UP) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
			else if (_dir.test(DOWN) && _frame / 10 > IMAGEMANAGER->findImage("SaladinAttackDown")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
		}
		else if (_state.test(DIE))
		{
			if (255 - 255 / 30 * _frame < 0)
			{
				_isDie = true;
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_frame / 5 > 0)
			{
				_curHP -= _damage;
				if (_curHP <= 0)
				{
					_curHP = 0;
					setState(pow(2, DIE));
				}
				else
				{
					_state.reset();
					setDoing(false);
				}
			}
		}
		else if (_state.test(SKILL))
		{
			if (!strcmp(_skillName, "«≥æ∆ø≠∞¯¬¸"))
			{
				if (_skillOrder.test(0))
				{
					if (_frame == 1)
					{
						SOUNDMANAGER->playSoundFMOD("SaladinSkillStart");
						if (_destTilePos.x - _tilePos.x > 0)
						{
							_dir.reset();
							_dir.set(RIGHT);
						}
						else if (_destTilePos.x - _tilePos.x < 0)
						{
							_dir.reset();
							_dir.set(LEFT);
						}
						else
						{
							if (_destTilePos.y - _tilePos.y > 0)
							{
								_dir.reset();
								_dir.set(DOWN);
							}
							else if (_destTilePos.y - _tilePos.y < 0)
							{
								_dir.reset();
								_dir.set(UP);
							}
						}
					}
				}
				else if (_skillOrder.test(1))
				{
					if (_frame == 1)
					{
						SOUNDMANAGER->playEffectSoundWave("Resources/Sounds/SoundEffect/SaladinAttack.wav");
					}
					if (_frame == (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10 - 1)
					{
						SOUNDMANAGER->playSoundFMOD("FourAttack");
					}
				}
				else if (_skillOrder.test(2))
				{

				}
				else if (_skillOrder.test(3))
				{

				}
			}
			else if (!strcmp(_skillName, "√µ¡ˆ∆ƒø≠π´"))
			{
				if (_skillOrder.test(1))
				{
					if (_frame == 43)
					{
						SOUNDMANAGER->playSoundFMOD("SaladinSkillStart");
					}
				}
			}
			else if (!strcmp(_skillName, "«˜∂˚∏∂»•"))
			{
				if (_skillOrder.test(0))
				{
					if (_frame == 1)
					{
						if (_destTilePos.x - _tilePos.x > 0)
						{
							_dir.reset();
							_dir.set(RIGHT);
						}
						else if (_destTilePos.x - _tilePos.x < 0)
						{
							_dir.reset();
							_dir.set(LEFT);
						}
						else
						{
							if (_destTilePos.y - _tilePos.y > 0)
							{
								_dir.reset();
								_dir.set(DOWN);
							}
							else if (_destTilePos.y - _tilePos.y < 0)
							{
								_dir.reset();
								_dir.set(UP);
							}
						}
					}
				}
				else if (_skillOrder.test(1))
				{

				}
				else if (_skillOrder.test(2))
				{
					if (_dir.test(LEFT))
					{
						if (x > _destTilePos.x * 40 + 40)
						{
							x -= 10;
						}
					}
					else if (_dir.test(RIGHT))
					{
						if (x < _destTilePos.x * 40)
						{
							x += 10;
						}
					}
					else if (_dir.test(UP))
					{
						if (y > _destTilePos.y * 30 + 15)
						{
							y -= 10;
						}
					}
					else if (_dir.test(DOWN))
					{
						if (y < _destTilePos.y * 30 + 15)
						{
							y += 10;
						}
					}
				}
			}
			else if (_skillOrder.test(3))
			{

			}
			if (!_doing)
			{
				_state.reset();
				_turn.set(TURNACTION, false);

			}
		}
	}
		else if (!strcmp(_playerName.c_str(), "√∂∞°∏È"))
	{
		if (_state.test(MOVE))
		{
			move();
		}
		else if (_state.test(ATTACK))
		{
			if (_frame == 20 || _frame == 60)
			{
				SOUNDMANAGER->playSoundFMOD("IronMaskAttack1");

			}
			if ((_frame / 10 == 2) || (_frame / 10 == 6))
			{
				_isAttack = true;
			}
			else
			{
				_isAttack = false;
				_damage = 0;
			}
			if (_destTilePos.x - _tilePos.x > 0)
			{
				_dir.reset();
				_dir.set(RIGHT);
			}
			else if (_destTilePos.x - _tilePos.x < 0)
			{
				_dir.reset();
				_dir.set(LEFT);
			}
			else
			{
				if (_destTilePos.y - _tilePos.y > 0)
				{
					_dir.reset();
					_dir.set(DOWN);
				}
				else if (_destTilePos.y - _tilePos.y < 0)
				{
					_dir.reset();
					_dir.set(UP);
				}
			}
			if (_dir.test(LEFT) && _frame / 10 > IMAGEMANAGER->findImage("IronMaskAttackSide")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
			else if (_dir.test(RIGHT) && _frame / 10 > IMAGEMANAGER->findImage("IronMaskAttackSide")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
			else if (_dir.test(UP) && _frame / 10 > IMAGEMANAGER->findImage("IronMaskAttackUp")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
			else if (_dir.test(DOWN) && _frame / 10 > IMAGEMANAGER->findImage("IronMaskAttackDown")->getMaxFrameX())
			{
				_state.reset();
				setDoing(false);
				_turn.flip(1);
			}
		}
		else if (_state.test(DIE))
		{
			if (255 - 255 / 30 * _frame < 0)
			{
				_isDie = true;
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_frame / 5 > 0)
			{
				_curHP -= _damage;
				if (_curHP <= 0)
				{
					_curHP = 0;
					setState(pow(2, DIE));
				}
				else
				{
					_state.reset();
					setDoing(false);
				}
			}
		}
		else if (_state.test(SKILL))
		{

		}
	}
		else if (!strcmp(_playerName.c_str(), "≈©∏ÆΩ∫∆ºæ”"))
	{
		if (_state.test(MOVE))
		{
			move();
		}
		else if (_state.test(ATTACK))
		{
			if (_destTilePos.x - _tilePos.x > 0)
			{
				_dir.reset();
				_dir.set(RIGHT);
			}
			else if (_destTilePos.x - _tilePos.x < 0)
			{
				_dir.reset();
				_dir.set(LEFT);
			}
			else
			{
				if (_destTilePos.y - _tilePos.y > 0)
				{
					_dir.reset();
					_dir.set(DOWN);
				}
				else if (_destTilePos.y - _tilePos.y < 0)
				{
					_dir.reset();
					_dir.set(UP);
				}
			}
			if (_dir.test(LEFT) || _dir.test(RIGHT))
			{
				if (_frame == 10 || _frame == 80)
				{
					SOUNDMANAGER->playSoundFMOD("GunLoad");
				}
				if (_frame == 50)
				{
					SOUNDMANAGER->playSoundFMOD("ChristianFire");
				}
				if (_frame / 10 == 5 || _frame / 10 == 7)
				{
					_isAttack = true;
				}
				else
				{
					_isAttack = false;
					_damage = 0;
				}
				if (_frame / 10 > IMAGEMANAGER->findImage("ChristianAttackSide")->getMaxFrameX())
				{
					_state.reset();
					setDoing(false);
					_turn.flip(1);
				}
			}
			else if (_dir.test(UP))
			{
				if (_frame == 10 || _frame == 90)
				{
					SOUNDMANAGER->playSoundFMOD("GunLoad");
				}
				if (_frame == 50)
				{
					SOUNDMANAGER->playSoundFMOD("ChristianFire");
				}
				if (_frame / 10 == 4 || _frame / 10 == 6)
				{
					_isAttack = true;
				}
				else
				{
					_isAttack = false;
					_damage = 0;
				}
				if (_frame / 10 > IMAGEMANAGER->findImage("ChristianAttackUp")->getMaxFrameX())
				{
					_state.reset();
					setDoing(false);
					_turn.flip(1);
				}
			}
			else if (_dir.test(DOWN))
			{
				if (_frame == 10 || _frame == 90)
				{
					SOUNDMANAGER->playSoundFMOD("GunLoad");
				}
				if (_frame == 50)
				{
					SOUNDMANAGER->playSoundFMOD("ChristianFire");
				}
				if (_frame / 10 == 5 || _frame / 10 == 7)
				{
					_isAttack = true;
				}
				else
				{
					_isAttack = false;
					_damage = 0;
				}
				if (_frame / 10 > IMAGEMANAGER->findImage("ChristianAttackDown")->getMaxFrameX())
				{
					_state.reset();
					setDoing(false);
					_turn.flip(1);
				}
			}
		}
		else if (_state.test(DIE))
		{
			if (255 - 255 / 30 * _frame < 0)
			{
				_isDie = true;
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_frame / 5 > 0)
			{
				_curHP -= _damage;
				if (_curHP <= 0)
				{
					_curHP = 0;
					setState(pow(2, DIE));
				}
				else
				{
					_state.reset();
					setDoing(false);
				}
			}
		}
		else if (_state.test(SKILL))
		{

		}
	}
		else if (!strcmp(_playerName.c_str(), "¡“æ» ƒ´∆Æ∂Û¿Ã∆Æ"))
	{
		if (_state.test(MOVE))
		{
			move();
		}
		else if (_state.test(ATTACK))
		{
			if (_destTilePos.x - _tilePos.x > 0)
			{
				_dir.reset();
				_dir.set(RIGHT);
			}
			else if (_destTilePos.x - _tilePos.x < 0)
			{
				_dir.reset();
				_dir.set(LEFT);
			}
			else
			{
				if (_destTilePos.y - _tilePos.y > 0)
				{
					_dir.reset();
					_dir.set(DOWN);
				}
				else if (_destTilePos.y - _tilePos.y < 0)
				{
					_dir.reset();
					_dir.set(UP);
				}
			}
			if (_dir.test(LEFT) || _dir.test(RIGHT))
			{
				if (_frame == 20 || _frame == 60)
				{
					SOUNDMANAGER->playSoundFMOD("Rapier");
				}
				if (_frame / 10 == 2 || _frame / 10 == 6)
				{
					_isAttack = true;
				}
				else
				{
					_isAttack = false;
					_damage = 0;
				}
				if (_frame / 10 > IMAGEMANAGER->findImage("JoanAttackSide")->getMaxFrameX())
				{
					_state.reset();
					setDoing(false);
					_turn.flip(1);
				}
			}
			else if (_dir.test(UP))
			{
				if (_frame == 20 || _frame == 60)
				{
					SOUNDMANAGER->playSoundFMOD("Rapier");
				}
				if (_frame / 10 == 2 || _frame / 10 == 6)
				{
					_isAttack = true;
				}
				else
				{
					_isAttack = false;
					_damage = 0;
				}
				if (_frame / 10 > IMAGEMANAGER->findImage("JoanAttackUp")->getMaxFrameX())
				{
					_state.reset();
					setDoing(false);
					_turn.flip(1);
				}
			}
			else if (_dir.test(DOWN))
			{
				if (_frame == 20 || _frame == 60)
				{
					SOUNDMANAGER->playSoundFMOD("Rapier");
				}
				if (_frame / 10 == 2 || _frame / 10 == 6)
				{
					_isAttack = true;
				}
				else
				{
					_isAttack = false;
					_damage = 0;
				}
				if (_frame / 10 > IMAGEMANAGER->findImage("JoanAttackDown")->getMaxFrameX())
				{
					_state.reset();
					setDoing(false);
					_turn.flip(1);
				}
			}
		}
		else if (_state.test(DIE))
		{
			if (255 - 255 / 30 * _frame < 0)
			{
				_isDie = true;
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_frame / 5 > 0)
			{
				_curHP -= _damage;
				if (_curHP <= 0)
				{
					_curHP = 0;
					setState(pow(2, DIE));
				}
				else
				{
					_state.reset();
					setDoing(false);
				}
			}
		}
		else if (_state.test(SKILL))
		{

		}
	}
	}
}

void Player::render(HDC hdc, POINT position, POINT cameraPos)
{
	if (_isRide)
	{
		if (_dir.test(LEFT))
		{
			if (_state.test(ATTACK))
			{
				IMAGEMANAGER->findImage("AjdahakaAttackSideEffect")->alphaFrameRender(hdc, position.x - 80, position.y - 95, (_frame / 2) % 6, LEFT, 128);
			}
			if (_state.test(MOVE))
			{
				IMAGEMANAGER->findImage("AjdahakaSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 225, (_frame / 5) % 12, LEFT);
			}
			else
			{
				IMAGEMANAGER->findImage("AjdahakaSide")->frameRender(hdc, position.x - 40, position.y - 165, (_frame / 5) % 12, LEFT);
			}
		}
		else if (_dir.test(RIGHT))
		{
			if (_state.test(ATTACK))
			{
				IMAGEMANAGER->findImage("AjdahakaAttackSideEffect")->alphaFrameRender(hdc, position.x + 20, position.y - 95, 5 - (_frame / 2) % 6, RIGHT, 128);
			}
			if (_state.test(MOVE))
			{
				IMAGEMANAGER->findImage("AjdahakaSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 100, WINSIZE_Y / 2 - (cameraPos.y - y) - 225, 11 - (_frame / 5) % 12, RIGHT);
			}
			else
			{
				IMAGEMANAGER->findImage("AjdahakaSide")->frameRender(hdc, position.x - 80, position.y - 165, 11 - (_frame / 5) % 12, RIGHT);
			}
		}
		else if (_dir.test(UP))
		{
			if (_state.test(ATTACK))
			{
				IMAGEMANAGER->findImage("AjdahakaAttackUpEffect")->alphaFrameRender(hdc, position.x, position.y - 125, (_frame / 2) % 6, 0, 128);
			}
			if (_state.test(MOVE))
			{
				IMAGEMANAGER->findImage("AjdahakaUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 120, WINSIZE_Y / 2 - (cameraPos.y - y) - 170, (_frame / 5) % 12, 0);
			}
			else
			{
				IMAGEMANAGER->findImage("AjdahakaUp")->frameRender(hdc, position.x - 100, position.y - 110, (_frame / 5) % 12, 0);
			}
		}
		else if (_dir.test(DOWN))
		{
			if (_state.test(ATTACK))
			{
				IMAGEMANAGER->findImage("AjdahakaAttackDownEffect")->alphaFrameRender(hdc, position.x - 40, position.y - 60, (_frame / 2) % 6, 0, 128);
			}
			if (_state.test(MOVE))
			{
				IMAGEMANAGER->findImage("AjdahakaDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 120, WINSIZE_Y / 2 - (cameraPos.y - y) - 195, (_frame / 5) % 12, 0);
			}
			else
			{
				IMAGEMANAGER->findImage("AjdahakaDown")->frameRender(hdc, position.x - 100, position.y - 135, (_frame / 5) % 12, 0);
			}
		}
		if (_state.test(DAMAGED))
		{
			char damageStr[50];
			wsprintf(damageStr, "%d", _damage);
			FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "∞°¿ª√º", 20, 500, damageStr, strlen(damageStr), RGB(255, 0, 0));
		}
	}
	else
	{
		if (!strcmp(_playerName.c_str(), "ªÏ∂ÛµÚ"))
	{
		if (_state.none())
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("SaladinIdleLeft")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 10) % 4, 0);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("SaladinIdleRight")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 10) % 4, 0);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("SaladinIdleUp")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 10) % 4, 0);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("SaladinIdleDown")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 10) % 4, 0);
			}
		}
		if (_state.test(MOVE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 90, (_frame / 5) % 6, 2);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 90, (_frame / 5) % 6, 3);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 90, (_frame / 5) % 6, 0);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 90, (_frame / 5) % 6, 1);
			}
		}
		else if (_state.test(ATTACK))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, _frame / 10, LEFT);
				if (_frame / 10 == 1)
				{
					IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 100, position.y - 60, _frame / 4 - 2, 0, 200);
				}
				if (_frame / 10 > 2)
				{
					IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 100, position.y - 60, _frame / 5 - 3, 0, 200);
				}
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20, 4 - _frame / 10, RIGHT);
				if (_frame / 10 == 1)
				{
					IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 40, position.y - 60, 6 - (_frame / 4 - 2), 1, 200);
				}
				if (_frame / 10 > 2)
				{
					IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 40, position.y - 60, 6 - (_frame / 5 - 3), 1, 200);
				}
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60, _frame / 10, 0);
				if (_frame / 10 == 1)
				{
					IMAGEMANAGER->findImage("SaladinAttackUpEffect")->alphaFrameRender(hdc, position.x - 50, position.y - 100, _frame / 4 - 2, 0, 200);
				}
				if (_frame / 10 > 3)
				{
					IMAGEMANAGER->findImage("SaladinAttackUpEffect")->alphaFrameRender(hdc, position.x - 50, position.y - 100, _frame / 5 - 5, 0, 200);
				}
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, _frame / 10, 0);
				if (_frame / 10 == 1)
				{
					IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 50, _frame / 4 - 2, 0, 200);
				}
				if (_frame / 10 > 2)
				{
					IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, position.x - 45, position.y - 40, _frame / 5 - 3, 0, 200);
				}
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("SaladinDamagedLeft")->render(hdc, position.x, position.y);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("SaladinDamagedRight")->render(hdc, position.x - 20, position.y);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("SaladinDamagedUp")->render(hdc, position.x, position.y);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("SaladinDamagedDown")->render(hdc, position.x - 5, position.y - 10);
			}
			char damageStr[50];
			wsprintf(damageStr, "%d", _damage);
			FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "∞°¿ª√º", 20, 500, damageStr, strlen(damageStr), RGB(255, 0, 0));
		}
		else if (_state.test(DIE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("SaladinDamagedLeft")->alphaRender(hdc, position.x, position.y, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("SaladinDamagedRight")->alphaRender(hdc, position.x - 20, position.y, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("SaladinDamagedUp")->alphaRender(hdc, position.x, position.y, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("SaladinDamagedDown")->alphaRender(hdc, position.x - 5, position.y - 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
		}
		else if (_state.test(SKILL))
		{
			if (!strcmp(_skillName, "√µ¡ˆ∆ƒø≠π´"))
			{
				if (_skillOrder.test(0))
				{
					IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 0, 0);
				}
				else if (_skillOrder.test(1))
				{
					IMAGEMANAGER->findImage("SaladinSkill")->frameRender(hdc, position.x - 29, position.y - 31, _frame / 4, 0);
				}
				else if (_skillOrder.test(2))
				{
					IMAGEMANAGER->findImage("SaladinIdleDown")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
				}
			}
			else if (!strcmp(_skillName, "«≥æ∆ø≠∞¯¬¸"))
			{
				if (_dir.test(LEFT))
				{
					if (_skillOrder.test(0))
					{
						IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, 0, LEFT);
					}
					else if (_skillOrder.test(1))
					{
						if (_frame / 10 <= IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, _frame / 10, LEFT);

							if (_frame / 10 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 100, position.y - 60, _frame / 4 - 2, 0, 200);
							}
							if (_frame / 10 > 2)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 100, position.y - 60, _frame / 5 - 3, 0, 200);
							}
						}
						else if (_frame / 10 > IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() && _frame / 10 < IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, 0, LEFT);
						}
						else if ((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10 < 8)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20,
								((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10) % 2, LEFT);
							if (((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10) % 2 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 100, position.y - 60,
									(_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 4 - 2, 0, 200);
							}
						}
					}
					else if (_skillOrder.test(2))
					{
						if (_frame < 50)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, 0, LEFT);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, 1, LEFT);
							if (_frame < 58)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 100, position.y - 60,
									_frame - 50, 0, 200);
							}
						}
					}
					else if (_skillOrder.test(3))
					{
						IMAGEMANAGER->findImage("SaladinIdleLeft")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 4, 0);
					}
				}
				else if (_dir.test(RIGHT))
				{
					if (_skillOrder.test(0))
					{
						IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20, IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - 0, RIGHT);
					}
					else if (_skillOrder.test(1))
					{
						if (_frame / 10 <= IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20, IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - _frame / 10, RIGHT);

							if (_frame / 10 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 40, position.y - 60, IMAGEMANAGER->findImage("SaladinAttackSideEffect")->getMaxFrameX() - (_frame / 4 - 2), 1, 200);
							}
							if (_frame / 10 > 2)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 40, position.y - 60, IMAGEMANAGER->findImage("SaladinAttackSideEffect")->getMaxFrameX() - (_frame / 5 - 3), 1, 200);
							}
						}
						else if (_frame / 10 > IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() && _frame / 10 < IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20, IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - 0, RIGHT);
						}
						else if ((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10 < 8)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20,
								IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - (((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10) % 2), RIGHT);
							if (((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 10) % 2 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 40, position.y - 60,
									IMAGEMANAGER->findImage("SaladinAttackSideEffect")->getMaxFrameX() - ((_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 4 - 2), 1, 200);
							}
						}
					}
					else if (_skillOrder.test(2))
					{
						if (_frame < 50)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20, IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - 0, RIGHT);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 45, position.y - 20, IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - 1, RIGHT);
							if (_frame < 58)
							{
								IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, position.x - 40, position.y - 60,
									IMAGEMANAGER->findImage("SaladinAttackSideEffect")->getMaxFrameX() - (_frame - 50), 0, 200);
							}
						}
					}
					else if (_skillOrder.test(3))
					{
						IMAGEMANAGER->findImage("SaladinIdleRight")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
					}
				}
				else if (_dir.test(UP))
				{
					if (_skillOrder.test(0))
					{
						IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60, 0, 0);
					}
					else if (_skillOrder.test(1))
					{
						// «—π¯ ªÁ¿Ã≈¨ ∞¯∞›
						if (_frame / 10 <= IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60, _frame / 10, 0);

							if (_frame / 10 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackUpEffect")->alphaFrameRender(hdc, position.x - 50, position.y - 100, _frame / 4 - 2, 0, 200);
							}
							if (_frame / 10 > 2)
							{
								IMAGEMANAGER->findImage("SaladinAttackUpEffect")->alphaFrameRender(hdc, position.x - 50, position.y - 100, _frame / 5 - 3, 0, 200);
							}
						}
						// ¥Î±‚
						else if (_frame / 10 > IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX() && _frame / 10 < IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10)
						{
							IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60, 0, 0);
						}
						// Ω¥Ω¥Ω¥Ωµ
						else if ((_frame - (IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX() + 10) * 10) / 10 < 8)
						{
							IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60,
								((_frame - (IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX() + 10) * 10) / 10) % 2, 0);
							if (((_frame - (IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX() + 10) * 10) / 10) % 2 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackUpEffect")->alphaFrameRender(hdc, position.x - 50, position.y - 100,
									(_frame - (IMAGEMANAGER->findImage("SaladinAttackUp")->getMaxFrameX() + 10) * 10) / 4 - 2, 0, 200);
							}
						}
					}
					else if (_skillOrder.test(2))
					{
						if (_frame < 50)
						{
							IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60, 0, 0);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 40, position.y - 60, 1, 0);
							if (_frame < 58)
							{
								IMAGEMANAGER->findImage("SaladinAttackUpEffect")->alphaFrameRender(hdc, position.x - 50, position.y - 100,
									_frame - 50, 0, 200);
							}
						}
					}
					else if (_skillOrder.test(3))
					{
						IMAGEMANAGER->findImage("SaladinIdleUp")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 4, 0);
					}
				}
				else if (_dir.test(DOWN))
				{
					if (_skillOrder.test(0))
					{
						IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 0, 0);
					}
					else if (_skillOrder.test(1))
					{
						if (_frame / 10 <= IMAGEMANAGER->findImage("SaladinAttackDown")->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, _frame / 10, 0);

							if (_frame / 10 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 50, _frame / 4 - 2, 0, 200);
							}
							if (_frame / 10 > 2)
							{
								IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 50, _frame / 5 - 3, 0, 200);
							}
						}
						else if (_frame / 10 > IMAGEMANAGER->findImage("SaladinAttackDown")->getMaxFrameX() && _frame / 10 < IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10)
						{
							IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 0, 0);
						}
						else if ((_frame - (IMAGEMANAGER->findImage("SaladinAttackDown")->getMaxFrameX() + 10) * 10) / 10 < 8)
						{
							IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20,
								((_frame - (IMAGEMANAGER->findImage("SaladinAttackDown")->getMaxFrameX() + 10) * 10) / 10) % 2, 0);
							if (((_frame - (IMAGEMANAGER->findImage("SaladinAttackDown")->getMaxFrameX() + 10) * 10) / 10) % 2 == 1)
							{
								IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 50,
									(_frame - (IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() + 10) * 10) / 4 - 2, 0, 200);
							}
						}
					}
					else if (_skillOrder.test(2))
					{
						if (_frame < 50)
						{
							IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 0, 0);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 1, 0);
							if (_frame < 58)
							{
								IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, position.x - 35, position.y - 50,
									_frame - 50, 0, 200);
							}
						}
					}
					else if (_skillOrder.test(3))
					{
						IMAGEMANAGER->findImage("SaladinIdleDown")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
					}
				}
			}
			else if (!strcmp(_skillName, "«˜∂˚∏∂»•"))
			{
				if (_skillOrder.test(0))
				{
					IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 0, 0);
				}
				else if (_skillOrder.test(1))
				{
					IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 0, 0);
				}
				else if (_skillOrder.test(2))
				{
					if (_dir.test(LEFT))
					{
						IMAGEMANAGER->findImage("SaladinDashLeft")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 60);
						if (_frame > (_tilePos.x - _destTilePos.x) * 40 / 20)
						{
							IMAGEMANAGER->findImage("SaladinDashLeft")->render(hdc, position.x - 10 * (_frame - (_tilePos.x - _destTilePos.x) * 40 / 20) - 40, WINSIZE_Y / 2 - (cameraPos.y - y) - 90);
							IMAGEMANAGER->findImage("SaladinDashLeft")->render(hdc, position.x - 10 * (_frame - (_tilePos.x - _destTilePos.x) * 40 / 20) - 40, WINSIZE_Y / 2 - (cameraPos.y - y) - 30);
						}
						// ¿‹ªÛ
						for (int i = 1; x + 20 * i <= _tilePos.x * 40 + 20; i++)
						{
							IMAGEMANAGER->findImage("SaladinDashLeft")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (x + 20 * i)) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 60,
								255 - 10 * i - _frame * 3 < 0 ? 0 : 255 - 10 * i - _frame * 3);
						}
					}
					else if (_dir.test(RIGHT))
					{
						IMAGEMANAGER->findImage("SaladinDashRight")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 60);
						if (_frame > (_destTilePos.x - _tilePos.x) * 40 / 20)
						{
							IMAGEMANAGER->findImage("SaladinDashRight")->render(hdc, position.x + 10 * (_frame - (_destTilePos.x - _tilePos.x) * 40 / 20), WINSIZE_Y / 2 - (cameraPos.y - y) - 90);
							IMAGEMANAGER->findImage("SaladinDashRight")->render(hdc, position.x + 10 * (_frame - (_destTilePos.x - _tilePos.x) * 40 / 20), WINSIZE_Y / 2 - (cameraPos.y - y) - 30);
						}
						// ¿‹ªÛ
						for (int i = 1; x - 20 * i >= _tilePos.x * 40 + 20; i++)
						{
							IMAGEMANAGER->findImage("SaladinDashRight")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - (x - 20 * i)) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 60,
								255 - 10 * i - _frame * 3 < 0 ? 0 : 255 - 10 * i - _frame * 3);
						}
					}
					else if (_dir.test(UP))
					{
						IMAGEMANAGER->findImage("SaladinDashUp")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 40, WINSIZE_Y / 2 - (cameraPos.y - y) - 80);
						if (_frame >= (_tilePos.y - _destTilePos.y) * 30 / 20)
						{
							IMAGEMANAGER->findImage("SaladinDashUp")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 80, position.y - 10 * (_frame - (_tilePos.y - _destTilePos.y) * 30 / 20) - 15);
							IMAGEMANAGER->findImage("SaladinDashUp")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x), position.y - 10 * (_frame - (_tilePos.y - _destTilePos.y) * 30 / 20) - 15);
						}
						// ¿‹ªÛ
						for (int i = 1; y + 20 * i <= _tilePos.y * 30 + 15; i++)
						{
							IMAGEMANAGER->findImage("SaladinDashUp")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 40, WINSIZE_Y / 2 - (cameraPos.y - (y + 20 * i)) - 80,
								255 - 10 * i - _frame * 3 < 0 ? 0 : 255 - 10 * i - _frame * 3);
						}
					}
					else if (_dir.test(DOWN))
					{
						IMAGEMANAGER->findImage("SaladinDashDown")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 30, WINSIZE_Y / 2 - (cameraPos.y - y) - 60);
						if (_frame > (float)(_destTilePos.y - _tilePos.y) * 30.f / 20.f)
						{
							IMAGEMANAGER->findImage("SaladinDashDown")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 70, position.y + 10 * (_frame - (float)(_destTilePos.y - _tilePos.y) * 30.f / 20.f));
							IMAGEMANAGER->findImage("SaladinDashDown")->render(hdc, WINSIZE_X / 2 - (cameraPos.x - x) + 10, position.y + 10 * (_frame - (float)(_destTilePos.y - _tilePos.y) * 30.f / 20.f));
						}
						// ¿‹ªÛ
						for (int i = 1; y - 20 * i >= _tilePos.y * 30 + 15; i++)
						{
							IMAGEMANAGER->findImage("SaladinDashDown")->alphaRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 30, WINSIZE_Y / 2 - (cameraPos.y - (y - 20 * i)) - 60,
								255 - 10 * i - _frame * 3 < 0 ? 0 : 255 - 10 * i - _frame * 3);
						}
					}
				}
				else if (_skillOrder.test(3))
				{
					if (_dir.test(LEFT))
					{
						if (_frame / 4 < 3)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 110, WINSIZE_Y / 2 - (cameraPos.y - y) - 80, IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - 1, LEFT);
							IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 120, WINSIZE_Y / 2 - (cameraPos.y - y) - 105, _frame / 4, 0, 200);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 70, position.y - 20, 0, LEFT);
						}
					}
					else if (_dir.test(RIGHT))
					{
						if (_frame / 4 < 3)
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 50, WINSIZE_Y / 2 - (cameraPos.y - y) - 80,
								IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX() - 1, RIGHT);
							IMAGEMANAGER->findImage("SaladinAttackSideEffect")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60,
								WINSIZE_Y / 2 - (cameraPos.y - y) - 105, IMAGEMANAGER->findImage("SaladinAttackSideEffect")->getMaxFrameX() - _frame / 4, 1, 200);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackSide")->frameRender(hdc, position.x - 50, position.y - 20,
								IMAGEMANAGER->findImage("SaladinAttackSide")->getMaxFrameX(), RIGHT);
						}
					}
					else if (_dir.test(UP))
					{
						if (_frame / 4 < 3)
						{
							IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 50, WINSIZE_Y / 2 - (cameraPos.y - y) - 110, 1, 0);
							IMAGEMANAGER->findImage("SaladinAttackUpEffect")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 70,
								WINSIZE_Y / 2 - (cameraPos.y - y) - 115, _frame / 4, 0, 200);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackUp")->frameRender(hdc, position.x - 30, position.y - 50, 0, 0);
						}
					}
					else if (_dir.test(DOWN))
					{
						if (_frame / 4 < 3)
						{
							IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 50, WINSIZE_Y / 2 - (cameraPos.y - y) - 80, 1, 0);
							IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 50,
								WINSIZE_Y / 2 - (cameraPos.y - y) - 110, _frame / 4, 0, 200);
						}
						else
						{
							IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 30, position.y - 15, 0, 0);
						}
					}
				}
			}
		}
	}
		else if (!strcmp(_playerName.c_str(), "√∂∞°∏È"))
	{
		if (_state.none())
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("IronMaskIdleSide")->frameRender(hdc, position.x - 15, position.y - 10, (_frame / 10) % 3, 0);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("IronMaskIdleSide")->frameRender(hdc, position.x - 5, position.y - 10, 2 - (_frame / 10) % 3, 1);

			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("IronMaskIdleUp")->frameRender(hdc, position.x - 15, position.y - 10, (_frame / 10) % 3, 0);

			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("IronMaskIdleDown")->frameRender(hdc, position.x - 15, position.y - 10, (_frame / 10) % 3, 0);
			}
		}
		else if (_state.test(MOVE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("IronMaskMoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 30, WINSIZE_Y / 2 - (cameraPos.y - y) - 75, (_frame / 10) % 6, 0);

			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("IronMaskMoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 75, 5 - (_frame / 10) % 6, 1);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("IronMaskMoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 75, (_frame / 10) % 6, 0);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("IronMaskMoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 60, WINSIZE_Y / 2 - (cameraPos.y - y) - 75, (_frame / 10) % 6, 0);
			}
		}
		else if (_state.test(ATTACK))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("IronMaskAttackSide")->frameRender(hdc, position.x - 108, position.y - 45, _frame / 10, LEFT);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("IronMaskAttackSide")->frameRender(hdc, position.x - 37, position.y - 45, 7 - (_frame / 10), RIGHT);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("IronMaskAttackUp")->frameRender(hdc, position.x - 20, position.y - 70, _frame / 10, 0);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("IronMaskAttackDown")->frameRender(hdc, position.x - 50, position.y - 30, _frame / 10, 0);
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedSide")->frameRender(hdc, position.x, position.y - 5, 0, LEFT);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedSide")->frameRender(hdc, position.x - 45, position.y - 5, 0, RIGHT);

			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedUp")->render(hdc, position.x, position.y + 10);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedDown")->render(hdc, position.x - 20, position.y - 5);
			}
			char damageStr[50];
			wsprintf(damageStr, "%d", _damage);
			FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "∞°¿ª√º", 20, 500, damageStr, strlen(damageStr), RGB(255, 0, 0));
		}
		else if (_state.test(DIE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedSide")->alphaFrameRender(hdc, position.x, position.y - 5, 0, LEFT, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedSide")->alphaFrameRender(hdc, position.x - 45, position.y - 5, 0, RIGHT, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedUp")->alphaRender(hdc, position.x, position.y + 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("IronMaskDamagedDown")->alphaRender(hdc, position.x - 20, position.y - 5, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
		}
		else if (_state.test(SKILL))
		{

		}
	}
		else if (!strcmp(_playerName.c_str(), "≈©∏ÆΩ∫∆ºæ”"))
	{
		if (_state.none())
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("ChristianIdleSide")->frameRender(hdc, position.x + 5, position.y - 5, _frame / 10 % 3, 0);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("ChristianIdleSide")->frameRender(hdc, position.x + 5, position.y - 5, 2 - _frame / 10 % 3, 1);

			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("ChristianIdleUp")->frameRender(hdc, position.x + 5, position.y, _frame / 10 % 3, 0);

			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("ChristianIdleDown")->frameRender(hdc, position.x, position.y - 5, _frame / 10 % 3, 0);
			}
		}
		else if (_state.test(MOVE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("ChristianMoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_Y / 2 - (cameraPos.y - y) - 65, _frame / 10 % 6, 0);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("ChristianMoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 65, 5 - _frame / 10 % 6, 1);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("ChristianMoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 65, _frame / 10 % 6, 0);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("ChristianMoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 65, _frame / 10 % 6, 0);
			}
		}
		else if (_state.test(ATTACK))
		{
			if (_dir.test(LEFT))
			{
				if (_frame / 10 == 8)
				{
					IMAGEMANAGER->findImage("GunTurnSide")->frameRender(hdc, position.x - 5, position.y + 25, _frame % 8, 0);
				}
				IMAGEMANAGER->findImage("ChristianAttackSide")->frameRender(hdc, position.x - 28, position.y - 28, _frame / 10 % 10, LEFT);
				if (_frame / 10 == 8)
				{
					IMAGEMANAGER->findImage("GunTurnSide")->frameRender(hdc, position.x + 15, position.y + 30, _frame % 8, 0);
				}
				if (_frame / 10 > 4)
				{
					IMAGEMANAGER->findImage("GunFireSide")->alphaFrameRender(hdc, position.x - 85, position.y - 30, (_frame - 50) / 2, 0, 128);
				}
				if (_frame / 10 > 6)
				{
					IMAGEMANAGER->findImage("GunFireSide")->alphaFrameRender(hdc, position.x - 70, position.y - 30, (_frame - 70) / 2, 0, 128);
				}
			}
			else if (_dir.test(RIGHT))
			{
				if(_frame / 10 == 8)
				{
					IMAGEMANAGER->findImage("GunTurnSide")->frameRender(hdc, position.x + 15, position.y + 25, _frame % 8, 0);
				}
				IMAGEMANAGER->findImage("ChristianAttackSide")->frameRender(hdc, position.x - 2, position.y - 28, 9 - _frame / 10 % 10, RIGHT);
				if (_frame / 10 == 8)
				{
					IMAGEMANAGER->findImage("GunTurnSide")->frameRender(hdc, position.x - 5, position.y + 30, _frame % 8, 0);
				}
				if (_frame / 10 > 4)
				{
					IMAGEMANAGER->findImage("GunFireSide")->alphaFrameRender(hdc, position.x + 15, position.y - 30, 7 - (_frame - 50) / 2, 1, 128);
				}
				if (_frame / 10 > 6)
				{
					IMAGEMANAGER->findImage("GunFireSide")->alphaFrameRender(hdc, position.x + 30, position.y - 30, 7 - (_frame - 70) / 2, 1, 128);
				}
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("ChristianAttackUp")->frameRender(hdc, position.x - 15, position.y - 35, _frame / 10, 0);
				if (_frame / 10 ==9)
				{
					IMAGEMANAGER->findImage("GunTurnUpDown")->frameRender(hdc, position.x - 5, position.y + 30, _frame % 8, 0);
					IMAGEMANAGER->findImage("GunTurnUpDown")->frameRender(hdc, position.x + 40, position.y + 30, _frame % 8, 0);
				}
				if (_frame / 10 > 3)
				{
					IMAGEMANAGER->findImage("GunFireUp")->alphaFrameRender(hdc, position.x - 25, position.y - 80, (_frame - 40) / 2, 0, 128);
				}
				if (_frame / 10 > 5)
				{
					IMAGEMANAGER->findImage("GunFireUp")->alphaFrameRender(hdc, position.x - 10, position.y - 80, (_frame - 60) / 2, 0, 128);
				}
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("ChristianAttackDown")->frameRender(hdc, position.x - 15, position.y - 20, _frame / 10, 0);
				if(_frame / 10 == 8)
				{
					IMAGEMANAGER->findImage("GunTurnUpDown")->frameRender(hdc, position.x, position.y + 25, _frame % 8, 0);
					IMAGEMANAGER->findImage("GunTurnUpDown")->frameRender(hdc, position.x + 35, position.y + 25, _frame % 8, 0);
				}
				if (_frame / 10 > 4)
				{
					IMAGEMANAGER->findImage("GunFireDown")->alphaFrameRender(hdc, position.x - 25, position.y - 5, (_frame - 50) / 2 , 0, 128);
				}
				if (_frame / 10 > 6)
				{
					IMAGEMANAGER->findImage("GunFireDown")->alphaFrameRender(hdc, position.x - 15, position.y - 5, (_frame - 70) / 2, 0, 128);
				}
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("ChristianDamagedSide")->frameRender(hdc, position.x - 5, position.y + 10, 0, LEFT);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("ChristianDamagedSide")->frameRender(hdc, position.x, position.y + 10, 0, RIGHT);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("ChristianDamagedUp")->render(hdc, position.x + 5, position.y + 5);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("ChristianDamagedDown")->render(hdc, position.x, position.y + 10);
			}
			char damageStr[50];
			wsprintf(damageStr, "%d", _damage);
			FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "∞°¿ª√º", 20, 500, damageStr, strlen(damageStr), RGB(255, 0, 0));
		}
		else if (_state.test(DIE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("ChristianDamagedSide")->alphaFrameRender(hdc, position.x - 5, position.y + 10, 0, LEFT, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("ChristianDamagedSide")->alphaFrameRender(hdc, position.x, position.y  + 10, 0, RIGHT, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("ChristianDamagedUp")->alphaRender(hdc, position.x + 5, position.y + 5, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("ChristianDamagedDown")->alphaRender(hdc, position.x, position.y + 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
		}
		else if (_state.test(SKILL))
		{

		}
	}
		else if (!strcmp(_playerName.c_str(), "¡“æ» ƒ´∆Æ∂Û¿Ã∆Æ"))
	{
		if (_state.none())
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("JoanIdleSide")->frameRender(hdc, position.x, position.y, (_frame / 10) % 3, 0);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("JoanIdleSide")->frameRender(hdc, position.x + 5, position.y, 2 - (_frame / 10) % 3, 1);

			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("JoanIdleUp")->frameRender(hdc, position.x + 5, position.y - 5, (_frame / 10) % 3, 0);

			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("JoanIdleDown")->frameRender(hdc, position.x + 5, position.y, (_frame / 10) % 3, 0);

			}
		}
		else if (_state.test(MOVE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("JoanMoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 35, WINSIZE_Y / 2 - (cameraPos.y - y) - 60, (_frame / 10) % 6, 0);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("JoanMoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_Y / 2 - (cameraPos.y - y) - 60, 5 - (_frame / 10) % 6, 1);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("JoanMoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 18, WINSIZE_Y / 2 - (cameraPos.y - y) - 65, (_frame / 10) % 6, 0);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("JoanMoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_Y / 2 - (cameraPos.y - y) - 60, (_frame / 10) % 6, 0);
			}
		}
		else if (_state.test(ATTACK))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("JoanAttackSide")->frameRender(hdc, position.x - 63, position.y + 2, _frame / 10, LEFT);
				if ((_frame / 10 == 2) && (_frame - 20 < 16))
				{
					IMAGEMANAGER->findImage("JoanAttackSideEffect1")->alphaFrameRender(hdc, position.x - 83, position.y - 5, (_frame - 20) / 2, LEFT, 128);
				}
				if ((_frame / 10 == 6) && (_frame - 60 < 10))
				{
					IMAGEMANAGER->findImage("JoanAttackSideEffect2")->alphaFrameRender(hdc, position.x - 83, position.y - 16, (_frame - 60) / 2, LEFT, 128);
				}
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("JoanAttackSide")->frameRender(hdc, position.x - 18, position.y + 2, 7 - _frame / 10, RIGHT);
				if ((_frame / 10 == 2) && (_frame - 20 < 16))
				{
					IMAGEMANAGER->findImage("JoanAttackSideEffect1")->alphaFrameRender(hdc, position.x - 3, position.y - 5, 7 - (_frame - 20) / 2, RIGHT, 128);
				}
				if ((_frame / 10 == 6) && (_frame - 60 < 10))
				{
					IMAGEMANAGER->findImage("JoanAttackSideEffect2")->alphaFrameRender(hdc, position.x - 3, position.y - 14, 4 - (_frame - 60) / 2, RIGHT, 128);
				}
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("JoanAttackUp")->frameRender(hdc, position.x - 5, position.y - 43, _frame / 10, 0);
				if ((_frame / 10 == 2) && (_frame - 20 < 16))
				{
					IMAGEMANAGER->findImage("JoanAttackUpEffect1")->alphaFrameRender(hdc, position.x - 25, position.y - 37, (_frame - 20) / 2, 0, 128);
				}
				if ((_frame / 10 == 6) && (_frame - 60 < 10))
				{
					IMAGEMANAGER->findImage("JoanAttackUpEffect2")->alphaFrameRender(hdc, position.x - 20, position.y - 67, (_frame - 60) / 2, 0, 128);
				}
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("JoanAttackDown")->frameRender(hdc, position.x - 32, position.y + 12, _frame / 10, 0);
				if ((_frame / 10 == 2) && (_frame - 20 < 18))
				{
					IMAGEMANAGER->findImage("JoanAttackDownEffect1")->alphaFrameRender(hdc, position.x - 25, position.y + 23, (_frame - 20) / 2, 0, 128);
				}
				if ((_frame / 10 == 6) && (_frame - 60 < 10))
				{
					IMAGEMANAGER->findImage("JoanAttackDownEffect2")->alphaFrameRender(hdc, position.x - 24, position.y - 3, (_frame - 60) / 2, 0, 128);
				}
			}
		}
		else if (_state.test(DAMAGED))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("JoanDamagedSide")->frameRender(hdc, position.x + 5, position.y + 15, 0, LEFT);

			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("JoanDamagedSide")->frameRender(hdc, position.x, position.y + 15, 0, RIGHT);

			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("JoanDamagedUp")->render(hdc, position.x, position.y + 10);

			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("JoanDamagedDown")->render(hdc, position.x, position.y + 15);
			}
			char damageStr[50];
			wsprintf(damageStr, "%d", _damage);
			FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "∞°¿ª√º", 20, 500, damageStr, strlen(damageStr), RGB(255, 0, 0));
		}
		else if (_state.test(DIE))
		{
			if (_dir.test(LEFT))
			{
				IMAGEMANAGER->findImage("JoanDamagedSide")->alphaFrameRender(hdc, position.x + 5, position.y + 15, 0, LEFT, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(RIGHT))
			{
				IMAGEMANAGER->findImage("JoanDamagedSide")->alphaFrameRender(hdc, position.x, position.y + 15, 0, RIGHT, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(UP))
			{
				IMAGEMANAGER->findImage("JoanDamagedUp")->alphaRender(hdc, position.x, position.y + 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
			else if (_dir.test(DOWN))
			{
				IMAGEMANAGER->findImage("JoanDamagedDown")->alphaRender(hdc, position.x, position.y + 15, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
			}
		}
		else if (_state.test(SKILL))
		{

		}
	}
	}
}