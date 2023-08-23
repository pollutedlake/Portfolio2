#include "../FrameWork/PCH/Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
	_textBoxImg = IMAGEMANAGER->findImage("TextBox");
	_vermontImg = IMAGEMANAGER->findImage("Vermont");
	_whiteImg = IMAGEMANAGER->findImage("White");
	_blackImg = IMAGEMANAGER->findImage("Black");
	_backGroundImg.push_back(IMAGEMANAGER->findImage("EndingBG"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("PlaySong"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reminisce1"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reminisce2"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reminisce3"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reminisce4"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reminisce5"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reminisce6"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reminisce7"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("PlaySong"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Reveal"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("EndingBG"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Brother"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("White"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Black"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle1"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle2"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle3"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle4"));
	_brothersImg = IMAGEMANAGER->findImage("ForeheadKiss");
	_vermont = IMAGEMANAGER->findImage("VermontEnding");
	_saladin = IMAGEMANAGER->findImage("SaladinEnding");
	_slashRight = IMAGEMANAGER->findImage("SlashRight");
	_pipe = IMAGEMANAGER->findImage("Pipe");
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 150, WINSIZE_X - 200, 200);

	// 대화
	for (int i = 0; i < sizeof(_dialogs) / sizeof(*_dialogs); i++)
	{
		for (int j = 0; j < sizeof(_dialogs[i]._dialog) / sizeof(*_dialogs[i]._dialog); j++)
		{
			_dialogs[i]._dialog[j] = L"\0";
		}
	}
	_dialogs[0]._speaker = "Vermont";
	_dialogs[0]._dialog[0] = L"[버몬트]";
	_dialogs[0]._dialog[1] = L"죽여라...";
	
	_dialogs[1]._speaker = "Saladin";
	_dialogs[1]._dialog[0] = L"[살라딘]";
	_dialogs[1]._dialog[1] = L"...";

	_dialogs[2]._speaker = "Vermont";
	_dialogs[2]._dialog[0] = L"[버몬트]";
	_dialogs[2]._dialog[1] = L"그것만은...";
	_dialogs[2]._dialog[2] = L"제발 돌려줘 그것만은...";

	_typingLetterN = 0;
	_currentDialog = 0;
	_curBGIndex = 0;
	_fadeStartTime = 0;
	_fadeEndTime = 0;
	_playTime = 0;
	_showDialog = false;
	_frame = 0;
	_index = 0;
	_saladinIndex = 0;
	_brothersIndex = 0;
	return S_OK;
}

void EndingScene::release(void)
{

}

