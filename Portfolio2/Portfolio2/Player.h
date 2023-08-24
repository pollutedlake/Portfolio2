#pragma once
#include "Character.h"

class Player : public Character
{
private:
	bool _cameraShake;
	string _playerName;
	vector<pair<char*, int>> _skill;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos);

	void setCameraShake(bool cameraShake) {_cameraShake = cameraShake;}

	string getPlayerName() { return _playerName; }
	bool isCameraShake() { return _cameraShake; }
	vector<pair<char*, int>> getSkill() { return _skill; }

	Player(string playerName, vector<pair<char*, int>> skill) { _playerName = playerName; _skill = skill; }
	~Player() {}
};

