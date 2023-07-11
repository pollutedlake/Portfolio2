#pragma once
#include "GImage.h"

#pragma region
/*
����ü���� ���α׷���(OOP)

-�ڵ��� ���뼺�� ���� �ڵ��� ������ �����ϴ�.

-�������� �ֱ� ������ �ŷڼ��� ���� ���α׷����� �����ϰ� �Ѵ�.

����ü���� 4�� Ư¡

ĸ��ȭ / ��� / ������ / �߻�

1. ĸ��ȭ

-��ü�� �Ӽ��� ��ȣ�ϱ� ���� Ű����

2. ���

-��ü���⿡���� ����� ������ ���� ������ ��üȭ �Ǵ� ���� �ǹ��Ѵ�.

-���뼺 ��� + Ȯ�强 ��� + ���������� ��� + ���α׷� ������ ���� ���ص��� ���� ���� �ִ�.

3. ������

-�ϳ��� ��ü�� ���� ���·� ��ȭ�ϴ°��� �ǹ��Ѵ�.
	���������̵�

4. �߻�ȭ

-�������� �κа� Ư�� Ư���� �и� �� �����Ͽ� ������ �� �籸���ϴ� ���� �ǹ��Ѵ�.


����ü���� 5�� ���� ��Ģ [SOLID]

1. SRP (���� å���� ��Ģ)
�����յ��� ���߰� �������� ������
����� / �������̵��� ����ϸ� �������� ��������.

2. OCP (��������� ��Ģ)
���ڽ��� Ȯ�忡�� �����ְ� �ֺ��� ��ȭ�� ���ؼ��� ���� �־�� �Ѵ�.

3. LSP (�����ں� ġȯ�� ��Ģ)
������ Ÿ���� ������ �ڽ��� ����� ���� Ÿ������ ��ü�� �����ؾ� �Ѵ�.

4. ISP (�������̽� �и��� ��Ģ)
��Ŭ���̾�Ʈ�� �ڽ��� ������� �ʴ� �Լ� �Ǵ� �޼��忡 ���� ���踦 ������ �ȵȴ�.

5. DIP (�������� ������ ��Ģ)
- �ڽź��� ���ϱ� ����Ϳ� �����ϸ� �ȵȴ�.
*/
#pragma endregion

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
