#include "Stdafx.h"
#include "AStar.h"

vector<POINT> AStar::findRoute(POINT start, POINT dest, int map[][60], int rowN, int colN)
{
	if ((start.x == dest.x) && (start.y == dest.y))
	{
		_route.clear();
		return _route;
	}
	for (int i = 0; i < rowN; i++)
	{
		for (int j = 0; j < colN; j++)
		{
			_distance[i][j] = 999999;
		}
	}
	while (!_closedList.empty())
	{
		_closedList.pop();
	}
	_route.clear();
	_closedList.push(make_pair(start, heuristic(start, dest)));
	_distance[start.y][start.x] = heuristic(start, dest);
	while (!_closedList.empty())
	{
		POINT node = _closedList.top().first;
		if (node.x == dest.x)
		{
			if (node.y == dest.y)
			{
				break;
			}
		}
		POINT next;
		if (node.x != 0)
		{
			next.x = node.x - 1;
			next.y = node.y;
			if (map[next.y][next.x] == 1)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		if (node.x != colN - 1)
		{
			next.x = node.x + 1;
			next.y = node.y;
			if (map[next.y][next.x] == 1)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		if (node.y != 0)
		{
			next.x = node.x;
			next.y = node.y - 1;
			if (map[next.y][next.x] == 1)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		if (node.y != rowN - 1)
		{
			next.x = node.x;
			next.y = node.y + 1;
			if (map[next.y][next.x] == 1)
			{
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		_closedList.pop();
	}
	_route.push_back(dest);
	POINT temp = {dest.x, dest.y};
	while (distance(temp, start) != 0)
	{
		temp = _exNode[temp.y][temp.x];
		_route.push_back(temp);
		if (distance(temp, start) == 0)
		{
			_route.pop_back();
		}
	}
	return _route;
}

int AStar::heuristic(POINT node, POINT dest)
{
	return (abs(node.x - dest.x) + abs(node.y - dest.y)) * 10;
}

int AStar::distance(POINT start, POINT node)
{
	node.x -= start.x;
	node.y -= start.y;
	if (node.x == 0)
	{
		if (node.y == 0)
		{
			return 0;
		}
		else
		{
			return 10;
		}
	}
	if (node.y == 0)
	{
		return 10;
	}
	return 14;
}
