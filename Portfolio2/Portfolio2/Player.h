#pragma once
#include "Character.h"

class Player : public Character
{
private:
	bool _cameraShake;
	string _playerName;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos);

	string getPlayerName() { return _playerName; }

	Player(string playerName) { _playerName = playerName; }
	~Player() {}
};

