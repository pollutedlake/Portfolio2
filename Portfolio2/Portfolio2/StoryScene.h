#pragma once
#include "GameNode.h"
class StoryScene : public GameNode
{
private:
	int _frame;
	int _typingSpeed;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StoryScene() {}
	~StoryScene() {}
};

