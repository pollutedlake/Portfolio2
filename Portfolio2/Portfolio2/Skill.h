#pragma once
#include "Character.h"
#include "Saladin.h"
#include "Player.h"

// 설화난영참 얼음 기둥
struct IcePillar
{
	int _frame = -1;
	bool _broken = false;
	POINT _position;
};

class Skill
{
private:
	char* _skillName;
	int _frame;
	int _startFrame;
	bool _isFinish;										// 스킬이 끝났는지 확인
	Character* _curChar;								// 스킬 쓴 캐릭터
	Character* _targetChar;								// 타겟 캐릭터
	vector<Character*> _charList;						// 스킬 범위 내의 캐릭터목록
	vector<POINT> _snow;								// 설화난영참 눈
	bitset<4> _order;									// 스킬 순서
	bitset<20> _orderOrder;								// 스킬 순서 내 순서
	vector<pair<POINT, POINT>> _efxPos;					// 설화난영참 버몬트 쫓아다니는 원들
	vector<pair<pair<float, float>, float>> _dust1Pos;	// 설화난영참 먼지1
	vector<pair<pair<float, float>, float>> _dust2;		// 설화난영참 먼지2
	vector<IcePillar> _icePillars;
	pair<int, bool> _crackedEarth[4][12];				// 갈라진 땅 모양
	POINT _stonePos[4][12][5];							// 갈라진 땅 폭발하고 나온 돌들
	vector<pair<int, int>> _volcano;					// 적 밑에 생기는 화산
	vector<vector<pair<int, int>>> _bigStones;			// 화산 폭발하고 나오는 큰 돌들
	pair<float, float> _wolfPos[2];						// 혈랑마혼 늑대

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight);
	void release(void);
	int getOrder();

	bool isFinish() {return _isFinish;}
	// 스킬 시작
	void start(vector<Character*> charList, Character* curChar, char* skillName);
};

