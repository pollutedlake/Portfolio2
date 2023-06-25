#pragma once
#include "SingletonBase.h"
#include "GImage.h"

class ImageManager : public SingletonBase <ImageManager>
{
private:
	map<string, GImage*> imageMap;
	
public:
	HRESULT init(void);
	void release(void);

	GImage* addImage(string key, int width, int height);s
};

