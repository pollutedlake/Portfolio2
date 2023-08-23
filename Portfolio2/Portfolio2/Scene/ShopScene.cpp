#include "../FrameWork/PCH/Stdafx.h"
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
	_saleList.clear();
	_saleList.push_back(DATAMANAGER->findItem("자마드 아그니"));
	_saleList.push_back(DATAMANAGER->findItem("브리트라"));
	_saleList.push_back(DATAMANAGER->findItem("돌격소총"));
	_saleList.push_back(DATAMANAGER->findItem("스나이퍼 건"));
	_saleList.push_back(DATAMANAGER->findItem("테슈브"));
	_saleList.push_back(DATAMANAGER->findItem("벽력궁"));
	_partyList = DATAMANAGER->getPartyData();
	_priceSum = 0;
	for (int i = 0; i < _saleList.size(); i++)
	{
		_itemN.push_back(0);
		RECT rt = { 400 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5 , 125 + 39 * i,
			400 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5 + IMAGEMANAGER->findImage("UpButton")->getWidth() * 1.5, 125 + 39 * i + IMAGEMANAGER->findImage("UpButton")->getHeight() * 1.5 };
		RECT rt2 = { 420, rt.top, 420 + IMAGEMANAGER->findImage("DownButton")->getWidth() * 1.5, rt.bottom };
		_itemNumButton.push_back(make_pair(rt, false));
		_itemNumButton.push_back(make_pair(rt2, false));
	}
	for (int i = 0; i < _partyList.size(); i++)
	{
		_charChoiceRT[i].left = WINSIZE_X / 12 * (i + 1);
		_charChoiceRT[i].top = WINSIZE_Y - 200 / 3 * 2;
		_charChoiceRT[i].right = _charChoiceRT[i].left + WINSIZE_X / 12;
		_charChoiceRT[i].bottom = _charChoiceRT[i].top + WINSIZE_X / 12;
	}
	for (int i = 0; i < 5; i++)
	{
		_equipmentRT[i].left = WINSIZE_X / 6 + 15 + IMAGEMANAGER->findImage("없음")->getWidth() * 1.5;
		_equipmentRT[i].top = _shopButtons[0].top + 160 + WINSIZE_X / 12 + (2 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5) * i;
		_equipmentRT[i].right = _equipmentRT[i].left + WINSIZE_X / 3 - 20 - (IMAGEMANAGER->findImage("없음")->getWidth() * 1.5);
		_equipmentRT[i].bottom = _equipmentRT[i].top + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5;
	}
	for (int i = 5; i < 20; i++)
	{
		_equipmentRT[i].left = WINSIZE_X / 2 + 50 + 10 + IMAGEMANAGER->findImage("없음")->getWidth() * 1.5;
		_equipmentRT[i].top = 80 + 10 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5 * ((i - 5));
		_equipmentRT[i].right = _equipmentRT[i].left + 250 - 15 - IMAGEMANAGER->findImage("없음")->getWidth() * 1.5;
		_equipmentRT[i].bottom = _equipmentRT[i].top + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5;
	}
	_frame = 0;
	return S_OK;
}

