#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	if (fopen_s(&_fp, "Resources/Data/ItemList.txt", "r") == 0)
	{
		char itemName[256];
		char itemPrice[256];
		while(EOF != fscanf_s(_fp, "%[^\t]\t%s\n", itemName, _countof(itemName), itemPrice, _countof(itemPrice)))
		{
			_mSaleWeaponList.push_back(make_pair(itemName, itemPrice));
		}
	}
	for (auto it = _mSaleWeaponList.begin(); it != _mSaleWeaponList.end(); ++it)
	{
		cout << (*it).first << "\t" << (*it).second << endl;
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
