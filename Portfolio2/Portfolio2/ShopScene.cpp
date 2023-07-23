#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void)
{
	for (int i = 0; i < 4; i++)
	{
		_shopButtons[i].left = WINSIZE_X - 10 - IMAGEMANAGER->findImage("ShopButton")->getWidth() * 1.5f;
		_shopButtons[i].right = WINSIZE_X - 10;
		_shopButtons[i].top = 10 + IMAGEMANAGER->findImage("ShopTitle")->getHeight() + 20 + (5 + IMAGEMANAGER->findImage("ShopButton")->getHeight() * 1.5f) * i;
		_shopButtons[i].bottom = _shopButtons[i].top + IMAGEMANAGER->findImage("ShopButton")->getHeight() * 1.5f;
	}
	_exitButton.left = WINSIZE_X - 10 - IMAGEMANAGER->findImage("ShopButton")->getWidth() * 0.5f;
	_exitButton.top = WINSIZE_Y - 20 - IMAGEMANAGER->findImage("ShopButton")->getHeight() * 0.5f;
	_exitButton.right = WINSIZE_X - 10;
	_exitButton.bottom = WINSIZE_Y - 20;
	for (int i = 0; i < 2; i++)
	{
		_buySellButton[i].left = 30 + 50 * i;
		_buySellButton[i].top = 90;
		_buySellButton[i].right = _buySellButton[i].left + 50;
		_buySellButton[i].bottom = _buySellButton[i].top + 20;
	}
	_order.reset();
	_order.set(0);
	_sell = false;
	return S_OK;
}

void ShopScene::update(void)
{
	_frame++;
	if (_frame == 1)
	{
		SOUNDMANAGER->playSoundFMOD("ShopSceneBG");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_exitButton, _ptMouse))
		{
			_order = _order >> 1;
			IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _exitButton.left, _exitButton.top, IMAGEMANAGER->findImage("PressButton")->getWidth() * 0.5f, IMAGEMANAGER->findImage("PressButton")->getHeight() * 0.5f,
				0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
		}
		if(_order.test(0))
		{
			if (PtInRect(&_shopButtons[1], _ptMouse))
			{
				_order = _order << 1;
			}
		}
		else if (_order.test(1))
		{
			for(int i = 0; i < 2; i++)
			{
				if (PtInRect(&_buySellButton[i], _ptMouse))
				{
					_sell = i;
				}
			}
		}
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_order.none())
		{
			SOUNDMANAGER->stopAllSoundFMOD();
			SCENEMANAGER->changeScene("WorldMap");
		}
	}
}

