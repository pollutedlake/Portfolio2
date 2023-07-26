#pragma once
#include "Character.h"
#include "Obstacle.h"
#include "Camera.h"

class TurnSystem2
{
private:
	vector<Object*> _objectList;
	vector<Character*> _charList;
	Character* _curChar;
	Camera* _camera;
	int _frame;

public:
	HRESULT init(Camera* camera);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void addCharacter(Character* character, int dir, POINT tilePos, int turnOrder);
	void addObject(Object* object);

	TurnSystem2() {}
	~TurnSystem2() {}
};

