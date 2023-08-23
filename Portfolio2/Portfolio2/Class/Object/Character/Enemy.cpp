#include "../../../FrameWork/PCH/Stdafx.h"
#include "./Enemy.h"

POINT Enemy::findPlayer(int tileInfo[][60], int rowN, int colN)
{
	POINT node = _tilePos;
	queue<POINT> closedList;
	closedList.push(node);
	bitset<60> tileCheck[90];
	for (int i = 0; i < 90; i++)
	{
		tileCheck[i].reset();
	}
	tileCheck[node.y].set(node.x);
	while (true)
	{
		int leafN = closedList.size();
		while (leafN--)
		{
			node = closedList.front();
			if (node.x > 0 && tileInfo[node.y][node.x - 1] == 1)
			{
				if (!tileCheck[node.y].test(node.x - 1))
				{
					closedList.push(POINT{ node.x - 1, node.y });
					tileCheck[node.y].set(node.x - 1);
				}
			}
			else if(node.x > 0 && tileInfo[node.y][node.x - 1] == 2)
			{
				return {node.x - 1, node.y};
			}
			if (node.x < colN - 1 && tileInfo[node.y][node.x + 1] == 1)
			{
				if (!tileCheck[node.y].test(node.x + 1))
				{
					closedList.push(POINT{ node.x + 1, node.y });
					tileCheck[node.y].set(node.x + 1);
				}
			}
			else if (node.x > 0 && tileInfo[node.y][node.x + 1] == 2)
			{
				return { node.x + 1, node.y };
			}
			if (node.y > 0 && tileInfo[node.y - 1][node.x] == 1)
			{
				if (!tileCheck[node.y - 1].test(node.x))
				{
					closedList.push(POINT{ node.x, node.y - 1 });
					tileCheck[node.y - 1].set(node.x);
				}
			}
			else if (node.x > 0 && tileInfo[node.y - 1][node.x] == 2)
			{
				return { node.x, node.y - 1 };
			}
			if (node.y < rowN - 1 && tileInfo[node.y + 1][node.x] == 1)
			{
				if (!tileCheck[node.y + 1].test(node.x))
				{
					closedList.push(POINT{ node.x, node.y + 1 });
					tileCheck[node.y + 1].set(node.x);
				}
			}
			else if (node.x > 0 && tileInfo[node.y + 1][node.x] == 2)
			{
				return { node.x, node.y + 1 };
			}
			closedList.pop();
		}
	}
}
