#pragma once
#include "SingletonBase.h"


#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;


public:
	// 초기화
	HRESULT init(void);

	// 키가 한번만 눌렸는지
	bool isOnceKeyDown(int key);
	// 한번 누르고 띄었는지
	bool isOnceKeyUp(int key);
	// 키가 계속 눌려 있는지
	bool isStayKeyDown(int key);
	// 토글키
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	KeyManager();
	~KeyManager();
};

