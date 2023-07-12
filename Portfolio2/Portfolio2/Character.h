#pragma once

#define LEFT	0
#define RIGHT	1
#define UP		2
#define DOWN	3
#define IDLE	0
#define MOVE	1
#define ATTACK	2

class Character
{
protected:
	bitset<3> _state;
	POINT _tilePos;
	int _frame;
	vector<POINT> _route;
	bitset<4> _dir;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc, POINT position);
	void setState(int state);
	void setDir(int dir);
	void setTilePos(POINT tilePos) { _tilePos = tilePos; }
	void setRoute(vector<POINT> route) { _route = route; }
	void move();

	POINT getTilePos() { return _tilePos; }
public:
	Character() {}
	~Character() {}
};

