#include "Stdafx.h"
#include "GImage.h"

#pragma comment (lib, "msimg32.lib")

GImage::GImage() : _imageInfo(nullptr), _fileName(nullptr), _isTrans(false), _transColor(RGB(0, 0, 0)), _blendImage(NULL)
{

}

HRESULT GImage::init(int width, int height)
{
	// 재초기화 방지하겠다.
	// 혹시 값이 있다면 이상한 짓 하지말고 먼저 release하고 접근해라.
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	/*
		resID = 0;
		hMemDC = NULL;
		hBit = NULL;
		hOBit = NULL;
		width = 0;
		height = 0;
		loadType = LOAD_RESOURCE;
	*/

	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr;

	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	// 리소스를 얻어 오는데 실패했다.
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	// 재초기화 방지하겠다.
	// 혹시 값이 있다면 이상한 짓 하지말고 먼저 release하고 접근해라.
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr;

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new char[len + 1];
	// strcpy -> 인자 1개 더 추가
	// ㄴ 고질적인 문자/문자열에서 사이즈 문제를 해졀한 함수
	// (복사받을 변수, 최대길이, 원본)
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);

	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);

	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::initForAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	// 알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	//_blendFunc.SourceConstantAlpha = 0;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

// 특히 이미지에서는 매우 중요한 함수
void GImage::release(void)
{
	if (_imageInfo)
	{
		// 이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		// 포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		// 투명 Color키 초기화
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}
}

void GImage::render(HDC hdc)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올 때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,						// 복사할 장소의 DC(화면 DC)
			0,							// 복사될 좌표 시작 X
			0,							// 복사될 좌표 시작 Y
			_imageInfo->width,			// 복사될 이미지 가로 크기
			_imageInfo->height,			// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 메모리DC
			0, 0,						// 복사 시작 지점
			_imageInfo->width,			// 복사 영역 가로 크기
			_imageInfo->height,			// 복사 영역 세로 크기
			_transColor					// 복사할때 제외할 색상 (마젠타)
		);
	}
	else
	{
		// ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY : 소스 영역을 영여게 복사한다.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올 때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,						// 복사할 장소의 DC(화면 DC)
			destX,						// 복사될 좌표 시작 X
			destY,						// 복사될 좌표 시작 Y
			_imageInfo->width,			// 복사될 이미지 가로 크기
			_imageInfo->height,			// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 메모리DC
			0, 0,						// 복사 시작 지점
			_imageInfo->width,			// 복사 영역 가로 크기
			_imageInfo->height,			// 복사 영역 세로 크기
			_transColor					// 복사할때 제외할 색상 (마젠타)
		);
	}
	else
	{
		// ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY : 소스 영역을 영여게 복사한다.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올 때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,						// 복사할 장소의 DC(화면 DC)
			destX,						// 복사될 좌표 시작 X
			destY,						// 복사될 좌표 시작 Y
			destWidth,			// 복사될 이미지 가로 크기
			destHeight,			// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 메모리DC
			sourX, sourY,				// 복사 시작 지점
			sourWidth,			// 복사 영역 가로 크기
			sourHeight,			// 복사 영역 세로 크기
			_transColor					// 복사할때 제외할 색상 (마젠타)
		);
	}
	else
	{
		// ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY : 소스 영역을 영여게 복사한다.
		StretchBlt(hdc, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, SRCCOPY);
	}
}

