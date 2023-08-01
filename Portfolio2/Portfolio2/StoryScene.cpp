#include "Stdafx.h"
#include "StoryScene.h"

HRESULT StoryScene::init(void)
{
	if(DATAMANAGER->getScenario() == 75)
	{
	_storyBG = IMAGEMANAGER->findImage("StoryBG");
	_textBoxImg = IMAGEMANAGER->findImage("TextBox");
	_vermontSherazade = IMAGEMANAGER->findImage("VermontSherazade");
	_redImage = IMAGEMANAGER->findImage("Red");
	_saladin = IMAGEMANAGER->findImage("SaladinStory");

	_soundList[0] = "Fight";
	_soundList[1] = "Scream1";
	_soundList[2] = "Fight";
	_soundList[3] = "Scream2";
	_soundList[4] = "Dialog19";
	_soundList[5] = "Dialog20";
	_soundList[6] = "Dialog21";
	_soundList[7] = "Dialog22";
	_soundList[8] = "Dialog23";
	_soundList[9] = "Dialog24";
	_soundList[10] = "Dialog25";
	_soundList[11] = "Dialog26";
	_soundList[12] = "Dialog27";
	_soundList[13] = "Dialog28";
	_soundList[14] = "Dialog29";
	_soundList[15] = "Dialog30";
	_soundList[16] = "Dialog31";
	_soundList[17] = "Dialog32";
	_soundList[18] = "Dialog33";
	_soundList[19] = "Dialog34";
	_soundList[20] = "Dialog35";
	_soundList[21] = "Dialog36";

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_storyDialog[i]._script[j] = L"\0";
		}
	}

	_storyDialog[0]._speaker = "Vermont";
	_storyDialog[0]._dialogN = 2;
	_storyDialog[0]._dialogType = 0;
	_storyDialog[0]._script[0] = L"[버몬트]";
	_storyDialog[0]._script[1] = L"기다리고 있었다.";

	_storyDialog[1]._speaker = "Saladin";
	_storyDialog[1]._dialogN = 2;
	_storyDialog[1]._dialogType = 0;
	_storyDialog[1]._script[0] = L"[살라딘]";
	_storyDialog[1]._script[1] = L"...";

	_storyDialog[2]._speaker = "Vermont";
	_storyDialog[2]._dialogN = 2;
	_storyDialog[2]._dialogType = 0;
	_storyDialog[2]._script[0] = L"[버몬트]";
	_storyDialog[2]._script[1] = L"지난번엔 운좋게 빠져 나갔지만 이번엔 힘들걸?";

	_storyDialog[3]._speaker = "Sherazade";
	_storyDialog[3]._dialogN = 2;
	_storyDialog[3]._dialogType = 0;
	_storyDialog[3]._script[0] = L"[셰라자드]";
	_storyDialog[3]._script[1] = L"살라딘...";

	_storyDialog[4]._speaker = "Saladin";
	_storyDialog[4]._dialogN = 2;
	_storyDialog[4]._dialogType = 0;
	_storyDialog[4]._script[0] = L"[살라딘]";
	_storyDialog[4]._script[1] = L"셰라자드, 걱정마시오. 곧 구해줄테니...";

	_storyDialog[5]._speaker = "Vermont";
	_storyDialog[5]._dialogN = 4;
	_storyDialog[5]._dialogType = 0;
	_storyDialog[5]._script[0] = L"[버몬트]";
	_storyDialog[5]._script[1] = L"흥 ! 네놈의 이야기는 들었다. 요새 두개가 네녀석에게 박살이 났더군.";
	_storyDialog[5]._script[2] = L"자, 어서 그 칼을 버리지 않으면, 이 여자를 두 번 다시 볼수 없을 것";
	_storyDialog[5]._script[3] = L"이다.";

	_storyDialog[6]._speaker = "Sherazade";
	_storyDialog[6]._dialogN = 3;
	_storyDialog[6]._dialogType = 1;
	_storyDialog[6]._script[0] = L"[셰라자드]";
	_storyDialog[6]._script[1] = L"살라딘, 저는 개의치 마세요.";
	_storyDialog[6]._script[2] = L"저는 이미 깨끗하지 못한 몸이에요.";

	_storyDialog[7]._speaker = "Saladin";
	_storyDialog[7]._dialogN = 2;
	_storyDialog[7]._dialogType = 2;
	_storyDialog[7]._script[0] = L"[살라딘]";
	_storyDialog[7]._script[1] = L"설마...";

	_storyDialog[8]._speaker = "Vermont";
	_storyDialog[8]._dialogN = 4;
	_storyDialog[8]._dialogType = 1;
	_storyDialog[8]._script[0] = L"[버몬트]";
	_storyDialog[8]._script[1] = L"하하하! 투르제국의 여술탄과 팬드래건 왕가의 결합.";
	_storyDialog[8]._script[2] = L"멋지지 않나?";
	_storyDialog[8]._script[3] = L"단, 투르의 영토는 지참금으로 가지고 와야지.";

	_storyDialog[9]._speaker = "Saladin";
	_storyDialog[9]._dialogN = 2;
	_storyDialog[9]._dialogType = 2;
	_storyDialog[9]._script[0] = L"[살라딘]";
	_storyDialog[9]._script[1] = L"왜 그런짓을 하는거지?";

	_storyDialog[10]._speaker = "Vermont";
	_storyDialog[10]._dialogN = 4;
	_storyDialog[10]._dialogType = 0;
	_storyDialog[10]._script[0] = L"[버몬트]";
	_storyDialog[10]._script[1] = L"복수다! 네놈따위는 상상도 하지 못할 증오에 찬 복수!";
	_storyDialog[10]._script[2] = L"자, 네놈과 떠들 시간따윈 없어. 어서 칼을 버리지 않으면 이 여자의";
	_storyDialog[10]._script[3] = L"목숨은 없다!";

	_storyDialog[11]._speaker = "Saladin";
	_storyDialog[11]._dialogN = 2;
	_storyDialog[11]._dialogType = 0;
	_storyDialog[11]._script[0] = L"[살라딘]";
	_storyDialog[11]._script[1] = L"좋다. 칼을 버리겠다.";

	_storyDialog[12]._speaker = "Sherazade";
	_storyDialog[12]._dialogN = 3;
	_storyDialog[12]._dialogType = 1;
	_storyDialog[12]._script[0] = L"[셰라자드]";
	_storyDialog[12]._script[1] = L"살라딘님, 안돼요!";
	_storyDialog[12]._script[2] = L"왜 자신에 대해 얘기 안하시는 거죠?";

	_storyDialog[13]._speaker = "Saladin";
	_storyDialog[13]._dialogN = 3;
	_storyDialog[13]._dialogType = 2;
	_storyDialog[13]._script[0] = L"[살라딘]";
	_storyDialog[13]._script[1] = L"셰라자드, 나는 이미 과거는 잊었다오.";
	_storyDialog[13]._script[2] = L"단지 한사람의 투르인으로 살아왔고 투르인으로 죽을것이오.";

	_storyDialog[14]._speaker = "Vermont";
	_storyDialog[14]._dialogN = 2;
	_storyDialog[14]._dialogType = 0;
	_storyDialog[14]._script[0] = L"[버몬트]";
	_storyDialog[14]._script[1] = L"어서, 녀석을 체포해라!";

	_storyDialog[15]._speaker = "Sherazade";
	_storyDialog[15]._dialogN = 3;
	_storyDialog[15]._dialogType = 0;
	_storyDialog[15]._script[0] = L"[셰라자드]";
	_storyDialog[15]._script[1] = L"살라딘님! 저는 언제나 당신의 짐만 되는군요.";
	_storyDialog[15]._script[2] = L"하지만, 이젠 저도 용기를 내겠어요...";

	_storyDialog[16]._speaker = "Vermont";
	_storyDialog[16]._dialogN = 2;
	_storyDialog[16]._dialogType = 0;
	_storyDialog[16]._script[0] = L"[버몬트]";
	_storyDialog[16]._script[1] = L"제길, 할수없군";

	_storyDialog[17]._speaker = "Vermont";
	_storyDialog[17]._dialogN = 2;
	_storyDialog[17]._dialogType = 0;
	_storyDialog[17]._script[0] = L"[버몬트]";
	_storyDialog[17]._script[1] = L"다, 끝내셨나?";

	_storyDialog[18]._speaker = "Saladin";
	_storyDialog[18]._dialogN = 2;
	_storyDialog[18]._dialogType = 0;
	_storyDialog[18]._script[0] = L"[살라딘]";
	_storyDialog[18]._script[1] = L"복수심에 붙잡혀 있는 불쌍한 인간이군.";

	_storyDialog[19]._speaker = "Vermont";
	_storyDialog[19]._dialogN = 3;
	_storyDialog[19]._dialogType = 0;
	_storyDialog[19]._script[0] = L"[버몬트]";
	_storyDialog[19]._script[1] = L"너 따위가 나에 대해 뭘 안단 거냐?";
	_storyDialog[19]._script[2] = L"뭐, 상관없지...자 각오해라!";

	_frame = 0;
	_typing = 0;
	_dialogRC[0] = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 150, WINSIZE_X - 160, 200);
	_dialogRC[1] = {150, WINSIZE_Y - 170, WINSIZE_X - 50, WINSIZE_Y - 20};
	_dialogRC[2] = {50, WINSIZE_Y - 330, WINSIZE_X - 150, WINSIZE_Y - 180};
	_startFadeIn = 0;
	_vermontSherazadeIndex = 0;
	_backGroundIndex = 0;
	_soundIndex = 0;
	_fadeRedStart = 0;
	_speakFinish = false;
	_fadeIn = false;
	_fadeWhite = false;
	_fadeWhiteFrame = 0;
	_speakStartFrame = 0;
	}
	else
	{
		_speakFinish = false;
		_fadeIn = true;
		_fadeOut = false;
		_frame = 0;
		_dialogData = DATAMANAGER->getDialogList(DATAMANAGER->getScenario());
		_storyDataList = DATAMANAGER->getStoryData(DATAMANAGER->getScenario());
		_dialogIndex = 0;
		_backGroundIndex = 1;
		//_backGroundIndex = 5;
		_stopDialogIndex = 0;
		_soundIndex = 1;
		_objectIndex = 1;
		_typing = 0;
		_fadeStartFrame = 0;
		_dialogRC[0] = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 150, WINSIZE_X - 160, 200);
		_dialogRC[1] = { 150, WINSIZE_Y - 170, WINSIZE_X - 50, WINSIZE_Y - 20 };
		_dialogRC[2] = { 50, WINSIZE_Y - 330, WINSIZE_X - 150, WINSIZE_Y - 180 };
	}
	return S_OK;
}

