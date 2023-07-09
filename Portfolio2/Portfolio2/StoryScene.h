#pragma once
#include "GameNode.h"

struct StoryDialog
{
	string _speaker;
	int _dialogN;
	LPCWSTR _script[10];
	int _dialogType;
};

class StoryScene : public GameNode
{
private:
	GImage* _storyBG;
	GImage* _speakerImg;
	GImage* _textBoxImg;
	RECT _dialogRC[3];

	StoryDialog _storyDialog[50];
	int _frame;
	int _typing;
	int _dialogIndex;
	int _playTime;
	int _startFadeIn;
	bool _speakFinish;
	bool _fadeIn;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void dialog(string charName, LPCWSTR* printStringArr, int length, int arrSize, int dialogType);

	StoryScene() {}
	~StoryScene() {}
};

