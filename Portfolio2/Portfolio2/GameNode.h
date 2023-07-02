#pragma once
#include "GImage.h"

#pragma region
/*
▶객체지향 프로그래밍(OOP)

-코드의 재사용성이 높고 코드의 관리가 용이하다.

-기준점이 있기 때문에 신뢰성이 높은 프로그래밍을 가능하게 한다.

▶객체지향 4대 특징

캡슐화 / 상속 / 다형성 / 추상

1. 캡슐화

-객체의 속성을 보호하기 위한 키워드

2. 상속

-객체지향에서의 상속은 하위로 내려 갈수록 구체화 되는 것을 의미한다.

-재사용성 향상 + 확장성 향상 + 유지보수성 향상 + 프로그램 구조에 대한 이해도를 높일 수가 있다.

3. 다형성

-하나의 객체가 여러 형태로 변화하는것을 의미한다.
	ㄴ오버라이딩

4. 추상화

-공통적인 부분과 특정 특성을 분리 및 추출하여 재조합 및 재구성하는 것을 의미한다.


▶객체지향 5대 설계 원칙 [SOLID]

1. SRP (단일 책임의 원칙)
ㄴ결합도는 낮추고 응집도를 높여라
ㄴ상속 / 오버라이딩을 사용하면 응집도가 높아진다.

2. OCP (개방폐쇄의 원칙)
ㄴ자신의 확장에는 열려있고 주변의 변화에 대해서는 닫혀 있어야 한다.

3. LSP (리스코브 치환의 원칙)
ㄴ하위 타입은 언제나 자신의 기반인 상위 타입으로 교체가 가능해야 한다.

4. ISP (인터페이스 분리의 원칙)
ㄴ클라이언트는 자신이 사용하지 않는 함수 또는 메서드에 의존 관계를 맺으면 안된다.

5. DIP (의존관계 역전의 원칙)
- 자신보다 변하기 쉬운것에 의존하면 안된다.
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

