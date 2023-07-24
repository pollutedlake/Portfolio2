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
	_exitButton.left = WINSIZE_X - 10 - 100;
	_exitButton.top = WINSIZE_Y - 20 - 20;
	_exitButton.right = WINSIZE_X - 10;
	_exitButton.bottom = WINSIZE_Y - 20;
	for (int i = 0; i < 2; i++)
	{
		_buySellButton[i].left = 30 + 100 * i;
		_buySellButton[i].top = 90;
		_buySellButton[i].right = _buySellButton[i].left + 100;
		_buySellButton[i].bottom = _buySellButton[i].top + 20;
	}
	_decisionButton.first.right = WINSIZE_X / 2 - 20;
	_decisionButton.first.left = _decisionButton.first.right - 80;
	_decisionButton.first.bottom = 510 - 10;
	_decisionButton.first.top = _decisionButton.first.bottom - 20;
	_decisionButton.second = false;
	_order.reset();
	_order.set(0);
	_sell = false;
	_saleList = DATAMANAGER->getSaleList();
	for (int i = 0; i < _saleList.size(); i++)
	{
		_itemN.push_back(0);
	}
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
			if (PtInRect(&_decisionButton.first, _ptMouse))
			{
				_decisionButton.second = true;
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
		if (_decisionButton.second)
		{
			_decisionButton.second = false;
		}
	}
}

