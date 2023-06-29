#include "Stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
	IMAGEMANAGER->addImage("TitleBG", "Resources/Images/BackGrounds/TitleScene/TitleBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("TitleName", "Resources/Images/BackGrounds/TitleScene/TitleName.bmp", 451, 117, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TitleEFX2", "Resources/Images/Effects/TitleScene/TitleEFX2.bmp", 2241, 2025, 6, 6, true, RGB(4, 0, 4));
	IMAGEMANAGER->addFrameImage("TitleEFX1", "Resources/Images/Effects/TitleScene/TitleEFX1.bmp", 3315, 2398, 13, 11, true, RGB(4, 100, 4));
	return S_OK;
}

void ImageManager::release(void)
{
	deleteAll();
}

GImage* ImageManager::addImage(string key, int width, int height)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		return image;
	}

	image = new GImage;
	if (FAILED(image->init(width, height)))
	{
		image->release();
		SAFE_DELETE(image);
		return nullptr;
	}

	_imageMap.insert(make_pair(key, image));

	return image;
}

GImage* ImageManager::addImage(string key, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		return image;
	}

	image = new GImage;
	if (FAILED(image->init(fileName, width, height, isTrans, transColor)))
	{
		image->release();
		SAFE_DELETE(image);
		return nullptr;
	}

	_imageMap.insert(make_pair(key, image));

	return image;
}

GImage* ImageManager::addImage(string key, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		return image;
	}

	image = new GImage;
	if (FAILED(image->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		image->release();
		SAFE_DELETE(image);
		return nullptr;
	}

	_imageMap.insert(make_pair(key, image));

	return image;
}

GImage* ImageManager::addFrameImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		return image;
	}

	image = new GImage;
	if (FAILED(image->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		image->release();
		SAFE_DELETE(image);
		return nullptr;
	}

	_imageMap.insert(make_pair(key, image));

	return image;
}

GImage* ImageManager::addFrameImage(string key, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		return image;
	}

	image = new GImage;
	if (FAILED(image->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		image->release();
		SAFE_DELETE(image);
		return nullptr;
	}

	_imageMap.insert(make_pair(key, image));

	return image;
}

GImage* ImageManager::findImage(string key)
{
	auto node = _imageMap.find(key);
	if (node != _imageMap.end())
	{
		return node->second;
	}
	return nullptr;
}

bool ImageManager::deleteImage(string key)
{
	auto node = _imageMap.find(key);

	if (node != _imageMap.end())
	{
		node->second->release();
		SAFE_DELETE(node->second);
		_imageMap.erase(node);
		return true;
	}
	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _imageMap.begin();
	for (; iter != _imageMap.end();)
	{
		if (iter->second != nullptr)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _imageMap.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_imageMap.clear();
	return true;
}

void ImageManager::render(string key, HDC hdc)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->render(hdc);
	}
}

void ImageManager::render(string key, HDC hdc, int destX, int destY)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->render(hdc, destX, destY);
	}
}

void ImageManager::render(string key, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
	}
}

void ImageManager::render(string key, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->render(hdc, destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight);
	}
}

void ImageManager::alphaRender(string key, HDC hdc, BYTE alphpa)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->alphaRender(hdc, alphpa);
	}
}

void ImageManager::alphaRender(string key, HDC hdc, int destX, int destY, BYTE alphpa)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->alphaRender(hdc, destX, destY, alphpa);
	}
}

void ImageManager::alphaRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alphpa)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alphpa);
	}
}

void ImageManager::alphaRender(string key, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alphpa)
{
	GImage* image = findImage(key);
	if (image != nullptr)
	{
		image->alphaRender(hdc, destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight, alphpa);
	}
}
