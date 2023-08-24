#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include "AStar.h"
#include "Skill.h"

#define CANTMOVE	0
#define MOVABLE		1
#define SALADIN		2
#define ENEMY		3

#define ACTION		0
#define MOVE		1

class TurnSystem
{
private:
	Character* _curChar;			// 현재 턴 캐릭터
	Enemy* _enemy;
	Saladin* _player;
	AStar* _aStar;					// A*
	vector<Character*> _charList;	// 캐릭터 목록
	vector<Object*> _objectList;	// 오브젝트 목록
	bitset<4> _actionChoice;		// 액션 버튼
	bool _skillChoice;				// 스킬을 골랐는지 여부
	bool _skillRangeChoice;			// 스킬 범위를 골랐는지 여부
	RECT _actionButtons[4];			// 액션 버튼
	RECT _skillButtons[3];			// 스킬 버튼
	vector<POINT> _attackTiles;		// 공격 가능한 타일들
	vector<POINT> _skillableTiles;	// 스킬 사용 가능한 타일들
	int _frame;
	bool _isClear;		// 클리어 여부
	bool _isFail;		// GameOver 실패 여부
	Skill* _skill;
	char* _skillName;

public:
	HRESULT init(void);
	void update(int tileInfo[][60], int rowN, int colN, POINT cursorTile);
	void release(void);
	void render(HDC hdc, int tileHeight, int tileWidth, POINT cameraPos);

	Character* getCurChar() {return _curChar;}

	// 캐릭터 목록에 캐릭터 추가
	void addCharacter(Character* character);
	// 오브젝트 목록에 오브젝트 추가
	void addObject(Object* object);
	// 다음 턴
	void nextTurn();
	// 오브젝트 목록 정렬
	void sortObjectList();
	// 클릭한 위치에 있는 캐릭터찾기
	Character* findCharacter(POINT cursorPoint);
	bool checkAllDoingNot();

	TurnSystem() {}
	~TurnSystem() {}

};

