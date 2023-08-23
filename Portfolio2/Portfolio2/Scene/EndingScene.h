#pragma once
#include "../FrameWork/GameNode/GameNode.h"

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
	GImage* _whiteImg;
	GImage* _blackImg;
	GImage* _saladin;
	GImage* _brothersImg;
	GImage* _vermont;
	GImage* _pipe;
	GImage* _slashRight;
	
	vector<GImage*> _backGroundImg;

	RECT _dialogRC;
	bitset<4> _fade;
	unsigned int _fadeStartTime;
	unsigned int _fadeEndTime;
	unsigned int _playTime;

	Dialog _dialogs[3];
	int _typingLetterN;
	int _currentDialog;
	int _frame;
	int _index;
	int _curBGIndex;
	int _saladinIndex;
	int _brothersIndex;
	bool _showDialog;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void fadeOutWhite(int startTime, int curTime, int endTime);
	void fadeInWhite(int startTime, int curTime, int endTime);
	void fadeOutBlack(int startTime, int curTime, int endTime);
	void fadeInBlack(int startTime, int curTime, int endTime);

	void dialog(string charName, LPCWSTR* printStringArr, int _typingLetterN, int arrSize);

	EndingScene() {}
	~EndingScene() {}
};

