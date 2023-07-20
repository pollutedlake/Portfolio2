#include "Stdafx.h"
#include "Saladin.h"

HRESULT Saladin::init(void)
{
	_frame = 0;
	_wtp = 10;
	_mobility = 7;
	_type = 0;
	_maxHP = 500.f;
	_curHP = _maxHP;
	//_curHP = 10;
	_maxMP = 100.f;
	_curMP = _maxMP;
	Character::init();
	return S_OK;
}

void Saladin::release(void)
{
	Character::release();
}

void Saladin::update(void)
{
	_frame++;
	if(_state.test(MOVE))
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
		if (_skillOrder.test(1))
		{
			if (_frame == 43)
			{
				SOUNDMANAGER->playSoundFMOD("SaladinSkillStart");
			}
		}
	}
}

void Saladin::render(HDC hdc, POINT position, POINT cameraPos)
{
	//IMAGEMANAGER->findImage("Explosion2")->frameRender(hdc, position.x - 35, position.y - 50, (_frame / 5) % IMAGEMANAGER->findImage("Explosion2")->getMaxFrameX(), 0);
	if (_state.none())
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("SaladinIdleLeft")->frameRender(hdc, position.x - 10, position.y - 10, (_frame / 5) % 4, 0);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("SaladinIdleRight")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("SaladinIdleUp")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("SaladinIdleDown")->frameRender(hdc, position.x - 20, position.y - 10, (_frame / 5) % 4, 0);
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
		FONTMANAGER->textOut(hdc, position.x + 15, position.y - _frame * 5 - 20, "°¡À»Ã¼", 20, 500, damageStr, strlen(damageStr), RGB(255, 0, 0));
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
}
void Saladin::searchMovable(int map[][60], int rowN, int colN)
{
	_movableTiles.clear();
	_attackableTiles.clear();
	int mobility = _mobility;
	POINT node = _tilePos;
	queue<POINT> closedList;
	closedList.push(node);
	bitset<60> tileCheck[90];
	for (int i = 0; i < 90; i++)
	{
		tileCheck[i].reset();
	}
	tileCheck[node.y].set(node.x);
	while (mobility >= -1)
	{
		int leafN = closedList.size();
		while (leafN--)
		{
			node = closedList.front();
			if (node.x > 0 && map[node.y][node.x - 1] == 1)
			{
				if (!tileCheck[node.y].test(node.x - 1))
				{
					if(mobility >= 0)
					{
						closedList.push(POINT{ node.x - 1, node.y });
					}
					else
					{
						_attackableTiles.push_back({ node.x - 1, node.y });
					}
					tileCheck[node.y].set(node.x - 1);
				}
			}
			else if (node.x > 0 && map[node.y][node.x - 1] == 3)
			{
				if (!tileCheck[node.y].test(node.x - 1))
				{
					_attackableTiles.push_back(POINT{ node.x - 1, node.y });
					tileCheck[node.y].set(node.x - 1);
				}
			}
			if (node.x < colN - 1 && map[node.y][node.x + 1] == 1)
			{
				if (!tileCheck[node.y].test(node.x + 1))
				{
					if(mobility >= 0)
					{
						closedList.push(POINT{ node.x + 1, node.y });
					}
					else
					{
						_attackableTiles.push_back({node.x + 1, node.y});
					}
					tileCheck[node.y].set(node.x + 1);
				}
			}
			else if (node.x < colN - 1 && map[node.y][node.x + 1] == 3)
			{
				if (!tileCheck[node.y].test(node.x + 1))
				{
					_attackableTiles.push_back(POINT{ node.x + 1, node.y });
					tileCheck[node.y].set(node.x + 1);
				}
			}
			if (node.y > 0 && map[node.y - 1][node.x] == 1)
			{
				if (!tileCheck[node.y - 1].test(node.x))
				{
					if(mobility >= 0)
					{
						closedList.push(POINT{ node.x, node.y - 1 });
					}
					else
					{
						_attackableTiles.push_back({ node.x, node.y - 1 });
					}
					tileCheck[node.y - 1].set(node.x);
				}
			}
			else if (node.y > 0 && map[node.y - 1][node.x] == 3)
			{
				if (!tileCheck[node.y].test(node.x - 1))
				{
					_attackableTiles.push_back(POINT{ node.x, node.y -1 });
					tileCheck[node.y - 1].set(node.x);
				}
			}
			if (node.y < rowN - 1 && map[node.y + 1][node.x] == 1)
			{
				if (!tileCheck[node.y + 1].test(node.x))
				{	
					if(mobility >= 0)
					{
						closedList.push(POINT{ node.x, node.y + 1 });
					}
					else
					{
						_attackableTiles.push_back({ node.x, node.y + 1 });
					}
					tileCheck[node.y + 1].set(node.x);
				}
			}
			else if (node.y < rowN - 1 && map[node.y + 1][node.x] == 3)
			{
				if (!tileCheck[node.y + 1].test(node.x))
				{
					_attackableTiles.push_back(POINT{ node.x, node.y + 1 });
					tileCheck[node.y + 1].set(node.x);
				}
			}
			closedList.pop();
			if( mobility >= 0 )
			{
				_movableTiles.push_back(node);
			}
			else
			{
				_attackableTiles.push_back(node);
			}
		}
		mobility--;
	}
	while (!closedList.empty())
	{
		node = closedList.front();
		closedList.pop();
		_attackableTiles.push_back(node);
	}
}
