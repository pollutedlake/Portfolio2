#pragma once
#include "GameNode.h"

class ShopScene : public GameNode
{
private:
	int _frame;
	RECT _shopButtons[4];
	RECT _exitButton;
	bitset<50> _order;
	char* _shopText[4] = {"��������", "������", "�뺴���", "����"};
	RECT _buySellButton[2];
	pair<RECT, bool> _decisionButton;
	bool _sell;
	vector<pair<string, string>> _saleList;
	vector<int> _itemN;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	ShopScene() {}
	~ShopScene() {}
};

