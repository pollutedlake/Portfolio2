#include "Stdafx.h"
#include "AStar.h"

vector<POINT> AStar::findRoute(POINT start, POINT dest, int map[][60], int rowN, int colN)
{
	// 시작 노드가 도착노드와 같다면
	if ((start.x == dest.x) && (start.y == dest.y))
	{
		_route.clear();
		return _route;
	}

	// 초기화
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

	// 시작 노드를 탐색 목록에 넣고 가중치 계산해서 닫힌목록에 넣는다.
	_closedList.push(make_pair(start, heuristic(start, dest)));
	_distance[start.y][start.x] = heuristic(start, dest);

	// 탐색할 노드가 없을 때까지
	while (!_closedList.empty())
	{
		// 가중치가 제일 작은 노드
		POINT node = _closedList.top().first;
		if (node.x == dest.x)
		{
			if (node.y == dest.y)
			{
				break;
			}
		}
		// 주변에 갈 수 있는 노드
		POINT next;
		// 왼쪽 노드
		if (node.x != 0)
		{
			next.x = node.x - 1;
			next.y = node.y;
			// 움직일 수 있는 노드라면
			if (map[next.y][next.x] == 1)
			{
				// 계산한 가중치가 현재 그 노드의 가중치보다 작다면 가중치와 부모 노드를 바꿔준다.
				if (_distance[next.y][next.x] > 10 + heuristic(next, dest) + _distance[node.y][node.x])
				{
					// 열린 목록에 있는 노드라면 노드라면 탐색할 노드목록에 넣는다.
					if (_distance[next.y][next.x] == 999999)
					{
						_closedList.push(make_pair(next, 10 + heuristic(next, dest) + _distance[node.y][node.x]));
					}
					_distance[next.y][next.x] = 10 + heuristic(next, dest) + _distance[node.y][node.x];
					_exNode[next.y][next.x] = node;
				}
			}
		}
		// 오른쪽 노드
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
		// 위쪽 노드
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
		// 아래쪽 노드
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
	// 도착 노드부터 부모 노드를 역으로 찾아 올라가면서 경로에 넣는다.
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

// x와 y의 차이의 합을 휴리스틱으로 계산한다.
int AStar::heuristic(POINT node, POINT dest)
{
	return (abs(node.x - dest.x) + abs(node.y - dest.y)) * 10;
}

// 거리 계산
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
