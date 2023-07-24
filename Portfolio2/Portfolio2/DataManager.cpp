#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	if (fopen_s(&_itemFP, "Resources/Data/ItemList.txt", "r") == 0)
	{
		char itemName[256];
		char itemPrice[256];
		while(EOF != fscanf_s(_itemFP, "%[^\t]\t%s\n", itemName, _countof(itemName), itemPrice, _countof(itemPrice)))
		{
			_mSaleWeaponList.push_back(make_pair(itemName, itemPrice));
		}
	}
	for (auto it = _mSaleWeaponList.begin(); it != _mSaleWeaponList.end(); ++it)
	{
		cout << (*it).first << "\t" << (*it).second << endl;
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
