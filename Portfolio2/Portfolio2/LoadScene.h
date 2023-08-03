#pragma once
#include "GameNode.h"
class LoadScene : public GameNode
{
private:
	int _frame;
	char _text[256];
	pair<FILE*, int> _fp[9];
	RECT _loadButton[9];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LoadScene() {}
	~LoadScene() {}
};

