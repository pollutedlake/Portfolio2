#pragma once
#include "../GImage/GImage.h"

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	// 백버퍼 + 더블 버퍼 이미지 얻기
	GImage* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	// 순수가상 함수
	//virtual void IFunction() abstract;

	// 메인 프로시저
	// LRESULT : 콜백의 반환형으로 많이 사용이 된다.
	// ㄴ 메세지 처리를 마친후에 OS에게 신호를 주기 위한 값
	// ㄴ 스위치문에서 각 메세지에 대한 처리값을 -1, 0, 1로 운영체제에 어떤 작업을 해야 하는지 알려주는 역할을 한다. 기본적으로 0이 리턴되면 모든 메세지가 처리되었다는 것을 의미한다.
	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}
};

