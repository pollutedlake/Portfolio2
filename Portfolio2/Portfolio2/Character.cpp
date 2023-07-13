#include "Stdafx.h"
#include "Character.h"

HRESULT Character::init(void)
{
	_doing = false;
	_curWait = _wtp;
	_turn.reset();
	_turn.flip();
	_state.reset();
	_turnOrder.reset();
	_curMobility = _mobility;
	return S_OK;
}

void Character::release(void)
{
}

void Character::update(void)
{

}

void Character::render(HDC hdc, POINT position)
{
}

void Character::setState(int state)
{
	_state.reset();
	_state |= state;
	_frame = 0;
}

void Character::setDir(int dir)
{
	_dir.reset();
	_dir.set(dir, true);
}

int Character::getTurnOrder(int charN)
{
	for (int i = 0; i < charN - 1; i++)
	{
		if (_turnOrder.test(i))
		{
			return i;
		}
	}
}

vector<POINT> Character::searchMovable(int map[][60], int rowN, int colN)
{
	vector<POINT> movableTiles;
	int mobility = _mobility;
	POINT node = _tilePos;
	movableTiles.push_back(node);
	queue<POINT> closedList;
	closedList.push(node);
	bitset<60> tileCheck[90];
	for (int i = 0; i < 90; i++)
	{
		tileCheck[i].reset();
	}
	tileCheck[node.y].set(node.x);
	while (mobility > 0)
	{
		int leafN = closedList.size();
		while(leafN--)
		{
			node = closedList.front();
			if (node.x > 0 && map[node.y][node.x - 1] == 1)
			{
				if(!tileCheck[node.y].test(node.x - 1))
				{
					closedList.push(POINT{node.x - 1, node.y});
					tileCheck[node.y].set(node.x - 1);
				}
			}
			if (node.x < colN - 1 && map[node.y][node.x + 1] == 1)
			{
				if (!tileCheck[node.y].test(node.x + 1))
				{
					closedList.push(POINT{ node.x + 1, node.y });
					tileCheck[node.y].set(node.x + 1);
				}
			}
			if (node.y > 0 && map[node.y - 1][node.x] == 1)
			{
				if (!tileCheck[node.y - 1].test(node.x))
				{
					closedList.push(POINT{ node.x, node.y - 1 });
					tileCheck[node.y - 1].set(node.x);
				}
			}
			if (node.y < rowN - 1 && map[node.y + 1][node.x] == 1)
			{	
				if (!tileCheck[node.y + 1].test(node.x))
				{
					closedList.push(POINT{ node.x, node.y + 1 });
					tileCheck[node.y + 1].set(node.x);
				}
			}
			closedList.pop();
			movableTiles.push_back(node);
		}
		mobility--;
	}
	while (!closedList.empty())
	{
		node = closedList.front();
		closedList.pop();
		movableTiles.push_back(node);
	}
	movableTiles.erase(movableTiles.begin());
	return movableTiles;
}

void Character::move()
{
	if (_route.size() > 0 && _curMobility > 0)
	{
		if (_tilePos.x - _route.back().x == 1)
		{
			_dir.reset();
			_dir.set(LEFT, true);
		}
		else if (_tilePos.x - _route.back().x == -1)
		{
			_dir.reset();
			_dir.set(RIGHT, true);
		}
		else if (_tilePos.y - _route.back().y == 1)
		{
			_dir.reset();
			_dir.set(UP, true);
		}
		else if (_tilePos.y - _route.back().y == -1)
		{
			_dir.reset();
			_dir.set(DOWN, true);
		}
		_tilePos.x = _route.back().x;
		_tilePos.y = _route.back().y;
		_route.pop_back();
		_curMobility--;
	}
	else
	{
		if(_state.test(ATTACK) && _route.empty())
		{
			if (_tilePos.x - _destTilePos.x > 0)
			{
				_dir.reset();
				_dir.set(LEFT, true);
			}
			else if (_tilePos.x - _destTilePos.x < 0)
			{
				_dir.reset();
				_dir.set(RIGHT, true);
			}
			else if (_tilePos.y - _destTilePos.y > 0)
			{
				_dir.reset();
				_dir.set(UP, true);
			}
			else if (_tilePos.y - _destTilePos.y < 0)
			{
				_dir.reset();
				_dir.set(DOWN, true);
			}
			setState(2);
		}
		else
		{
			_state.reset();
			_doing = false;
		}
		_curMobility = _mobility;
		if(_type == 0)
		{
			_turn.flip(0);
		}
		else
		{
			endTurn();
		}
		_route.clear();
	}
}

//void Character::moveAndAttack(POINT cursorTile, vector<POINT> route)
//{
//	if (_route.size() > 0)
//	{
//		if (_tilePos.x - _route.back().x == 1)
//		{
//			_dir.reset();
//			_dir.set(LEFT, true);
//		}
//		else if (_tilePos.x - _route.back().x == -1)
//		{
//			_dir.reset();
//			_dir.set(RIGHT, true);
//		}
//		else if (_tilePos.y - _route.back().y == 1)
//		{
//			_dir.reset();
//			_dir.set(UP, true);
//		}
//		else if (_tilePos.y - _route.back().y == -1)
//		{
//			_dir.reset();
//			_dir.set(DOWN, true);
//		}
//		_tilePos.x = _route.back().x;
//		_tilePos.y = _route.back().y;
//		_route.pop_back();
//	}
//	else
//	{
//		if (cursorTile.y - _tilePos.y > 0)
//		{
//			setDir(DOWN);
//		}
//		else if (cursorTile.y - _tilePos.y < 0)
//		{
//			setDir(UP);
//		}
//		else
//		{
//			if (cursorTile.x - _tilePos.x > 0)
//			{
//				setDir(RIGHT);
//			}
//			else if (cursorTile.x - _tilePos.x < 0)
//			{
//				setDir(LEFT);
//			}
//		}
//		setState(ATTACK);
//	}
//}
