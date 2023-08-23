#include "../PCH/Stdafx.h"
#include "./GImage.h"

#pragma comment (lib, "msimg32.lib")

GImage::GImage() : _imageInfo(nullptr), _fileName(nullptr), _isTrans(false), _transColor(RGB(0, 0, 0)), _blendImage(NULL)
{

}

HRESULT GImage::init(int width, int height)
{
	// ���ʱ�ȭ �����ϰڴ�.
	// Ȥ�� ���� �ִٸ� �̻��� �� �������� ���� release�ϰ� �����ض�.
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

	// ���ҽ��� ��� ���µ� �����ߴ�.
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
	// ���ʱ�ȭ �����ϰڴ�.
	// Ȥ�� ���� �ִٸ� �̻��� �� �������� ���� release�ϰ� �����ض�.
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
	// strcpy -> ���� 1�� �� �߰�
	// �� �������� ����/���ڿ����� ������ ������ ������ �Լ�
	// (������� ����, �ִ����, ����)
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

	// ���ĺ����� �ɼ�
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

HRESULT GImage::initForAlphaBlend2(void)
{
	HDC hdc = GetDC(_hWnd);

	// ���ĺ����� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	//_blendFunc.SourceConstantAlpha = 0;

	_blendImage2 = new IMAGE_INFO;
	_blendImage2->loadType = LOAD_FILE;
	_blendImage2->resID = 0;
	_blendImage2->hMemDC = CreateCompatibleDC(hdc);
	_blendImage2->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage2->hOBit = (HBITMAP)SelectObject(_blendImage2->hMemDC, _blendImage2->hBit);
	_blendImage2->width = WINSIZE_X;
	_blendImage2->height = WINSIZE_Y;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

// Ư�� �̹��������� �ſ� �߿��� �Լ�
void GImage::release(void)
{
	if (_imageInfo)
	{
		// �̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		// ������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		// ���� ColorŰ �ʱ�ȭ
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
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,						// ������ ����� DC(ȭ�� DC)
			0,							// ����� ��ǥ ���� X
			0,							// ����� ��ǥ ���� Y
			_imageInfo->width,			// ����� �̹��� ���� ũ��
			_imageInfo->height,			// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,			// ����� ��� �޸�DC
			0, 0,						// ���� ���� ����
			_imageInfo->width,			// ���� ���� ���� ũ��
			_imageInfo->height,			// ���� ���� ���� ũ��
			_transColor					// �����Ҷ� ������ ���� (����Ÿ)
		);
	}
	else
	{
		// �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
		// �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,						// ������ ����� DC(ȭ�� DC)
			destX,						// ����� ��ǥ ���� X
			destY,						// ����� ��ǥ ���� Y
			_imageInfo->width,			// ����� �̹��� ���� ũ��
			_imageInfo->height,			// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,			// ����� ��� �޸�DC
			0, 0,						// ���� ���� ����
			_imageInfo->width,			// ���� ���� ���� ũ��
			_imageInfo->height,			// ���� ���� ���� ũ��
			_transColor					// �����Ҷ� ������ ���� (����Ÿ)
		);
	}
	else
	{
		// �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
		// �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,						// ������ ����� DC(ȭ�� DC)
			destX,						// ����� ��ǥ ���� X
			destY,						// ����� ��ǥ ���� Y
			destWidth,			// ����� �̹��� ���� ũ��
			destHeight,			// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,			// ����� ��� �޸�DC
			sourX, sourY,				// ���� ���� ����
			sourWidth,			// ���� ���� ���� ũ��
			sourHeight,			// ���� ���� ���� ũ��
			_transColor					// �����Ҷ� ������ ���� (����Ÿ)
		);
	}
	else
	{
		// �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
		// �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
		StretchBlt(hdc, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, SRCCOPY);
	}
}

