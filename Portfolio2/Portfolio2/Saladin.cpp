#include "Stdafx.h"
#include "Saladin.h"

HRESULT Saladin::init(void)
{
	_frame = 0;
	_wtp = 10;
	_mobility = 7;
	_type = 0;
	Character::init();
	return S_OK;
}

void Saladin::release(void)
{

}

void Saladin::update(void)
{
	_frame++;
	if(_state.test(MOVE))
	{
		if (_frame % 5 == 0)
		{
			move();
		}
	}
	else if (_state.test(ATTACK))
	{
		if (_frame == 2)
		{
			SOUNDMANAGER->playEffectSoundWave("Resources/Sounds/SoundEffect/SaladinAttack.wav");
			//SOUNDMANAGER->playEffectSoundWave("Resources/Sounds/SoundEffect/test.wav");
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
}

void Saladin::render(HDC hdc, POINT position)
{
	if (_state.none())
	{
		//IMAGEMANAGER->findImage("SaladinAttackDown")->frameRender(hdc, position.x - 35, position.y - 20, 3, 0);
		//IMAGEMANAGER->findImage("SaladinAttackDownEffect")->alphaFrameRender(hdc, position.x - 45, position.y - 40, 4, 0, 200);
		//if (_turn.test(0))
		//{

		//}
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
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 3);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("SaladinMove")->frameRender(hdc, position.x - 40, position.y - 30, (_frame / 5) % 6, 1);
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
}
void Saladin::searchMovable(int map[][60], int rowN, int colN)
{
	_movableTiles.clear();
	_attackableTiles.clear();
	int mobility = _mobility;
	POINT node = _tilePos;
//	_movableTiles.push_back(node);
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
