#include "Stdafx.h"
#include "StoryScene.h"

HRESULT StoryScene::init(void)
{
	TCHAR* fontName = TEXT("�޸ձ���");
	LPCWSTR test[] = { L"�������� ������ �ʹ��ʹ� ��밡 �ȴ�.\n", L"��ε� \n��� �ϰ� �ִ�.", L"��\n�����̴�." };
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
