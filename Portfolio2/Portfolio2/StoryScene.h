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
	GImage* _vermontSherazade;
	GImage* _redImage;
	GImage* _saladin;

	RECT _dialogRC[3];

	StoryDialog _storyDialog[20];
	int _frame;
	int _typing;
	int _vermontSherazadeIndex;
	int _saladinIndex;
	int _dialogIndex;
	char* _soundList[22];
	int _soundIndex;
	int _backGroundIndex;
	int _playTime;
	int _startFadeIn;
	bool _speakFinish;
	bool _fadeWhite;
	bool _fadeIn;
	int _fadeRedStart;
	int _fadeWhiteFrame;
	int _speakStartFrame;

	DialogData* _dialogData;
	vector<StoryData*> _storyDataList;
	int _stopDialogIndex;
	char _text[256];
	int _objectIndex;
	bool _fadeOut;
	int _fadeStartFrame;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void dialog(string charName, LPCWSTR* printStringArr, int length, int arrSize, int dialogType);

	StoryScene() {}
	~StoryScene() {}
};

