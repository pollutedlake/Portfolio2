#pragma once
#include "SingletonBase.h"
#include "Player.h"
#include "Soldier.h"

// ����
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

// ������ ����
enum ITEMTYPE
{
	EMPTY,
	WEAPON,
	ARMOR,
	SHOES,
	ACCESSORY
};


// ����������
struct ItemData
{
	string _name;	// �̸�
	int _price;		// ����
	int _type;		// ����
	int _stat;		// ����

	ItemData(string name, int price, int type, int stat) { _name = name; _price = price; _type = type; _stat = stat;}
};

// ĳ���� ������
struct CharacterData
{
	string _name;
	string _belong;						// �Ҽ�
	string _class;						// ����
	int _status[14];					// ����
	ItemData* _equipment[5];			// ���
	vector<pair<char*, int>> _skill;	// ��ų
};

// ������ ������
struct BattleData
{
	struct Enemy {
		POINT _tilePos;				// Ÿ�� ��ġ
		int _dir;					// ����
		int _turnOrder;				// �� ����
		int _type;					// Ÿ��
	};
	struct Object {
		POINT _rcLT;				// �׷��ִ� ��ġ
		POINT _sortTile;			// ���� �� ������ �Ǵ� ��ġ
		int _width;					// ����
		int _height;				// ����
		int _index;					// �ε���
	};
	int _dir;						// ĳ���� ��ġ�� ����
	vector<POINT> _launchTile;		// ĳ���� ��ġŸ�ϵ�
	vector<Enemy> _enemy;			// ��
	vector<Object> _object;			// ������Ʈ
	int _bgImgN;					// ��� �̹���
};

// ��ȭ ������
struct DialogData
{
	struct Dialog
	{
		string _speaker;			// ���ϴ� ���
		int _dialogN;				// ���̾�α� ��
		int _dialogType;			// ���̾�α� Ÿ��
		LPCWSTR _script[10];		// ���̾�α� ����
	};
	vector<Dialog> _dialogList;		
	vector<int> _stopDialog;		// ���̾�α� ���� �� ���ߴ� Ÿ�̹�
};

// ���丮 �� ������
struct StoryData
{
	struct Object					// ���丮 �� ���� ������ �ִ� ��
	{
		int _objectType;			// index
		int _x;						// �׷��� X
		int _y;						// �׷��� Y
	};
	vector<Object> _objectList;
};

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _fp;												// ����������
	vector<CharacterData*> _mParty;							// ��Ƽ������ ����
	map<string, pair<ItemData*, int>> _mInventory;			// �κ��丮
	map<string, ItemData*> _mItemList;						// ���������� map
	map < string, vector<BattleData*>> _mBattleList;		// ������ ���� map
	map<int, DialogData*> _mDialogList;						// ���̾�α� ���� map
	map<int, vector<StoryData*>> _mStoryData;				// ���丮�� ���� map
	map<int, vector<string>> _mSceneList;					// �� ���� map
	vector<Character*> _loadCharList;						// �ҷ��� ���̺�
	
	int _eld;												// ������
	int _scenario;											// ���� �ó�����
	int _battleIdx;											// ������ �ε���
	int _sceneIdx;											// �� �ε���
	int _maxScenario;										// �رݵǾ� �ִ� �ִ� �ó�����
	bool _introVideo;										// ��Ʈ�� ���� ���� ����
	bool _loadGame;											// ���̺� �ҷ��Դ��� ����

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

	// ����������
	BattleData* findBattleData(string strKey, int i);

	// ������ ������
	ItemData* findItem(string strKey);

	// �κ��丮
	pair<ItemData*, int> findItemInven(string strKey);
	ItemData* buyItem(string strKey, int num, ItemData* item);
	void sellItem(string strKey, int num);
	void equipItem(string strKey, int charIdx, int itemIdx);
	void takeOffEquip(int charIdx, int itemIdx);

	// ���̾�α�
	DialogData* getDialogList(int scenarioN) { return _mDialogList.find(scenarioN)->second; }

	// StoryData
	vector<StoryData*> getStoryData(int scenarioN) { return _mStoryData.find(scenarioN)->second; }

	vector<string> getSceneList(int scenarioN) {return _mSceneList.find(scenarioN)->second;}

	vector<Character*> getLoadCharList() {return _loadCharList;}

	DataManager() {}
	~DataManager() {}
};

