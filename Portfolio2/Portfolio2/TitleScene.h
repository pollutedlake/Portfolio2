#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _titleBG;				// 타이틀 화면 배경
	GImage* _titleName;				// 타이틀 게임 제목
	GImage* _titleEFX2;				 
	GImage* _titleEFX1;				
	GImage* _titleButtons;			// 타이틀 버튼들
	GImage* _cursor;

	int _frame;
	int _deltaTime;
	int _activeButton;			// 마우스가 올라가 있는 버튼
	RECT _buttonsRC[4];

public :
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	TitleScene() {}
	virtual ~TitleScene() {}
};

