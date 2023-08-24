#pragma once
#include "GameNode.h"

class ShopScene : public GameNode
{
private:
	int _frame;
	RECT _shopButtons[4];
	RECT _exitButton;
	bitset<50> _order;
	char* _shopText[4] = {"도구상점", "무기점", "용병길드", "주점"};
	RECT _buySellButton[2];
	pair<RECT, bool> _decisionButton;

	vector<pair<RECT, bool>> _itemNumButton;
	vector<int> _itemN;
	bool _sell;
	vector<ItemData*> _saleList;
	vector<ItemData*> _invenList;
	
	vector<CharacterData*> _partyList;
	RECT _charChoiceRT[10];
	RECT _equipmentRT[20];
	char _text[256];
	int _selectChar;
	int _selectEquipment;
	int _priceSum;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	void showCharacterStat(HDC hdc, int index, int left, int top);
	void showInventory(HDC hdc, int index, int left, int top);
	void shopRender(HDC hdc);
	void getInven();
	void getInven(int type);

	ShopScene() {}
	~ShopScene() {}
};

