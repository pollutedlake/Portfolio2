#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _titleBG;	// Ÿ��Ʋ ȭ�� ��� �̹���
	GImage* _titleName;
	GImage* _titleEFX2;
	GImage* _titleEFX1;
	int _frame;
	int _deltaTime;

public :
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);
	void release(void);

	TitleScene() {}
	virtual ~TitleScene() {}
};

