#include "Stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
	return S_OK;
}

void ImageManager::release(void)
{
}

GImage* ImageManager::addImage(string key, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		return image;
	}

	image = new GImage;
	if (image->init(fileName, width, height, isTrans, transColor))
	{
		SAFE_DELETE(image);
		return nullptr;
	}

	_imageMap.insert(make_pair(key, image));

	return image;
}

GImage* ImageManager::findImage(string key)
{
	return _imageMap.at(key);
}

void ImageManager::deleteImage(string key)
{

}
