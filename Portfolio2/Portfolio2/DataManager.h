#pragma once
#include "SingletonBase.h"

class DataManager : public SingletonBase<DataManager>
{
private:
	FILE* _itemFP;
	vector<pair<string, int>> _mItemList;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	DataManager() {}
	~DataManager() {}
};

