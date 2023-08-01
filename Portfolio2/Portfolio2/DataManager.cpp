#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	_introVideo = true;
	_scenario = 69;
	_sceneIdx = 0;
	_battleIdx = 0;
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
			fscanf_s(_fp, "%[^\t]\t", str, _countof(str));
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
		int secnarioN;
		fscanf_s(_fp, "%d\n",  &secnarioN);
		while(secnarioN--)
		{
			char str[256];
			fscanf_s(_fp, "%s", str, _countof(str));
			vector<BattleData*> battleList;
			int battleN;
			fscanf_s(_fp, "%d\n", &battleN);
			while (battleN--)
			{
				BattleData* battleData = new BattleData;
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
	}
	fclose(_fp);
	if (fopen_s(&_fp, "Resources/Data/DialogList.txt", "r") == 0)
	{
		int totalScenario = 2;
		char str[256];
		while (totalScenario--)
		{
			int scenarioN;
			int dialogN;
			//vector<DialogData*> dialogList;
			fscanf_s(_fp, "%d%d\n", &scenarioN, &dialogN);
			DialogData* dialogData = new DialogData;
			while (dialogN--)
			{
				DialogData::Dialog dialog;
				fscanf_s(_fp, "%[^\t]\t%d%d ", str, _countof(str), &dialog._dialogN, &dialog._dialogType);
				dialog._speaker = str;
				for (int i = 0; i < dialog._dialogN - 1; i++)
				{
					wchar_t* charBuffer = new wchar_t[256];
					fscanf_s(_fp, "%[^\t]\t", str, _countof(str));
					ZeroMemory(charBuffer, sizeof(charBuffer));
					MultiByteToWideChar(CP_ACP, 0, str, _countof(str), charBuffer, 256);
					dialog._script[i] = charBuffer;
				}
				fscanf_s(_fp, "%[^\n]\n", str, _countof(str));
				wchar_t* charBuffer = new wchar_t[256];
				ZeroMemory(charBuffer, sizeof(charBuffer));
				MultiByteToWideChar(CP_ACP, 0, str, _countof(str), charBuffer, 256);
				dialog._script[dialog._dialogN - 1] = charBuffer;
				dialogData->_dialogList.push_back(dialog);
			}
			int stopDialogN;
			fscanf_s(_fp, "%d", &stopDialogN);
			while(stopDialogN--)
			{
				int stopDialog;
				fscanf_s(_fp, "%d", &stopDialog);
				dialogData->_stopDialog.push_back(stopDialog);
			}
			_mDialogList.insert(make_pair(scenarioN, dialogData));
		}
	}
	fclose(_fp);
	if (fopen_s(&_fp, "Resources/Data/StoryData.txt", "r") == 0)
	{
		int totalScenario = 1;
		while (totalScenario--)
		{
			int scenarioN;
			fscanf_s(_fp, "%d\n", &scenarioN);
			int backGroundN;
			fscanf_s(_fp, "%d\n", &backGroundN);
			vector<StoryData*> storyDataList;
			while(backGroundN--)
			{
				int objectN;
				fscanf_s(_fp, "%d\n", &objectN);
				StoryData* storyData = new StoryData;
				while (objectN--)
				{
					
					StoryData::Object objectData;
					fscanf_s(_fp, "%d%d%d\n", &objectData._objectType, &objectData._x, &objectData._y);
					storyData->_objectList.push_back(objectData);
				}
				storyDataList.push_back(storyData);
			}
			_mStoryData.insert(make_pair(scenarioN, storyDataList));
		}
	}
	fclose(_fp);
	if (fopen_s(&_fp, "Resources/Data/SceneOrderData.txt", "r") == 0)
	{
		int totalScenarioN = 2;
		while (totalScenarioN--)
		{
			int scenarioN;
			int sceneN;
			fscanf_s(_fp, "%d %d", &scenarioN, &sceneN);
			vector<string> sceneList;
			while (sceneN--)
			{
				char scene[256];
				fscanf_s(_fp, "%s", scene, _countof(scene));
				sceneList.push_back(scene);
			}
			fscanf_s(_fp, "\n");
			_mSceneList.insert(make_pair(scenarioN, sceneList));
		}
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
