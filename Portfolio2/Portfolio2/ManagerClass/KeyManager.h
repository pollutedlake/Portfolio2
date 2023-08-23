#pragma once
#include "../FrameWork/DesignPattern/SingletonBase.h"

// ��ü ���� ��ȯ -> ���� ��� / �����

#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;


public:
	// �ʱ�ȭ
	HRESULT init(void);

	// Ű�� �ѹ��� ���ȴ���
	bool isOnceKeyDown(int key);
	// �ѹ� ������ �������
	bool isOnceKeyUp(int key);
	// Ű�� ��� ���� �ִ���
	bool isStayKeyDown(int key);
	// ���Ű
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	KeyManager();
	~KeyManager();
};
