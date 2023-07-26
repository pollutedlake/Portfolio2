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

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _fp;
	FILE* _partyFP;
	vector<CharacterData*> _mParty;
	map<string, pair<ItemData*, int>> _mInventory;
	map<string, ItemData*> _mItemList;
	int _eld;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void setEld(int eld) { _eld = eld; }

	vector<CharacterData*> getPartyData() {return _mParty;}
	map<string, pair<ItemData*, int>> getInventory() { return _mInventory; }
	int getEld() {return _eld;}

	// 아이템 데이터
	ItemData* findItem(string strKey);

	// 인벤토리
	pair<ItemData*, int> findItemInven(string strKey);
	ItemData* buyItem(string strKey, int num, ItemData* item);
	void sellItem(string strKey, int num);
	void equipItem(string strKey, int charIdx, int itemIdx);
	void takeOffEquip(int charIdx, int itemIdx);

	DataManager() {}
	~DataManager() {}
};

