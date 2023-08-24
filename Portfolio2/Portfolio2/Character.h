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
	bitset<2> _turn;			// Move, Action 턴
	bitset<5> _state;			// 상태
	bitset<4> _skillOrder;		// 스킬 순서
	bitset<50> _turnOrder;		// 턴 순서
	POINT _destTilePos;			// 목적지 타일 위치
	int _frame;
	vector<POINT> _route;		// 경로
	bitset<4> _dir;				// 방향
	int _wtp;					// 턴 속도
	int _curWait;				// 현재 턴 속도
	int _mobility;				// 총 이동력
	int _curMobility;			// 현재 이동력
	bool _doing;				// 행동중인지 여부
	int _damage;				// 데미지
	bool _isAttack;				// 공격 중인지 여부
	bool _isDie;				// 죽었는지 여부
	bool _isRide;				// 공중 탈것을 탔는지
	float x, y;					// 선형 보간에 쓸 위치값
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
	// 턴 초기화
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
	void setCurMobility(int curMobility) {_curMobility = _mobility;}

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
	int getCurMobility() {return _curMobility;}
	int getDir() {for(int i = 0; i < 4; i++) {if(_dir.test(i)) {return i;} } }
	int getFrame() {return _frame;}
	bool isRide() {return _isRide;}

	// 턴 순서 이동
	void moveTurnOrder() {_turnOrder = _turnOrder >> 1;}
	// 턴 종료
	void endTurn() {_turn.reset();}
	// 이동
	void move();
	// x, y 초기화
	void setXY(int tileWidth, int tileHeight);
	bool isDie();
	virtual int getDamage();
public:
	Character() {}
	virtual ~Character() {}
};

