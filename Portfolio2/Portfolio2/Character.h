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
#define DIE		4

#define TURNMOVE	0
#define TURNACTION	1

class Character : public Object
{
protected:
	bitset<2> _turn;
	bitset<5> _state;
	bitset<4> _skillOrder;
	bitset<50> _turnOrder;
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
	bool _isDie;
	bool _isRide;
	float x, y;
	char* _skillName;

	int _curHP;
	int _maxHP;
	int _maxMP;
	int _curMP;
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc, POINT position, POINT cameraPos);

	void setState(int state);
	void setDir(int dir);
	void setTilePos(POINT tilePos) { _tilePos = tilePos; }
	void setRoute(vector<POINT> route) { _route = route; }
	void setTurnOder(int order) { _turnOrder.reset(); _turnOrder.set(order, true); }
	void setCurWait(int curWait) {_curWait = curWait;}
	void setDoing(bool doing) {_doing = doing;}
	void resetTurn() {_turn.reset(); _turn.flip();}
	void setTurn(int index, bool active) {_turn.set(index, active);}
	void setDestTilePos(POINT destTilePos) {_destTilePos = destTilePos;}
	void setDamage(int damage) {_damage = damage;}
	void setSkillOrder(int i) {_skillOrder.reset(); _skillOrder.set(i); _frame = 0; }
	void setSkillName(char* skillName) { _skillName = skillName; }
	void setCurHP(int curHP) {_curHP = curHP;}
	void setCurMP(int curMP) {_curMP = curMP;}
	void setMobility(int mobility) {_mobility = mobility;}
	void setWTP(int wtp) {_wtp = wtp;}
	void setRide(bool ride);

	POINT getDestTilePos() {return _destTilePos;}
	int getWTP() {return _wtp;}
	int getCurWait() {return _curWait;}
	int getTurnOrder(int charN);
	float getX() {return x;}
	float getY() {return y;}
	bool isDoing() {return _doing;}
	bool canMove() {return _turn.test(TURNMOVE);}
	bool canAction() {return _turn.test(TURNACTION);}
	bool isAttack() {return _isAttack;}
	bool isSkill() { return _state[SKILL]; }
	int getCurHP() { return _curHP; }
	int getMaxHP() { return _maxHP; }
	int getMaxMP() { return _maxMP; }
	int getCurMP() { return _curMP; }
	int getMobility() {return _mobility;}
	int getDir() {for(int i = 0; i < 4; i++) {if(_dir.test(i)) {return i;} } }
	int getFrame() {return _frame;}
	bool isRide() {return _isRide;}

	void moveTurnOrder() {_turnOrder = _turnOrder >> 1;}
	void endTurn() {_turn.reset();}
	void move();
	void setXY(int tileWidth, int tileHeight);
	bool isDie();
	virtual int getDamage();
public:
	Character() {}
	virtual ~Character() {}
};

