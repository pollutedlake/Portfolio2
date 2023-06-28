#include "Stdafx.h"
#include "GameNode.h"

// 객체지향 프로그래밍 -> 설계의 기반한 효율적인 방법론과 관리 쳬계

//POINT _ptMouse;

HRESULT GameNode::init(void)
{
    // 타이머 초기화
    SetTimer(_hWnd, 1, 1000 / 60 , NULL);

    RND->init();
    KEYMANAGER->init();

    this->setDoubleBuffer();
    // 함수가 성공적으로 실행 되었음을 알린다.
    return S_OK;
}

void GameNode::setDoubleBuffer(void)
{
	_doubleBuffer = new GImage;
	_doubleBuffer->init(WINSIZE_X, WINSIZE_Y);
}

void GameNode::release(void)
{
    // 동적할당과 같이 삭제하지 않고 종료하면 메모리 줄줄줄...
    KillTimer(_hWnd, 1);

    RND->releaseSingleton();
    KEYMANAGER->releaseSingleton();
}

void GameNode::update(void)
{
    InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(HDC hdc)
{
    //! Do Nothing
}

// 메인 프로시저
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        this->render(hdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;
    case WM_DESTROY:                // 소멸자
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
