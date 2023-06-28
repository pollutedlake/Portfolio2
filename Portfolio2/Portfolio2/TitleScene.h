#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _titleBG;	// 타이틀 화면 배경 이미지
	GImage* _startGame;
	GImage* _loadGame;
	GImage* _tutorial;
	GImage* _exit;
	RECT _startGameRC;
	RECT _loadGameRC;
	RECT _tutorialRC;
	RECT _exitRC;

public :
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);
	void release(void);

	TitleScene() {}
	virtual ~TitleScene() {}
};