void EndingScene::update(void)
{
	SOUNDMANAGER->update();
	if (!SOUNDMANAGER->isPlaying())
	{
		SOUNDMANAGER->playSoundFMOD("Brother");
	}
	_playTime = SOUNDMANAGER->getCurrentPos("Brother");
	_fade.reset();
	if (_playTime < 1500)
	{
		_fadeStartTime = 0;
		_fadeEndTime = 1500;
		_fade.set(3, true);
	}
	else if (_playTime < 7000)
	{
		_showDialog = true;
	}
	else if (_playTime < 8000)
	{
		_showDialog = false;
		_typingLetterN = 0;
	}
	else if (_playTime < 10000)
	{
		_showDialog = true;
		_currentDialog = 1;
	}
	else if (_playTime < 12000)
	{
		_showDialog = false;
		_typingLetterN = 0;
	}
	else if (_playTime < 25000)
	{
		_showDialog = true;
		_currentDialog = 2;
	}
	else if (_playTime < 30000)
	{
		_showDialog = false;
		_fadeStartTime = 26000;
		_fadeEndTime = 30000;
		_fade.set(0, true);
	}
	else if (_playTime < 36000)
	{
		if(_playTime < 35000)
		{
			_fadeStartTime = 30000;
			_fadeEndTime = 35000;
			_fade.set(1, true);
		}
		else
		{
			_fadeStartTime = 35000;
			_fadeEndTime = 36000;
			_fade.set(0, true);
		}
		_showDialog = false;
		_curBGIndex = 1;
	}
	else if (_playTime < 42000)
	{
		if (_playTime < 37000)
		{
			_fadeStartTime = 36000;
			_fadeEndTime = 37000;
			_fade.set(1, true);
		}
		if (_playTime > 41000)
		{
			_fadeStartTime = 41000;
			_fadeEndTime = 42000;
			_fade.set(0, true);
		}
		_curBGIndex = 2;
	}
	else if (_playTime < 47000)
	{
		if (_playTime < 43000)
		{
			_fadeStartTime = 42000;
			_fadeEndTime = 43000;
			_fade.set(1, true);
		}
		if (_playTime > 46000)
		{
			_fadeStartTime = 46000;
			_fadeEndTime = 47000;
			_fade.set(0, true);
		}
		_curBGIndex = 3;
	}
	else if (_playTime < 51000)
	{
		if (_playTime < 48000)
		{
			_fadeStartTime = 47000;
			_fadeEndTime = 48000;
			_fade.set(1, true);
		}
		if (_playTime > 50000)
		{
			_fadeStartTime = 50000;
			_fadeEndTime = 51000;
			_fade.set(0, true);
		}
		_curBGIndex = 4;
	}
	else if (_playTime < 56000)
	{
		if (_playTime < 52000)
		{
			_fadeStartTime = 51000;
			_fadeEndTime = 52000;
			_fade.set(1, true);
		}
		if (_playTime > 55000)
		{
			_fadeStartTime = 55000;
			_fadeEndTime = 56000;
			_fade.set(0, true);
		}
		_curBGIndex = 5;
	}
	else if (_playTime < 62000)
	{
		if (_playTime < 57000)
		{
			_fadeStartTime = 56000;
			_fadeEndTime = 57000;
			_fade.set(1, true);
		}
		if (_playTime > 61000)
		{
			_fadeStartTime = 61000;
			_fadeEndTime = 62000;
			_fade.set(0, true);
		}
		_curBGIndex = 6;
	}
	else if (_playTime < 67000)
	{
		if (_playTime < 63000)
		{
			_fadeStartTime = 62000;
			_fadeEndTime = 63000;
			_fade.set(1, true);
		}
		if (_playTime > 66000)
		{
			_fadeStartTime = 66000;
			_fadeEndTime = 67000;
			_fade.set(0, true);
		}
		_curBGIndex = 7;
	}
	else if (_playTime < 72000)
	{
		if (_playTime < 68000)
		{
			_fadeStartTime = 67000;
			_fadeEndTime = 68000;
			_fade.set(1, true);
		}
		if (_playTime > 71000)
		{
			_fadeStartTime = 71000;
			_fadeEndTime = 72000;
			_fade.set(0, true);
		}
		_curBGIndex = 8;
	}
	else if (_playTime < 81000)
	{
		if (_playTime < 73000)
		{
			_fadeStartTime = 72000;
			_fadeEndTime = 73000;
			_fade.set(1, true);
		}
		if (_playTime >77000)
		{
			_fadeStartTime = 77000;
			_fadeEndTime = 81000;
			_fade.set(0, true);
		}
		_curBGIndex = 9;
	}
	else if (_playTime < 104500)
	{
		if (_playTime < 87000)
		{
			_fadeStartTime = 81000;
			_fadeEndTime = 87000;
			_fade.set(1, true);
		}
		if (_playTime > 104000)
		{
			_fadeStartTime = 104000;
			_fadeEndTime = 104500;
			_fade.set(0, true);
		}
		_curBGIndex = 10;
	}
	else if (_playTime < 114000)
	{
		if (_playTime < 106000)
		{
			_fadeStartTime = 104500;
			_fadeEndTime = 106000;
			_fade.set(1, true);
		}
		if (_playTime > 112000)
		{
			_fadeStartTime = 112000;
			_fadeEndTime = 114000;
			_fade.set(0, true);
		}
		_curBGIndex = 11;
	}
	else if (_playTime < 125000)
	{
		if (_playTime < 116000)
		{
			_fadeStartTime = 114000;
			_fadeEndTime = 116000;
			_fade.set(1, true);
		}
		if (_playTime > 118000)
		{
			_fadeStartTime = 118000;
			_fadeEndTime = 125000;
			_fade.set(0, true);
		}
		_curBGIndex = 12;
	}
	else if (_playTime < 149000)
	{
		_curBGIndex = 13;
	}
	else if (_playTime < 157000)
	{
		if (_playTime < 151000)
		{
			_fadeStartTime = 149000;
			_fadeEndTime = 151000;
			_fade.set(1, true);
			_curBGIndex = 14;
		}
		else if (_playTime < 153000)
		{
			_fadeStartTime = 151000;
			_fadeEndTime = 153000;
			_fade.set(3, true);
			_curBGIndex = 15;
		}
		else if (_playTime > 155000)
		{
			_fadeStartTime = 155000;
			_fadeEndTime = 157000;
			_fade.set(2, true);
			_curBGIndex = 15;
		}
	}
	else if (_playTime < 163000)
	{
		if (_playTime < 158000)
		{
		_fadeStartTime = 157000;
		_fadeEndTime = 158000;
		_fade.set(3, true);
		}
		else if (_playTime > 162000)
		{
		_fadeStartTime = 162000;
		_fadeEndTime = 163000;
		_fade.set(2, true);
		}
		_curBGIndex = 16;
	}
	else if (_playTime < 169000)
	{
		if (_playTime < 165000)
		{
			_fadeStartTime = 163000;
			_fadeEndTime = 165000;
			_fade.set(3, true);
		}
		else if (_playTime > 168000)
		{
			_fadeStartTime = 168000;
			_fadeEndTime = 169000;
			_fade.set(2, true);
		}
		_curBGIndex = 17;
	}
	else if(_playTime < 175000)
	{
		if (_playTime < 171000)
		{
			_fadeStartTime = 169000;
			_fadeEndTime = 171000;
			_fade.set(3, true);
		}
		else if (_playTime > 174000)
		{
			_fadeStartTime = 174000;
			_fadeEndTime = 175000;
			_fade.set(2, true);
		}
		_curBGIndex = 18;
	}
	else
	{
		SCENEMANAGER->loadingScene();
	}
	if (_showDialog)
	{
		_frame++;
		if(_frame % 5 == 0)
		{
			_typingLetterN++;
		}
	}
	else
	{
		if(_playTime < 30000)
		{
			_frame = 0;
		}
	}
	if (_playTime < 10000)
	{
		_saladinIndex = 0;
	}
	else if (_playTime < 10700)
	{
		_saladinIndex = 1;
	}
	else if (_playTime < 10800)
	{
		_saladinIndex = 2;
	}
	else if (_playTime < 11500)
	{
		_saladinIndex = 3;
	}
	else if (_playTime < 11600)
	{
		_saladinIndex = 4;
	}
	else if (_playTime < 12200)
	{
		_saladinIndex = 5;
	}
	else
	{
		_saladinIndex = 6;
	}
	if (_playTime > 111000)
	{
		_frame++;
		if (_frame % 10 == 0)
		{
			_brothersIndex++;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Title");
	}
}

void EndingScene::render(void)
{
	if(_playTime > 0)
	{
		_backGroundImg[_curBGIndex]->render(getMemDC());
		switch (_curBGIndex)
		{
			case 0:
				if(_playTime < 11500)
				{
					_vermont->frameRender(getMemDC(), WINSIZE_X / 2, WINSIZE_Y - 200, _vermont->getFrameWidth() * 1.4f, _vermont->getFrameHeight() * 1.4f, 0, 0);
				}
				else
				{
					_vermont->frameRender(getMemDC(), WINSIZE_X / 2, WINSIZE_Y - 200, _vermont->getFrameWidth() * 1.4f, _vermont->getFrameHeight() * 1.4f, 1, 0);
					int pipeX = WINSIZE_X / 2 - 30;
					int pipeY = WINSIZE_Y - 200;
					if(_playTime < 11800)
					{
						pipeX = WINSIZE_X / 2 + 30 - 60.0f * (float)(_playTime - 11500) / 300.0f;
						pipeY = WINSIZE_Y - 230 + 40.0f * (float)(_playTime - 11500) / 300.0f;
						_pipe->frameRender(getMemDC(), pipeX, pipeY,
							_pipe->getFrameWidth() * 1.5, _pipe->getFrameHeight() * 1.5, _playTime % 2, 0);
					}
					else if(_playTime < 12200)
					{
						_pipe->frameRender(getMemDC(), pipeX, pipeY,
							_pipe->getFrameWidth() * 1.5, _pipe->getFrameHeight() * 1.5, 0, 0);
					}
				}
				if (_saladinIndex == 2)
				{
					_slashRight->frameRender(getMemDC(), WINSIZE_X / 2 - 110, WINSIZE_Y - 260, _slashRight->getFrameWidth() * 1.4, _slashRight->getFrameHeight() * 1.4, (_playTime - 10700) / 25, 0);
				}
				_saladin->frameRender(getMemDC(), WINSIZE_X / 2 - _saladin->getFrameWidth() * 1.4f + 100.0f, WINSIZE_Y - 230, _saladin->getFrameWidth()*1.4f, _saladin->getFrameHeight()*1.4f, _saladinIndex, 0);
			break;
			case 11:
				_brothersImg->frameRender(getMemDC(), WINSIZE_X / 2, WINSIZE_Y - 200, _brothersImg->getFrameWidth() * 1.4f, _brothersImg->getFrameHeight() * 1.4f, _brothersIndex, 0);
			break;
		}
	}
	if (_curBGIndex == 0 && _showDialog)
	{
		dialog(_dialogs[_currentDialog]._speaker, _dialogs[_currentDialog]._dialog, _typingLetterN,
			sizeof(_dialogs[_currentDialog]._dialog) / sizeof(_dialogs[_currentDialog]._dialog[0]));
	}
	if(_playTime >= _fadeStartTime && _playTime <= _fadeEndTime)
	{
		if (_fade[0])
		{
			fadeOutWhite(_fadeStartTime, _playTime, _fadeEndTime);
		}
		if (_fade[1])
		{
			fadeInWhite(_fadeStartTime, _playTime, _fadeEndTime);
		}
		if (_fade[2])
		{
			fadeOutBlack(_fadeStartTime, _playTime, _fadeEndTime);
		}
		if (_fade[3])
		{
			fadeInBlack(_fadeStartTime, _playTime, _fadeEndTime);
		}
	}
}

void EndingScene::fadeOutWhite(int startTime, int curTime, int endTime)
{
	_whiteImg->alphaRender(getMemDC(), 255.0f / (float)(endTime - startTime) * (float)(curTime - startTime));
}

void EndingScene::fadeInWhite(int startTime, int curTime, int endTime)
{
	_whiteImg->alphaRender(getMemDC(), 255.0f - 255.0f / (float)(endTime - startTime) * (float)(curTime - startTime));
}

void EndingScene::fadeOutBlack(int startTime, int curTime, int endTime)
{
	_blackImg->alphaRender(getMemDC(), 255.0f / (float)(endTime - startTime) * (float)(curTime - startTime));
}

void EndingScene::fadeInBlack(int startTime, int curTime, int endTime)
{
	_blackImg->alphaRender(getMemDC(), 255.0f - 255.0f / (float)(endTime - startTime) * (float)(curTime - startTime));
}

void EndingScene::dialog(string charName, LPCWSTR* printStringArr, int length, int arrSize)
{
	char text[256];
	wsprintf(text, "Dialog%s", charName.c_str());
	_speakerImg = IMAGEMANAGER->findImage(text);
	_speakerImg->render(getMemDC(), (WINSIZE_X - _speakerImg->getWidth() * 1.5) / 2, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
		_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
		0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
	_textBoxImg->alphaRender(getMemDC(), 100, WINSIZE_Y - 250,
		WINSIZE_X - 200, 200,
		0, 0, _textBoxImg->getWidth(), _textBoxImg->getHeight(), 127);
	FONTMANAGER->textOut(getMemDC(), _dialogRC.left + 20, _dialogRC.top + 20, "가을체", 25, 50, printStringArr, arrSize, _typingLetterN, RGB(255, 255, 255));

}
