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
	bool _sell;
	vector<pair<string, string>> _saleList;
	vector<CharacterData*> _partyList;
	vector<int> _itemN;
	RECT _charChoiceRT[10];
	char _text[256];
	int _selectChar;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	void showCharacterStat(HDC hdc, int index, int left, int top);


	ShopScene() {}
	~ShopScene() {}
};

