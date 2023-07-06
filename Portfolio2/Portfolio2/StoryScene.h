#pragma once
#include "GameNode.h"
class StoryScene : public GameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StoryScene() {}
	~StoryScene() {}
};

