#include "Stdafx.h"
#include "Soldier.h"

HRESULT Soldier::init(EnemyType enemyType)
{
	_frame = 0;
	_wtp = 10;
	_mobility = 5;
	_type = 1;
	_maxHP = 50.f;
	_curHP = _maxHP;
	_maxMP = 100.f;
	_curMP = 0;
	_enemyType = enemyType;
	Character::init();
	return S_OK;
}

void Soldier::release(void)
{
	Enemy::release();
}

// 병사의 상태, 방향, 타입에 따라 다른 이미지, 소리를 출력한다.
void Soldier::update(void)
{
	_frame++;
	if (_state.test(MOVE))
	{
		move();
	}
	else if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT) || _dir.test(RIGHT))
		{
			switch (_enemyType)
			{
				case EnemyType::SOLDIER1:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Fire");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier1AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER2:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("Thrust");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier2AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER3:
					if (_frame == 10)
					{
						SOUNDMANAGER->playSoundFMOD("Bang");
					}
					if (_frame / 10 == 1)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier3AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER4:
					if (_frame == 20 || _frame == 70)
					{
						SOUNDMANAGER->playSoundFMOD("IronMaskAttack1");
					}
					if (_frame / 10 == 2 || _frame / 10 == 7)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier4AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER5:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Machinegun");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier5AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER6:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("Sword");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier6AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER8:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("IronMaskAttack1");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier8AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER9:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Sword");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier9AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER10:
					if (_frame == 30)
					{
						SOUNDMANAGER->playSoundFMOD("Tang");
					}
					if (_frame / 10 == 3)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier10AttackSide")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
				case EnemyType::SOLDIER1:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Fire");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier1AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER2:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("Thrust");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier2AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER3:
					if (_frame == 10)
					{
						SOUNDMANAGER->playSoundFMOD("Bang");
					}
					if (_frame / 10 == 1)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier3AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER4:
					if (_frame == 20 || _frame == 70)
					{
						SOUNDMANAGER->playSoundFMOD("IronMaskAttack1");
					}
					if (_frame / 10 == 2 || _frame / 10 == 7)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if(_frame / 10 > IMAGEMANAGER->findImage("Soldier4AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER5:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Machinegun");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier5AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER6:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("Sword");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier6AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER8:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("IronMaskAttack1");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier8AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER9:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Sword");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier9AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER10:
					if (_frame == 30)
					{
						SOUNDMANAGER->playSoundFMOD("Tang");
					}
					if (_frame / 10 == 3)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier10AttackUp")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch(_enemyType)
			{
				case EnemyType::SOLDIER1:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Fire");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier1AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER2:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("Thrust");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier2AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER3:
					if (_frame == 10)
					{
						SOUNDMANAGER->playSoundFMOD("Bang");
					}
					if (_frame / 10 == 1)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier3AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER4:
					if (_frame == 20 || _frame == 70)
					{
						SOUNDMANAGER->playSoundFMOD("IronMaskAttack1");
					}
					if (_frame / 10 == 2 || _frame / 10 == 7)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier4AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
				case EnemyType::SOLDIER5:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Machinegun");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier5AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER6:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("Sword");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier6AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER8:
					if (_frame == 20 || _frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("IronMaskAttack1");
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
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier8AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER9:
					if (_frame == 20)
					{
						SOUNDMANAGER->playSoundFMOD("Sword");
					}
					if (_frame / 10 == 2)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier9AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
					break;
				case EnemyType::SOLDIER10:
					if (_frame == 30)
					{
						SOUNDMANAGER->playSoundFMOD("Tang");
					}
					if (_frame / 10 == 3)
					{
						_isAttack = true;
					}
					else
					{
						_isAttack = false;
						_damage = 0;
					}
					if (_frame / 10 > IMAGEMANAGER->findImage("Soldier10AttackDown")->getMaxFrameX())
					{
						_state.reset();
						setDoing(false);
						endTurn();
					}
				break;
			}
		}
	}
	else if (_state.test(DAMAGED))
	{
		if (_frame / 5 > 0)
		{
			_curHP -= _damage;
			if (_curHP < 0)
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
	else if (_state.test(DIE))
	{
		if (255 - 255 / 30 * _frame < 0)
		{
			_isDie = true;
		}
	}
}

void Soldier::render(HDC hdc, POINT position, POINT cameraPos)
{
	if (_state.none())
	{
		if (_dir.test(LEFT))
		{
			switch(_enemyType)
			{
				case EnemyType::SOLDIER1:
					IMAGEMANAGER->findImage("Soldier1IdleSide")->frameRender(hdc, position.x - 5, position.y - 10, (_frame / 10) % 3, 0);
				break;
				case EnemyType::SOLDIER2:
					IMAGEMANAGER->findImage("Soldier2IdleSide")->frameRender(hdc, position.x + 5, position.y - 30, (_frame / 10) % 3, 0);
					break;
				case EnemyType::SOLDIER3:
					IMAGEMANAGER->findImage("Soldier3IdleSide")->frameRender(hdc, position.x, position.y, (_frame / 10) % 3, 0);
					break;
				case EnemyType::SOLDIER4:
					IMAGEMANAGER->findImage("Soldier4IdleSide")->frameRender(hdc, position.x - 25, position.y - 5, (_frame / 10) % 3, 0);
				break;
				case EnemyType::SOLDIER5:
					IMAGEMANAGER->findImage("Soldier5IdleSide")->frameRender(hdc, position.x - 5, position.y, (_frame / 10) % 3, 0);
					break;
				case EnemyType::SOLDIER6:
					IMAGEMANAGER->findImage("Soldier6IdleSide")->frameRender(hdc, position.x, position.y- 5, (_frame / 10) % 3, 0);
					break;
				case EnemyType::SOLDIER8:
					IMAGEMANAGER->findImage("Soldier8IdleSide")->frameRender(hdc, position.x - 5, position.y - 5, (_frame / 10) % 3, 0);
					break;
				case EnemyType::SOLDIER9:
					IMAGEMANAGER->findImage("Soldier9IdleSide")->frameRender(hdc, position.x - 5, position.y, (_frame / 10) % 3, 0);
					break;
				case EnemyType::SOLDIER10:
					IMAGEMANAGER->findImage("Soldier10IdleSide")->frameRender(hdc, position.x - 20, position.y + 5, (_frame / 10) % 3, 0);
					break;
			}
		}
		else if (_dir.test(RIGHT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1IdleSide")->frameRender(hdc, position.x, position.y - 10, (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2IdleSide")->frameRender(hdc, position.x + 5, position.y - 30, (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3IdleSide")->frameRender(hdc, position.x, position.y, (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4IdleSide")->frameRender(hdc, position.x + 5, position.y - 5, 2 - (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5IdleSide")->frameRender(hdc, position.x - 5, position.y, 2 - (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6IdleSide")->frameRender(hdc, position.x + 5, position.y - 5, 2 - (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8IdleSide")->frameRender(hdc, position.x + 5, position.y - 5, 2 - (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9IdleSide")->frameRender(hdc, position.x - 5, position.y, 2 - (_frame / 10) % 3, 1);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10IdleSide")->frameRender(hdc, position.x + 5, position.y + 5, 2 - (_frame / 10) % 3, 1);
				break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1IdleUp")->frameRender(hdc, position.x + 5, position.y - 5, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2IdleUp")->frameRender(hdc, position.x, position.y - 15, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3IdleUp")->frameRender(hdc, position.x - 5, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4IdleUp")->frameRender(hdc, position.x + 5, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5IdleUp")->frameRender(hdc, position.x + 5, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6IdleUp")->frameRender(hdc, position.x + 5, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8IdleUp")->frameRender(hdc, position.x - 5, position.y - 5, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9IdleUp")->frameRender(hdc, position.x + 5, position.y - 5, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10IdleUp")->frameRender(hdc, position.x + 5, position.y - 5, (_frame / 10) % 3, 0);
				break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1IdleDown")->frameRender(hdc, position.x, position.y - 5, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2IdleDown")->frameRender(hdc, position.x - 5, position.y - 25, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3IdleDown")->frameRender(hdc, position.x + 5, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4IdleDown")->frameRender(hdc, position.x - 5, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5IdleDown")->frameRender(hdc, position.x + 5, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6IdleDown")->frameRender(hdc, position.x, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8IdleDown")->frameRender(hdc, position.x, position.y, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9IdleDown")->frameRender(hdc, position.x + 5, position.y - 5, (_frame / 10) % 3, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10IdleDown")->frameRender(hdc, position.x + 3, position.y + 5, (_frame / 10) % 3, 0);
				break;
			}
		}
	}
	if (_state.test(MOVE))
	{
		if (_dir.test(LEFT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_X / 2 - (cameraPos.y - y) - 190, (_frame / 10) % 6, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 50, WINSIZE_X / 2 - (cameraPos.y - y) - 205, (_frame / 10) % 6, 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 35, WINSIZE_X / 2 - (cameraPos.y - y) - 185, (_frame / 10) % 6, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 40, WINSIZE_X / 2 - (cameraPos.y - y) - 195, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 35, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 5, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 30, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 55, WINSIZE_X / 2 - (cameraPos.y - y) - 190, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 35, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 6, 0);
				break;
			}
		}
		else if (_dir.test(RIGHT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 190, 5 - (_frame / 10) % 6, 1);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 35, WINSIZE_X / 2 - (cameraPos.y - y) - 205, 5 - (_frame / 10) % 6, 1);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 30, WINSIZE_X / 2 - (cameraPos.y - y) - 185, 5 - (_frame / 10) % 6, 1);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 35, WINSIZE_X / 2 - (cameraPos.y - y) - 200, 5 - _frame / 10 % 6, 1);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 180, 4 - _frame / 10 % 5, 1);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 180, 5 - _frame / 10 % 6, 1);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 190, 5 - _frame / 10 % 6, 1);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 40, WINSIZE_X / 2 - (cameraPos.y - y) - 180, 5 - _frame / 10 % 6, 1);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_X / 2 - (cameraPos.y - y) - 180, 5 - _frame / 10 % 6, 1);
				break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 190, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 210, (_frame / 10) % 6, 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 175, (_frame / 10) % 6, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_X / 2 - (cameraPos.y - y) - 210, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 5, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 210, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 185, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 27, WINSIZE_X / 2 - (cameraPos.y - y) - 185, _frame / 10 % 6, 0);
				break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 190, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 200, (_frame / 10) % 6, 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 175, (_frame / 10) % 6, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_X / 2 - (cameraPos.y - y) - 195, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 5, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_X / 2 - (cameraPos.y - y) - 180, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_X / 2 - (cameraPos.y - y) - 175, _frame / 10 % 6, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 17, WINSIZE_X / 2 - (cameraPos.y - y) - 175, _frame / 10 % 6, 0);
				break;
			}
		}
	}
	else if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1AttackSide")->frameRender(hdc, position.x - 45, position.y - 35, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2AttackSide")->frameRender(hdc, position.x - 120, position.y - 20, (_frame / 10), 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3AttackSide")->frameRender(hdc, position.x - 18, position.y, (_frame / 10), 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackSide")->frameRender(hdc, position.x - 70, position.y - 25, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5AttackSide")->frameRender(hdc, position.x - 15, position.y, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6AttackSide")->frameRender(hdc, position.x - 45, position.y - 20, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8AttackSide")->frameRender(hdc, position.x - 25, position.y - 20, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9AttackSide")->frameRender(hdc, position.x - 25, position.y + 5, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10AttackSide")->frameRender(hdc, position.x - 20, position.y - 5, _frame / 10, 0);
				break;
			}
		}
		else if (_dir.test(RIGHT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1AttackSide")->frameRender(hdc, position.x - 5, position.y - 35, 3 - _frame / 10, 1);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2AttackSide")->frameRender(hdc, position.x - 15, position.y - 20, 7 - (_frame / 10), 1);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3AttackSide")->frameRender(hdc, position.x, position.y, 5 - (_frame / 10), 1);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackSide")->frameRender(hdc, position.x - 30, position.y - 25, 8 - _frame / 10, 1);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5AttackSide")->frameRender(hdc, position.x, position.y, 3 - _frame / 10, 1);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6AttackSide")->frameRender(hdc, position.x - 15, position.y - 20, 7 - _frame / 10, 1);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8AttackSide")->frameRender(hdc, position.x - 25, position.y - 20, 7 - _frame / 10, 1);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9AttackSide")->frameRender(hdc, position.x - 15, position.y + 5, 3 - _frame / 10, 1);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10AttackSide")->frameRender(hdc, position.x, position.y - 5, 4 - _frame / 10, 1);
				break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1AttackUp")->frameRender(hdc, position.x + 5, position.y - 35, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2AttackUp")->frameRender(hdc, position.x - 40, position.y - 65, (_frame / 10), 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3AttackUp")->frameRender(hdc, position.x - 5, position.y - 5, (_frame / 10), 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackUp")->frameRender(hdc, position.x - 45, position.y - 55, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5AttackUp")->frameRender(hdc, position.x + 5, position.y, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6AttackUp")->frameRender(hdc, position.x - 25, position.y + 10, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8AttackUp")->frameRender(hdc, position.x - 45, position.y - 30, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9AttackUp")->frameRender(hdc, position.x - 40, position.y, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10AttackUp")->frameRender(hdc, position.x + 5, position.y - 20, _frame / 10, 0);
				break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1AttackDown")->frameRender(hdc, position.x, position.y - 5, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2AttackDown")->frameRender(hdc, position.x - 45, position.y + 10, (_frame / 10), 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3AttackDown")->frameRender(hdc, position.x, position.y - 5, (_frame / 10), 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackDown")->frameRender(hdc, position.x - 10, position.y - 25, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5AttackDown")->frameRender(hdc, position.x + 5, position.y + 5, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6AttackDown")->frameRender(hdc, position.x - 35, position.y - 5, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8AttackDown")->frameRender(hdc, position.x - 35, position.y - 5, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9AttackDown")->frameRender(hdc, position.x + 5, position.y, _frame / 10, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10AttackDown")->frameRender(hdc, position.x + 3, position.y + 5, _frame / 10, 0);
				break;
			}
		}
	}
	else if (_state.test(DAMAGED))
	{
		if (_dir.test(LEFT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedSide")->frameRender(hdc, position.x - 15, position.y + 15, 0, 0);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedSide")->frameRender(hdc, position.x - 10, position.y - 25, 0, 0);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedSide")->frameRender(hdc, position.x, position.y + 15, 0, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedSide")->frameRender(hdc, position.x - 15, position.y + 15, 0, 0);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedSide")->frameRender(hdc, position.x - 5, position.y + 15, 0, 0);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedSide")->frameRender(hdc, position.x - 5, position.y + 15, 0, 0);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedSide")->frameRender(hdc, position.x - 15, position.y + 20, 0, 0);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedSide")->frameRender(hdc, position.x - 25, position.y + 10, 0, 0);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedSide")->frameRender(hdc, position.x - 15, position.y + 15, 0, 0);
				break;
			}
		}
		else if (_dir.test(RIGHT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedSide")->frameRender(hdc, position.x + 5, position.y + 15, 0, 1);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedSide")->frameRender(hdc, position.x, position.y - 15, 0, 1);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedSide")->frameRender(hdc, position.x - 5, position.y + 15, 0, 1);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedSide")->frameRender(hdc, position.x - 5, position.y + 15, 0, 1);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedSide")->frameRender(hdc, position.x, position.y + 15, 0, 1);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedSide")->frameRender(hdc, position.x, position.y + 15, 0, 1);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedSide")->frameRender(hdc, position.x, position.y + 20, 0, 1);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedSide")->frameRender(hdc, position.x, position.y + 10, 0, 1);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedSide")->frameRender(hdc, position.x + 5, position.y + 15, 0, 1);
				break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedUp")->render(hdc, position.x, position.y + 10);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedUp")->render(hdc, position.x + 5, position.y - 10);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedUp")->render(hdc, position.x, position.y + 5);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedUp")->render(hdc, position.x + 3, position.y + 5);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedUp")->render(hdc, position.x, position.y + 10);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedUp")->render(hdc, position.x - 15, position.y + 20);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedUp")->render(hdc, position.x - 25, position.y + 15);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedUp")->render(hdc, position.x + 10, position.y + 5);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedUp")->render(hdc, position.x + 5, position.y + 5);
				break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedDown")->render(hdc, position.x - 15, position.y + 10);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedDown")->render(hdc, position.x - 5, position.y - 25);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedDown")->render(hdc, position.x, position.y + 20);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedDown")->render(hdc, position.x - 10, position.y + 15);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedDown")->render(hdc, position.x, position.y + 15);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedDown")->render(hdc, position.x, position.y + 30);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedDown")->render(hdc, position.x, position.y + 20);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedDown")->render(hdc, position.x + 5, position.y + 15);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedDown")->render(hdc, position.x, position.y + 25);
				break;
			}
		}
		char damageStr[50];
		wsprintf(damageStr, "%d", _damage);
		FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "가을체", 20, 50, damageStr, strlen(damageStr), RGB(255, 0, 0));
	}
	else if (_state.test(SKILL))
	{
		
	}
	else if (_state.test(DIE))
	{
		if (_dir.test(LEFT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedSide")->alphaFrameRender(hdc, position.x - 15, position.y + 15, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedSide")->alphaFrameRender(hdc, position.x - 10, position.y - 25, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedSide")->alphaFrameRender(hdc, position.x, position.y + 15, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedSide")->alphaFrameRender(hdc, position.x - 15, position.y + 15, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedSide")->alphaFrameRender(hdc, position.x - 5, position.y + 15, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedSide")->alphaFrameRender(hdc, position.x - 5, position.y + 15, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedSide")->alphaFrameRender(hdc, position.x - 15, position.y + 20, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedSide")->alphaFrameRender(hdc, position.x - 25, position.y + 10, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedSide")->alphaFrameRender(hdc, position.x - 15, position.y + 15, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			}
		}
		else if (_dir.test(RIGHT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedSide")->alphaFrameRender(hdc, position.x + 5, position.y + 15, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedSide")->alphaFrameRender(hdc, position.x, position.y - 15, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedSide")->alphaFrameRender(hdc, position.x - 5, position.y + 15, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedSide")->alphaFrameRender(hdc, position.x - 5, position.y + 15, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedSide")->alphaFrameRender(hdc, position.x, position.y + 15, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedSide")->alphaFrameRender(hdc, position.x, position.y + 15, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedSide")->alphaFrameRender(hdc, position.x, position.y + 20, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedSide")->alphaFrameRender(hdc, position.x, position.y + 10, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedSide")->alphaFrameRender(hdc, position.x + 5, position.y + 15, 0, 1, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedUp")->alphaRender(hdc, position.x, position.y + 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedUp")->alphaRender(hdc, position.x + 5, position.y - 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedUp")->alphaRender(hdc, position.x, position.y + 5, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedUp")->alphaRender(hdc, position.x + 3, position.y + 5, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedUp")->alphaRender(hdc, position.x, position.y + 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedUp")->alphaRender(hdc, position.x - 15, position.y + 20, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedUp")->alphaRender(hdc, position.x - 25, position.y + 15, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedUp")->alphaRender(hdc, position.x + 10, position.y + 5, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedUp")->alphaRender(hdc, position.x + 5, position.y + 5, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1DamagedDown")->alphaRender(hdc, position.x - 15, position.y + 10, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER2:
				IMAGEMANAGER->findImage("Soldier2DamagedDown")->alphaRender(hdc, position.x - 5, position.y - 25, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER3:
				IMAGEMANAGER->findImage("Soldier3DamagedDown")->alphaRender(hdc, position.x, position.y + 20, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedDown")->alphaRender(hdc, position.x - 10, position.y + 15, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER5:
				IMAGEMANAGER->findImage("Soldier5DamagedDown")->alphaRender(hdc, position.x, position.y + 15, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER6:
				IMAGEMANAGER->findImage("Soldier6DamagedDown")->alphaRender(hdc, position.x, position.y + 30, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER8:
				IMAGEMANAGER->findImage("Soldier8DamagedDown")->alphaRender(hdc, position.x, position.y + 20, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER9:
				IMAGEMANAGER->findImage("Soldier9DamagedDown")->alphaRender(hdc, position.x + 5, position.y + 15, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			case EnemyType::SOLDIER10:
				IMAGEMANAGER->findImage("Soldier10DamagedDown")->alphaRender(hdc, position.x, position.y + 25, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
				break;
			}
		}
	}
}
