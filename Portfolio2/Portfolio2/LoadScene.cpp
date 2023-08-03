#include "Stdafx.h"
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
		if (_fp[i].first != nullptr)
		{
			fclose(_fp[i].first);
		}
		wsprintf(_text, "save%d.txt", i + 1);
		if (fopen_s(&_fp[i].first, _text, "r") == 0)
		{
			fscanf_s(_fp[i].first, "%d", &_fp[i].second);
		}
	}
	return S_OK;
}

void LoadScene::release(void)
{
	for (int i = 0; i < 9; i++)
	{
		fclose(_fp[i].first);
		SAFE_DELETE(_fp[i].first);
	}
}

void LoadScene::update(void)
{
	SOUNDMANAGER->update();
	_frame++;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 9; i++)
		{
			if (PtInRect(&_loadButton[i], _ptMouse) && _fp[i].first != nullptr)
			{
				DATAMANAGER->setScenario(_fp[i].second);
				DATAMANAGER->loadGame(_fp[i].first);
				SCENEMANAGER->loadingScene();
				for (int i = 0; i < 9; i++)
				{
					if (_fp[i].first != nullptr)
					{
						fclose(_fp[i].first);
					}
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
		IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameWidth() * 2, IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameHeight() * 2, 1, 0);
	IMAGEMANAGER->findImage("SaveLoadIcon")->frameRender(getMemDC(), 210, WINSIZE_Y - 140,
		IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameWidth() * 2, IMAGEMANAGER->findImage("SaveLoadIcon")->getFrameHeight() * 2, 2, 0);
	FONTMANAGER->textOut(getMemDC(), 250, 115, "가을체", 30, 100, "로드", strlen("로드"), RGB(164, 215, 242));
	FONTMANAGER->textOut(getMemDC(), 250, WINSIZE_Y - 135, "가을체", 30, 100, "퀵 로드", strlen("퀵 로드"), RGB(164, 215, 242));
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
		if (_fp[i].first == nullptr)
		{
			FONTMANAGER->textOut(getMemDC(), 250, _loadButton[i].top + 5, "가을체", 30, 100, "BLANK", strlen("BLANK"), RGB(248, 136, 0));
		}
		else
		{
			switch (_fp[i].second % 3)
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
			switch (_fp[i].second)
			{
				case 69:
					wsprintf(_text, "불사조");
				break;
				case 75:
					wsprintf(_text, "형제");
				break;
			}
			FONTMANAGER->textOut(getMemDC(), 450, _loadButton[i].top + 5, "가을체", 30, 100, _text, strlen(_text), RGB(255, 255, 255));
		}
		IMAGEMANAGER->findImage("BulletPoint")->render(getMemDC(), _loadButton[i].left + 10, _loadButton[i].top + 15, IMAGEMANAGER->findImage("BulletPoint")->getWidth() * 2,
			IMAGEMANAGER->findImage("BulletPoint")->getHeight() * 2, 0, 0, IMAGEMANAGER->findImage("BulletPoint")->getWidth(), IMAGEMANAGER->findImage("BulletPoint")->getHeight());
	}
	IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
}
