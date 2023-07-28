#pragma once
#include "GameNode.h"
#include "Camera.h"
#include "TurnSystem2.h"
#include "Object.h"
#include "Character.h"
#include "Player.h"
#include "Saladin.h"
#include "Soldier.h"
#include "Obstacle.h"

class BattleScene : public GameNode
{
private:
	Camera* _camera;
	TurnSystem2* _turnSystem;
	vector<CharacterData*> _party;
	int _frame;
	POINT _cameraPos;
	POINT _cursorTile;
	POINT _cursorTileLT;
	pair<RECT, bool> _launchRT[10];
	RECT _launchButton[4];
	vector<POINT> _launchTile;
	bool _debug;
	bool _launch;
	char _text[50];
	char _bgImg[256];
	char _checkBGImg[256];
	int _showMiniStatusFrame;
	int _selectCharIndex;
	bitset<4> _launchOrder;
	POINT _exPtMouse;
	

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	BattleScene() {}
	~BattleScene() {}
};

