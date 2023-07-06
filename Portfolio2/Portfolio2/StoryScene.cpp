#include "Stdafx.h"
#include "StoryScene.h"

HRESULT StoryScene::init(void)
{
	TCHAR* fontName = TEXT("휴먼굴림");
	LPCWSTR test[] = { L"진영이의 포폴이 너무너무 기대가 된다.\n", L"모두들 \n기대 하고 있다.", L"그\n짓말이다." };
    return S_OK;
}

void StoryScene::release(void)
{
}

void StoryScene::update(void)
{
}

void StoryScene::render(void)
{
	TCHAR* fontName = TEXT("휴먼굴림");
	LPCWSTR test[] = { L"진영이의 포폴이 너무너무 기대가 된다.", L"모두들 \n기대 하고 있다.\n", L"그\n짓말이다." };
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, fontName, 25, 25, test, sizeof(test) / sizeof(*test), NULL, RGB(0, 0, 255));
}