void ShopScene::render(void)
{
	IMAGEMANAGER->findImage("ShopSceneBG")->render(getMemDC());
	if(_order.test(0))
	{
		IMAGEMANAGER->findImage("ShopTitle")->render(getMemDC(), 0, 10, WINSIZE_X, 50, 0, 0, IMAGEMANAGER->findImage("ShopTitle")->getWidth(), IMAGEMANAGER->findImage("ShopTitle")->getHeight());
		IMAGEMANAGER->findImage("ShopTitleLT")->render(getMemDC(), 0, 0, IMAGEMANAGER->findImage("ShopTitleLT")->getWidth() * 1.5, IMAGEMANAGER->findImage("ShopTitleLT")->getHeight() * 1.5,
			0, 0, IMAGEMANAGER->findImage("ShopTitleLT")->getWidth(), IMAGEMANAGER->findImage("ShopTitleLT")->getHeight());
		IMAGEMANAGER->findImage("ShopTitleRB")->render(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("ShopTitleRB")->getWidth() * 1.5, IMAGEMANAGER->findImage("ShopTitle")->getHeight(),
			IMAGEMANAGER->findImage("ShopTitleRB")->getWidth() * 1.5, IMAGEMANAGER->findImage("ShopTitleRB")->getHeight() * 1.5,
			0, 0, IMAGEMANAGER->findImage("ShopTitleRB")->getWidth(), IMAGEMANAGER->findImage("ShopTitleRB")->getHeight());
		SetTextAlign(getMemDC(), TA_CENTER);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X / 2, 5 + 15, "가을체", 30, 100, "자비단 입구", strlen("자비단 입구"), RGB(212, 204, 192));
		SetTextAlign(getMemDC(), TA_LEFT);
		for (int i = 0; i < 4; i++)
		{
			if(PtInRect(&_shopButtons[i], _ptMouse))
			{
				IMAGEMANAGER->findImage("ShopButtonActive")->alphaRender(getMemDC(), _shopButtons[i].left, _shopButtons[i].top, 
					IMAGEMANAGER->findImage("ShopButtonActive")->getWidth() * 1.5f, IMAGEMANAGER->findImage("ShopButtonActive")->getHeight() * 1.5f,
					0, 0, IMAGEMANAGER->findImage("ShopButtonActive")->getWidth(), IMAGEMANAGER->findImage("ShopButtonActive")->getHeight(), 128);
			}
			else
			{
				IMAGEMANAGER->findImage("ShopButton")->alphaRender(getMemDC(), _shopButtons[i].left, _shopButtons[i].top,
					IMAGEMANAGER->findImage("ShopButton")->getWidth() * 1.5f, IMAGEMANAGER->findImage("ShopButton")->getHeight() * 1.5f,
					0, 0, IMAGEMANAGER->findImage("ShopButton")->getWidth(), IMAGEMANAGER->findImage("ShopButton")->getHeight(), 128);
			}
			IMAGEMANAGER->findImage("ShopIcon")->frameRender(getMemDC(), _shopButtons[i].left + 5, _shopButtons[i].top + 5, i, 0);
			FONTMANAGER->textOut(getMemDC(), _shopButtons[i].left + IMAGEMANAGER->findImage("ShopIcon")->getFrameWidth() + 5, _shopButtons[i].top + 10, 
				"가을체", 30, 100, _shopText[i], strlen(_shopText[i]), RGB(255, 255, 255));
		}
	}
	// 무기점 진입상태
	else if(_order.test(1))
	{
		IMAGEMANAGER->findImage("TextBox")->render(getMemDC(), 10, 10, 300, 50, 0, 0, IMAGEMANAGER->findImage("TextBox")->getWidth(), IMAGEMANAGER->findImage("TextBox")->getHeight());
		SetTextAlign(getMemDC(), TA_CENTER);
		FONTMANAGER->textOut(getMemDC(), 10 + 150, 20, "가을체", 30, 100, "무기점", strlen("무기점"), RGB(255, 255, 255));
		IMAGEMANAGER->findImage("ShopEmployee")->render(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("ShopEmployee")->getWidth() * 1.4 - 20, 
			WINSIZE_Y - 80 - IMAGEMANAGER->findImage("ShopEmployee")->getHeight() * 1.4, IMAGEMANAGER->findImage("ShopEmployee")->getWidth() * 1.4, 
			IMAGEMANAGER->findImage("ShopEmployee")->getHeight() * 1.4, 0, 0, IMAGEMANAGER->findImage("ShopEmployee")->getWidth(), IMAGEMANAGER->findImage("ShopEmployee")->getHeight());
		// 상점 아이템 목록
		IMAGEMANAGER->findImage("TextBox")->render(getMemDC(), 20, 80, WINSIZE_X / 2 - 20, 300, 0, 0, IMAGEMANAGER->findImage("TextBox")->getWidth(), IMAGEMANAGER->findImage("TextBox")->getHeight());
		IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _buySellButton[_sell].left, _buySellButton[_sell].top,
			_buySellButton[_sell].right - _buySellButton[_sell].left, _buySellButton[_sell].bottom - _buySellButton[_sell].top,
			0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
		IMAGEMANAGER->findImage("ShopButton")->render(getMemDC(), _buySellButton[!_sell].left, _buySellButton[!_sell].top,
			_buySellButton[!_sell].right - _buySellButton[!_sell].left, _buySellButton[!_sell].bottom - _buySellButton[!_sell].top,
			0, 0, IMAGEMANAGER->findImage("ShopButton")->getWidth(), IMAGEMANAGER->findImage("ShopButton")->getHeight());
		FONTMANAGER->textOut(getMemDC(), (_buySellButton[0].left + _buySellButton[0].right) / 2, _buySellButton[0].top, "가을체", 20, 100, "구입", strlen("구입"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), (_buySellButton[1].left + _buySellButton[1].right) / 2, _buySellButton[1].top, "가을체", 20, 100, "판매", strlen("판매"), RGB(255, 255, 255));

		// eld
		IMAGEMANAGER->findImage("TextBox")->render(getMemDC(), 100, 390, WINSIZE_X / 2 - 100, 120, 0, 0, IMAGEMANAGER->findImage("TextBox")->getWidth(), IMAGEMANAGER->findImage("TextBox")->getHeight());
	}
	IMAGEMANAGER->findImage("TextBox")->render(getMemDC(), 0, WINSIZE_Y - 200, WINSIZE_X, 200, 
		0, 0, IMAGEMANAGER->findImage("TextBox")->getWidth(), IMAGEMANAGER->findImage("TextBox")->getHeight());
	// 파티 캐릭터 이미지 출력
	for(int i = 0; i < 10; i++)
	{
		IMAGEMANAGER->findImage("Empty")->render(getMemDC(), WINSIZE_X / 12 * (i + 1), WINSIZE_Y - 200 / 3 * 2, WINSIZE_X / 12, WINSIZE_X / 12,
			0, 0, IMAGEMANAGER->findImage("Empty")->getWidth(), IMAGEMANAGER->findImage("Empty")->getHeight());
	}
	if (_order.none())
	{
		IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _exitButton.left, _exitButton.top, IMAGEMANAGER->findImage("PressButton")->getWidth() * 0.5f, IMAGEMANAGER->findImage("PressButton")->getHeight() * 0.5f,
			0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
	}
	else
	{
		IMAGEMANAGER->findImage("ShopButton")->render(getMemDC(), _exitButton.left, _exitButton.top, IMAGEMANAGER->findImage("ShopButton")->getWidth() * 0.5f, IMAGEMANAGER->findImage("ShopButton")->getHeight() * 0.5f,
			0, 0, IMAGEMANAGER->findImage("ShopButton")->getWidth(), IMAGEMANAGER->findImage("ShopButton")->getHeight());
	}
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->textOut(getMemDC(), (_exitButton.right + _exitButton.left) / 2, (_exitButton.top + 2),
		"가을체", 15, 100, "EXIT", strlen("EXIT"), RGB(255, 255, 255));
	SetTextAlign(getMemDC(), TA_LEFT);
	IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
}

void ShopScene::release(void)
{
}
