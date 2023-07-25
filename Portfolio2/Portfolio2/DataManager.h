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

struct CharacterData
{
	string _name;
	string _belong;
	string _class;
	int _status[14];
};

struct ItemData
{
	string _name;
	int _price;

	ItemData(string name, int price) { _name = name; _price = price; }
};

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _fp;
	FILE* _partyFP;
	vector<ItemData*> _mSaleWeaponList;
	vector<CharacterData*> _mParty;
	map<string, pair<ItemData*, int>> _mInventory;
	int _eld;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void setEld(int eld) { _eld = eld; }

	vector<ItemData*> getSaleList() {return _mSaleWeaponList;}
	vector<CharacterData*> getPartyData() {return _mParty;}
	map<string, pair<ItemData*, int>> getInventory() { return _mInventory; }
	int getEld() {return _eld;}

	pair<ItemData*, int> findItem(string strKey);
	ItemData* buyItem(string strKey, int num, ItemData* item);
	void sellItem(string strKey, int num);

	DataManager() {}
	~DataManager() {}
};

