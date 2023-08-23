#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class LoadingScene : public GameNode
{
private:
	string _nextScene;
	int _loadingImgIndex;
	int _frame;

public:
	HRESULT init(string nextScene);
	void release(void);
	void update(void);
	void render(void);

	LoadingScene() {}
	~LoadingScene() {}
};

