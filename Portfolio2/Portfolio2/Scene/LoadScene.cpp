#include "../FrameWork/PCH/Stdafx.h"
#include "LoadScene.h"

HRESULT LoadScene::init(void)
{
	_frame = 0;
	for (int i = 0; i < 8; i++)
	{
		_loadButton[i].left = 210;
		_loadButton[i].right = WINSIZE_X - 210;
		_loadButton[i].top = 200 + 45 * i;
		_loadButton[i].bottom = _loadButton[i].top + 40;
	}
	_loadButton[8].left = 210;
	_loadButton[8].right = WINSIZE_X - 210;
	_loadButton[8].top = WINSIZE_Y - 100;
	_loadButton[8].bottom = WINSIZE_Y - 60;
	for (int i = 0; i < 9; i++)
	{	
		_scenarioN[i] = -1;
		if (_loadFP != nullptr)
		{
			fclose(_loadFP);
		}
		wsprintf(_text, "save%d.txt", i + 1);
		if (fopen_s(&_loadFP, _text, "r") == 0)
		{
			fscanf_s(_loadFP, "%d %d %d %d %d %d", &_scenarioN[i], &_time[i].month, &_time[i].day, &_time[i].hour, &_time[i].minute, &_time[i].second);
			fclose(_loadFP);
		}
	}
	return S_OK;
}

void LoadScene::release(void)
{
	fclose(_loadFP);
	fclose(_saveFP);
}

void LoadScene::update(void)
{
	SOUNDMANAGER->update();
	_frame++;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 9; i++)
		{
			if (PtInRect(&_loadButton[i], _ptMouse))
			{
				SOUNDMANAGER->playSoundFMOD("Button");
				if (DATAMANAGER->isLoadGame())
				{
					_selectButton = i;
					saveGame();
					DATAMANAGER->setSceneIdx(DATAMANAGER->getSceneIdx() - 1);
					SCENEMANAGER->loadingScene();
				}
				else if(_scenarioN[i] != -1)
				{
					DATAMANAGER->setScenario(_scenarioN[i]);
					wsprintf(_text, "save%d.txt", i + 1);
					fopen_s(&_loadFP, _text, "r");
					int temp;
					for (int i = 0; i < 6; i++)
					{
						fscanf_s(_loadFP, "%d", &temp);
					}
					DATAMANAGER->loadGame(_loadFP);
					SCENEMANAGER->loadingScene();
					fclose(_loadFP);
				}
			}
		}
	}
}

