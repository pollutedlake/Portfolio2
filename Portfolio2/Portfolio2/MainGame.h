#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	HBITMAP title, oldBitmap;
	HBITMAP backDCBitmap, backDCOldBitmap;
	HDC memDC;
	HDC backDC[2];
	int backDCIndex;
	RECT rc;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};