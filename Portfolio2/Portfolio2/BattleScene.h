#pragma once
#include "GameNode.h"

class BattleScene : public GameNode
{
private:

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	BattleScene() {}
	~BattleScene() {}
};

