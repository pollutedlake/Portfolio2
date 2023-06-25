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

	GImage* addImage(string key, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	GImage* findImage(string key);
	void deleteImage(string key);
	//void renderImage(string key, HDC hdc, int desX, int desY, )
};

