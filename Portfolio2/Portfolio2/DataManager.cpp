#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	if (fopen_s(&_fp, "Resources/Data/ItemList.txt", "r") == 0)
	{
		char itemName[256];
		int itemPrice;
		int itemType;
		while(EOF != fscanf_s(_fp, "%[^\t]\t%d%d\n", itemName, _countof(itemName), &itemPrice, &itemType))
		{
			ItemData* item = new ItemData(itemName, itemPrice, itemType);
			_mItemList.insert(make_pair(itemName, item));
		}
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
			fscanf_s(_fp, " %[^\t]\t", str, _countof(str));
			character->_class = str;
			for (int i = 0; i < 4; i++)
			{
				fscanf_s(_fp, "%[^\t]\t", str, _countof(str));
				character->_equipment[i] = findItem(str);
			}
			fscanf_s(_fp, "%[^\n]\n", str, _countof(str));
			character->_equipment[4] = findItem(str);
			_mParty.push_back(character);
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
		for (int i = 0; i < 5; i++)
		{
			cout << (*it)->_equipment[i]->_name << endl;
		}
	}
	cout << _eld << endl;
	fclose(_fp);
	if (fopen_s(&_fp, "Resources/Data/BattleStageData.txt", "r") == 0)
	{
		char str[256];
		fscanf_s(_fp, "%s", str, _countof(str));
		BattleData* battleData = new BattleData;
		vector<BattleData*> battleList;
		int battleN;
		fscanf_s(_fp, "%d\n", &battleN);
		while (battleN--)
		{
			fscanf_s(_fp, "%d", &(battleData->_bgImgN));
			int enemyTotal;
			fscanf_s(_fp, "%d\n", &enemyTotal);
			int enemyN = 0;
			while (enemyTotal != enemyN)
			{
				int type;
				int num;
				fscanf_s(_fp, "%d%d\n", &type, &num);
				enemyN += num;
				while (num--)
				{
					BattleData::Enemy enemy;
					enemy._type = type;
					fscanf_s(_fp, "%d%d%d%d\n", &(enemy._tilePos.x), &(enemy._tilePos.y), &(enemy._dir), &(enemy._turnOrder));
					battleData->_enemy.push_back(enemy);
				}
			}
			int objectN;
			fscanf_s(_fp, "%d\n", &objectN);
			while (objectN--)
			{
				BattleData::Object object;
				fscanf_s(_fp, "%d%d%d%d%d%d%d\n", 
					&(object._index), &(object._rcLT.x), &(object._rcLT.y), &(object._width), &(object._height), &(object._sortTile.x), &(object._sortTile.y));
				battleData->_object.push_back(object);

			}
			int launchTileN;
			fscanf_s(_fp, "%d\n", &launchTileN);
			while (launchTileN--)
			{
				POINT launchTile;
				fscanf_s(_fp, "%d%d", &launchTile.x, &launchTile.y);
				battleData->_launchTile.push_back(launchTile);
			}
			battleList.push_back(battleData);
		}
		_mBattleList.insert(make_pair(str, battleList));
	}
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

ItemData* DataManager::findItem(string strKey)
{
	auto key = _mItemList.find(strKey);

	if (key != _mItemList.end())
	{
		return key->second;
	}
	return nullptr;
}

pair<ItemData*, int> DataManager::findItemInven(string strKey)
{	
	auto key = _mInventory.find(strKey);
	if (key != _mInventory.end())
	{
		return key->second;
	}
	return make_pair(nullptr, NULL);
}

BattleData* DataManager::findBattleData(string strKey, int i)
{
	return _mBattleList.find(strKey)->second[i];
}

ItemData* DataManager::buyItem(string strKey, int num, ItemData* item)
{
	pair<ItemData*, int> find = findItemInven(strKey);
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

void DataManager::equipItem(string strKey, int charIdx, int itemIdx)
{
	if (strcmp(_mParty[charIdx]->_equipment[itemIdx]->_name.c_str(), "없음"))
	{
		buyItem(_mParty[charIdx]->_equipment[itemIdx]->_name, 1, _mParty[charIdx]->_equipment[itemIdx]);
	}
	_mParty[charIdx]->_equipment[itemIdx] = findItem(strKey);
	if (strcmp(strKey.c_str(), "없음"))
	{
		sellItem(strKey, 1);
	}
}

void DataManager::takeOffEquip(int charIdx, int itemIdx)
{
	_mParty[charIdx]->_equipment[itemIdx] = findItem("없음");

}
