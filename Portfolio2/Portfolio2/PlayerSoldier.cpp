#include "Stdafx.h"
#include "PlayerSoldier.h"

HRESULT PlayerSoldier::init(void)
{
	_frame = 0;
	_wtp = 10;
	_mobility = 7;
	_type = 0;
	_maxHP = 10.f;
	_curHP = _maxHP;
	_maxMP = 100.f;
	_curMP = _maxMP;
	Character::init();
	return S_OK;
}

void PlayerSoldier::release(void)
{
	Character::release();
}

void PlayerSoldier::update(void)
{
	_frame++;
	if (_state.test(MOVE))
	{
		move();
	}
	else if (_state.test(ATTACK))
	{
		
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
		
	}
}

void PlayerSoldier::render(HDC hdc, POINT position, POINT cameraPos)
{
	if (_state.none())
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 20, position.y - 25, (_frame / 10) % 3, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 20, position.y - 25, (_frame / 10) % 3, 4);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 25, position.y - 20, (_frame / 10) % 3, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 25, position.y - 20, (_frame / 10) % 3, 6);
		}
	}
	if (_state.test(MOVE))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 25, (_frame / 5) % 6, 3);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 20, WINSIZE_Y / 2 - (cameraPos.y - y) - 25, (_frame / 5) % 6, 5);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_Y / 2 - (cameraPos.y - y) - 20, (_frame / 5) % 6, 1);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, WINSIZE_X / 2 - (cameraPos.x - x) - 25, WINSIZE_Y / 2 - (cameraPos.y - y) - 20, (_frame / 5) % 6, 7);
		}
	}
	else if (_state.test(ATTACK))
	{

	}
	else if (_state.test(DAMAGED))
	{
		if (_dir.test(LEFT))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 20, position.y - 25, 0, 2);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 20, position.y - 25, 0, 4);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 25, position.y - 20, 0, 0);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Nakama")->frameRender(hdc, position.x - 25, position.y - 20, 0, 6);
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
			IMAGEMANAGER->findImage("Nakama")->alphaFrameRender(hdc, position.x - 20, position.y - 25, 0, 2, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(RIGHT))
		{
			IMAGEMANAGER->findImage("Nakama")->alphaFrameRender(hdc, position.x - 20, position.y - 25, 0, 4, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(UP))
		{
			IMAGEMANAGER->findImage("Nakama")->alphaFrameRender(hdc, position.x - 25, position.y - 20, 0, 0, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
		else if (_dir.test(DOWN))
		{
			IMAGEMANAGER->findImage("Nakama")->alphaFrameRender(hdc, position.x - 25, position.y - 20, 0, 6, 255 - 255 / 30 * _frame < 0 ? 0 : 255 - 255 / 30 * _frame);
		}
	}
}
void PlayerSoldier::searchMovable(int map[][60], int rowN, int colN)
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
					if (mobility >= 0)
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
					if (mobility >= 0)
					{
						closedList.push(POINT{ node.x + 1, node.y });
					}
					else
					{
						_attackableTiles.push_back({ node.x + 1, node.y });
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
					if (mobility >= 0)
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
					_attackableTiles.push_back(POINT{ node.x, node.y - 1 });
					tileCheck[node.y - 1].set(node.x);
				}
			}
			if (node.y < rowN - 1 && map[node.y + 1][node.x] == 1)
			{
				if (!tileCheck[node.y + 1].test(node.x))
				{
					if (mobility >= 0)
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
			if (mobility >= 0)
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