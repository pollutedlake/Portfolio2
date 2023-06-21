#include "Stdafx.h"
#include "MainGame.h"
#include "resource.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	title = LoadBitmap(_hInstance, MAKEINTRESOURCE(IDB_TITLE));
	backDC[0] = CreateCompatibleDC(GetDC(_hWnd));
	backDC[1] = CreateCompatibleDC(GetDC(_hWnd));
	backDCIndex = 0;
	rc = { 0, 0, 200, 200 };
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	DeleteObject(title);
	SelectObject(backDC[0], backDCOldBitmap);
	SelectObject(backDC[1], backDCOldBitmap);
	DeleteObject(backDCBitmap);
	DeleteDC(backDC[0]);
	DeleteDC(backDC[1]);
}

void MainGame::update(void)
{
	GameNode::update();
	backDCBitmap = CreateCompatibleBitmap(GetDC(_hWnd), WINSIZE_X, WINSIZE_Y);
	backDCOldBitmap = (HBITMAP)SelectObject(backDC[backDCIndex], backDCBitmap);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		rc.left += 5;
		rc.right += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 5;
		rc.right -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 5;
		rc.bottom -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 5;
		rc.bottom += 5;
	}
}

void MainGame::render(HDC hdc)
{
	memDC = CreateCompatibleDC(hdc);
	oldBitmap = (HBITMAP)SelectObject(memDC, title);
	BITMAP titleBitmap;
	GetObject(title, sizeof(BITMAP), &titleBitmap);
	StretchBlt(backDC[backDCIndex], 0, 0, WINSIZE_X, WINSIZE_Y, memDC, 0, 0, titleBitmap.bmWidth, titleBitmap.bmHeight, SRCCOPY);
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
	Rectangle(backDC[backDCIndex], rc.left, rc.top,rc.right, rc.bottom);
	BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, backDC[backDCIndex], 0, 0, SRCCOPY);
	SelectObject(backDC[backDCIndex], backDCOldBitmap);
	DeleteObject(backDCBitmap);
	backDCIndex = !backDCIndex;
}