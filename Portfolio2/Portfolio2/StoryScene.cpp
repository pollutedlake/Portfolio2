#include "Stdafx.h"
#include "StoryScene.h"

HRESULT StoryScene::init(void)
{
	TCHAR* fontName = TEXT("�޸ձ���");
	LPCWSTR test[] = { L"�������� ������ �ʹ��ʹ� ��밡 �ȴ�.\n", L"��ε� \n��� �ϰ� �ִ�.", L"��\n�����̴�." };
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
	TCHAR* fontName = TEXT("�޸ձ���");
	LPCWSTR test[] = { L"�������� ������ �ʹ��ʹ� ��밡 �ȴ�.", L"��ε� \n��� �ϰ� �ִ�.\n", L"��\n�����̴�." };
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, fontName, 25, 25, test, sizeof(test) / sizeof(*test), NULL, RGB(0, 0, 255));
}
