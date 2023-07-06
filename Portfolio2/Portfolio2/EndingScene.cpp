#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
	_textBoxImg = IMAGEMANAGER->findImage("TextBox");
	_vermontImg = IMAGEMANAGER->findImage("Vermont");
	_backGroundImg = IMAGEMANAGER->findImage("EndingBG");
	//_backGroundImg = IMAGEMANAGER->findImage("회상2");
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 150, WINSIZE_X - 200, 200);
	for (int i = 0; i < sizeof(_dialogs) / sizeof(*_dialogs); i++)
	{
		for(int j = 0; j < sizeof(_dialogs[i]._dialog) / sizeof(*_dialogs[i]._dialog); j++)
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
	return S_OK;
}

void EndingScene::release(void)
{

}

void EndingScene::update(void)
{
	_frame++;
	if (_frame > 5)
	{
		_frame = 0;
		_typingLetterN++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if(_currentDialog < 2)
		{
			_currentDialog++;
			_typingLetterN = 0;
			_frame = 0;
		}
	}
}

void EndingScene::render(void)
{
	_backGroundImg->render(getMemDC());
	dialog(_dialogs[_currentDialog]._speaker, _dialogs[_currentDialog]._dialog, _typingLetterN, 
	sizeof(_dialogs[_currentDialog]._dialog) / sizeof(_dialogs[_currentDialog]._dialog[0]));
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
