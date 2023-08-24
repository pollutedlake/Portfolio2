#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	_introVideo = true;
	_maxScenario = 75;
	_scenario = 69;
	_sceneIdx = 0;
	_battleIdx = 0;
	_loadGame = false;
	if (fopen_s(&_fp, "Resources/Data/ItemList.txt", "r") == 0)
	{
		char itemName[256];
		int itemPrice;
		int itemType;
		int stat;
		while(EOF != fscanf_s(_fp, "%[^\t]\t%d%d%d\n", itemName, _countof(itemName), &itemPrice, &itemType, &stat))
		{
			ItemData* item = new ItemData(itemName, itemPrice, itemType, stat);
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
			fscanf_s(_fp, "%[^\t]\t", str, _countof(str));
			character->_equipment[4] = findItem(str);
			int skillN;
			fscanf_s(_fp, "%d ", &skillN);
			while (skillN--)
			{
				int skillType;
				char* skillName = new char[256];
				fscanf_s(_fp, "%[^\t]\t%d ", skillName, strlen(skillName), &skillType);
				character->_skill.push_back(make_pair(skillName, skillType));
			}
			fscanf_s(_fp, "\n");
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
		for (auto it2 = (*it)->_skill.begin(); it2 != (*it)->_skill.end(); ++it2)
		{
			cout << (*it2).first << "\t" << (*it2).second << endl;
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
				fscanf_s(_fp, "%d\n", &battleData->_dir);
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

void DataManager::loadGame(FILE* fp)
{
	_loadCharList.clear();
	_loadGame = true;
	fscanf_s(fp, "%d %d\n", &_battleIdx, &_sceneIdx);
	int charN;
	fscanf_s(fp, "%d\n", &charN);
	char str[256];
	int data;
	int data2;
	for (int i = 0; i < charN; i++)
	{
		fscanf_s(fp, "%d %d\n", &data, &data2);
		if (data == 0)
		{
			char name[256];
			fscanf_s(fp, "%[^\n]\n", name, _countof(name));
			int skillN;
			fscanf_s(fp, "%d\n", &skillN);
			vector<pair<char*, int>> skill;
			while (skillN--)
			{
				char* skillName = new char[256];
				fscanf_s(fp, "%[^\t]\t%d ", skillName, strlen(skillName), &data);
				skill.push_back(make_pair(skillName, data));
			}
			fscanf_s(fp, "\n");
			Player* player = new Player(name, skill);
			player->init();
			player->setRide(data2);
			int canMove;
			int canAction;
			fscanf_s(_fp, "%d %d\n", &canMove, &canAction);
			player->setTurn(0, canMove);
			player->setTurn(1, canAction);
			fscanf_s(fp, "%d", &data);
			fscanf_s(fp, "%d", &data2);
			player->setTilePos({data, data2});
			fscanf_s(fp, "%d", &data);
			player->setCurHP(data);
			fscanf_s(fp, "%d", &data);
			player->setCurMP(data);
			fscanf_s(fp, "%d", &data);
			player->setMobility(data);
			fscanf_s(fp, "%d", &data);
			player->setWTP(data);
			fscanf_s(fp, "%d", &data);
			player->setCurWait(data);
			fscanf_s(fp, "%d", &data);
			player->setTurnOder(data);
			fscanf_s(fp, "%d", &data);
			player->setDir(data);
			fscanf_s(fp, "%d", &data);
			player->setCurMobility(data);
			fscanf_s(fp, "\n");
			_loadCharList.push_back(player);
		}
		else
		{
			fscanf_s(_fp, "%d\n", &data);
			Soldier* enemy = new Soldier;
			enemy->init((EnemyType)data);
			fscanf_s(fp, "%d", &data);
			fscanf_s(fp, "%d", &data2);
			enemy->setTilePos({ data, data2 });
			fscanf_s(fp, "%d", &data);
			enemy->setCurHP(data);
			fscanf_s(fp, "%d", &data);
			enemy->setCurMP(data);
			fscanf_s(fp, "%d", &data);
			enemy->setMobility(data);
			fscanf_s(fp, "%d", &data);
			enemy->setWTP(data);
			fscanf_s(fp, "%d", &data);
			enemy->setCurWait(data);
			fscanf_s(fp, "%d", &data);
			enemy->setTurnOder(data);
			fscanf_s(fp, "%d", &data);
			enemy->setDir(data);
			fscanf_s(fp, "%d", &data);
			enemy->setCurMobility(data);
			fscanf_s(fp, "\n");
			_loadCharList.push_back(enemy);
		}
	}
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
	switch (_mParty[charIdx]->_equipment[itemIdx]->_type)
	{
	case 1:
		_mParty[charIdx]->_status[STR] -= _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
	case 2:
		_mParty[charIdx]->_status[DEX] -= _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
	case 3:
		_mParty[charIdx]->_status[SPD] -= _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
	}
	_mParty[charIdx]->_equipment[itemIdx] = findItem(strKey);
	switch (_mParty[charIdx]->_equipment[itemIdx]->_type)
	{
		case 1:
			_mParty[charIdx]->_status[STR] += _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
		case 2:
			_mParty[charIdx]->_status[DEX] += _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
		case 3:
			_mParty[charIdx]->_status[SPD] += _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
	}
	if (strcmp(strKey.c_str(), "없음"))
	{
		sellItem(strKey, 1);
	}
}

void DataManager::takeOffEquip(int charIdx, int itemIdx)
{
	switch (_mParty[charIdx]->_equipment[itemIdx]->_type)
	{
	case 1:
		_mParty[charIdx]->_status[STR] -= _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
	case 2:
		_mParty[charIdx]->_status[DEX] -= _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
	case 3:
		_mParty[charIdx]->_status[SPD] -= _mParty[charIdx]->_equipment[itemIdx]->_stat;
		break;
	}
	_mParty[charIdx]->_equipment[itemIdx] = findItem("없음");
}
