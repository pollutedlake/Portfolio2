#pragma once
#include "SingletonBase.h"
#include "GImage.h"

class ImageManager : public SingletonBase <ImageManager>
{
private:
	map<string, GImage*> _imageMap;		// image들을 관리하는 맵
	
public:
	HRESULT init(void);
	void release(void);

	GImage* addImage(string key, int width, int height);
	GImage* addImage(string key, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string key, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor);
	GImage* addFrameImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor);
	GImage* addFrameImage(string key, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor);

	GImage* findImage(string key);
	bool deleteImage(string key);
	bool deleteAll();

	void render(string key, HDC hdc);
	void render(string key, HDC hdc, int destX, int destY);
	void render(string key, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(string key, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	
	void alphaRender(string key, HDC hdc, BYTE alphpa);
	void alphaRender(string key, HDC hdc, int destX, int destY, BYTE alphpa);
	void alphaRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alphpa);
	void alphaRender(string key, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alphpa);
};