void StoryScene::release(void)
{
}

void StoryScene::update(void)
{
	if(DATAMANAGER->getScenario() == 75)
	{
		if (_backGroundIndex < 2)
		{
			if (!_fadeIn)
			{
				_frame++;
				if (_frame == 1)
				{
					SOUNDMANAGER->playSoundFMOD("Dialog0");
				}
				if (_frame == 100)
				{
					SOUNDMANAGER->playSoundFMOD("Dialog1");
				}
				if (_frame == 200)
				{
					_fadeIn = true;
					_frame = 0;
				}
			}
			else
			{
				if (_frame == 0)
				{
					SOUNDMANAGER->playSoundFMOD("Conspiracy2");
				}
				if (_frame == 300)
				{
					SOUNDMANAGER->playSoundFMOD("Dialog2");
				}
				_frame++;
				if (_frame % 5 == 0)
				{
					if (_typing != 999)
					{
						_typing++;
					}
				}
				if (_frame > 300)
				{
					char exSound[50];
					wsprintf(exSound, "Dialog%d", _dialogIndex + 2);
					if (SOUNDMANAGER->getCurrentPos(exSound) == 0)
					{
						_speakFinish = true;
					}
					else
					{
						_speakFinish = false;
					}
					if (_dialogIndex < 16)
					{
						if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
						{
							char sound[50];
							if (_speakFinish)
							{
								_speakFinish = false;
								if (_dialogIndex < 15)
								{
									wsprintf(sound, "Dialog%d", _dialogIndex + 3);
									SOUNDMANAGER->playSoundFMOD(sound);
									_typing = 0;
								}
								_dialogIndex++;
							}
							else
							{
								_speakFinish = true;
								char exSound[50];
								wsprintf(exSound, "Dialog%d", _dialogIndex + 2);
								SOUNDMANAGER->stopSoundFMOD(exSound);
								_typing = 999;
							}
						}
					}
				}
			}
			if (_dialogIndex == 6)
			{
				if (_frame % 5 == 0 && _vermontSherazadeIndex < 2)
				{
					_vermontSherazadeIndex++;
				}
			}
			else if (_dialogIndex == 12)
			{
				_vermontSherazadeIndex = 3;
				if (_frame % 5 == 0)
				{
					_saladinIndex++;
				}
			}
			else if (_dialogIndex == 16)
			{
				if (_frame % 5 == 0 && _vermontSherazadeIndex < 14)
				{
					_vermontSherazadeIndex++;
				}
			}
			if (_vermontSherazadeIndex == 8 && _frame % 5 == 1)
			{
				SOUNDMANAGER->playSoundFMOD("Dialog18");
			}
			if (_vermontSherazadeIndex == 14 && _fadeRedStart == 0)
			{
				_fadeRedStart = _frame;
				SOUNDMANAGER->stopSoundFMOD("Conspiracy2");
			}
			if ((_frame == _fadeRedStart + 50 && _fadeRedStart != 0) && _soundIndex == 0)
			{
				_backGroundIndex = 1;
				SOUNDMANAGER->playSoundFMOD(_soundList[_soundIndex]);
				_speakStartFrame = _frame;
				_soundIndex++;
			}
			if (_backGroundIndex == 1)
			{
				if (_frame > _speakStartFrame + 10)
				{
					if (SOUNDMANAGER->getCurrentPos(_soundList[_soundIndex - 1]) == 0 && _soundIndex < 4)
					{
						SOUNDMANAGER->playSoundFMOD(_soundList[_soundIndex]);
						_speakStartFrame = _frame;
						_soundIndex++;
						if (_soundIndex == 4)
						{
							_fadeRedStart = _frame;
							_backGroundIndex = 0;
						}
					}
				}
			}
			if (_frame < _fadeRedStart + 50 && _soundIndex == 4)
			{
				_typing = 0;
			}
			if (_frame == _fadeRedStart + 50 && _soundIndex == 4)
			{
				_typing = 0;
				SOUNDMANAGER->playSoundFMOD(_soundList[_soundIndex]);
			}
			if (_frame > _fadeRedStart + 50 && _soundIndex == 4)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					if (SOUNDMANAGER->getCurrentPos(_soundList[_soundIndex]) == 0)
					{
						_soundIndex++;
					}
					else
					{
						_typing = 999;
						SOUNDMANAGER->stopSoundFMOD(_soundList[_soundIndex]);
					}
				}
			}
			if (_soundIndex == 5)
			{
				if (_frame % 5 == 0)
				{
					_vermontSherazadeIndex++;
				}
			}
			if (_vermontSherazadeIndex > _vermontSherazade->getMaxFrameX())
			{
				if (250 - (_vermontSherazadeIndex - _vermontSherazade->getMaxFrameX()) * 15 < -IMAGEMANAGER->findImage("VermontMoveLeft")->getFrameWidth() * 1.4)
				{
					_vermontSherazadeIndex--;
					_frame--;
					_fadeWhite = true;
					_fadeWhiteFrame++;
					if (_fadeWhiteFrame > 100)
					{
						_frame = 0;
						_fadeWhiteFrame = 0;
						_backGroundIndex = 2;
					}
				}
			}
		}
		else if (_backGroundIndex < 4)
		{
			_frame++;
			if (_fadeWhite)
			{
				if (_frame > 100 && _soundIndex != 19)
				{
					_fadeWhite = false;
					SOUNDMANAGER->playSoundFMOD(_soundList[_soundIndex]);
					_speakStartFrame = _frame;
					_soundIndex++;
				}
			}
			else
			{
				if (SOUNDMANAGER->getCurrentPos(_soundList[_soundIndex - 1]) == 0 && _speakStartFrame + 10 < _frame)
				{
					if (_soundIndex == 19)
					{
						_fadeWhite = true;
						_fadeWhiteFrame = _frame;
					}
					if (_soundIndex < 19)
					{
						SOUNDMANAGER->playSoundFMOD(_soundList[_soundIndex]);
						_speakStartFrame = _frame;
						if (_soundIndex == 10)
						{
							SOUNDMANAGER->playSoundFMOD("SherazadeDead");
						}
						if (_soundIndex == 18)
						{
							_backGroundIndex = 3;
						}
						_soundIndex++;
					}
				}
			}
			if (_frame > _fadeWhiteFrame + 300 && _fadeWhiteFrame != 0)
			{
				_backGroundIndex = 4;
				_fadeWhiteFrame = 0;
				_frame = 0;
			}
		}
		else if (_backGroundIndex == 4)
		{
			if (SOUNDMANAGER->getCurrentPos("SherazadeDead") > SOUNDMANAGER->getSoundLength("SherazadeDead") + 3000)
			{
				_backGroundIndex = 5;
				_dialogIndex = 17;
			}
		}
		else
		{
			if (_frame == 0)
			{
				SOUNDMANAGER->playSoundFMOD("BeforeLastBattle");
			}
			_frame++;
			if (_fadeWhite)
			{
				if (_frame > 100 && _dialogIndex != 20)
				{
					_fadeWhite = false;
					SOUNDMANAGER->playSoundFMOD(_soundList[_soundIndex]);
					_speakStartFrame = _frame;
					_soundIndex++;
					_typing = 0;
				}
				if (_frame > _fadeWhiteFrame + 300 && _dialogIndex == 20)
				{
					SOUNDMANAGER->stopAllSoundFMOD();
					SCENEMANAGER->loadingScene();
					DATAMANAGER->setSceneIdx(DATAMANAGER->getSceneIdx() + 1);
				}
			}
			else
			{
				if (_frame % 5 == 0)
				{
					_typing++;
				}
				if (SOUNDMANAGER->getCurrentPos(_soundList[_soundIndex - 1]) == 0 && _speakStartFrame + 10 < _frame)
				{
					_speakFinish = true;
				}
				else
				{
					_speakFinish = false;
				}
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					if (_speakFinish)
					{
						_speakFinish = false;
						if (_dialogIndex == 19)
						{
							_fadeWhite = true;
							_fadeWhiteFrame = _frame;
						}
						else
						{
							SOUNDMANAGER->playSoundFMOD(_soundList[_soundIndex]);
							_soundIndex++;
							_typing = 0;
						}
						_dialogIndex++;
					}
					else
					{
						_speakFinish = true;
						SOUNDMANAGER->stopSoundFMOD(_soundList[_soundIndex - 1]);
						_typing = 999;
					}
				}
			}
		}
	}
	else
	{
		_frame++;
		switch(_backGroundIndex)
		{
			case 1:
				if (_frame == 100 && _dialogIndex == 0)
				{
					_fadeIn = false;
					_stopDialogIndex++;
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					SOUNDMANAGER->playSoundFMOD(_text);
				}
				if(_dialogIndex == 8 && !_fadeOut)
				{
 					_fadeOut = true;
					_fadeStartFrame = _frame;
				}
				if (_frame > _fadeStartFrame + 100 && _fadeOut)
				{
					_backGroundIndex++;
					_frame = 0;
				}
			break;
			case 2:
				if (_frame > 100)
				{
					_backGroundIndex++;
					_frame = 0;
					_fadeOut = false;
					_fadeIn = true;
				}
			break;
			case 3:
				if (_frame == 100 && _dialogIndex == 8)
				{
					_stopDialogIndex++;
					_fadeIn = false;
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					SOUNDMANAGER->playSoundFMOD(_text);
				}
				if (_dialogIndex == 26 && !_fadeOut)
				{
					_fadeOut = true;
					_fadeStartFrame = _frame;
				}
				if (_frame > _fadeStartFrame + 100 && _fadeOut)
				{
					_backGroundIndex++;
					_frame = 0;
				}
			break;
			case 4:
				if (_frame > 100)
				{
					_backGroundIndex++;
					_frame = 0;
					_fadeOut = false;
					_fadeIn = true;
				}
				break;
			case 5:
				if (_frame == 100 && _dialogIndex == 26)
				{
					_fadeIn = false;
					_stopDialogIndex++;
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					SOUNDMANAGER->playSoundFMOD(_text);
					SOUNDMANAGER->playSoundFMOD("Story69-BG");
				}
				if (_dialogIndex >= 29 && _dialogIndex <= 30)
				{
					if (_frame == 40)
					{
						SOUNDMANAGER->playSoundFMOD("BangBangBang");
					}
					if (_frame == 130)
					{
						_stopDialogIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
				}
				if (_dialogIndex == 31)
				{
					if (_frame == 40)
					{
						SOUNDMANAGER->playSoundFMOD("BangBangBang");
					}
					if (_frame == 270)
					{
						_stopDialogIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
				}
				if (_dialogIndex == 35)
				{
					if (_frame == 20)
					{
						_stopDialogIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
				}
				if (_dialogIndex == 38)
				{
					if (_frame == 110)
					{
						_stopDialogIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
				}
				if (_dialogIndex == 39)
				{
					if (_frame == 10)
					{
						_stopDialogIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
				}
				if (_dialogIndex == 40)
				{
					if (_frame == 90)
					{
						_stopDialogIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
					if (_frame == 50)
					{
						SOUNDMANAGER->playSoundFMOD("Flirting");
					}
				}
				if (_dialogIndex == 41)
				{
					if (_frame == 1)
					{
						SOUNDMANAGER->stopSoundFMOD("Story69-BG");
					}
					if (_frame == 40)
					{
						_stopDialogIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
				}
				if (_dialogIndex == 42)
				{
					if (_frame == 60)
					{
						SOUNDMANAGER->playSoundFMOD("BangBangBang");
					}
					if (_frame == 140)
					{
						_fadeOut = true;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
					if (_frame > 160)
					{
						_fadeOut = false;
						_fadeIn = true;
						_frame = 0;
						_backGroundIndex++;
					}
				}
				break;
			case 6:
				if (_frame > 20 && _fadeIn)
				{
					_fadeIn = false;
					_frame = 0;
				}
				if(!_fadeIn)
				{
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					if (SOUNDMANAGER->getCurrentPos(_text) == 0 && !_fadeOut)
					{
						_fadeOut = true;
						_frame = 0;
					}
					if (_frame > 10 && _fadeOut)
					{
						_fadeOut = false;
						_fadeIn = true;
						_frame = 0;
						_backGroundIndex++;
						_soundIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
					}
				}
			break;
			case 7:
				if (_frame == 20 && _fadeIn)
				{
					_fadeIn = false;
				}
				if(!_fadeIn)
				{
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					if (SOUNDMANAGER->getCurrentPos(_text) == 0 && _soundIndex == 43)
					{
						_soundIndex++;
						wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
						SOUNDMANAGER->playSoundFMOD(_text);
						_fadeOut = true;
						_fadeStartFrame = _frame;
					}
					if (_frame > _fadeStartFrame + 200 && _fadeOut)
					{
						_backGroundIndex++;
						_fadeOut = false;
						_frame = 0;
					}
				}
			break;
			case 8:
				wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
				if (SOUNDMANAGER->getCurrentPos(_text) == 0)
				{
					_fadeIn = true;
					_backGroundIndex++;
					_frame = 0;
				}
			break;
			case 9:
				if (_frame == 20)
				{
					_fadeIn = false;
					_soundIndex++;
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					SOUNDMANAGER->playSoundFMOD(_text);
				}
				if(_frame > 30)
				{
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					if (SOUNDMANAGER->getCurrentPos(_text) == 0 && _soundIndex == 45)
					{
						if(!_fadeOut)
						{
							_fadeOut = true;
							_fadeStartFrame = _frame;
						}
					}
				}
				if (_frame > 500)
				{
					SCENEMANAGER->loadingScene();
				}
			break;
		}
		if (_dialogData->_stopDialog[_stopDialogIndex] != _dialogIndex)
		{
			if (_frame % 5 == 0)
			{
				_typing++;
			}
			wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
			if (SOUNDMANAGER->getCurrentPos(_text) == 0)
			{
				_speakFinish = true;
			}
			else
			{
				_speakFinish = false;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				if (_speakFinish)
				{
					_speakFinish = false;
					if (_dialogIndex != 15)
					{
						_soundIndex++;
						if (_dialogIndex != _dialogData->_stopDialog[_stopDialogIndex] - 1)
						{
							wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
							SOUNDMANAGER->playSoundFMOD(_text);
						}
						else
						{
							_frame = 0;
						}
					}
					_typing = 0;
					_dialogIndex++;
				}
				else
				{
					_speakFinish = true;
					wsprintf(_text, "%d-%d", DATAMANAGER->getScenario(), _soundIndex);
					SOUNDMANAGER->stopSoundFMOD(_text);
					_typing = 999;
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SOUNDMANAGER->stopAllSoundFMOD();
		SCENEMANAGER->loadingScene();
		SetTextAlign(getMemDC(), TA_NOUPDATECP);
	}
}

void StoryScene::render(void)
{
	if(DATAMANAGER->getScenario() == 75)
	{
		if(_backGroundIndex < 2)
		{
			if (!_fadeIn)
			{
				IMAGEMANAGER->findImage("Black")->render(getMemDC());
			}
			else
			{
				_storyBG->frameRender(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, _backGroundIndex, 0);
				if(_backGroundIndex == 0)
				{
					if(_soundIndex < 4)
					{
						_vermontSherazade->frameRender(getMemDC(), 170, 340, _vermontSherazade->getFrameWidth() * 1.4, _vermontSherazade->getFrameHeight() * 1.4, _vermontSherazadeIndex, 0);
						if (_saladinIndex != 0)
						{
							IMAGEMANAGER->findImage("AbandonedSwords")->render(getMemDC(), 250, 500);
						}
						_saladin->frameRender(getMemDC(), 250, 500, _saladin->getFrameWidth() * 1.4, _saladin->getFrameHeight() * 1.4, _saladinIndex, 0);
						IMAGEMANAGER->findImage("Soldier4")->render(getMemDC(), WINSIZE_X / 2 + 200, 420, IMAGEMANAGER->findImage("Soldier4")->getWidth() * 1.4, IMAGEMANAGER->findImage("Soldier4")->getHeight() * 1.4,
						0, 0, IMAGEMANAGER->findImage("Soldier4")->getWidth(), IMAGEMANAGER->findImage("Soldier4")->getHeight());
						IMAGEMANAGER->findImage("Soldier1")->render(getMemDC(), WINSIZE_X / 2 + 200, 500, IMAGEMANAGER->findImage("Soldier1")->getWidth() * 1.4, IMAGEMANAGER->findImage("Soldier1")->getHeight() * 1.4,
							0, 0, IMAGEMANAGER->findImage("Soldier1")->getWidth(), IMAGEMANAGER->findImage("Soldier1")->getHeight());
						IMAGEMANAGER->findImage("Soldier2")->render(getMemDC(), 130, 500, IMAGEMANAGER->findImage("Soldier2")->getWidth() * 1.4, IMAGEMANAGER->findImage("Soldier2")->getHeight() * 1.4,
							0, 0, IMAGEMANAGER->findImage("Soldier2")->getWidth(), IMAGEMANAGER->findImage("Soldier2")->getHeight());
						IMAGEMANAGER->findImage("Soldier3")->render(getMemDC(), 150, 550, IMAGEMANAGER->findImage("Soldier3")->getWidth() * 1.4, IMAGEMANAGER->findImage("Soldier3")->getHeight() * 1.4,
							0, 0, IMAGEMANAGER->findImage("Soldier3")->getWidth(), IMAGEMANAGER->findImage("Soldier3")->getHeight());
						SCENEMANAGER->fadeInBlack(0, _frame, 300);
						if (_frame > 300 && _dialogIndex <= 15)
						{
							dialog(_storyDialog[_dialogIndex]._speaker, _storyDialog[_dialogIndex]._script, _typing, _storyDialog[_dialogIndex]._dialogN, _storyDialog[_dialogIndex]._dialogType);
						}
					}
					else
					{
						_vermontSherazade->frameRender(getMemDC(), 170, 340, _vermontSherazade->getFrameWidth() * 1.4, _vermontSherazade->getFrameHeight() * 1.4, _vermontSherazadeIndex, 0);
						if(_vermontSherazadeIndex < _vermontSherazade->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("SaladinIdleRight")->frameRender(getMemDC(), WINSIZE_X / 2 + 150, 420, 
								IMAGEMANAGER->findImage("SaladinIdleRight")->getFrameWidth() * 1.4, IMAGEMANAGER->findImage("SaladinIdleRight")->getFrameHeight() * 1.4, (_frame / 5) % 4, 0);
						}
						else
						{
							IMAGEMANAGER->findImage("VermontMoveLeft")->frameRender(getMemDC(), 250 - (_vermontSherazadeIndex - _vermontSherazade->getMaxFrameX()) * 15, 
							340 + (_vermontSherazadeIndex - _vermontSherazade->getMaxFrameX()) * 10 > 420 ? 420 : 340 + (_vermontSherazadeIndex - _vermontSherazade->getMaxFrameX()) * 10,
							IMAGEMANAGER->findImage("VermontMoveLeft")->getFrameWidth()*1.4, IMAGEMANAGER->findImage("VermontMoveLeft")->getFrameHeight() * 1.4, (_frame / 5) % 6, 0);
							IMAGEMANAGER->findImage("SaladinMove")->frameRender(getMemDC(), WINSIZE_X / 2 + 150 - (_vermontSherazadeIndex - _vermontSherazade->getMaxFrameX()) * 15, 420,
								IMAGEMANAGER->findImage("SaladinMove")->getFrameWidth() * 1.4, IMAGEMANAGER->findImage("SaladinMove")->getFrameHeight() * 1.4, (_frame / 5) % 6, 2);
							SCENEMANAGER->fadeOutWhite(0, _fadeWhiteFrame, 100);
						}
						if(_soundIndex == 4)
						{
							dialog(_storyDialog[_dialogIndex]._speaker, _storyDialog[_dialogIndex]._script, _typing, _storyDialog[_dialogIndex]._dialogN, _storyDialog[_dialogIndex]._dialogType);
						}
					}
				}
				if (_fadeRedStart != 0)
				{
					if (_soundIndex == 4)
					{
						_redImage->alphaRender(getMemDC(), _frame > _fadeRedStart + 50 ? 0 : 255.0f - 255.0f / (float)(50) * (float)(_frame - _fadeRedStart));
					}
					else if(_soundIndex < 4)
					{
						_redImage->alphaRender(getMemDC(), _frame > _fadeRedStart + 50 ? 255 : 255.0f / (float)(50) * (float)(_frame - _fadeRedStart));
					}
				}
			}
		}
		else if (_backGroundIndex < 4)
		{
			_storyBG->frameRender(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, _backGroundIndex, 0);
			if (_soundIndex >= 11)
			{
				for (int i = 0; i < 4; i++)
				{
					IMAGEMANAGER->findImage("FireFly")->alphaFrameRender(getMemDC(), (float)WINSIZE_X / 4.f * i, WINSIZE_Y - IMAGEMANAGER->findImage("FireFly")->getFrameHeight() + 50, 
					(float)WINSIZE_X / 4.f, IMAGEMANAGER->findImage("FireFly")->getFrameHeight(), (_frame / 5) % 31, 0, 50);
				}
			}
			if (_fadeWhite)
			{
				if (_soundIndex == 19)
				{
					SCENEMANAGER->fadeOutWhite(_fadeWhiteFrame, _frame, _fadeWhiteFrame + 300);
				}
				else
				{
					SCENEMANAGER->fadeInWhite(0, _frame, 100);
				}
			}
		}
		else if(_backGroundIndex == 4)
		{
			_storyBG->frameRender(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, _backGroundIndex, 0);
		}
		else
		{
			_storyBG->frameRender(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, _backGroundIndex, 0);
			if(_fadeWhite)
			{
				if(_dialogIndex != 20)
				{
					SCENEMANAGER->fadeInWhite(0, _frame, 100);
				}
				else
				{
					SCENEMANAGER->fadeOutBlack(_fadeWhiteFrame, _frame, _fadeWhiteFrame + 300);
				}
			}
			else
			{
				dialog(_storyDialog[_dialogIndex]._speaker, _storyDialog[_dialogIndex]._script, _typing, _storyDialog[_dialogIndex]._dialogN, _storyDialog[_dialogIndex]._dialogType);
			}
		}
	}
	else
	{
		wsprintf(_text, "StoryBG%d-%d", DATAMANAGER->getScenario(), _backGroundIndex);
		IMAGEMANAGER->findImage(_text)->render(getMemDC());
		if (_backGroundIndex == 5)
		{
			if(_dialogIndex < 35)
			{
				IMAGEMANAGER->findImage("Story69-Soldier")->frameRender(getMemDC(), 690, 140, 0, 0);
			}
			else if (_dialogIndex == 35)
			{
				if(_frame <= 20)
				IMAGEMANAGER->findImage("Story69-Soldier")->frameRender(getMemDC(), (690.f * (float)(20 - _frame) + 630.f * (float)_frame) / 20.f, 140, 1, 0);
			}
			else
			{
				IMAGEMANAGER->findImage("Story69-Soldier")->frameRender(getMemDC(), 630, 140, 0, 0);
			}
		}
		for(auto it  = _storyDataList[_backGroundIndex - 1]->_objectList.begin(); it != _storyDataList[_backGroundIndex - 1]->_objectList.end(); ++it)
		{
			wsprintf(_text, "StoryObject%d-%d", DATAMANAGER->getScenario(), (*it)._objectType);
			IMAGEMANAGER->findImage(_text)->render(getMemDC(), (*it)._x, (*it)._y);
		}
		switch (_backGroundIndex)
		{
			case 3:
				if (_dialogIndex < 18)
				{
					IMAGEMANAGER->findImage("Story69-Soldier")->frameRender(getMemDC(), 350, 330, 1, 0);
				}
				else
				{
					IMAGEMANAGER->findImage("Story69-Soldier")->frameRender(getMemDC(), 350, 330, 2, 0);
				}
				if (_dialogIndex < 9)
				{
					IMAGEMANAGER->findImage("StoryObject69-6")->render(getMemDC(), 570, 380);
				}
				else if (_dialogIndex < 20)
				{
					IMAGEMANAGER->findImage("StoryObject69-12")->render(getMemDC(), 560, 380);
				}
				else if (_dialogIndex < 22)
				{
					IMAGEMANAGER->findImage("StoryObject69-6")->render(getMemDC(), 570, 380);
				}
				else
			{
				IMAGEMANAGER->findImage("StoryObject69-12")->render(getMemDC(), 560, 380);
			}
			break;
			case 5:
				for (int i = 0; i < 3; i++)
			{
				wsprintf(_text, "Story69-Die%d", i + 1);
				if (_dialogIndex < 29 + i)
				{
					IMAGEMANAGER->findImage(_text)->frameRender(getMemDC(), 215 + 140 * i, 170, 0, 0);
				}
				else if (_dialogIndex == 29 + i)
				{
					IMAGEMANAGER->findImage(_text)->frameRender(getMemDC(), 215 + 140 * i, 170, _frame / 10 - 3, 0);
				}
				else
				{
					IMAGEMANAGER->findImage(_text)->frameRender(getMemDC(), 215 + 140 * i, 170, 7, 0);
				}
			}
				// 얀
				if (_dialogIndex < 29)
				{
					IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, 0, 0);
				}
				else if (_dialogIndex <= 31)
				{
					if(_dialogIndex < 31)
					{
						IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, (_frame / 10 + 1) > 3 ? 3 : (_frame / 10 + 1), 0);
					}
					else
					{
						if (_frame < 130)
						{
							IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, (_frame / 10 + 1) > 3 ? 3 : (_frame / 10 + 1), 0);
						}
						else
						{
							IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, 0, 0);
						}
					}
				}
				else if(_dialogIndex < 35)
				{
					IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, 0, 0);
				}
				else if (_dialogIndex == 35)
				{
					if (_frame <= 20)
					{
						IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, 0, 0);
					}
					else
					{
						IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, 4, 0);
					}
				}
				else if(_dialogIndex < 40)
				{
					IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, 4, 0);
				}
				else if (_dialogIndex == 40)
				{
					IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, _frame / 30 + 5 > 7 ? 7 : _frame / 30 + 5, 0);
				}
				else if (_dialogIndex < 42)
				{
					IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), 615, 180, 7, 0);
				}
				else if (_dialogIndex == 42)
				{
					if(_frame <= 50)
					{
						IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), (float)(615 * (50 - _frame) + (180 * _frame)) / 50.f, 
							(float)(180 * (50 - _frame) + 270 * _frame)/ 50.f, (_frame / 10) % 5 + 8, 0);
					}
					if (_frame > 50)
					{
						IMAGEMANAGER->findImage("Story69-Yan")->frameRender(getMemDC(), (float)(180 * (90 - (_frame - 50)) + (160 * (_frame - 50))) / 90.f,
							(float)(270 * (90 - (_frame - 50)) + 280 * (_frame - 50)) / 90.f, ((_frame - 50) / 30) + 13, 0);
					}
				}
				// 오스만
				if (_dialogIndex < 29)
				{
					IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 150, 250, 0, 0);
				}
				else if (_dialogIndex <= 31)
				{
					if(_dialogIndex < 31)
					{
						IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 150, 250, _frame / 10 > 4 ? 0 : _frame / 10, 0);
					}
					else
					{
						if (_frame < 130)
						{
							IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 150, 250, _frame / 10 > 4 ? 0 : _frame / 10, 0);
						}
						else if(_frame <= 270)
						{
							IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 
								(150.f * (140.f - (float)(_frame - 130)) + 550.0f * (float)(_frame - 130)) / 140.f, 
								(250.f * (140.f - (float)(_frame - 130)) + 180.f * (float)(_frame - 130)) / 140.f, (_frame / 10) % 6 + 5, 0);
						}
						else
						{
							IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 550, 180, 11, 0);
						}
					}
				}
				else if (_dialogIndex < 39)
				{
					IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 550, 180, 11, 0);
				}
				else if (_dialogIndex == 39)
				{
					if(_frame <= 10)
					{
						IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(),
							(550.f * (10.f - (float)(_frame)) + 590.0f * (float)(_frame)) / 10.f, 180, (_frame / 10) % 6 + 5, 0);
					}
					else
					{
						IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 590, 180, 11, 0);
					}
				}
				else if (_dialogIndex == 40)
				{
					IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), _frame / 30 > 0 ? 570 : 590, 180, _frame / 30 + 11 > 12 ? 11 : _frame / 30 + 11, 0);
				}
				else
				{
					IMAGEMANAGER->findImage("Story69-Osman")->frameRender(getMemDC(), 590, 180, _frame / 10 + 1 > 4 ? 4 : _frame / 10 + 1, 0);
				}
				// 살라딘
				if (_dialogIndex < 29)
			{
				IMAGEMANAGER->findImage("Story69-Saladin")->frameRender(getMemDC(), 150, 300, 0, 0);
			}
				else if (_dialogIndex == 29)
			{
				IMAGEMANAGER->findImage("Story69-Saladin")->frameRender(getMemDC(), 150, 300, _frame / 10 - 10, 0);
			}
				else
			{
				IMAGEMANAGER->findImage("Story69-Saladin")->frameRender(getMemDC(), 150, 300, 2, 0);
			}
				// 총 쏘는 군인들
				for (int i = 0; i < 4; i++)
				{
					if (_dialogIndex < 29 + i)
					{
						IMAGEMANAGER->findImage("Story69-FireUp")->frameRender(getMemDC(), 220 + 140 * i, 350, 0, 0);
					}
					else if (_dialogIndex == 29 + i)
					{
						if (_frame / 10 > 3 && (_frame - 40) / 4 <= IMAGEMANAGER->findImage("GunFireUp")->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("GunFireUp")->alphaFrameRender(getMemDC(), 200 + 140 * i, 300, (_frame - 40) / 4, 0, 200);
						}
						if (_frame / 10 > 6 && (_frame - 70) / 4 <= IMAGEMANAGER->findImage("GunFireUp")->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("GunFireUp")->alphaFrameRender(getMemDC(), 200 + 140 * i, 300, (_frame - 70) / 4, 0, 200);
						}
						if (_frame / 10 > 9 && (_frame - 90) / 4 <= IMAGEMANAGER->findImage("GunFireUp")->getMaxFrameX())
						{
							IMAGEMANAGER->findImage("GunFireUp")->alphaFrameRender(getMemDC(), 200 + 140 * i, 300, (_frame - 90) / 4, 0, 200);
						}
						IMAGEMANAGER->findImage("Story69-FireUp")->frameRender(getMemDC(), 220 + 140 * i, 350, _frame / 10, 0);
					}
					else if (_dialogIndex < 38)
					{
						IMAGEMANAGER->findImage("Story69-FireUp")->frameRender(getMemDC(), 220 + 140 * i, 350, 0, 0);
					}
					if (_dialogIndex == 38)
					{
						if(_frame <=  100)
						{
							IMAGEMANAGER->findImage("Story69-Soldier2")->frameRender(getMemDC(), 
								(float)((195 + 140 * i) * (100 - _frame) + (600 + 5 * i) * _frame) / 100.f, 
								(float)(360 * (100 - _frame) + (240 + 40 * i) * _frame) / 100.f, (_frame / 10) % 6, 0);

						}
						else
						{
							IMAGEMANAGER->findImage("Story69-Soldier2")->frameRender(getMemDC(), 600 + 5 * i, 240 + 40 * i, 6, 0);
						}
					}
					else if (_dialogIndex > 38 && _dialogIndex < 42)
					{
						IMAGEMANAGER->findImage("Story69-Soldier2")->frameRender(getMemDC(), 600 + 5 * i, 240 + 40 * i, 6, 0);
					}
					else if (_dialogIndex == 42)
					{
						if (_frame > 60)
						{
							IMAGEMANAGER->findImage("GunFireSide")->alphaFrameRender(getMemDC(), 540 + 5 * i, 210 + 40 * i, (_frame - 60) / 4, 0, 200);
						}
						if (_frame > 90)
						{
							IMAGEMANAGER->findImage("GunFireSide")->alphaFrameRender(getMemDC(), 540 + 5 * i, 210 + 40 * i, (_frame - 90) / 4, 0, 200);

						}
						if (_frame > 120)
						{
							IMAGEMANAGER->findImage("GunFireSide")->alphaFrameRender(getMemDC(), 540 + 5 * i, 210 + 40 * i, (_frame - 120) / 4, 0, 200);
						}
						IMAGEMANAGER->findImage("Story69-Soldier2")->frameRender(getMemDC(), 600 + 5 * i, 240 + 40 * i, 
							_frame / 10 + 7 > 12 ? _frame / 10 % 3 + 10 : _frame / 10 + 7, 0);
					}
				}
			break;
		}
		if (_fadeIn)
		{
			if (_backGroundIndex == 6 || _backGroundIndex == 7)
			{
				SCENEMANAGER->fadeInImage(0, _frame, 20, "Red");
			}
			else if (_backGroundIndex == 9)
			{
				SCENEMANAGER->fadeInImage(0, _frame, 20, "Red");
			}
			else
			{
				SCENEMANAGER->fadeInBlack(0, _frame, 100);
			}
		}
		if (_fadeOut)
		{
			if (_backGroundIndex == 5 || _backGroundIndex == 6)
			{
				SCENEMANAGER->fadeOutImage(140, _frame, 160, "Red");
			}
			else if (_backGroundIndex == 7)
			{
				SCENEMANAGER->fadeOutImage(_fadeStartFrame, _frame, _fadeStartFrame + 200, "Red");
			}
			else if (_backGroundIndex == 9)
			{
				SCENEMANAGER->fadeOutBlack(_fadeStartFrame, _frame, _fadeStartFrame + 20);
			}
			else
			{
				SCENEMANAGER->fadeOutBlack(_fadeStartFrame, _frame, _fadeStartFrame + 100);
			}
		}
		if(_dialogData->_stopDialog[_stopDialogIndex] != _dialogIndex)
		{
			dialog(_dialogData->_dialogList[_dialogIndex]._speaker, _dialogData->_dialogList[_dialogIndex]._script, _typing, _dialogData->_dialogList[_dialogIndex]._dialogN, _dialogData->_dialogList[_dialogIndex]._dialogType);
		}
	}
}

