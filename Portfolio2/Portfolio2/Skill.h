#pragma once
#include "Character.h"
#include "Saladin.h"
#include "Player.h"

// ��ȭ������ ���� ���
struct IcePillar
{
	int _frame = -1;
	bool _broken = false;
	POINT _position;
};

class Skill
{
private:
	char* _skillName;
	int _frame;
	int _startFrame;
	bool _isFinish;										// ��ų�� �������� Ȯ��
	Character* _curChar;								// ��ų �� ĳ����
	Character* _targetChar;								// Ÿ�� ĳ����
	vector<Character*> _charList;						// ��ų ���� ���� ĳ���͸��
	vector<POINT> _snow;								// ��ȭ������ ��
	bitset<4> _order;									// ��ų ����
	bitset<20> _orderOrder;								// ��ų ���� �� ����
	vector<pair<POINT, POINT>> _efxPos;					// ��ȭ������ ����Ʈ �Ѿƴٴϴ� ����
	vector<pair<pair<float, float>, float>> _dust1Pos;	// ��ȭ������ ����1
	vector<pair<pair<float, float>, float>> _dust2;		// ��ȭ������ ����2
	vector<IcePillar> _icePillars;
	pair<int, bool> _crackedEarth[4][12];				// ������ �� ���
	POINT _stonePos[4][12][5];							// ������ �� �����ϰ� ���� ����
	vector<pair<int, int>> _volcano;					// �� �ؿ� ����� ȭ��
	vector<vector<pair<int, int>>> _bigStones;			// ȭ�� �����ϰ� ������ ū ����
	pair<float, float> _wolfPos[2];						// ������ȥ ����

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc, POINT position, POINT cameraPos, int tileWidth, int tileHeight);
	void release(void);
	int getOrder();

	bool isFinish() {return _isFinish;}
	// ��ų ����
	void start(vector<Character*> charList, Character* curChar, char* skillName);
};

