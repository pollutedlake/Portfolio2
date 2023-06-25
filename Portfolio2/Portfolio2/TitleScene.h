#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _titleBG;
public :
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);
	void release(void);

	TitleScene() {}
	virtual ~TitleScene() {}
};