void LoadScene::render(void)
{
	IMAGEMANAGER->findImage("LoadBG")->render(getMemDC());
	DIALOGMANAGER->makeTextBox(getMemDC(), 200, 100, WINSIZE_X - 400, WINSIZE_Y - 250, 200);
	DIALOGMANAGER->makeTextBox(getMemDC(), 200, WINSIZE_Y - 150, WINSIZE_X - 400, 100, 200);
	IMAGEMANAGER->findImage("SaveLoadIcon")->frameRender(getMemDC(), 210, 110, 
		IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameWidth() * 2, IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameHeight() * 2, !DATAMANAGER->isLoadGame(), 0);
	IMAGEMANAGER->findImage("SaveLoadIcon")->frameRender(getMemDC(), 210, WINSIZE_Y - 140,
		IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameWidth() * 2, IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameHeight() * 2, 2, 0);
	if (DATAMANAGER->isLoadGame())
	{
		FONTMANAGER->textOut(getMemDC(), 250, 115, "가을체", 30, 100, "세이브", strlen("세이브"), RGB(164, 215, 242));
		FONTMANAGER->textOut(getMemDC(), 250, WINSIZE_Y - 135, "가을체", 30, 100, "퀵 세이브", strlen("퀵 세이브"), RGB(164, 215, 242));
		IMAGEMANAGER->findImage("PreferenceIcon")->frameRender(getMemDC(), 210, WINSIZE_Y - 140,
			IMAGEMANAGER->findImage("PreferenceIcon")->getFrameWidth() * 2, IMAGEMANAGER->findImage("PreferenceIcon")->getFrameHeight() * 2, 1, 0);
	}
	else
	{
		FONTMANAGER->textOut(getMemDC(), 250, 115, "가을체", 30, 100, "로드", strlen("로드"), RGB(164, 215, 242));
		FONTMANAGER->textOut(getMemDC(), 250, WINSIZE_Y - 135, "가을체", 30, 100, "퀵 로드", strlen("퀵 로드"), RGB(164, 215, 242));
		IMAGEMANAGER->findImage("SaveLoadIcon")->frameRender(getMemDC(), 210, WINSIZE_Y - 140,
			IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameWidth() * 2, IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameHeight() * 2, 2, 0);
	}
	IMAGEMANAGER->findImage("Episode")->render(getMemDC(), 250, 160, IMAGEMANAGER->findImage("Episode")->getWidth() * 2, IMAGEMANAGER->findImage("Episode")->getHeight() * 2,
		0, 0, IMAGEMANAGER->findImage("Episode")->getWidth(), IMAGEMANAGER->findImage("Episode")->getHeight());
	IMAGEMANAGER->findImage("Chapter")->render(getMemDC(), 450, 160, IMAGEMANAGER->findImage("Chapter")->getWidth() * 2, IMAGEMANAGER->findImage("Chapter")->getHeight() * 2,
		0, 0, IMAGEMANAGER->findImage("Chapter")->getWidth(), IMAGEMANAGER->findImage("Chapter")->getHeight());
	IMAGEMANAGER->findImage("Time")->render(getMemDC(), 650, 160, IMAGEMANAGER->findImage("Time")->getWidth() * 2, IMAGEMANAGER->findImage("Time")->getHeight() * 2,
		0, 0, IMAGEMANAGER->findImage("Time")->getWidth(), IMAGEMANAGER->findImage("Time")->getHeight());
	for (int i = 0; i < 9; i++)
	{
		if (PtInRect(&_loadButton[i], _ptMouse))
		{
			IMAGEMANAGER->findImage("SkillButtonActive")->alphaRender(getMemDC(), _loadButton[i].left, _loadButton[i].top, _loadButton[i].right - _loadButton[i].left, 
				_loadButton[i].bottom - _loadButton[i].top, 0, 0, IMAGEMANAGER->findImage("SkillButtonActive")->getWidth(), IMAGEMANAGER->findImage("SkillButtonActive")->getHeight(), 200);
		}
		wsprintf(_text, "save%d.txt", i + 1);
		if (_scenarioN[i] == -1)
		{
			FONTMANAGER->textOut(getMemDC(), 250, _loadButton[i].top + 5, "가을체", 30, 100, "BLANK", strlen("BLANK"), RGB(248, 136, 0));
		}
		else
		{
			switch (_scenarioN[i] % 3)
			{
				case 0:
					wsprintf(_text, "시반 슈미터");
				break;
				case 1:
					wsprintf(_text, "크림슨 크루세이드");
				break;
				case 2:
					wsprintf(_text, "아포칼립스");
				break;
			}
			FONTMANAGER->textOut(getMemDC(), 250, _loadButton[i].top + 5, "가을체", 30, 100, _text, strlen(_text), RGB(255, 255, 255));
			switch (_scenarioN[i])
			{
				case 69:
					wsprintf(_text, "불사조");
				break;
				case 75:
					wsprintf(_text, "형제");
				break;
			}
			FONTMANAGER->textOut(getMemDC(), 450, _loadButton[i].top + 5, "가을체", 30, 100, _text, strlen(_text), RGB(255, 255, 255));
			wsprintf(_text, "%d/%d %d:%d:%d", _time[i].month, _time[i].day, _time[i].hour, _time[i].minute, _time[i].second);
			FONTMANAGER->textOut(getMemDC(), 600, _loadButton[i].top + 10, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
		}
		IMAGEMANAGER->findImage("BulletPoint")->render(getMemDC(), _loadButton[i].left + 10, _loadButton[i].top + 15, IMAGEMANAGER->findImage("BulletPoint")->getWidth() * 2,
			IMAGEMANAGER->findImage("BulletPoint")->getHeight() * 2, 0, 0, IMAGEMANAGER->findImage("BulletPoint")->getWidth(), IMAGEMANAGER->findImage("BulletPoint")->getHeight());
	}
	IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
}

void LoadScene::saveGame()
{
	wsprintf(_text, "save%d.txt", _selectButton + 1);
	if (0 == fopen_s(&_saveFP, _text, "w"))
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(_saveFP, "%d %d %d %d %d %d %d %d\n", DATAMANAGER->getScenario(), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, DATAMANAGER->getBattleIdx(), DATAMANAGER->getSceneIdx() - 1);
		fprintf(_saveFP, "%d\n", DATAMANAGER->getLoadCharList().size());
		for (int i = 0; i < DATAMANAGER->getLoadCharList().size(); i++)
		{
			fprintf(_saveFP, "%d %d\n", DATAMANAGER->getLoadCharList()[i]->getType(), DATAMANAGER->getLoadCharList()[i]->isRide());
			if (DATAMANAGER->getLoadCharList()[i]->getType() == 0)
			{
				Player* player = (Player*)DATAMANAGER->getLoadCharList()[i];
				fprintf(_saveFP, "%s\n", player->getPlayerName().c_str());
				fprintf(_saveFP, "%d\n", player->getSkill().size());
				for (int j = 0; j < player->getSkill().size(); j++)
				{
					fprintf(_saveFP, "%s\t%d ", player->getSkill()[j].first, player->getSkill()[j].second);
				}
				fprintf(_saveFP, "\n");
				fprintf(_saveFP, "%d %d\n", player->canMove(), player->canAction());
			}
			else
			{
				Soldier* enemy = (Soldier*)DATAMANAGER->getLoadCharList()[i];
				fprintf(_saveFP, "%d\n", enemy->getEnemyType());
			}
			fprintf(_saveFP, "%d %d %d %d %d %d %d %d %d %d\n", DATAMANAGER->getLoadCharList()[i]->getTilePos().x, DATAMANAGER->getLoadCharList()[i]->getTilePos().y, DATAMANAGER->getLoadCharList()[i]->getCurHP(), DATAMANAGER->getLoadCharList()[i]->getCurMP(),
				DATAMANAGER->getLoadCharList()[i]->getMobility(), DATAMANAGER->getLoadCharList()[i]->getWTP(), DATAMANAGER->getLoadCharList()[i]->getCurWait(), DATAMANAGER->getLoadCharList()[i]->getTurnOrder(DATAMANAGER->getLoadCharList().size()), DATAMANAGER->getLoadCharList()[i]->getDir(), DATAMANAGER->getLoadCharList()[i]->getCurMobility());
		}
		/*for (auto it = DATAMANAGER->getPartyData().begin(); it != DATAMANAGER->getPartyData().end(); ++it)
		{

		}*/
		fclose(_saveFP);
	}
}
