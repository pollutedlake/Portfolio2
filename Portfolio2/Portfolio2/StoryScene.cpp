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
	_storyDialog[0]._script[0] = L"[����Ʈ]";
	_storyDialog[0]._script[1] = L"��ٸ��� �־���.";

	_storyDialog[1]._speaker = "Saladin";
	_storyDialog[1]._dialogN = 2;
	_storyDialog[1]._dialogType = 0;
	_storyDialog[1]._script[0] = L"[����]";
	_storyDialog[1]._script[1] = L"...";

	_storyDialog[2]._speaker = "Vermont";
	_storyDialog[2]._dialogN = 2;
	_storyDialog[2]._dialogType = 0;
	_storyDialog[2]._script[0] = L"[����Ʈ]";
	_storyDialog[2]._script[1] = L"�������� ������ ���� �������� �̹��� �����?";

	_storyDialog[3]._speaker = "Sherazade";
	_storyDialog[3]._dialogN = 2;
	_storyDialog[3]._dialogType = 0;
	_storyDialog[3]._script[0] = L"[�ζ��ڵ�]";
	_storyDialog[3]._script[1] = L"����...";

	_storyDialog[4]._speaker = "Saladin";
	_storyDialog[4]._dialogN = 2;
	_storyDialog[4]._dialogType = 0;
	_storyDialog[4]._script[0] = L"[����]";
	_storyDialog[4]._script[1] = L"�ζ��ڵ�, �������ÿ�. �� �������״�...";

	_storyDialog[5]._speaker = "Vermont";
	_storyDialog[5]._dialogN = 4;
	_storyDialog[5]._dialogType = 0;
	_storyDialog[5]._script[0] = L"[����Ʈ]";
	_storyDialog[5]._script[1] = L"�� ! �׳��� �̾߱�� �����. ��� �ΰ��� �׳༮���� �ڻ��� ������.";
	_storyDialog[5]._script[2] = L"��, � �� Į�� ������ ������, �� ���ڸ� �� �� �ٽ� ���� ���� ��";
	_storyDialog[5]._script[3] = L"�̴�.";

	_storyDialog[6]._speaker = "Sherazade";
	_storyDialog[6]._dialogN = 3;
	_storyDialog[6]._dialogType = 1;
	_storyDialog[6]._script[0] = L"[�ζ��ڵ�]";
	_storyDialog[6]._script[1] = L"����, ���� ����ġ ������.";
	_storyDialog[6]._script[2] = L"���� �̹� �������� ���� ���̿���.";

	_storyDialog[7]._speaker = "Saladin";
	_storyDialog[7]._dialogN = 2;
	_storyDialog[7]._dialogType = 2;
	_storyDialog[7]._script[0] = L"[����]";
	_storyDialog[7]._script[1] = L"����...";

	_storyDialog[8]._speaker = "Vermont";
	_storyDialog[8]._dialogN = 4;
	_storyDialog[8]._dialogType = 1;
	_storyDialog[8]._script[0] = L"[����Ʈ]";
	_storyDialog[8]._script[1] = L"������! ���������� ����ź�� �ҵ巡�� �հ��� ����.";
	_storyDialog[8]._script[2] = L"������ �ʳ�?";
	_storyDialog[8]._script[3] = L"��, ������ ����� ���������� ������ �;���.";

	_storyDialog[9]._speaker = "Saladin";
	_storyDialog[9]._dialogN = 2;
	_storyDialog[9]._dialogType = 2;
	_storyDialog[9]._script[0] = L"[����]";
	_storyDialog[9]._script[1] = L"�� �׷����� �ϴ°���?";

	_storyDialog[10]._speaker = "Vermont";
	_storyDialog[10]._dialogN = 4;
	_storyDialog[10]._dialogType = 0;
	_storyDialog[10]._script[0] = L"[����Ʈ]";
	_storyDialog[10]._script[1] = L"������! �׳������ ��� ���� ���� ������ �� ����!";
	_storyDialog[10]._script[2] = L"��, �׳�� ���� �ð����� ����. � Į�� ������ ������ �� ������";
	_storyDialog[10]._script[3] = L"����� ����!";

	_storyDialog[11]._speaker = "Saladin";
	_storyDialog[11]._dialogN = 2;
	_storyDialog[11]._dialogType = 0;
	_storyDialog[11]._script[0] = L"[����]";
	_storyDialog[11]._script[1] = L"����. Į�� �����ڴ�.";

	_storyDialog[12]._speaker = "Sherazade";
	_storyDialog[12]._dialogN = 3;
	_storyDialog[12]._dialogType = 1;
	_storyDialog[12]._script[0] = L"[�ζ��ڵ�]";
	_storyDialog[12]._script[1] = L"�����, �ȵǿ�!";
	_storyDialog[12]._script[2] = L"�� �ڽſ� ���� ��� ���Ͻô� ����?";

	_storyDialog[13]._speaker = "Saladin";
	_storyDialog[13]._dialogN = 3;
	_storyDialog[13]._dialogType = 2;
	_storyDialog[13]._script[0] = L"[����]";
	_storyDialog[13]._script[1] = L"�ζ��ڵ�, ���� �̹� ���Ŵ� �ؾ��ٿ�.";
	_storyDialog[13]._script[2] = L"���� �ѻ���� ���������� ��ƿ԰� ���������� �������̿�.";

	_storyDialog[14]._speaker = "Vermont";
	_storyDialog[14]._dialogN = 2;
	_storyDialog[14]._dialogType = 0;
	_storyDialog[14]._script[0] = L"[����Ʈ]";
	_storyDialog[14]._script[1] = L"�, �༮�� ü���ض�!";

	_storyDialog[15]._speaker = "Sherazade";
	_storyDialog[15]._dialogN = 3;
	_storyDialog[15]._dialogType = 0;
	_storyDialog[15]._script[0] = L"[�ζ��ڵ�]";
	_storyDialog[15]._script[1] = L"�����! ���� ������ ����� ���� �Ǵ±���.";
	_storyDialog[15]._script[2] = L"������, ���� ���� ��⸦ ���ھ��...";

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
			FONTMANAGER->textOut(getMemDC(), _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].left + 20, _dialogRC[_storyDialog[_dialogIndex - 1]._dialogType].top + 20, "����ü", 25, 50, 
				_storyDialog[_dialogIndex - 1]._script, _storyDialog[_dialogIndex - 1]._dialogN, 999, RGB(255, 255, 255));
		}
	}
	_textBoxImg->alphaRender(getMemDC(), _dialogRC[dialogType].left, _dialogRC[dialogType].top,
		_dialogRC[dialogType].right - _dialogRC[dialogType].left, _dialogRC[dialogType].bottom - _dialogRC[dialogType].top,
		0, 0, _textBoxImg->getWidth(), _textBoxImg->getHeight(), 127);
	FONTMANAGER->textOut(getMemDC(), _dialogRC[dialogType].left + 20, _dialogRC[dialogType].top + 20, "����ü", 25, 50, printStringArr, arrSize, length, RGB(255, 255, 255));
}