void ShopScene::render(void)
{
	IMAGEMANAGER->findImage("ShopSceneBG")->render(getMemDC());
	if(_order.test(0))
	{	
		DIALOGMANAGER->makeTextBox(getMemDC(), 0, 10, WINSIZE_X, 50, 255);
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
		DIALOGMANAGER->makeTextBox(getMemDC(), 10, 10, 300, 50, 200);
		SetTextAlign(getMemDC(), TA_CENTER);
		FONTMANAGER->textOut(getMemDC(), 10 + 150, 20, "가을체", 30, 100, "무기점", strlen("무기점"), RGB(255, 255, 255));
		IMAGEMANAGER->findImage("ShopEmployee")->render(getMemDC(), WINSIZE_X - IMAGEMANAGER->findImage("ShopEmployee")->getWidth() * 1.4 - 20, 
			WINSIZE_Y - 80 - IMAGEMANAGER->findImage("ShopEmployee")->getHeight() * 1.4, IMAGEMANAGER->findImage("ShopEmployee")->getWidth() * 1.4, 
			IMAGEMANAGER->findImage("ShopEmployee")->getHeight() * 1.4, 0, 0, IMAGEMANAGER->findImage("ShopEmployee")->getWidth(), IMAGEMANAGER->findImage("ShopEmployee")->getHeight());
		
		// 상점 아이템 목록
		// 텍스트 박스
		DIALOGMANAGER->makeTextBox(getMemDC(), 20, 80, WINSIZE_X / 2 - 20, 300, 255);
		// 구매 판매 버튼
		IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _buySellButton[_sell].left, _buySellButton[_sell].top,
			_buySellButton[_sell].right - _buySellButton[_sell].left, _buySellButton[_sell].bottom - _buySellButton[_sell].top,
			0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
		IMAGEMANAGER->findImage("ShopButton")->render(getMemDC(), _buySellButton[!_sell].left, _buySellButton[!_sell].top,
			_buySellButton[!_sell].right - _buySellButton[!_sell].left, _buySellButton[!_sell].bottom - _buySellButton[!_sell].top,
			0, 0, IMAGEMANAGER->findImage("ShopButton")->getWidth(), IMAGEMANAGER->findImage("ShopButton")->getHeight());
		FONTMANAGER->textOut(getMemDC(), (_buySellButton[0].left + _buySellButton[0].right) / 2, _buySellButton[0].top, "가을체", 20, 100, "구입", strlen("구입"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), (_buySellButton[1].left + _buySellButton[1].right) / 2, _buySellButton[1].top, "가을체", 20, 100, "판매", strlen("판매"), RGB(255, 255, 255));
		// 구매 아이템 목록
		if(!_sell)
		{
			SetTextAlign(getMemDC(), TA_LEFT);
			for (auto it = _saleList.begin(); it != _saleList.end(); ++it)
			{
				IMAGEMANAGER->findImage((*it).first)->render(getMemDC(), 30, 
					_buySellButton[0].bottom + 10 + (IMAGEMANAGER->findImage((*it).first)->getHeight() * 1.5 + 2) * (it - _saleList.begin()),
					IMAGEMANAGER->findImage((*it).first)->getWidth() * 1.5, IMAGEMANAGER->findImage((*it).first)->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage((*it).first)->getWidth(), IMAGEMANAGER->findImage((*it).first)->getHeight());
				char itemInfo[50];
				wsprintf(itemInfo, (*it).first.c_str());
				FONTMANAGER->textOut(getMemDC(), 80, 125 + 39 * (it - _saleList.begin()), "가을체", 20, 100,
					itemInfo, strlen(itemInfo), RGB(255, 255, 255));
				SetTextAlign(getMemDC(), TA_RIGHT);
				wsprintf(itemInfo, (*it).second.c_str());
				strcat_s(itemInfo, " Eld");
				FONTMANAGER->textOut(getMemDC(), 300, 125 + 39 * (it - _saleList.begin()), "가을체", 20, 100,
					itemInfo, strlen(itemInfo), RGB(255, 255, 255));
				SetTextAlign(getMemDC(), TA_LEFT);
				// 아이템 수량 결정하는 버튼과 개수 출력하는 영역
				IMAGEMANAGER->findImage("UpButton")->render(getMemDC(), 400 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5, 
					125 + 39 * (it - _saleList.begin()),
					IMAGEMANAGER->findImage("UpButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("UpButton")->getHeight() * 1.5, 
					0, 0, IMAGEMANAGER->findImage("UpButton")->getWidth(), IMAGEMANAGER->findImage("UpButton")->getHeight());
				IMAGEMANAGER->findImage("ItemNum")->render(getMemDC(), 420 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5,
					125 + 39 * (it - _saleList.begin()), IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5, 
					IMAGEMANAGER->findImage("ItemNum")->getHeight() * 1.5, 0, 0, IMAGEMANAGER->findImage("ItemNum")->getWidth(), IMAGEMANAGER->findImage("ItemNum")->getHeight());
				IMAGEMANAGER->findImage("DownButton")->render(getMemDC(), 420, 125 + 39 * (it - _saleList.begin()),
					IMAGEMANAGER->findImage("DownButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("DownButton")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("DownButton")->getWidth(), IMAGEMANAGER->findImage("DownButton")->getHeight());
			}
		}
		IMAGEMANAGER->findImage("SlideUpButton")->render(getMemDC(), WINSIZE_X / 2 - 30, _buySellButton[0].bottom + 10);
		IMAGEMANAGER->findImage("SlideDownButton")->render(getMemDC(), WINSIZE_X / 2 - 30, 345 - IMAGEMANAGER->findImage("SlideDownButton")->getHeight());
		
		// eld
		DIALOGMANAGER->makeTextBox(getMemDC(), 100, 390, WINSIZE_X / 2 - 100, 120, 200);
		// 결정 버튼
		if (_decisionButton.second)
		{
			IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _decisionButton.first.left, _decisionButton.first.top,
				_decisionButton.first.right - _decisionButton.first.left, _decisionButton.first.bottom - _decisionButton.first.top,
				0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
		}
		else {
			IMAGEMANAGER->findImage("ShopButton")->render(getMemDC(), _decisionButton.first.left, _decisionButton.first.top,
				_decisionButton.first.right - _decisionButton.first.left, _decisionButton.first.bottom - _decisionButton.first.top,
				0, 0, IMAGEMANAGER->findImage("ShopButton")->getWidth(), IMAGEMANAGER->findImage("ShopButton")->getHeight());
		}
		SetTextAlign(getMemDC(), TA_CENTER);
		FONTMANAGER->textOut(getMemDC(), (_decisionButton.first.left + _decisionButton.first.right) / 2, _decisionButton.first.top, "가을체", 20, 100, "결   정", strlen("결   정"), RGB(255, 255, 255));
		SetTextAlign(getMemDC(), TA_LEFT);
	}

	// 맨 밑 텍스트박스
	DIALOGMANAGER->makeTextBox(getMemDC(), 0, WINSIZE_Y - 200, WINSIZE_X, 200, 200);
	// 파티 캐릭터 이미지 출력
	if(_order.test(0))
	{
		for(int i = 0; i < 10; i++)
		{
			IMAGEMANAGER->findImage("Empty")->render(getMemDC(), WINSIZE_X / 12 * (i + 1), WINSIZE_Y - 200 / 3 * 2, WINSIZE_X / 12, WINSIZE_X / 12,
				0, 0, IMAGEMANAGER->findImage("Empty")->getWidth(), IMAGEMANAGER->findImage("Empty")->getHeight());
		}
	}
	else if (_order.test(1))
	{

	}

	if (_order.none())
	{
		IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _exitButton.left, _exitButton.top, IMAGEMANAGER->findImage("PressButton")->getWidth() * 0.5f, IMAGEMANAGER->findImage("PressButton")->getHeight() * 0.5f,
			0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
	}
	else
	{
		IMAGEMANAGER->findImage("ShopButton")->render(getMemDC(), _exitButton.left, _exitButton.top, _exitButton.right - _exitButton.left, _exitButton.bottom - _exitButton.top,
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
