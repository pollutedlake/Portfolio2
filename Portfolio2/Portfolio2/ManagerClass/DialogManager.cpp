#include "../FrameWork/PCH/Stdafx.h"
#include "./DialogManager.h"

HRESULT DialogManager::init(void)
{
	return S_OK;
}

void DialogManager::release(void)
{
}

void DialogManager::makeTextBox(HDC hdc, int left, int top, int width, int height, BYTE alpha)
{
	IMAGEMANAGER->findImage("TextBox2")->alphaRender(hdc, left, top, width, height, 0, 0, width, height, alpha);
	IMAGEMANAGER->findImage("TextBoxLT")->render(hdc, left, top);
	IMAGEMANAGER->findImage("TextBoxLB")->render(hdc, left, top + height - IMAGEMANAGER->findImage("TextBoxLB")->getHeight());
	IMAGEMANAGER->findImage("TextBoxRT")->render(hdc, left + width - IMAGEMANAGER->findImage("TextBoxRT")->getWidth(), top);
	IMAGEMANAGER->findImage("TextBoxRB")->render(hdc, left + width - IMAGEMANAGER->findImage("TextBoxRB")->getWidth(), top + height - IMAGEMANAGER->findImage("TextBoxRB")->getHeight());
	SelectObject(hdc, GetStockObject(WHITE_PEN));
	LineMake(hdc, left + 5, top, left + width - 6, top);
	LineMake(hdc, left, top + 5, left, top + height - 6);
	LineMake(hdc, left + 5, top + height - 1, left + width - 6, top + height - 1);
	LineMake(hdc, left + width - 1, top + 5, left + width - 1, top + height - 6);
	SelectObject(hdc, GetStockObject(NULL_PEN));
}



