#pragma once
#pragma comment(lib, "strmiids")
#pragma comment(lib, "comsuppw.lib")
#include <dshow.h>
#include <comutil.h>
#include "GameNode.h"
#include <Mfidl.h>

class TitleScene : public GameNode
{
private:
	GImage* _titleBG;				// 타이틀 화면 배경
	GImage* _titleName;				// 타이틀 게임 제목
	GImage* _titleEFX2;				 
	GImage* _titleEFX4;				 
	GImage* _titleEFX3;				 
	GImage* _titleEFX1;				
	GImage* _titleButtons;			// 타이틀 버튼들
	GImage* _cursor;

	int _frame;
	int _deltaTime;
	int _activeButton;			// 마우스가 올라가 있는 버튼
	RECT _buttonsRC[4];
	int _fadeOutStartFrame;
	bool _fadeOut;
	bool _videoShow;
	bool _load;

	RECT rcSrc, rcDest;
	IGraphBuilder* _pGraphBuilder;
	IMediaControl* _pMediaControl;
	IMediaEvent* _pMediaEvent;
	IMediaSeeking* _pMediaSeeking;
	IVMRWindowlessControl* _pWindowless;

public :
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	HRESULT InitWindowlessVMR(HWND hwndApp, IGraphBuilder* pGraph, IVMRWindowlessControl** ppWc);
	bool LoadVideo(LPCWSTR videoFilePath);
	HRESULT PlayIntroVideo(LPTSTR szMovie, HINSTANCE hInstance);

	TitleScene() {}
	virtual ~TitleScene() {}
};

