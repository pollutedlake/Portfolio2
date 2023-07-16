#pragma once
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,		// 리소스, 파일
		LOAD_EMPTY, LOAD_END				// 빈 비트맵, 로드 Done
	};

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			frameWidth;
		int			frameHeight;
		BYTE		loadType;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	char* _fileName;
	bool			_isTrans;			// 없앨건지?
	COLORREF		_transColor;		// 없앨 RGB 값 (마젠타 = RGB(255, 0, 255)

	/*
	COLORREF

	- 윈도우즈 색상값을 표현하기 위한 부호없는 32비트 정수형
	ㄴ R, G, B 각각 1바이트(8비트)이며 0~255까지의 값을 표현하는데 최적화 되어 있다.
	*/

	BLENDFUNCTION	_blendFunc;			// 알파블렌드 기능
	LPIMAGE_INFO	_blendImage;		// 알파블렌드 이미지
	LPIMAGE_INFO	_blendImage2;		// 알파블렌드 이미지

public:
	HRESULT init(int width, int height);
	// 이미지 리소스로 초기화
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 파일로 초기화
	// 한번 쓰고 값을 안바꾸는 경우
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 배경 등
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 플레이어 객체
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);
	HRESULT initForAlphaBlend2(void);

	// 투명 Color키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);

	// 해제
	void release(void);

	// 렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	// 이미지 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	// 알파렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 프레임 렌더
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY, BYTE alpha);
	void alphaFrameRenderEFX(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY);

	LPIMAGE_INFO getImageInfo() { return _imageInfo; }

	// = 인라인 함수 =
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// 이미지 x 좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	// 이미지 y 좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// 이미지 센터 좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// 이미지 가로, 세로 크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// 바운딩 박스 (충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->x + _imageInfo->width,
			_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	// 바운딩 박스 (충돌용 렉트)
	inline RECT boundingBoxWidthFrame(void)
	{
		RECT rc =
		{
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->x + _imageInfo->frameWidth,
			_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// 이미지 1프레임 가로, 세로
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage();
	~GImage() {}
};

