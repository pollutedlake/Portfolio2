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
		int			width;
		int			height;
		BYTE		loadType;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
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

public:
	HRESULT init(int width, int height);
	// 이미지 리소스로 초기화
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	// 투명 Color키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);

	// 해제
	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

	// = 인라인 함수 =
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	GImage();
	~GImage() {}
};

