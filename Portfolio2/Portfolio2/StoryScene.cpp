#include "Stdafx.h"
#include "StoryScene.h"

HRESULT StoryScene::init(void)
{
	_storyBG = IMAGEMANAGER->findImage("StoryBG");
	_textBoxImg = IMAGEMANAGER->findImage("TextBox");
	_vermontSherazade = IMAGEMANAGER->findImage("VermontSherazade");
	_redImage = IMAGEMANAGER->findImage("Red");
	_saladin = IMAGEMANAGER->findImage("SaladinStory");
	for (int i = 0; i < 50; i++)
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
	_storyDialog[12]._script[1] = L"살라딘님, 안되요!";
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

	_frame = 0;
	_typing = 10;
	_dialogRC[0] = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 150, WINSIZE_X - 160, 200);
	_dialogRC[1] = {150, WINSIZE_Y - 170, WINSIZE_X - 50, WINSIZE_Y - 20};
	_dialogRC[2] = {50, WINSIZE_Y - 330, WINSIZE_X - 150, WINSIZE_Y - 180};
	_startFadeIn = 0;
	_vermontSherazadeIndex = 0;
	_fadeOutRedStart = 0;
	_speakFinish = false;
	_fadeIn = false;
	return S_OK;
}

void StoryScene::release(void)
{
}

void StoryScene::update(void)
{
	if(!_fadeIn)
	{
		_frame++;
		if(_frame == 1)
		{
			SOUNDMANAGER->playSoundFMOD("Dialog0");
		}
		if(_frame == 100)
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
		if (_frame == 300)
		{
			SOUNDMANAGER->playSoundFMOD("Dialog2");
		}
		_frame++;
		if (_frame % 5 == 0)
		{
			_typing++;
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
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _dialogIndex < 16)
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
					cout << exSound << endl;
					SOUNDMANAGER->stopSoundFMOD(exSound);
					_typing = 999;
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
		cout << "test" << endl;
		SOUNDMANAGER->playSoundFMOD("Dialog18");
	}
	if (_vermontSherazadeIndex == 14 && _fadeOutRedStart == 0)
	{
		_fadeOutRedStart = _frame;
	}
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		SCENEMANAGER->changeScene("BossBattle");
	}
}

void StoryScene::render(void)
{
	if (!_fadeIn)
	{
		IMAGEMANAGER->findImage("Black")->render(getMemDC());
	}
	else
	{
		_storyBG->render(getMemDC());
		_vermontSherazade->frameRender(getMemDC(), 170, 340, _vermontSherazade->getFrameWidth() * 1.4, _vermontSherazade->getFrameHeight() * 1.4, _vermontSherazadeIndex, 0);
		if (_saladinIndex != 0)
		{
			IMAGEMANAGER->findImage("AbandonedSwords")->render(getMemDC(), 250, 500);
		}
		_saladin->frameRender(getMemDC(), 250, 500, _saladin->getFrameWidth() * 1.4, _saladin->getFrameHeight() * 1.4, _saladinIndex, 0);
		SCENEMANAGER->fadeInBlack(0, _frame, 300);
		if (_frame > 300 && _dialogIndex <= 15)
		{
			dialog(_storyDialog[_dialogIndex]._speaker, _storyDialog[_dialogIndex]._script, _typing, _storyDialog[_dialogIndex]._dialogN, _storyDialog[_dialogIndex]._dialogType);
		}
		if (_fadeOutRedStart != 0)
		{
			_redImage->alphaRender(getMemDC(), _frame > _fadeOutRedStart + 50 ? 255 : 255.0f / (float)(50) * (float)(_frame - _fadeOutRedStart));
			if (_frame > _fadeOutRedStart + 50)
			{
				_redImage->render(getMemDC());
			}
		}
	}
}

void StoryScene::dialog(string charName, LPCWSTR* printStringArr, int length, int arrSize, int dialogType)
{
	if (_dialogIndex > 0)
	{
		if (dialogType && _storyDialog[_dialogIndex - 1]._dialogType)
		{
			
			_speakerImg = IMAGEMANAGER->findImage(_storyDialog[_dialogIndex - 1]._speaker);
			if (_storyDialog[_dialogIndex - 1]._dialogType == 1)
			{
				_speakerImg->render(getMemDC(), WINSIZE_X - 380, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
			}
			else if(_storyDialog[_dialogIndex - 1]._dialogType == 2)
			{
				_speakerImg->render(getMemDC(), -130, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
					_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
					0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
			}
		}
	}
	_speakerImg = IMAGEMANAGER->findImage(charName);
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