void StoryScene::dialog(string charName, LPCWSTR* printStringArr, int length, int arrSize, int dialogType)
{
	if(DATAMANAGER->getScenario() == 75)
	{
		if (_dialogIndex > 0)
		{
			if (dialogType && _storyDialog[_dialogIndex - 1]._dialogType)
			{

				wsprintf(_text, "Dialog%s", _storyDialog[_dialogIndex - 1]._speaker.c_str());
				_speakerImg = IMAGEMANAGER->findImage(_text);
				if (_storyDialog[_dialogIndex - 1]._dialogType == 1)
				{
					_speakerImg->render(getMemDC(), WINSIZE_X - 380, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
						_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
						0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				}
				else if (_storyDialog[_dialogIndex - 1]._dialogType == 2)
				{
					_speakerImg->render(getMemDC(), -130, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
						_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
						0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				}
			}
		}
		wsprintf(_text, "Dialog%s", charName.c_str());
		_speakerImg = IMAGEMANAGER->findImage(_text);
		if(_speakerImg != nullptr)
		{
			switch (dialogType)
			{
			case 0:
				_speakerImg->render(getMemDC(), (WINSIZE_X - _speakerImg->getWidth() * 1.5) / 2, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				break;
			case 1:
				_speakerImg->render(getMemDC(), WINSIZE_X - 380, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				break;
			case 2:
				_speakerImg->render(getMemDC(), -130, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				break;
			}
		}
		if (_dialogIndex > 0)
		{
			if (dialogType && _storyDialog[_dialogIndex - 1]._dialogType)
			{

				_textBoxImg->alphaRender(getMemDC(), _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].left, _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].top,
					_dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].right - _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].left, _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].bottom - _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].top,
					0, 0, _textBoxImg->getWidth(), _textBoxImg->getHeight(), 127);
				FONTMANAGER->textOut(getMemDC(), _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].left + 20, _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].top + 20, "가을체", 25, 50,
					_storyDialog[_dialogIndex - 1]._script, _storyDialog[_dialogIndex - 1]._dialogN, 999, RGB(255, 255, 255));
			}
		}
		_textBoxImg->alphaRender(getMemDC(), _dialogRC[dialogType].left, _dialogRC[dialogType].top,
			_dialogRC[dialogType].right - _dialogRC[dialogType].left, _dialogRC[dialogType].bottom - _dialogRC[dialogType].top,
			0, 0, _textBoxImg->getWidth(), _textBoxImg->getHeight(), 127);
		FONTMANAGER->textOut(getMemDC(), _dialogRC[dialogType].left + 20, _dialogRC[dialogType].top + 20, "가을체", 25, 50, printStringArr, arrSize, length, RGB(255, 255, 255));
	}
	else
	{
		if (_dialogIndex > 0)
		{
			if (dialogType && _dialogData->_dialogList[_dialogIndex - 1]._dialogType)
			{
				wsprintf(_text, "Dialog%s", _dialogData->_dialogList[_dialogIndex - 1]._speaker.c_str());
				_speakerImg = IMAGEMANAGER->findImage(_text);
				if (_dialogData->_dialogList[_dialogIndex - 1]._dialogType == 1)
				{
					_speakerImg->render(getMemDC(), WINSIZE_X - _speakerImg->getWidth() * 1.2, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
						_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
						0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				}
				else if (_dialogData->_dialogList[_dialogIndex - 1]._dialogType == 2)
				{
					_speakerImg->render(getMemDC(), - _speakerImg->getWidth() * 0.4, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				}
			}
		}
		wsprintf(_text, "Dialog%s", charName.c_str());
		_speakerImg = IMAGEMANAGER->findImage(_text);
		if(_speakerImg != nullptr)
		{
			switch (dialogType)
			{
				case 0:
					_speakerImg->render(getMemDC(), (WINSIZE_X - _speakerImg->getWidth() * 1.5) / 2, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				break;
				case 1:
					_speakerImg->render(getMemDC(), WINSIZE_X - _speakerImg->getWidth() * 1.2, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				break;
				case 2:
					_speakerImg->render(getMemDC(), - _speakerImg->getWidth() * 0.4, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
				break;
			}
		}
		if (_dialogIndex > 0)
		{
			if (dialogType && _dialogData->_dialogList[_dialogIndex - 1]._dialogType)
			{
				DIALOGMANAGER->makeTextBox(getMemDC(), _dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].left, _dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].top,
					_dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].right - _dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].left,
					_dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].bottom - _dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].top, 127);
				/*_textBoxImg->alphaRender(getMemDC(), _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].left, _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].top,
				_dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].right - _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].left, _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].bottom - _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].top,
				0, 0, _textBoxImg->getWidth(), _textBoxImg->getHeight(), 127);*/
				FONTMANAGER->textOut(getMemDC(), _dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].left + 20, _dialogRC[_dialogData->_dialogList[_dialogIndex - 1]._dialogType].top + 20, "가을체", 25, 50,
					_dialogData->_dialogList[_dialogIndex - 1]._script, _dialogData->_dialogList[_dialogIndex - 1]._dialogN, 999, RGB(255, 255, 255));
			}
		}
		DIALOGMANAGER->makeTextBox(getMemDC(), _dialogRC[dialogType].left, _dialogRC[dialogType].top,
			_dialogRC[dialogType].right - _dialogRC[dialogType].left, _dialogRC[dialogType].bottom - _dialogRC[dialogType].top, 127);
		/*_textBoxImg->alphaRender(getMemDC(), _dialogRC[dialogType].left, _dialogRC[dialogType].top,
		_dialogRC[dialogType].right - _dialogRC[dialogType].left, _dialogRC[dialogType].bottom - _dialogRC[dialogType].top,
		0, 0, _textBoxImg->getWidth(), _textBoxImg->getHeight(), 127);*/
		FONTMANAGER->textOut(getMemDC(), _dialogRC[dialogType].left + 20, _dialogRC[dialogType].top + 20, "가을체", 25, 50, printStringArr, arrSize, length, RGB(255, 255, 255));
	}
}
