#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include "AStar.h"
#include "Skill.h"

#define CANTMOVE	0
#define MOVABLE		1
#define SALADIN		2
#define ENEMY		3

#define ACTION		0
#define MOVE		1

class TurnSystem
{
private:
	Character* _curChar;			// ���� �� ĳ����
	Enemy* _enemy;
	Saladin* _player;
	AStar* _aStar;					// A*
	vector<Character*> _charList;	// ĳ���� ���
	vector<Object*> _objectList;	// ������Ʈ ���
	bitset<4> _actionChoice;		// �׼� ��ư
	bool _skillChoice;				// ��ų�� ������� ����
	bool _skillRangeChoice;			// ��ų ������ ������� ����
	RECT _actionButtons[4];			// �׼� ��ư
	RECT _skillButtons[3];			// ��ų ��ư
	vector<POINT> _attackTiles;		// ���� ������ Ÿ�ϵ�
	vector<POINT> _skillableTiles;	// ��ų ��� ������ Ÿ�ϵ�
	int _frame;
	bool _isClear;		// Ŭ���� ����
	bool _isFail;		// GameOver ���� ����
	Skill* _skill;
	char* _skillName;

public:
	HRESULT init(void);
	void update(int tileInfo[][60], int rowN, int colN, POINT cursorTile);
	void release(void);
	void render(HDC hdc, int tileHeight, int tileWidth, POINT cameraPos);

	Character* getCurChar() {return _curChar;}

	// ĳ���� ��Ͽ� ĳ���� �߰�
	void addCharacter(Character* character);
	// ������Ʈ ��Ͽ� ������Ʈ �߰�
	void addObject(Object* object);
	// ���� ��
	void nextTurn();
	// ������Ʈ ��� ����
	void sortObjectList();
	// Ŭ���� ��ġ�� �ִ� ĳ����ã��
	Character* findCharacter(POINT cursorPoint);
	bool checkAllDoingNot();

	TurnSystem() {}
	~TurnSystem() {}

};

