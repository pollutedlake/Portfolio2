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

	// ����� + ���� ���� �̹��� ���
	GImage* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	// �������� �Լ�
	//virtual void IFunction() abstract;

	// ���� ���ν���
	// LRESULT : �ݹ��� ��ȯ������ ���� ����� �ȴ�.
	// �� �޼��� ó���� ��ģ�Ŀ� OS���� ��ȣ�� �ֱ� ���� ��
	// �� ����ġ������ �� �޼����� ���� ó������ -1, 0, 1�� �ü���� � �۾��� �ؾ� �ϴ��� �˷��ִ� ������ �Ѵ�. �⺻������ 0�� ���ϵǸ� ��� �޼����� ó���Ǿ��ٴ� ���� �ǹ��Ѵ�.
	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}
};

