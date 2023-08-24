#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Soldier.h"
#include "Player.h"
#include "Obstacle.h"
#include "Camera.h"
#include "Skill.h"

// 타일정보
#define PLAYER 0
#define ENEMY 1
#define CANTMOVE 2
#define MOVABLE 3

struct cmp2 
{
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

class TurnSystem2
{
private:
	FILE* _fp;							// 퀵 세이브할 파일 포인터

	priority_queue<pair<POINT, int>, vector<pair<POINT, int>>, cmp2> _closedList;	// A* 탐색할 노드 목록
	vector<POINT> _route;				// 최단 경로

	vector<POINT> _movableTiles;		// 움직일 수 있는 타일들
	vector<POINT> _attackableTiles;		// 공격할 수 있는 타일들
	vector<POINT> _skillableTiles;		// 스킬 범위

	vector<Object*> _objectList;		// 오브젝트 목록
	vector<Character*> _charList;		// 캐릭터 목록

	Character* _curChar;				// 현재 캐릭터
	Enemy* _enemy;
	Camera* _camera;					// 카메라
	Skill* _skill;						// 스킬 이펙트
	HDC _tileCheckDC;					// GetPixel로 갈 수 없는 타일인지 확인하기 위한 Image DC
	int _frame;

	int _rowN;							// 가로 타일 수
	int _colN;							// 세로 타일 수

	RECT _actionButtons[4];				// 액션 버튼
	RECT _skillButtons[50];				// 스킬 버튼
	RECT _preferenceButtons[7];			// 환경설정 버튼
	POINT _exPtMouse;					// 마우스 이전 위치
	bitset<4> _actionChoice;			// 액션 선택 순서 
	char* _skillName;					// 선택한 스킬 이름
	int _skillIdx;						// 선택한 스킬 인덱스

	bool _isClear;						// 게임 클리어 여부
	bool _isFail;						// 게임오버 여부
	bool _start;						// 파티 캐릭터 배치 후 전투 시작
	bool _preference;					// 환경설정

public:
	HRESULT init(Camera* camera, HDC hdc, int rowN, int colN);
	void release(void);
	void update(POINT cursorTile);
	void render(HDC hdc);

	Character* getCurChar() { return _curChar; }
	// 클릭한 위치의 캐릭터 찾기
	Character* findCharacter(POINT cursorPoint);
	// 파티 캐릭터 이름으로 캐릭터 찾기
	Character* findCharacter(string playerName);

	// 파티 캐릭터 배치 시 캐릭터 목록에 추가
	void addCharacter(Character* character, int dir, POINT tilePos, int turnOrder);
	// 파티 캐릭터 배치 취소 시 캐릭터 목록에서 제거
	Player* deleteCharacter(string name);
	// 오브젝트 목록에 오브젝트 추가
	void addObject(Object* object);

	// 오브젝트 목록 정렬
	void sortObjectList();
	// 타일의 정보값 얻기
	int checkTile(POINT tilePos);
	// 움직일 수 있는 타일 탐색
	void searchMovableTiles();
	// 스킬 타입으로 스킬 범위 탐색
	void searchSkillableTiles(int skillType);
	// 모두 아무것도 안하고 있는 상태인지 확인
	bool checkAllDoingNot();
	POINT findPlayer();
	// 다음 턴
	void nextTurn();
	// 퀵 세이브
	void saveGame();
	void setCharList(vector<Character*> charList) {_charList = charList; for(int i = 0; i <_charList.size(); i++) { _objectList.push_back(_charList[i]);}}

	void setStart(bool start);

	// A*로 최단경로 탐색
	vector<POINT> astar(POINT start, POINT dest); 
	// 휴리스틱 값 계산
	int heuristic(POINT node, POINT dest);
	// 거리 계산
	int distance(POINT start, POINT node);

	TurnSystem2() {}
	~TurnSystem2() {}
};

