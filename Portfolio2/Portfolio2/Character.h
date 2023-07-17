#pragma once
#include "Object.h"

#define LEFT	0
#define RIGHT	1
#define UP		2
#define DOWN	3

#define MOVE	0
#define ATTACK	1
#define DAMAGED	2
#define SKILL	3

#define TURNMOVE	0
#define TURNACTION	1

class Character : public Object
{
protected:
	bitset<2> _turn;
	bitset<4> _state;
	bitset<4> _skillOrder;
	bitset<20> _turnOrder;
	POINT _destTilePos;
	int _frame;
	vector<POINT> _route;
	bitset<4> _dir;
	int _wtp;
	int _curWait;
	int _mobility;
	int _curMobility;
	bool _doing;
	int _damage;
	bool _isAttack;
	float x, y;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc, POINT position, POINT cameraPos);

	void setState(int state);
	void setDir(int dir);
	void setTilePos(POINT tilePos) { _tilePos = tilePos; }
	void setRoute(vector<POINT> route) { _route = route; }
	void setTurnOder(int order) { _turnOrder.set(order, true); }
	void setCurWait(int curWait) {_curWait = curWait;}
	void setDoing(bool doing) {_doing = doing;}
	void resetTurn() {_turn.reset(); _turn.flip();}
	void setDestTilePos(POINT destTilePos) {_destTilePos = destTilePos;}
	void setDamage(int damage) {_damage = damage;}
	void setSkillOrder(int i) {_skillOrder.reset(); _skillOrder.set(i); _frame = 0; }

	//POINT getTilePos() { return _tilePos; }
	POINT getDestTilePos() {return _destTilePos;}
	int getWTP() {return _wtp;}
	int getCurWait() {return _curWait;}
	int getTurnOrder(int charN);
	float getX() {return x;}
	float getY() {return y;}
	bool isDoing() {return _doing;}
	bool canMove() {return _turn.test(TURNMOVE);}
	bool canAction() {return _turn.test(TURNACTION);}
	//int getType() {return _type;}
	bool isAttack() {return _isAttack;}
	bool isSkill() {return _state[SKILL]; }

	void moveTurnOrder() {_turnOrder = _turnOrder >> 1;}
	void endTurn() {_turn.reset();}
	void move();
	void setXY(int tileWidth, int tileHeight);
	virtual int getDamage();

public:
	Character() {}
	virtual ~Character() {}
};

