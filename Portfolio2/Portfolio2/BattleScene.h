#pragma once
#include "GameNode.h"
#include "Camera.h"
#include "TurnSystem2.h"
#include "Object.h"
#include "Character.h"
#include "Saladin.h"
#include "Soldier.h"
#include "Obstacle.h"

class BattleScene : public GameNode
{
private:
	Camera* _camera;
	TurnSystem2* _turnSystem;
	int _frame;
	POINT _cameraPos;
	POINT _cursorTile;
	POINT _cursorTileLT;
	bool _debug;
	char _text[50];
	char _bgImg[256];
	char _checkBGImg[256];
	int _showMiniStatusFrame;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	BattleScene() {}
	~BattleScene() {}
};

