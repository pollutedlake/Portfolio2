#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	if (fopen_s(&_fp, "Resources/Data/ItemList.txt", "r") == 0)
	{
		char itemName[256];
		//char itemPrice[256];
		int itemPrice;
		//while(EOF != fscanf_s(_fp, "%[^\t]\t%s\n", itemName, _countof(itemName), itemPrice, _countof(itemPrice)))
		while(EOF != fscanf_s(_fp, "%[^\t]\t%d\n", itemName, _countof(itemName), &itemPrice))
		{
			ItemData* item = new ItemData(itemName, itemPrice);
			_mSaleWeaponList.push_back(item);
		}
	}
	for (auto it = _mSaleWeaponList.begin(); it != _mSaleWeaponList.end(); ++it)
	{
		cout << (*it)->_name << "\t" << (*it)->_price << endl;
	}
	fclose(_fp);
	if (fopen_s(&_fp, "Resources/Data/PartyData.txt", "r") == 0)
	{
		char str[256];
		int charN;
		fscanf_s(_fp, "%d\n", &charN);
		while (charN--)
		{
			fscanf_s(_fp, "%s", str, _countof(str));
			CharacterData* character = new CharacterData;
			character->_name = str;
			for (int i = 0; i < STATUSN; i++)
			{
				fscanf_s(_fp, "%d", &character->_status[i]);
			}
			fscanf_s(_fp, "%s", str, _countof(str));
			character->_belong = str;
			fscanf_s(_fp, " %[^\n]\n", str, _countof(str));
			character->_class = str;
			_mParty.push_back(character);
			fscanf_s(_fp, "\n");
		}
		fscanf_s(_fp, "%d\n", &_eld);
	}
	for (auto it = _mParty.begin(); it != _mParty.end(); ++it)
	{
		cout << (*it)->_name << endl;
		for (int i = 0; i < STATUSN; i++)
		{
			cout << (*it)->_status[i]<<endl;
		}
		cout << (*it)->_belong << endl;
		cout << (*it)->_class << endl;
	}
	cout << _eld << endl;
	fclose(_fp);
	return S_OK;
}

void DataManager::update(void)
{
}

void DataManager::release(void)
{
	fclose(_fp);
}

void DataManager::render(void)
{
}

pair<ItemData*, int> DataManager::findItem(string strKey)
{	
	auto key = _mInventory.find(strKey);
	if (key != _mInventory.end())
	{
		return key->second;
	}
	return make_pair(nullptr, NULL);
}

ItemData* DataManager::buyItem(string strKey, int num, ItemData* item)
{
	pair<ItemData*, int> find = findItem(strKey);
	if (find.second)
	{
		_mInventory.find(strKey)->second.second += num;
	}
	else
	{
		_mInventory.insert(make_pair(strKey, make_pair(item, num)));
	}
	return item;
}

void DataManager::sellItem(string strKey, int num)
{
	_mInventory.find(strKey)->second.second -= num;
	if (_mInventory.find(strKey)->second.second <= 0)
	{
		_mInventory.erase(strKey);
	}
}
