#include "Stdafx.h"
#include "StoryScene.h"

HRESULT StoryScene::init(void)
{
	TCHAR* fontName = TEXT("휴먼굴림");
	LPCWSTR test[] = { L"진영이의 포폴이 너무너무 기대가 된다.\n", L"모두들 \n기대 하고 있다.", L"그\n짓말이다." };
	_frame = 0;
	_typingSpeed = 10;
    return S_OK;
}

void StoryScene::release(void)
{
}

void StoryScene::update(void)
{
	_frame++;
	if (_frame > 10)
	{
		_frame = 0;

	}
}

void StoryScene::render(void)
{

}