// 이미지 클리핑 : 원본 이미지를 지정해서 가로, 세로 크기를 잘라서 내가 원하는 곳에 렌더
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,						// 복사할 장소의 DC(화면 DC)
			destX,						// 복사될 좌표 시작 X
			destY,						// 복사될 좌표 시작 Y
			sourWidth,			// 복사될 이미지 가로 크기
			sourHeight,			// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,			// 복사될 대상 메모리DC
			sourX, sourY,						// 복사 시작 지점
			sourWidth,			// 복사 영역 가로 크기
			sourHeight,			// 복사 영역 세로 크기
			_transColor					// 복사할때 제외할 색상 (마젠타)
		);
	}
	else
	{
		// ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
		// ㄴ SRCCOPY : 소스 영역을 영여게 복사한다.
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

// 알파렌더
void GImage::alphaRender(HDC hdc, BYTE alpha)
{
	// 알파블렌드 처음 쓰니?
	// ㄴ 사용할 수 있도록 초기화부터 진행한다.
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지 그린다.
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_blendImage->width,
			_blendImage->height,
			hdc,
			0, 0,
			SRCCOPY
		);

		// 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		// 3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지 그린다.
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_blendImage->width,
			_blendImage->height,
			hdc,
			destX, destY,
			SRCCOPY
		);

		// 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		// 3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지 그린다.
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHeight,
			hdc,
			destX, destY,
			SRCCOPY
		);

		// 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor
		);

		// 3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			sourWidth,
			sourHeight,
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHeight,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void GImage::alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지 그린다.
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHeight,
			hdc,
			destX, destY,
			SRCCOPY
		);

		// 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor
		);

		// 3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			destWidth,
			destHeight,
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHeight,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void GImage::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;
	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, hdc, destX, destY, SRCCOPY);
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, 
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void GImage::alphaFrameRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;
	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, destWidth, destHeight, hdc, destX, destY, SRCCOPY);
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		GdiAlphaBlend(hdc, destX, destY, destWidth, destHeight,
			_blendImage->hMemDC, 0, 0, destWidth, destHeight, _blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, destWidth, destHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, 
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void GImage::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사한다.      
		GdiTransparentBlt
		(
			hdc,               //복사할 장소와 DC(화면DC)
			destX,                  //복사될 좌표시작 X 
			destY,                  //복사될 좌표시작 Y
			_imageInfo->frameWidth,      //복사될 이미지 가로크기
			_imageInfo->frameHeight,      //복사될 이미지 세로크기
			_imageInfo->hMemDC,      //복사될 대상 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,               //복사 시작 지점
			_imageInfo->frameWidth,         //복사 영역 가로크기
			_imageInfo->frameHeight,    //복사 영역 세로크기
			_transColor            //복사할때 제외할 색상(마젠타)

		);
	}
	else
	{
		BitBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY
		);
	}
}

void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올 때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,                  // 복사할 장소의 DC(화면 DC)
			destX,                  // 복사될 좌표 시작 X
			destY,                  // 복사될 좌표 시작 Y
			_imageInfo->frameWidth,         // 복사될 이미지 가로 크기
			_imageInfo->frameHeight,         // 복사될 이미지 세로 크기
			_imageInfo->hMemDC,         // 복사될 대상 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,            // 복사 시작 지점
			_imageInfo->frameWidth,         // 복사 영역 가로 크기
			_imageInfo->frameHeight,         // 복사 영역 세로 크기
			_transColor               // 복사할때 제외할 색상 (마젠타)
		);
	}
	else
	{
		StretchBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY
		);
	}
}

void GImage::frameRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	if (_isTrans)
	{
		// GdiTransparentBlt() : 비트맵을 불러올 때 특정 색상을 제외하고 복사한다.
		GdiTransparentBlt
		(
			hdc,                  // 복사할 장소의 DC(화면 DC)
			destX,                  // 복사될 좌표 시작 X
			destY,                  // 복사될 좌표 시작 Y
			destWidth,
			destHeight,
			_imageInfo->hMemDC,         // 복사될 대상 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,            // 복사 시작 지점
			_imageInfo->frameWidth,         // 복사 영역 가로 크기
			_imageInfo->frameHeight,         // 복사 영역 세로 크기
			_transColor               // 복사할때 제외할 색상 (마젠타)
		);
	}
	else
	{
		StretchBlt
		(
			hdc,
			destX,
			destY,
			destWidth,
			destHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY
		);
	}
}
