#pragma once
#include "SingletonBase.h"
#include "Player.h"
#include "Soldier.h"

// 스탯
enum STATUS
{
	CURHP,
	MAXHP,
	CURSOUL,
	MAXSOUL,
	CUREXP,
	STR,
	DEX,
	INTELLIGENCE,
	SKILLPOWER,
	LUCK,
	SPD,
	AC,
	MR,
	WTP,
	STATUSN
};

// 아이템 종류
enum ITEMTYPE
{
	EMPTY,
	WEAPON,
	ARMOR,
	SHOES,
	ACCESSORY
};


// 아이템정보
struct ItemData
{
	string _name;	// 이름
	int _price;		// 가격
	int _type;		// 종류
	int _stat;		// 스탯

	ItemData(string name, int price, int type, int stat) { _name = name; _price = price; _type = type; _stat = stat;}
};

// 캐릭터 데이터
struct CharacterData
{
	string _name;
	string _belong;						// 소속
	string _class;						// 직업
	int _status[14];					// 스탯
	ItemData* _equipment[5];			// 장비
	vector<pair<char*, int>> _skill;	// 스킬
};

// 전투씬 데이터
struct BattleData
{
	struct Enemy {
		POINT _tilePos;				// 타일 위치
		int _dir;					// 방향
		int _turnOrder;				// 턴 순서
		int _type;					// 타입
	};
	struct Object {
		POINT _rcLT;				// 그려주는 위치
		POINT _sortTile;			// 정렬 때 기준이 되는 위치
		int _width;					// 넓이
		int _height;				// 높이
		int _index;					// 인덱스
	};
	int _dir;						// 캐릭터 배치시 방향
	vector<POINT> _launchTile;		// 캐릭터 배치타일들
	vector<Enemy> _enemy;			// 적
	vector<Object> _object;			// 오브젝트
	int _bgImgN;					// 배경 이미지
};

// 대화 데이터
struct DialogData
{
	struct Dialog
	{
		string _speaker;			// 말하는 사람
		int _dialogN;				// 다이얼로그 수
		int _dialogType;			// 다이얼로그 타입
		LPCWSTR _script[10];		// 다이얼로그 내용
	};
	vector<Dialog> _dialogList;		
	vector<int> _stopDialog;		// 다이얼로그 진행 중 멈추는 타이밍
};

// 스토리 씬 데이터
struct StoryData
{
	struct Object					// 스토리 씬 내내 가만히 있는 것
	{
		int _objectType;			// index
		int _x;						// 그려줄 X
		int _y;						// 그려줄 Y
	};
	vector<Object> _objectList;
};

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _fp;												// 파일포인터
	vector<CharacterData*> _mParty;							// 파티원들의 정보
	map<string, pair<ItemData*, int>> _mInventory;			// 인벤토리
	map<string, ItemData*> _mItemList;						// 아이템정보 map
	map < string, vector<BattleData*>> _mBattleList;		// 전투씬 정보 map
	map<int, DialogData*> _mDialogList;						// 다이얼로그 정보 map
	map<int, vector<StoryData*>> _mStoryData;				// 스토리씬 정보 map
	map<int, vector<string>> _mSceneList;					// 씬 순서 map
	vector<Character*> _loadCharList;						// 불러온 세이브
	
	int _eld;												// 소지금
	int _scenario;											// 현재 시나리오
	int _battleIdx;											// 전투씬 인덱스
	int _sceneIdx;											// 씬 인덱스
	int _maxScenario;										// 해금되어 있는 최대 시나리오
	bool _introVideo;										// 인트로 비디오 실행 여부
	bool _loadGame;											// 세이브 불러왔는지 여부

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void setEld(int eld) { _eld = eld; }
	void setIntroVideo(bool introVideo) {_introVideo = introVideo;}

	void loadGame(FILE* fp);

	vector<CharacterData*> getPartyData() {return _mParty;}
	map<string, pair<ItemData*, int>> getInventory() { return _mInventory; }
	int getEld() {return _eld;}

	void setScenario(int scenario) { _scenario = scenario; }
	int getScenario() {return _scenario;}
	void setBattleIdx(int battleIdx) {_battleIdx = battleIdx;}
	int getBattleIdx() {return _battleIdx;}
	void setSceneIdx(int sceneIdx) {_sceneIdx = sceneIdx;}
	void setLoadCharList(vector<Character*> loadCharList) { _loadCharList = loadCharList; }
	int getSceneIdx() {return _sceneIdx;}
	bool getIntroVideo() {return _introVideo;}
	bool isLoadGame() {return _loadGame;}
	void setLoadGame(bool load) {_loadGame = load;}
	int getMaxScenario() { return _maxScenario; }
	void setMaxScenario(int maxScenario) { _maxScenario = maxScenario; }

	// 전투데이터
	BattleData* findBattleData(string strKey, int i);

	// 아이템 데이터
	ItemData* findItem(string strKey);

	// 인벤토리
	pair<ItemData*, int> findItemInven(string strKey);
	ItemData* buyItem(string strKey, int num, ItemData* item);
	void sellItem(string strKey, int num);
	void equipItem(string strKey, int charIdx, int itemIdx);
	void takeOffEquip(int charIdx, int itemIdx);

	// 다이얼로그
	DialogData* getDialogList(int scenarioN) { return _mDialogList.find(scenarioN)->second; }

	// StoryData
	vector<StoryData*> getStoryData(int scenarioN) { return _mStoryData.find(scenarioN)->second; }

	vector<string> getSceneList(int scenarioN) {return _mSceneList.find(scenarioN)->second;}

	vector<Character*> getLoadCharList() {return _loadCharList;}

	DataManager() {}
	~DataManager() {}
};

