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
	priority_queue<pair<POINT, int>, vector<pair<POINT, int>>, cmp> _closedList;	// 탐색할 목록(우선순위큐)
	int _distance[90][60];	// f(x) + h(x)
	POINT _exNode[90][60];	// 부모 노드
	vector<POINT> _route;	// 경로

public:
	// 경로 탐색
	vector<POINT> findRoute(POINT start, POINT dest, int map[][60], int rowN, int colN);
	// 휴리스틱 값 계산
	int heuristic(POINT node, POINT dest);
	// 거리 계산
	int distance(POINT start, POINT node);

	AStar() {};
	~AStar() {};
};

