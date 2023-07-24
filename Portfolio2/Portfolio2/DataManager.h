#pragma once
#include "SingletonBase.h"

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _itemFP;
	vector<pair<string, string>> _mSaleWeaponList;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	vector<pair<string, string>> getSaleList() {return _mSaleWeaponList;}

	DataManager() {}
	~DataManager() {}
};

