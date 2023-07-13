#pragma once

#define LEFT	0
#define RIGHT	1
#define UP		2
#define DOWN	3

#define MOVE	0
#define ATTACK	1

#define TURNMOVE	0
#define TURNACTION	1

class Character
{
protected:
	bitset<2> _turn;
	bitset<3> _state;
	bitset<20> _turnOrder;
	POINT _tilePos;
	POINT _destTilePos;
	int _type;
	int _frame;
	vector<POINT> _route;
	bitset<4> _dir;
	int _wtp;
	int _curWait;
	int _mobility;
	int _curMobility;
	bool _doing;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc, POINT position);

	void setState(int state);
	void setDir(int dir);
	void setTilePos(POINT tilePos) { _tilePos = tilePos; }
	void setRoute(vector<POINT> route) { _route = route; }
	void setTurnOder(int order) { _turnOrder.set(order, true); }
	void setCurWait(int curWait) {_curWait = curWait;}
	void setDoing(bool doing) {_doing = doing;}
	void resetTurn() {_turn.reset(); _turn.flip();}
	void setdestTilePos(POINT destTilePos) {_destTilePos = destTilePos;}

	POINT getTilePos() { return _tilePos; }
	int getWTP() {return _wtp;}
	int getCurWait() {return _curWait;}
	int getTurnOrder(int charN);
	bool isDoing() {return _doing;}
	bool canMove() {return _turn.test(TURNMOVE);}
	bool canAction() {return _turn.test(TURNACTION);}
	int getType() {return _type;}

	void moveTurnOrder() {_turnOrder = _turnOrder >> 1;}
	vector<POINT> searchMovable(int map[][60], int rowN, int colN);
	void endTurn() {_turn.reset();}
	void move();
	//void moveAndAttack(POINT cursorTile, vector<POINT> route);
public:
	Character() {}
	~Character() {}
};

