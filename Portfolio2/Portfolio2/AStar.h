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
	priority_queue<pair<POINT, int>, vector<pair<POINT, int>>, cmp> _closedList;
	int _distance[90][60];
	POINT _exNode[90][60];
	vector<POINT> _route;

public:
	vector<POINT> findRoute(POINT start, POINT dest, int map[][60], int rowN, int colN);
	//int findRoute(POINT start, POINT dest, int map[][60], int rowN, int colN);
	int heuristic(POINT node, POINT dest);
	int distance(POINT start, POINT node);



	AStar() {};
	~AStar() {};
};

