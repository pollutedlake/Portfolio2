#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
	_textBoxImg = IMAGEMANAGER->findImage("TextBox");
	_vermontImg = IMAGEMANAGER->findImage("Vermont");
	_fadeOutWhiteImg = IMAGEMANAGER->findImage("FadeOutWhite");
	_fadeOutBlackImg = IMAGEMANAGER->findImage("FadeOutBlack");
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
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle1"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle2"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle3"));
	_backGroundImg.push_back(IMAGEMANAGER->findImage("Subtitle4"));
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 150, WINSIZE_X - 200, 200);

	// 한 컷당 시간
	for (int i = 0; i < 17; i++)
	{
		_cutTime[i] = 200;
	}
	_cutTime[0] = 2000;
	//_curTime[1] = 

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

	_frame = 0;
	_typingLetterN = 0;
	_currentDialog = 0;
	_curBGIndex = 0;
	_showDialog = false;
	return S_OK;
}

void EndingScene::release(void)
{

}

void EndingScene::update(void)
{
	if (_frame == 0 && _curBGIndex == 0)
	{
		SOUNDMANAGER->addSoundFMOD("Resources/Sounds/Brother.mp3");
		SOUNDMANAGER->playSoundFMOD();
		cout << SOUNDMANAGER->getSoundLength() << endl;
	}
	_frame++;
	/*if (_frame > _cutTime[_curBGIndex])
	{
		_frame = 0;
		if (_curBGIndex < _backGroundImg.size() - 1)
		{
			_curBGIndex++;
		}
		else 
		{
			SCENEMANAGER->changeScene("Title");
		}
	}*/
	if (_curBGIndex == 0)
	{
		cout << SOUNDMANAGER->getCurrentPos() << endl;
		switch (SOUNDMANAGER->getCurrentPos())
		{
		case 1000:
			_showDialog = true;
			break;
		/*case 7000:
			_showDialog = false;
			_typingLetterN = 0;
			break;
		case 8000:
			_showDialog = true;
			break;
		case 10000:
			_showDialog = false;
			_typingLetterN = 0;
			break;
		case 12000:
			_showDialog = true;
			break;
		case 30000:
			_curBGIndex++;
			break;*/
		}
	}
	if (_showDialog)
	{
		_typingLetterN++;
	}
}

void EndingScene::render(void)
{
	_backGroundImg[_curBGIndex]->render(getMemDC());
	if (_frame < 25)
	{
		if (_curBGIndex == 0)
		{
			fadeInBlack();
		}
		else if (_curBGIndex < 12)
		{
			fadeInWhite();
		}
		else
		{
			fadeInBlack();
		}
	}
	if (_frame > _cutTime[_curBGIndex] - 25)
	{
		if (_curBGIndex < 12)
		{
			fadeOutWhite();
		}
		else
		{
			fadeOutBlack();
		}
	}
	if (_curBGIndex == 0 && _showDialog)
	{
		dialog(_dialogs[_currentDialog]._speaker, _dialogs[_currentDialog]._dialog, _typingLetterN,
			sizeof(_dialogs[_currentDialog]._dialog) / sizeof(_dialogs[_currentDialog]._dialog[0]));
	}
}

void EndingScene::fadeOutWhite()
{
	_fadeOutWhiteImg->alphaRender(getMemDC(), (_frame - (_cutTime[_curBGIndex]) - 25) * 10 > 255 ? 255 : (_frame - (_cutTime[_curBGIndex] - 25)) * 10);
}

void EndingScene::fadeInWhite()
{
	_fadeOutWhiteImg->alphaRender(getMemDC(), 255 - (_frame * 10) < 0 ? 0 : 255 - (_frame * 10));
}

void EndingScene::fadeOutBlack()
{
	_fadeOutBlackImg->alphaRender(getMemDC(), (_frame - (_cutTime[_curBGIndex]) - 25) * 10 > 255 ? 255 : (_frame - (_cutTime[_curBGIndex] - 25)) * 10);
}

void EndingScene::fadeInBlack()
{
	_fadeOutBlackImg->alphaRender(getMemDC(), 255 - (_frame * 10) < 0 ? 0 : 255 - (_frame * 10));
}

void EndingScene::dialog(string charName, LPCWSTR* printStringArr, int length, int arrSize)
{
	_speakerImg = IMAGEMANAGER->findImage(charName);
	_speakerImg->render(getMemDC(), (WINSIZE_X - _speakerImg->getWidth() * 1.5) / 2, WINSIZE_Y - _speakerImg->getHeight() * 1.5,
		_speakerImg->getWidth() * 1.5, _speakerImg->getHeight() * 1.5,
		0, 0, _speakerImg->getWidth(), _speakerImg->getHeight());
	_textBoxImg->alphaRender(getMemDC(), 100, WINSIZE_Y - 250,
		WINSIZE_X - 200, 200,
		0, 0, _textBoxImg->getWidth(), _textBoxImg->getHeight(), 127);
	FONTMANAGER->textOut(getMemDC(), _dialogRC.left + 20, _dialogRC.top + 20, "가을체", 25, 50, printStringArr, arrSize, _typingLetterN, RGB(255, 255, 255));

}
