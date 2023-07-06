#pragma once
#include "GameNode.h"

struct Dialog
{
	string _speaker;
	LPCWSTR _dialog[3];
};

class EndingScene : public GameNode
{
private:
	GImage* _textBoxImg;
	GImage* _vermontImg;
	GImage* _speakerImg;
	GImage* _backGroundImg;

	RECT _dialogRC;

	Dialog _dialogs[3];
	int _frame;
	int _typingLetterN;
	int _currentDialog;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void dialog(string charName, LPCWSTR* printStringArr, int _typingLetterN, int arrSize);

	EndingScene() {}
	~EndingScene() {}
};

