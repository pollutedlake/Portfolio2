#pragma once
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,		// ���ҽ�, ����
		LOAD_EMPTY, LOAD_END				// �� ��Ʈ��, �ε� Done
	};

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		int x;
		int y;
		int	width;
		int	height;
		int maxFrameX;
		int maxFrameY;
		int currentFrameX;
		int currentFrameY;
		int frameWidth;
		int frameHeight;
		BYTE		loadType;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	char* _fileName;
	bool			_isTrans;			// ���ٰ���?
	COLORREF		_transColor;		// ���� RGB �� (����Ÿ = RGB(255, 0, 255)

	/*
	COLORREF

	- �������� ������ ǥ���ϱ� ���� ��ȣ���� 32��Ʈ ������
	�� R, G, B ���� 1����Ʈ(8��Ʈ)�̸� 0~255������ ���� ǥ���ϴµ� ����ȭ �Ǿ� �ִ�.
	*/

	BLENDFUNCTION	_blendFunc;			// ���ĺ��� ���
	LPIMAGE_INFO	_blendImage;		// ���ĺ��� �̹���

public:
	HRESULT init(int width, int height);
	// �̹��� ���ҽ��� �ʱ�ȭ
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);

	// ���� ColorŰ ����
	void setTransColor(bool isTrans, COLORREF transColor);

	// ����
	void release(void);

	// ����
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	// �̹��� Ŭ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	// ���ķ���
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	// �����ӷ���
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY);

	// = �ζ��� �Լ� =
	inline int  getWidth() { return _imageInfo->width; }
	inline int  getHeight() { return _imageInfo->height; }
	inline int  getframeWidth() { return _imageInfo->frameWidth; }
	inline int  getframeHeight() { return _imageInfo->frameHeight; }
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	inline void setFrameX(int frameX) { _imageInfo->currentFrameX = frameX; }
	inline void setFrameY(int frameY) { _imageInfo->currentFrameY = frameY; }

	GImage();
	~GImage() {}
};