// �̹��� Ŭ���� : ���� �̹����� �����ؼ� ����, ���� ũ�⸦ �߶� ���� ���ϴ� ���� ����
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,						// ������ ����� DC(ȭ�� DC)
			destX,						// ����� ��ǥ ���� X
			destY,						// ����� ��ǥ ���� Y
			sourWidth,			// ����� �̹��� ���� ũ��
			sourHeight,			// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,			// ����� ��� �޸�DC
			sourX, sourY,						// ���� ���� ����
			sourWidth,			// ���� ���� ���� ũ��
			sourHeight,			// ���� ���� ���� ũ��
			_transColor					// �����Ҷ� ������ ���� (����Ÿ)
		);
	}
	else
	{
		// �� BitBlt() : DC���� �������� ���� ���� ���縦 ���ش�.
		// �� SRCCOPY : �ҽ� ������ ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

// ���ķ���
void GImage::alphaRender(HDC hdc, BYTE alpha)
{
	// ���ĺ����� ó�� ����?
	// �� ����� �� �ֵ��� �ʱ�ȭ���� �����Ѵ�.
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ������ �̹��� �׸���.
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

		// 2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
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

		// 3. ������ �̹����� ȭ�鿡 �׸���.
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

	if (alpha < 0)
	{
		_blendFunc.SourceConstantAlpha = 0;
	}
	else if (alpha > 255)
	{
		_blendFunc.SourceConstantAlpha = 255;
	}
	else
	{
		_blendFunc.SourceConstantAlpha = alpha;
	}
	if (_isTrans)
	{
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ������ �̹��� �׸���.
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

		// 2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
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

		// 3. ������ �̹����� ȭ�鿡 �׸���.
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
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ������ �̹��� �׸���.
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

		// 2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
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

		// 3. ������ �̹����� ȭ�鿡 �׸���.
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
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ������ �̹��� �׸���.
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

		// 2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
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

		// 3. ������ �̹����� ȭ�鿡 �׸���.
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
	if (alpha < 0)
	{
		_blendFunc.SourceConstantAlpha = 0;
	}
	else if (alpha > 255)
	{
		_blendFunc.SourceConstantAlpha = 255;
	}
	else
	{
		_blendFunc.SourceConstantAlpha = alpha;
	}
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
			_imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
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
		/*GdiAlphaBlend(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendFunc);
		GdiTransparentBlt(
			hdc,
			destX, destY,
			destWidth,
			destHeight,
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		BitBlt(_blendImage->hMemDC, 0, 0, destWidth, destHeight, hdc, destX, destY, SRCCOPY);
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHeight,
			_blendImage2->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		StretchBlt(hdc, destX, destY, destWidth, destHeight,
			_blendImage->hMemDC, 0, 0, destWidth, destHeight, SRCCOPY);*/
	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, destWidth, destHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, 
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void GImage::alphaFrameRenderEFX(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
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
	if(!_blendImage)this->initForAlphaBlend();
	if (!_blendImage2)this->initForAlphaBlend2();
	_blendFunc.SourceConstantAlpha = alpha;
	//HBRUSH hBrush = CreateSolidBrush(RGB(8, 8, 16));
	//FillRect(_blendImage2->hMemDC, &RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y), hBrush);
	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, hdc, destX, destY, SRCCOPY);
		GdiTransparentBlt(_blendImage2->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, 
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage2->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			RGB(0, 0, 0));
			//RGB(8, 8, 16));

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void GImage::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//GdiTransparentBlt(): ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� �����Ѵ�.      
		GdiTransparentBlt
		(
			hdc,               //������ ��ҿ� DC(ȭ��DC)
			destX,                  //����� ��ǥ���� X 
			destY,                  //����� ��ǥ���� Y
			_imageInfo->frameWidth,      //����� �̹��� ����ũ��
			_imageInfo->frameHeight,      //����� �̹��� ����ũ��
			_imageInfo->hMemDC,      //����� ��� �޸�DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,               //���� ���� ����
			_imageInfo->frameWidth,         //���� ���� ����ũ��
			_imageInfo->frameHeight,    //���� ���� ����ũ��
			_transColor            //�����Ҷ� ������ ����(����Ÿ)

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
	if (currentFrameX < 0)
	{
		_imageInfo->currentFrameX = 0;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,                  // ������ ����� DC(ȭ�� DC)
			destX,                  // ����� ��ǥ ���� X
			destY,                  // ����� ��ǥ ���� Y
			_imageInfo->frameWidth,         // ����� �̹��� ���� ũ��
			_imageInfo->frameHeight,         // ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,         // ����� ��� �޸�DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,            // ���� ���� ����
			_imageInfo->frameWidth,         // ���� ���� ���� ũ��
			_imageInfo->frameHeight,         // ���� ���� ���� ũ��
			_transColor               // �����Ҷ� ������ ���� (����Ÿ)
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
	if (currentFrameX < 0)
	{
		_imageInfo->currentFrameX = 0;
	}
	if (_isTrans)
	{
		// GdiTransparentBlt() : ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� �����Ѵ�.
		GdiTransparentBlt
		(
			hdc,                  // ������ ����� DC(ȭ�� DC)
			destX,                  // ����� ��ǥ ���� X
			destY,                  // ����� ��ǥ ���� Y
			destWidth,
			destHeight,
			_imageInfo->hMemDC,         // ����� ��� �޸�DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,            // ���� ���� ����
			_imageInfo->frameWidth,         // ���� ���� ���� ũ��
			_imageInfo->frameHeight,         // ���� ���� ���� ũ��
			_transColor               // �����Ҷ� ������ ���� (����Ÿ)
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