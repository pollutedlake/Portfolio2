#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Soldier.h"
#include "Player.h"
#include "Obstacle.h"
#include "Camera.h"
#include "Skill.h"

// Ÿ������
#define PLAYER 0
#define ENEMY 1
#define CANTMOVE 2
#define MOVABLE 3

struct cmp2 
{
	bool operator()(pair<POINT, int> node1, pair<POINT, int> node2)
	{
		if (node1.second > node2.second)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class TurnSystem2
{
private:
	FILE* _fp;							// �� ���̺��� ���� ������

	priority_queue<pair<POINT, int>, vector<pair<POINT, int>>, cmp2> _closedList;	// A* Ž���� ��� ���
	vector<POINT> _route;				// �ִ� ���

	vector<POINT> _movableTiles;		// ������ �� �ִ� Ÿ�ϵ�
	vector<POINT> _attackableTiles;		// ������ �� �ִ� Ÿ�ϵ�
	vector<POINT> _skillableTiles;		// ��ų ����

	vector<Object*> _objectList;		// ������Ʈ ���
	vector<Character*> _charList;		// ĳ���� ���

	Character* _curChar;				// ���� ĳ����
	Enemy* _enemy;
	Camera* _camera;					// ī�޶�
	Skill* _skill;						// ��ų ����Ʈ
	HDC _tileCheckDC;					// GetPixel�� �� �� ���� Ÿ������ Ȯ���ϱ� ���� Image DC
	int _frame;

	int _rowN;							// ���� Ÿ�� ��
	int _colN;							// ���� Ÿ�� ��

	RECT _actionButtons[4];				// �׼� ��ư
	RECT _skillButtons[50];				// ��ų ��ư
	RECT _preferenceButtons[7];			// ȯ�漳�� ��ư
	POINT _exPtMouse;					// ���콺 ���� ��ġ
	bitset<4> _actionChoice;			// �׼� ���� ���� 
	char* _skillName;					// ������ ��ų �̸�
	int _skillIdx;						// ������ ��ų �ε���

	bool _isClear;						// ���� Ŭ���� ����
	bool _isFail;						// ���ӿ��� ����
	bool _start;						// ��Ƽ ĳ���� ��ġ �� ���� ����
	bool _preference;					// ȯ�漳��

public:
	HRESULT init(Camera* camera, HDC hdc, int rowN, int colN);
	void release(void);
	void update(POINT cursorTile);
	void render(HDC hdc);

	Character* getCurChar() { return _curChar; }
	// Ŭ���� ��ġ�� ĳ���� ã��
	Character* findCharacter(POINT cursorPoint);
	// ��Ƽ ĳ���� �̸����� ĳ���� ã��
	Character* findCharacter(string playerName);

	// ��Ƽ ĳ���� ��ġ �� ĳ���� ��Ͽ� �߰�
	void addCharacter(Character* character, int dir, POINT tilePos, int turnOrder);
	// ��Ƽ ĳ���� ��ġ ��� �� ĳ���� ��Ͽ��� ����
	Player* deleteCharacter(string name);
	// ������Ʈ ��Ͽ� ������Ʈ �߰�
	void addObject(Object* object);

	// ������Ʈ ��� ����
	void sortObjectList();
	// Ÿ���� ������ ���
	int checkTile(POINT tilePos);
	// ������ �� �ִ� Ÿ�� Ž��
	void searchMovableTiles();
	// ��ų Ÿ������ ��ų ���� Ž��
	void searchSkillableTiles(int skillType);
	// ��� �ƹ��͵� ���ϰ� �ִ� �������� Ȯ��
	bool checkAllDoingNot();
	POINT findPlayer();
	// ���� ��
	void nextTurn();
	// �� ���̺�
	void saveGame();
	void setCharList(vector<Character*> charList) {_charList = charList; for(int i = 0; i <_charList.size(); i++) { _objectList.push_back(_charList[i]);}}

	void setStart(bool start);

	// A*�� �ִܰ�� Ž��
	vector<POINT> astar(POINT start, POINT dest); 
	// �޸���ƽ �� ���
	int heuristic(POINT node, POINT dest);
	// �Ÿ� ���
	int distance(POINT start, POINT node);

	TurnSystem2() {}
	~TurnSystem2() {}
};

