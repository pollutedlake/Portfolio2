#pragma once
#include "GameNode.h"

struct TimeData
{
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

class LoadScene : public GameNode
{
private:
	int _frame;
	char _text[256];
	int _scenarioN[9];

	RECT _loadButton[9];
	TimeData _time[9];
	FILE* _saveFP;
	FILE* _loadFP;
	int _selectButton;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void saveGame();

	LoadScene() {}
	~LoadScene() {}
};

