#pragma once
#include "Character.h"

class Saladin : public Character
{
private:
	vector<POINT> _movableTiles;
	vector<POINT> _attackableTiles;
	vector<POINT> _skillableTiles;
	bool _cameraShake;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos);

	void setCameraShake(bool cameraShake) { _cameraShake = cameraShake; }

	void searchMovable(int map[][60], int rowN, int colN);

	vector<POINT> getMovableTiles() {return _movableTiles;}
	vector<POINT> getAttackableTiles() {return _attackableTiles;}
	vector<POINT> getSkillableTiles(int map[][60], int rowN, int colN, char skillName[]);
	bool isCameraShake() { return _cameraShake; }

	Saladin() {}
	virtual ~Saladin() {}
};

