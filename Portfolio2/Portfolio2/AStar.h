#pragma once

struct cmp {
	bool operator()(pair<POINT, int> node1, pair<POINT, int> node2)
	{
		if (node1.second > node2.second)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class AStar
{
private:
	priority_queue<pair<POINT, int>, vector<pair<POINT, int>>, cmp> _route;

public:
	void findRoute(POINT start, POINT dest, int map[][60], int rowN, int colN);
	int heuristic(POINT start, POINT dest);


	AStar() {};
	~AStar() {};
};

