#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _titleBG;				// Ÿ��Ʋ ȭ�� ���
	GImage* _titleName;				// Ÿ��Ʋ ���� ����
	GImage* _titleEFX2;				 
	GImage* _titleEFX4;				 
	GImage* _titleEFX3;				 
	GImage* _titleEFX1;				
	GImage* _titleButtons;			// Ÿ��Ʋ ��ư��
	GImage* _cursor;

	int _frame;
	int _deltaTime;
	int _activeButton;			// ���콺�� �ö� �ִ� ��ư
	RECT _buttonsRC[4];
	int _fadeOutStartFrame;
	bool _fadeOut;

public :
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	TitleScene() {}
	virtual ~TitleScene() {}
};

