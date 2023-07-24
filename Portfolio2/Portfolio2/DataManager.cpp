#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	if (fopen_s(&_itemFP, "Resources/Data/ItemList.txt", "r") == 0)
	{
		char itemName[256];
		int itemPrice;
		fscanf_s(_itemFP, "%s %d", itemName, _countof(itemName), &itemPrice);
		cout << itemName << "\t" << itemPrice << endl;
		_mItemList.push_back(make_pair(itemName, itemPrice));
	}
	else
	{
		cout << "½ÇÆÐ" << endl;
	}
	return S_OK;
}

void DataManager::update(void)
{
}

void DataManager::release(void)
{
	fclose(_itemFP);
}

void DataManager::render(void)
{
}