void ShopScene::update(void)
{
	_frame++;
	SOUNDMANAGER->update();
	if (_frame == 1)
	{
		SOUNDMANAGER->playSoundFMOD("ShopSceneBG");
		getInven();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// Exit를 누르면
		if (PtInRect(&_exitButton, _ptMouse))
		{
			if (_order.test(0))
			{
				_order = _order >> 1;
			}
			else
			{
				_order.reset();
				_order.set(0);
			}
			IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _exitButton.left, _exitButton.top, IMAGEMANAGER->findImage("PressButton")->getWidth() * 0.5f, IMAGEMANAGER->findImage("PressButton")->getHeight() * 0.5f,
				0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
			_priceSum = 0;
			for (int i = 0; i < _itemN.size(); i++)
			{
				_itemN[i] = 0;
			}
			SOUNDMANAGER->playSoundFMOD("Button");
		}
		// 처음화면일 때
		if(_order.test(0))
		{
			// 상점을 고르면
			if (PtInRect(&_shopButtons[1], _ptMouse))
			{
				_order = _order << 1;
				getInven();
				_sell = false;
				SOUNDMANAGER->playSoundFMOD("Select");
			}
			// 맨 처음 화면에서 캐릭터 사진 클릭 시
			for (int i = 0; i < _partyList.size(); i++)
			{
				if(PtInRect(&_charChoiceRT[i], _ptMouse))
				{

					_order = _order << 2;
					_selectChar = i;
					SOUNDMANAGER->playSoundFMOD("Select");
				}
			}
		}
		// 상점화면일 때
		else if (_order.test(1))
		{
			for(int i = 0; i < 2; i++)
			{
				if (PtInRect(&_buySellButton[i], _ptMouse))
				{
					if (_sell != i)
					{
						_priceSum = 0;
						for (int i = 0; i < _itemN.size(); i++)
						{
							_itemN[i] = 0;
						}
						SOUNDMANAGER->playSoundFMOD("Select");
					}
					_sell = i;
				}
			}

			// 결정버튼을 눌렀을 때
			if (PtInRect(&_decisionButton.first, _ptMouse))
			{
				SOUNDMANAGER->playSoundFMOD("Select");
				_decisionButton.second = true;
				if (!_sell)
				{
					DATAMANAGER->setEld(DATAMANAGER->getEld() - _priceSum);
					for (int i = 0; i < _itemN.size(); i++)
					{
						if (_itemN[i] != 0)
						{
							DATAMANAGER->buyItem(_saleList[i]->_name, _itemN[i], _saleList[i]);
							_itemN[i] = 0;
						}
					}
				}
				else
				{
					DATAMANAGER->setEld(DATAMANAGER->getEld() + _priceSum);
					int inventorySize = DATAMANAGER->getInventory().size();
					for (int i = 0; i < inventorySize; i++)
					{
						if (_itemN[i] != 0)
						{
							DATAMANAGER->sellItem(_invenList[i]->_name, _itemN[i]);
							_itemN[i] = 0;
						}
					}
				}
				_priceSum = 0;
				getInven();
			}

			// 구매할 아이템 개수를 변경하는 버튼을 눌렀을 때
			for (int i = 0; i < 2 * (_sell ? _invenList.size() : _saleList.size()); i++)
			{
				if (PtInRect(&_itemNumButton[i].first, _ptMouse))
				{
					_itemNumButton[i].second = true;
					if (i % 2 == 0)
					{
						if (!_sell || (DATAMANAGER->findItemInven(_invenList[i / 2]->_name)).second != _itemN[i / 2])
						{
							_itemN[i / 2]++;
							if (_sell)
							{
								_priceSum += _invenList[i / 2]->_price;
							}
							else
							{
								_priceSum += _saleList[i / 2]->_price;
							}
						}
					}
					else
					{
						if (_itemN[i / 2] > 0)
						{
							_itemN[i / 2]--;
							if (_sell)
							{
								_priceSum -= _invenList[i / 2]->_price;
							}
							else
							{
								_priceSum -= _saleList[i / 2]->_price;
							}
						}
					}
					SOUNDMANAGER->playSoundFMOD("Select");
				}
			}
		}
		else if (_order.test(2))
		{
			for (int i = 0; i < 5; i++)
			{
				if (PtInRect(&_equipmentRT[i], _ptMouse))
				{
					_order = _order << 1;
					_selectEquipment = i;
					getInven(i);
					SOUNDMANAGER->playSoundFMOD("Select");
				}
			}
			for (int i = 0; i < _partyList.size(); i++)
			{
				if (PtInRect(&_charChoiceRT[i], _ptMouse))
				{
					_selectChar = i;
					SOUNDMANAGER->playSoundFMOD("Select");
				}
			}
		}
		else if (_order.test(3))
		{
			for (int i = 5; i < 6 + _invenList.size(); i++)
			{
				if (PtInRect(&_equipmentRT[i], _ptMouse))
				{
					_order = _order >> 1;
					if (i == 5)
					{
						DATAMANAGER->equipItem("없음", _selectChar, _selectEquipment);
					}
					else
					{
						DATAMANAGER->equipItem(_invenList[i - 6]->_name, _selectChar, _selectEquipment);
					}
					SOUNDMANAGER->playSoundFMOD("Select");
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_order.test(3))
		{
			_order = _order >> 1;
		}
		else if (_order.test(2))
		{
			_order.reset();
			_order.set(0);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		// 처음 화면일 때 마을 나가서 월드맵 씬으로 이동
		if (_order.none())
		{
			SOUNDMANAGER->stopAllSoundFMOD();
			SCENEMANAGER->changeScene("WorldMap");
		}
		if (_decisionButton.second)
		{
			_decisionButton.second = false;
		}
		for (int i = 0; i < _itemNumButton.size(); i++)
		{
			if (_itemNumButton[i].second)
			{
				_itemNumButton[i].second = false;
			}
		}
	}
}

void ShopScene::render(void)
{
	IMAGEMANAGER->findImage("ShopSceneBG")->render(getMemDC());
	// 상단의 마을 정보
	if(!_order.test(1))
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
	}
	if(_order.test(0) || _order.none())
	{	
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
		shopRender(getMemDC());
	}
	else if (_order.test(2))
	{
		showCharacterStat(getMemDC(), _selectChar, WINSIZE_X / 6, _shopButtons[0].top);
	}
	else if (_order.test(3))
	{
		showInventory(getMemDC(), _selectEquipment, WINSIZE_X / 2 + 50, 80);
	}

	// 맨 밑 텍스트박스
	DIALOGMANAGER->makeTextBox(getMemDC(), 0, WINSIZE_Y - 200, WINSIZE_X, 200, 200);
	// 파티 캐릭터 이미지 출력
	if(!_order.test(1))
	{
		IMAGEMANAGER->findImage("Pattern1")->render(getMemDC(), WINSIZE_X / 8, WINSIZE_Y - 168, WINSIZE_X * 3 / 8, IMAGEMANAGER->findImage("Pattern1")->getHeight() * 1.5,
			0, 0, IMAGEMANAGER->findImage("Pattern1")->getWidth(), IMAGEMANAGER->findImage("Pattern1")->getHeight());
		IMAGEMANAGER->findImage("Pattern2")->render(getMemDC(), WINSIZE_X / 2, WINSIZE_Y - 153, WINSIZE_X * 3 / 8, IMAGEMANAGER->findImage("Pattern1")->getHeight() * 1.5,
			0, 0, IMAGEMANAGER->findImage("Pattern2")->getWidth(), IMAGEMANAGER->findImage("Pattern2")->getHeight());
		for(int i = 0; i < 10; i++)
		{
			if (i < _partyList.size())
			{
				char character[256];
				wsprintf(character, _partyList[i]->_name.c_str());
				strcat_s(character, "Mini");
				IMAGEMANAGER->findImage(character)->render(getMemDC(), WINSIZE_X / 12 * (i + 1), WINSIZE_Y - 200 / 3 * 2, WINSIZE_X / 12, WINSIZE_X / 12,
					0, 0, IMAGEMANAGER->findImage(character)->getWidth(), IMAGEMANAGER->findImage(character)->getHeight());
			}
			else
			{
				IMAGEMANAGER->findImage("Empty")->render(getMemDC(), WINSIZE_X / 12 * (i + 1), WINSIZE_Y - 200 / 3 * 2, WINSIZE_X / 12, WINSIZE_X / 12,
					0, 0, IMAGEMANAGER->findImage("Empty")->getWidth(), IMAGEMANAGER->findImage("Empty")->getHeight());
			}
		}
	}
	else if (_order.test(1))
	{
		FONTMANAGER->textOut(getMemDC(), 20, WINSIZE_Y - 180, "가을체", 20, 100, "[무기점주인]", strlen("[무기점주인]"), RGB(0, 255, 0));
		FONTMANAGER->textOut(getMemDC(), 20, WINSIZE_Y - 160, "가을체", 20, 100, "어서오세요. 무엇을 찾으시나요?", strlen("어서오세요. 무엇을 찾으시나요?"), RGB(255, 255, 255));
	}

	if (_order.none())
	{
		IMAGEMANAGER->findImage("PressButton")->render(getMemDC(), _exitButton.left, _exitButton.top, _exitButton.right - _exitButton.left, _exitButton.bottom - _exitButton.top,
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

void ShopScene::showCharacterStat(HDC hdc, int index, int left, int top)
{
	// 상태창 TextBox
	DIALOGMANAGER->makeTextBox(hdc, left, top, WINSIZE_X / 3, WINSIZE_Y - 200 - top - 5, 200);

	// 캐릭터 이미지
	wsprintf(_text, _partyList[index]->_name.c_str());
	strcat_s(_text, "Mini");
	IMAGEMANAGER->findImage(_text)->render(hdc, left + 5, top + 5, WINSIZE_X / 12, WINSIZE_X / 12, 
		0, 0, IMAGEMANAGER->findImage(_text)->getWidth(), IMAGEMANAGER->findImage(_text)->getHeight());

	// 이름, 소속, 직업
	wsprintf(_text, _partyList[index]->_name.c_str());
	FONTMANAGER->textOut(hdc, left + 10 + WINSIZE_X / 12, top + 10, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	wsprintf(_text, _partyList[index]->_belong.c_str());
	FONTMANAGER->textOut(hdc, left + 10 + WINSIZE_X / 12, top + 35, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	IMAGEMANAGER->findImage("StatusButton")->render(hdc, left + 5 + WINSIZE_X / 12, top + 55, WINSIZE_X / 4 - 10, 30, 
		0, 0, IMAGEMANAGER->findImage("StatusButton")->getWidth(), IMAGEMANAGER->findImage("StatusButton")->getHeight());
	wsprintf(_text, _partyList[index]->_class.c_str());
	FONTMANAGER->textOut(hdc, left + 10 + WINSIZE_X / 12, top + 60, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));

	//	HP, SOUL, EXP
	FONTMANAGER->textOut(hdc, left + 5, top + 10 + WINSIZE_X / 12, "가을체", 20, 100, "HP", strlen("HP"), RGB(255, 255, 255));
	IMAGEMANAGER->findImage("StatusBar")->render(hdc, left + 10, top + 30 + WINSIZE_X / 12, WINSIZE_X / 3 - 15, IMAGEMANAGER->findImage("StatusBar")->getHeight(),
		0, 0, IMAGEMANAGER->findImage("StatusBar")->getWidth(), IMAGEMANAGER->findImage("StatusBar")->getHeight());
	IMAGEMANAGER->findImage("StatusHpBar")->render(hdc, left + 10, top + 30 + WINSIZE_X / 12, 
		(WINSIZE_X / 3 - 15) * _partyList[index]->_status[CURHP] / _partyList[index]->_status[MAXHP], IMAGEMANAGER->findImage("StatusBar")->getHeight(),
		0, 0, IMAGEMANAGER->findImage("StatusHpBar")->getWidth(), IMAGEMANAGER->findImage("StatusHpBar")->getHeight());

	FONTMANAGER->textOut(hdc, left + 5, top + 35 + WINSIZE_X / 12, "가을체", 20, 100, "SOUL", strlen("SOUL"), RGB(255, 255, 255));
	IMAGEMANAGER->findImage("StatusBar")->render(hdc, left + 10, top + 55 + WINSIZE_X / 12, WINSIZE_X / 3 - 15, IMAGEMANAGER->findImage("StatusBar")->getHeight(),
		0, 0, IMAGEMANAGER->findImage("StatusBar")->getWidth(), IMAGEMANAGER->findImage("StatusBar")->getHeight());
	IMAGEMANAGER->findImage("StatusSoulBar")->render(hdc, left + 10, top + 55 + WINSIZE_X / 12,
		(WINSIZE_X / 3 - 15) * _partyList[index]->_status[CURSOUL] / _partyList[index]->_status[MAXSOUL], IMAGEMANAGER->findImage("StatusBar")->getHeight(),
		0, 0, IMAGEMANAGER->findImage("StatusSoulBar")->getWidth(), IMAGEMANAGER->findImage("StatusSoulBar")->getHeight());

	FONTMANAGER->textOut(hdc, left + 5, top + 60 + WINSIZE_X / 12, "가을체", 20, 100, "EXP", strlen("EXP"), RGB(255, 255, 255));
	IMAGEMANAGER->findImage("StatusBar")->render(hdc, left + 10, top + 80 + WINSIZE_X / 12, WINSIZE_X / 3 - 15, IMAGEMANAGER->findImage("StatusBar")->getHeight(),
		0, 0, IMAGEMANAGER->findImage("StatusBar")->getWidth(), IMAGEMANAGER->findImage("StatusBar")->getHeight());
	IMAGEMANAGER->findImage("StatusExpBar")->render(hdc, left + 10, top + 80 + WINSIZE_X / 12,
		(WINSIZE_X / 3 - 15) * _partyList[index]->_status[CUREXP] / 100, IMAGEMANAGER->findImage("StatusBar")->getHeight(),
		0, 0, IMAGEMANAGER->findImage("StatusExpBar")->getWidth(), IMAGEMANAGER->findImage("StatusExpBar")->getHeight());

	SetTextAlign(hdc, TA_RIGHT);
	wsprintf(_text, "%d/%d", _partyList[index]->_status[CURHP], _partyList[index]->_status[MAXHP]);
	FONTMANAGER->textOut(hdc, left + WINSIZE_X / 3 - 5, top + 10 + WINSIZE_X / 12, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	wsprintf(_text, "%d/%d", _partyList[index]->_status[CURSOUL], _partyList[index]->_status[MAXSOUL]);
	FONTMANAGER->textOut(hdc, left + WINSIZE_X / 3 - 5, top + 35 + WINSIZE_X / 12, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	wsprintf(_text, "%d/100", _partyList[index]->_status[CUREXP]);
	FONTMANAGER->textOut(hdc, left + WINSIZE_X / 3 - 5, top + 60 + WINSIZE_X / 12, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	SetTextAlign(hdc, TA_LEFT);

	// Str, Skill, Ac, Dex, Luck, Mr, Int, Spd, Wtp
	FONTMANAGER->textOut(hdc, left + 5, top + 85 + WINSIZE_X / 12, "가을체", 20, 100, "Str", strlen("Str"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 5, top + 110 + WINSIZE_X / 12, "가을체", 20, 100, "Skill", strlen("Skill"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 5, top + 135 + WINSIZE_X / 12, "가을체", 20, 100, "Ac", strlen("Ac"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 125, top + 85 + WINSIZE_X / 12, "가을체", 20, 100, "Dex", strlen("Dex"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 125, top + 110 + WINSIZE_X / 12, "가을체", 20, 100, "Luck", strlen("Luck"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 125, top + 135 + WINSIZE_X / 12, "가을체", 20, 100, "Mr", strlen("Mr"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 245, top + 85 + WINSIZE_X / 12, "가을체", 20, 100, "Int", strlen("Int"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 245, top + 110 + WINSIZE_X / 12, "가을체", 20, 100, "Spd", strlen("Spd"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, left + 245, top + 135 + WINSIZE_X / 12, "가을체", 20, 100, "Wtp", strlen("Wtp"), RGB(255, 255, 255));

	SetTextAlign(getMemDC(), TA_RIGHT);
	for (int i = 0; i < 9; i++)
	{
		wsprintf(_text, "%d", _partyList[index]->_status[i + STR]);
		FONTMANAGER->textOut(hdc, left + WINSIZE_X / 3 - 5 - 120 * (2 - (i % 3)), top + 85 + WINSIZE_X / 12 + 25 * (i / 3), "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	}
	SetTextAlign(getMemDC(), TA_LEFT);

	// 장비
	for (int i = 0; i < 5; i++)
	{
		IMAGEMANAGER->findImage(_partyList[index]->_equipment[i]->_name)->render(hdc, left + 5, top + 160 + WINSIZE_X / 12 + (2 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5) * i,
			IMAGEMANAGER->findImage("없음")->getWidth() * 1.5, IMAGEMANAGER->findImage("없음")->getHeight() * 1.5,
			0, 0, IMAGEMANAGER->findImage("없음")->getWidth(), IMAGEMANAGER->findImage("없음")->getHeight());
		if (PtInRect(&_equipmentRT[i], _ptMouse))
		{
			IMAGEMANAGER->findImage("SkillButtonActive")->alphaRender(hdc, left + 15 + IMAGEMANAGER->findImage("없음")->getWidth() * 1.5, top + 160 + WINSIZE_X / 12 + (2 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5) * i,
				WINSIZE_X / 3 - 20 - (IMAGEMANAGER->findImage("없음")->getWidth() * 1.5), IMAGEMANAGER->findImage("없음")->getWidth() * 1.5,
				0, 0, IMAGEMANAGER->findImage("SkillButtonActive")->getWidth(), IMAGEMANAGER->findImage("SkillButtonActive")->getHeight(), 200);
		}
		IMAGEMANAGER->findImage("StatusButton")->render(hdc, left + 15 + IMAGEMANAGER->findImage("없음")->getWidth() * 1.5, top + 160 + WINSIZE_X / 12 + (2 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5) * i,
			WINSIZE_X / 3 - 20 - (IMAGEMANAGER->findImage("없음")->getWidth() * 1.5), IMAGEMANAGER->findImage("없음")->getWidth() * 1.5,
			0, 0, IMAGEMANAGER->findImage("StatusButton")->getWidth(), IMAGEMANAGER->findImage("StatusButton")->getHeight());
		SetTextAlign(hdc, TA_CENTER);
		wsprintf(_text, _partyList[index]->_equipment[i]->_name.c_str());
		FONTMANAGER->textOut(hdc, left + 15 + IMAGEMANAGER->findImage("없음")->getWidth() * 1.5 + (WINSIZE_X / 3 - 20 - (IMAGEMANAGER->findImage("없음")->getWidth() * 1.5)) / 2,
			top + 160 + WINSIZE_X / 12 + (2 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5) * i + 10, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	}
}

void ShopScene::showInventory(HDC hdc, int index, int left, int top)
{
	DIALOGMANAGER->makeTextBox(hdc, left, top, 250, 20 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5 * (_invenList.size() + 1), 200);
	IMAGEMANAGER->findImage("없음")->render(hdc, left + 10, top + 10, IMAGEMANAGER->findImage("없음")->getWidth() * 1.5, IMAGEMANAGER->findImage("없음")->getHeight() * 1.5,
		0, 0, IMAGEMANAGER->findImage("없음")->getWidth(), IMAGEMANAGER->findImage("없음")->getHeight());
	if (PtInRect(&_equipmentRT[5], _ptMouse))
	{
		IMAGEMANAGER->findImage("SkillButtonActive")->alphaRender(hdc, _equipmentRT[5].left, _equipmentRT[5].top,
			_equipmentRT[5].right - _equipmentRT[5].left, _equipmentRT[5].bottom - _equipmentRT[5].top,
			0, 0, IMAGEMANAGER->findImage("SkillButtonActive")->getWidth(), IMAGEMANAGER->findImage("SkillButtonActive")->getHeight(), 200);
	}
	FONTMANAGER->textOut(hdc, left + 10 + IMAGEMANAGER->findImage("없음")->getWidth() * 1.5 + 10, top + 10 + 10, "가을체",
		20, 100, "해제", strlen("해제"), RGB(255, 255, 255));
	for (int i = 0; i < _invenList.size(); i++)
	{
		if (PtInRect(&_equipmentRT[6 + i], _ptMouse))
		{
			IMAGEMANAGER->findImage("SkillButtonActive")->alphaRender(hdc, _equipmentRT[6 + i].left, _equipmentRT[i + 6].top, 
				_equipmentRT[6 + i].right - _equipmentRT[6 + i].left, _equipmentRT[i + 6].bottom - _equipmentRT[i + 6].top,
				0, 0, IMAGEMANAGER->findImage("SkillButtonActive")->getWidth(), IMAGEMANAGER->findImage("SkillButtonActive")->getHeight(), 200);
		}
		IMAGEMANAGER->findImage(_invenList[i]->_name)->render(hdc, left + 10, top + 10 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5 * (i + 1), 
			IMAGEMANAGER->findImage("없음")->getWidth() * 1.5, IMAGEMANAGER->findImage("없음")->getHeight() * 1.5,
			0, 0, IMAGEMANAGER->findImage("없음")->getWidth(), IMAGEMANAGER->findImage("없음")->getHeight());
		wsprintf(_text, _invenList[i]->_name.c_str());
		FONTMANAGER->textOut(hdc, left + 10 + IMAGEMANAGER->findImage("없음")->getWidth() * 1.5 + 10, top + 10 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5 * (i + 1) + 10, 
			"가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
		wsprintf(_text, "%d", DATAMANAGER->findItemInven(_invenList[i]->_name).second);
		SetTextAlign(hdc, TA_RIGHT);
		FONTMANAGER->textOut(hdc, left + 250 - 10, top + 10 + IMAGEMANAGER->findImage("없음")->getHeight() * 1.5 * (i + 1) + 10,
			"가을체", 20, 100, _text, strlen(_text), RGB(255, 0, 0));
		SetTextAlign(hdc, TA_LEFT);
	}
}

void ShopScene::shopRender(HDC hdc)
{
	DIALOGMANAGER->makeTextBox(hdc, 10, 10, 300, 50, 200);
	SetTextAlign(hdc, TA_CENTER);
	FONTMANAGER->textOut(hdc, 10 + 150, 20, "가을체", 30, 100, "무기상점", strlen("무기상점"), RGB(255, 255, 255));
	IMAGEMANAGER->findImage("ShopEmployee")->render(hdc, WINSIZE_X - IMAGEMANAGER->findImage("ShopEmployee")->getWidth() * 1.4 - 20,
		WINSIZE_Y - 80 - IMAGEMANAGER->findImage("ShopEmployee")->getHeight() * 1.4, IMAGEMANAGER->findImage("ShopEmployee")->getWidth() * 1.4,
		IMAGEMANAGER->findImage("ShopEmployee")->getHeight() * 1.4, 0, 0, IMAGEMANAGER->findImage("ShopEmployee")->getWidth(), IMAGEMANAGER->findImage("ShopEmployee")->getHeight());

	// 상점 아이템 목록
	// 텍스트 박스
	DIALOGMANAGER->makeTextBox(hdc, 20, 80, WINSIZE_X / 2 - 20, 300, 255);
	// 구매 판매 버튼
	IMAGEMANAGER->findImage("PressButton")->render(hdc, _buySellButton[_sell].left, _buySellButton[_sell].top,
		_buySellButton[_sell].right - _buySellButton[_sell].left, _buySellButton[_sell].bottom - _buySellButton[_sell].top,
		0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
	IMAGEMANAGER->findImage("ShopButton")->render(hdc, _buySellButton[!_sell].left, _buySellButton[!_sell].top,
		_buySellButton[!_sell].right - _buySellButton[!_sell].left, _buySellButton[!_sell].bottom - _buySellButton[!_sell].top,
		0, 0, IMAGEMANAGER->findImage("ShopButton")->getWidth(), IMAGEMANAGER->findImage("ShopButton")->getHeight());
	FONTMANAGER->textOut(hdc, (_buySellButton[0].left + _buySellButton[0].right) / 2, _buySellButton[0].top, "가을체", 20, 100, "구입", strlen("구입"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, (_buySellButton[1].left + _buySellButton[1].right) / 2, _buySellButton[1].top, "가을체", 20, 100, "판매", strlen("판매"), RGB(255, 255, 255));
	SetTextAlign(hdc, TA_LEFT);

	// 구매 아이템 목록
	if (!_sell)
	{
		SetTextAlign(hdc, TA_LEFT);
		for (auto it = _saleList.begin(); it != _saleList.end(); ++it)
		{
			IMAGEMANAGER->findImage((*it)->_name)->render(hdc, 30,
				_buySellButton[0].bottom + 10 + (IMAGEMANAGER->findImage((*it)->_name)->getHeight() * 1.5 + 2) * (it - _saleList.begin()),
				IMAGEMANAGER->findImage((*it)->_name)->getWidth() * 1.5, IMAGEMANAGER->findImage((*it)->_name)->getHeight() * 1.5,
				0, 0, IMAGEMANAGER->findImage((*it)->_name)->getWidth(), IMAGEMANAGER->findImage((*it)->_name)->getHeight());
			char itemInfo[50];
			wsprintf(itemInfo, (*it)->_name.c_str());
			FONTMANAGER->textOut(hdc, 80, 125 + 39 * (it - _saleList.begin()), "가을체", 20, 100,
				itemInfo, strlen(itemInfo), RGB(255, 255, 255));
			SetTextAlign(hdc, TA_RIGHT);
			wsprintf(itemInfo, "%d", (*it)->_price);
			strcat_s(itemInfo, " Eld");
			FONTMANAGER->textOut(hdc, 300, 125 + 39 * (it - _saleList.begin()), "가을체", 20, 100,
				itemInfo, strlen(itemInfo), RGB(255, 255, 255));
			wsprintf(_text, "(%2d)", (DATAMANAGER->findItemInven((*it)->_name)).second);
			FONTMANAGER->textOut(hdc, 350, 125 + 39 * (it - _saleList.begin()), "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
			SetTextAlign(hdc, TA_LEFT);

			// 아이템 수량 결정하는 버튼과 개수 출력하는 영역
			if (_itemNumButton[(it - _saleList.begin()) * 2].second)
			{
				IMAGEMANAGER->findImage("UpButtonPress")->render(hdc, _itemNumButton[(it - _saleList.begin()) * 2].first.left, _itemNumButton[(it - _saleList.begin()) * 2].first.top,
					IMAGEMANAGER->findImage("UpButtonPress")->getWidth() * 1.5, IMAGEMANAGER->findImage("UpButtonPress")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("UpButtonPress")->getWidth(), IMAGEMANAGER->findImage("UpButtonPress")->getHeight());
			}
			else
			{
				IMAGEMANAGER->findImage("UpButton")->render(hdc, _itemNumButton[(it - _saleList.begin()) * 2].first.left, _itemNumButton[(it - _saleList.begin()) * 2].first.top,
					IMAGEMANAGER->findImage("UpButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("UpButton")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("UpButton")->getWidth(), IMAGEMANAGER->findImage("UpButton")->getHeight());
			}
			IMAGEMANAGER->findImage("ItemNum")->render(hdc, 420 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5,
				125 + 39 * (it - _saleList.begin()), IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5,
				IMAGEMANAGER->findImage("ItemNum")->getHeight() * 1.5, 0, 0, IMAGEMANAGER->findImage("ItemNum")->getWidth(), IMAGEMANAGER->findImage("ItemNum")->getHeight());
			if (_itemNumButton[(it - _saleList.begin()) * 2 + 1].second)
			{
				IMAGEMANAGER->findImage("DownButtonPress")->render(hdc, _itemNumButton[(it - _saleList.begin()) * 2 + 1].first.left, _itemNumButton[(it - _saleList.begin()) * 2 + 1].first.top,
					IMAGEMANAGER->findImage("DownButtonPress")->getWidth() * 1.5, IMAGEMANAGER->findImage("DownButtonPress")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("DownButtonPress")->getWidth(), IMAGEMANAGER->findImage("DownButtonPress")->getHeight());
			}
			else
			{
				IMAGEMANAGER->findImage("DownButton")->render(hdc, _itemNumButton[(it - _saleList.begin()) * 2 + 1].first.left, _itemNumButton[(it - _saleList.begin()) * 2 + 1].first.top,
					IMAGEMANAGER->findImage("DownButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("DownButton")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("DownButton")->getWidth(), IMAGEMANAGER->findImage("DownButton")->getHeight());
			}
			wsprintf(_text, "%d", _itemN[(it - _saleList.begin())]);
			SetTextAlign(hdc, TA_RIGHT);
			FONTMANAGER->textOut(hdc, 420, 125 + 39 * (it - _saleList.begin()), "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 0));
			SetTextAlign(hdc, TA_LEFT);
		}
	}
	// 판매아아템 목록
	else
	{
		SetTextAlign(hdc, TA_LEFT);
		for (auto it = _invenList.begin(); it != _invenList.end(); ++it)
		{
			IMAGEMANAGER->findImage((*it)->_name)->render(hdc, 30,
				_buySellButton[0].bottom + 10 + (IMAGEMANAGER->findImage((*it)->_name)->getHeight() * 1.5 + 2) * (it - _invenList.begin()),
				IMAGEMANAGER->findImage((*it)->_name)->getWidth() * 1.5, IMAGEMANAGER->findImage((*it)->_name)->getHeight() * 1.5,
				0, 0, IMAGEMANAGER->findImage((*it)->_name)->getWidth(), IMAGEMANAGER->findImage((*it)->_name)->getHeight());
			char itemInfo[50];
			wsprintf(itemInfo, (*it)->_name.c_str());
			FONTMANAGER->textOut(hdc, 80, 125 + 39 * (it - _invenList.begin()), "가을체", 20, 100,
				itemInfo, strlen(itemInfo), RGB(255, 255, 255));
			SetTextAlign(hdc, TA_RIGHT);
			wsprintf(itemInfo, "%d", (*it)->_price);
			strcat_s(itemInfo, " Eld");
			FONTMANAGER->textOut(hdc, 300, 125 + 39 * (it - _invenList.begin()), "가을체", 20, 100,
				itemInfo, strlen(itemInfo), RGB(255, 255, 255));
			wsprintf(_text, "(%2d)", (DATAMANAGER->findItemInven((*it)->_name)).second);
			FONTMANAGER->textOut(hdc, 350, 125 + 39 * (it - _invenList.begin()), "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
			SetTextAlign(hdc, TA_LEFT);

			// 아이템 수량 결정하는 버튼과 개수 출력하는 영역
			if (_itemNumButton[(it - _invenList.begin()) * 2].second)
			{
				IMAGEMANAGER->findImage("UpButtonPress")->render(hdc, _itemNumButton[(it - _invenList.begin()) * 2].first.left, _itemNumButton[(it - _invenList.begin()) * 2].first.top,
					IMAGEMANAGER->findImage("UpButtonPress")->getWidth() * 1.5, IMAGEMANAGER->findImage("UpButtonPress")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("UpButtonPress")->getWidth(), IMAGEMANAGER->findImage("UpButtonPress")->getHeight());
			}
			else
			{
				IMAGEMANAGER->findImage("UpButton")->render(hdc, _itemNumButton[(it - _invenList.begin()) * 2].first.left, _itemNumButton[(it - _invenList.begin()) * 2].first.top,
					IMAGEMANAGER->findImage("UpButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("UpButton")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("UpButton")->getWidth(), IMAGEMANAGER->findImage("UpButton")->getHeight());
			}
			IMAGEMANAGER->findImage("ItemNum")->render(hdc, 420 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5,
				125 + 39 * (it - _invenList.begin()), IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5,
				IMAGEMANAGER->findImage("ItemNum")->getHeight() * 1.5, 0, 0, IMAGEMANAGER->findImage("ItemNum")->getWidth(), IMAGEMANAGER->findImage("ItemNum")->getHeight());
			if (_itemNumButton[(it - _invenList.begin()) * 2 + 1].second)
			{
				IMAGEMANAGER->findImage("DownButtonPress")->render(hdc, _itemNumButton[(it - _invenList.begin()) * 2 + 1].first.left, _itemNumButton[(it - _invenList.begin()) * 2 + 1].first.top,
					IMAGEMANAGER->findImage("DownButtonPress")->getWidth() * 1.5, IMAGEMANAGER->findImage("DownButtonPress")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("DownButtonPress")->getWidth(), IMAGEMANAGER->findImage("DownButtonPress")->getHeight());
			}
			else
			{
				IMAGEMANAGER->findImage("DownButton")->render(hdc, _itemNumButton[(it - _invenList.begin()) * 2 + 1].first.left, _itemNumButton[(it - _invenList.begin()) * 2 + 1].first.top,
					IMAGEMANAGER->findImage("DownButton")->getWidth() * 1.5, IMAGEMANAGER->findImage("DownButton")->getHeight() * 1.5,
					0, 0, IMAGEMANAGER->findImage("DownButton")->getWidth(), IMAGEMANAGER->findImage("DownButton")->getHeight());
			}
			wsprintf(_text, "%d", _itemN[(it - _invenList.begin())]);
			SetTextAlign(hdc, TA_RIGHT);
			FONTMANAGER->textOut(hdc, 420, 125 + 39 * (it - _invenList.begin()), "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 0));
			SetTextAlign(hdc, TA_LEFT);
		}
	}

	// 스크롤
	IMAGEMANAGER->findImage("ScrollUpButton")->render(hdc, WINSIZE_X / 2 - 30, _buySellButton[0].bottom + 10);
	IMAGEMANAGER->findImage("ScrollDownButton")->render(hdc, WINSIZE_X / 2 - 30, 345 - IMAGEMANAGER->findImage("ScrollDownButton")->getHeight());
	FillRect(hdc, &RectMake(WINSIZE_X / 2 - 30, _buySellButton[0].bottom + 10 + IMAGEMANAGER->findImage("ScrollUpButton")->getHeight(),
		IMAGEMANAGER->findImage("ScrollUpButton")->getWidth(),
		345 - IMAGEMANAGER->findImage("ScrollDownButton")->getHeight() - (_buySellButton[0].bottom + 10 + IMAGEMANAGER->findImage("ScrollUpButton")->getHeight())), CreateSolidBrush(RGB(49, 49, 147)));
	IMAGEMANAGER->findImage("ScrollButton")->render(hdc, WINSIZE_X / 2 - 30, _buySellButton[0].bottom + 10 + IMAGEMANAGER->findImage("ScrollUpButton")->getHeight());

	// eld
	DIALOGMANAGER->makeTextBox(hdc, 100, 390, WINSIZE_X / 2 - 100, 120, 200);
	FONTMANAGER->textOut(hdc, 120, 405, "가을체", 20, 100, "소지금액", strlen("소지금액"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, 120, 440, "가을체", 20, 100, "물품총액", strlen("물품총액"), RGB(255, 255, 255));
	FONTMANAGER->textOut(hdc, 120, 475, "가을체", 20, 100, "잔      액", strlen("잔      액"), RGB(255, 255, 255));
	SetTextAlign(hdc, TA_RIGHT);
	wsprintf(_text, "%d Eld", DATAMANAGER->getEld());
	FONTMANAGER->textOut(hdc, 400 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5 - 20, 405, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	wsprintf(_text, "%d Eld", _priceSum);
	FONTMANAGER->textOut(hdc, 400 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5 - 20, 440, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	wsprintf(_text, "%d Eld", _sell ? DATAMANAGER->getEld() +_priceSum : DATAMANAGER->getEld() - _priceSum);
	FONTMANAGER->textOut(hdc, 400 - IMAGEMANAGER->findImage("ItemNum")->getWidth() * 1.5 - 20, 475, "가을체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	SetTextAlign(hdc, TA_LEFT);
	// 결정 버튼
	if (_decisionButton.second)
	{
		IMAGEMANAGER->findImage("PressButton")->render(hdc, _decisionButton.first.left, _decisionButton.first.top,
			_decisionButton.first.right - _decisionButton.first.left, _decisionButton.first.bottom - _decisionButton.first.top,
			0, 0, IMAGEMANAGER->findImage("PressButton")->getWidth(), IMAGEMANAGER->findImage("PressButton")->getHeight());
	}
	else {
		IMAGEMANAGER->findImage("ShopButton")->render(hdc, _decisionButton.first.left, _decisionButton.first.top,
			_decisionButton.first.right - _decisionButton.first.left, _decisionButton.first.bottom - _decisionButton.first.top,
			0, 0, IMAGEMANAGER->findImage("ShopButton")->getWidth(), IMAGEMANAGER->findImage("ShopButton")->getHeight());
	}
	SetTextAlign(hdc, TA_CENTER);
	FONTMANAGER->textOut(hdc, (_decisionButton.first.left + _decisionButton.first.right) / 2, _decisionButton.first.top, "가을체", 20, 100, "결   정", strlen("결   정"), RGB(255, 255, 255));
	SetTextAlign(hdc, TA_LEFT);
}

void ShopScene::getInven()
{
	_invenList.clear();
	for (auto item : DATAMANAGER->getInventory())
	{
		_invenList.push_back(item.second.first);
	}
}

void ShopScene::getInven(int type)
{
	_invenList.clear();
	for (auto item : DATAMANAGER->getInventory())
	{
		switch (type)
		{
		case 0:
			if (item.second.first->_type == WEAPON)
			{
				_invenList.push_back(item.second.first);
			}
			break;
		case 1:
			if (item.second.first->_type == WEAPON)
			{
				_invenList.push_back(item.second.first);
			}
			break;
		case 2:
			if (item.second.first->_type == ARMOR)
			{
				_invenList.push_back(item.second.first);
			}
			break;
		case 3:
			if (item.second.first->_type == SHOES)
			{
				_invenList.push_back(item.second.first);
			}
			break;
		case 4:
			if (item.second.first->_type == ACCESSORY)
			{
				_invenList.push_back(item.second.first);
			}
			break;
		}
	}
}
