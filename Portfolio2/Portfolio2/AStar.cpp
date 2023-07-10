#include "Stdafx.h"
#include "AStar.h"

void AStar::findRoute(POINT start, POINT dest, int map[][60], int rowN, int colN)
{
	_route.push(make_pair(start, heuristic(start, dest)));
	if (start.x != 0)
	{

	}
	if (start.x != colN - 1)
	{

	}
}

int AStar::heuristic(POINT start, POINT dest)
{
	return abs(start.x - dest.x) + abs(start.y - dest.y);
}
