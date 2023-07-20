#pragma once
#include "Saladin.h"
class PlayerSoldier	: public Saladin
{
private:
	vector<POINT> _movableTiles;
	vector<POINT> _attackableTiles;
	bool _cameraShake;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos);

	void setCameraShake(bool cameraShake) { _cameraShake = cameraShake; }

	void searchMovable(int map[][60], int rowN, int colN);

	vector<POINT> getMovableTiles() { return _movableTiles; }
	vector<POINT> getAttackableTiles() { return _attackableTiles; }
	bool isCameraShake() { return _cameraShake; }

	PlayerSoldier() {}
	virtual ~PlayerSoldier() {}
};

