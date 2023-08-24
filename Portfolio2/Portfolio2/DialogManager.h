#pragma once
#include "SingletonBase.h"

class DialogManager : public SingletonBase<DialogManager>
{
private:

public:
	HRESULT init(void);
	void release(void);

	void makeTextBox(HDC hdc, int left, int top, int width, int height, BYTE alpha);

	DialogManager() {}
	~DialogManager() {}
};

