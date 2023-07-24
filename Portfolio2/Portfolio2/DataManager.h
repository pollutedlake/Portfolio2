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
	APD,
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

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _fp;
	FILE* _partyFP;
	vector<pair<string, string>> _mSaleWeaponList;
	vector<CharacterData*> _mParty;
	int _eld;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	vector<pair<string, string>> getSaleList() {return _mSaleWeaponList;}
	vector<CharacterData*> getPartyData() {return _mParty;}
	int* getEld() {return &_eld;}

	DataManager() {}
	~DataManager() {}
};

