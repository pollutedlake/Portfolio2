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

void Soldier::update(void)
{
	_frame++;
	if (_state.test(MOVE))
	{
		move();
	}
	else if (_state.test(ATTACK))
	{
		if (_dir.test(LEFT) && _frame / 10 > IMAGEMANAGER->findImage("Soldier4AttackSide")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(RIGHT) && _frame / 10 > IMAGEMANAGER->findImage("Soldier4AttackSide")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(UP) && _frame / 10 > IMAGEMANAGER->findImage("Soldier4AttackUp")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
		}
		else if (_dir.test(DOWN) && _frame / 10 > IMAGEMANAGER->findImage("Soldier4AttackDown")->getMaxFrameX())
		{
			_state.reset();
			setDoing(false);
			endTurn();
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
				case EnemyType::SOLDIER4:
					IMAGEMANAGER->findImage("Soldier4IdleSide")->frameRender(hdc, position.x - 25, position.y - 5, (_frame / 10) % 3, 0);
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
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4IdleSide")->frameRender(hdc, position.x + 5, position.y - 5, 2 - (_frame / 10) % 3, 1);
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
			case EnemyType::SOLDIER4:
					IMAGEMANAGER->findImage("Soldier4IdleUp")->frameRender(hdc, position.x + 5, position.y, (_frame / 10) % 3, 0);
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
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4IdleDown")->frameRender(hdc, position.x - 5, position.y, (_frame / 10) % 3, 0);
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
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 40, WINSIZE_X / 2 - (cameraPos.y - y) - 195, _frame / 10 % 6, 0);
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
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveSide")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 35, WINSIZE_X / 2 - (cameraPos.y - y) - 200, 5 - _frame / 10 % 6, 1);
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
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveUp")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 15, WINSIZE_X / 2 - (cameraPos.y - y) - 210, _frame / 10 % 6, 0);
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
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4MoveDown")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_X / 2 - (cameraPos.y - y) - 195, _frame / 10 % 6, 0);
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
				IMAGEMANAGER->findImage("Soldier1AttackSide")->frameRender(hdc, position.x - 70, position.y - 25, IMAGEMANAGER->findImage("Soldier1AttackSide")->getMaxFrameX() - 1 - 0, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackSide")->frameRender(hdc, position.x - 70, position.y - 25, _frame / 10, 0);
				break;
			}
		}
		else if (_dir.test(RIGHT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1AttackSide")->frameRender(hdc, position.x - 70, position.y - 25, 0, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackSide")->frameRender(hdc, position.x - 30, position.y - 25, 8 - _frame / 10, 1);
				break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1AttackUp")->frameRender(hdc, position.x - 70, position.y - 25, 0, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackUp")->frameRender(hdc, position.x - 45, position.y - 55, _frame / 10, 0);
				break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER1:
				IMAGEMANAGER->findImage("Soldier1AttackDown")->frameRender(hdc, position.x - 70, position.y - 25, 0, 0);
				break;
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4AttackDown")->frameRender(hdc, position.x - 10, position.y - 25, _frame / 10, 0);
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
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedSide")->frameRender(hdc, position.x - 15, position.y + 15, 0, 0);
				break;
			}
		}
		else if (_dir.test(RIGHT))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedSide")->frameRender(hdc, position.x - 5, position.y + 15, 0, 1);
				break;
			}
		}
		else if (_dir.test(UP))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedUp")->render(hdc, position.x + 3, position.y + 5);
				break;
			}
		}
		else if (_dir.test(DOWN))
		{
			switch (_enemyType)
			{
			case EnemyType::SOLDIER4:
				IMAGEMANAGER->findImage("Soldier4DamagedDown")->render(hdc, position.x - 10, position.y + 15);
				break;
			}
		}
		char damageStr[50];
		wsprintf(damageStr, "%d", _damage);
		FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "°¡À»Ã¼", 20, 50, damageStr, strlen(damageStr), RGB(255, 0, 0));
	}
	else if (_state.test(SKILL))
	{
		
	}
	else if (_state.test(DIE))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 20, position.y - 30, 0, 2, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 20, position.y - 30, 0, 4, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 25, position.y - 25, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Enemy")->alphaFrameRender(hdc, position.x - 25, position.y - 25, 0, 6, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
	}
}
