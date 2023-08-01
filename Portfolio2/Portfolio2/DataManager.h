#pragma once
#include "SingletonBase.h"

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
	SKILL,
	LUCK,
	SPD,
	AC,
	MR,
	WTP,
	STATUSN
};

enum ITEMTYPE
{
	EMPTY,
	WEAPON,
	ARMOR,
	SHOES,
	ACCESSORY
};


struct ItemData
{
	string _name;
	int _price;
	int _type;

	ItemData(string name, int price, int type) { _name = name; _price = price; _type = type; }
};

struct CharacterData
{
	string _name;
	string _belong;
	string _class;
	int _status[14];
	ItemData* _equipment[5];
};

struct BattleData
{
	struct Enemy {
		POINT _tilePos;
		int _dir;
		int _turnOrder;
		int _type;
	};
	struct Object {
		POINT _rcLT;
		POINT _sortTile;
		int _width;
		int _height;
		int _index;
	};
	vector<POINT> _launchTile;
	vector<Enemy> _enemy;
	vector<Object> _object;
	int _bgImgN;
};

struct DialogData
{
	struct Dialog
	{
		string _speaker;
		int _dialogN;
		int _dialogType;
		LPCWSTR _script[10];
	};
	vector<Dialog> _dialogList;
	vector<int> _stopDialog;
};

struct StoryData
{
	struct Object
	{
		int _objectType;
		int _x;
		int _y;
	};
	vector<Object> _objectList;
};

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _fp;
	vector<CharacterData*> _mParty;
	map<string, pair<ItemData*, int>> _mInventory;
	map<string, ItemData*> _mItemList;
	map < string, vector<BattleData*>> _mBattleList;
	map<int, DialogData*> _mDialogList;
	map<int, vector<StoryData*>> _mStoryData;
	map<int, vector<string>> _mSceneList;
	int _eld;
	int _scenario;
	int _battleIdx;
	int _sceneIdx;
	bool _introVideo;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void setEld(int eld) { _eld = eld; }
	void setIntroVideo(bool introVideo) {_introVideo = introVideo;}

	vector<CharacterData*> getPartyData() {return _mParty;}
	map<string, pair<ItemData*, int>> getInventory() { return _mInventory; }
	int getEld() {return _eld;}

	void setScenario(int scenario) { _scenario = scenario; }
	int getScenario() {return _scenario;}
	void setBattleIdx(int battleIdx) {_battleIdx = battleIdx;}
	int getBattleIdx() {return _battleIdx;}
	void setSceneIdx(int sceneIdx) {_sceneIdx = sceneIdx;}
	int getSceneIdx() {return _sceneIdx;}
	bool getIntroVideo() {return _introVideo;}

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

	DataManager() {}
	~DataManager() {}
};

