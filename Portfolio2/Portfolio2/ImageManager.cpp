#include "Stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
	IMAGEMANAGER->addImage("TitleBG", "Resources/Images/BackGrounds/TitleScene/TitleBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("TitleName", "Resources/Images/BackGrounds/TitleScene/TitleName.bmp", 451, 117, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TitleEFX2", "Resources/Images/Effects/TitleScene/TitleEFX2.bmp", 2241, 2025, 6, 6, true, RGB(4, 0, 4));
	IMAGEMANAGER->addFrameImage("TitleEFX1", "Resources/Images/Effects/TitleScene/TitleEFX1.bmp", 3315, 2398, 13, 11, true, RGB(4, 100, 4));
	IMAGEMANAGER->addFrameImage("TitleButtons", "Resources/Images/BackGrounds/TitleScene/TitleButtons.bmp", 390, 124, 2, 4, true, RGB(252, 0, 0));


	IMAGEMANAGER->addImage("ScenarioBG", "Resources/Images/BackGrounds/ScenarioScene/Scenario_BG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("Scenarios", "Resources/Images/BackGrounds/ScenarioScene/Scenarios.bmp", 1680, 2700, 3, 27, true, RGB(0, 0, 0));
	return S_OK;
}

void ImageManager::release(void)
{
}

GImage* ImageManager::addImage(string strKey, int width, int height)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));
	return img;
}

GImage* ImageManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}
	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);
		return true;
	}
	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();
	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mImageList.clear();
	return true;
}

void ImageManager::render(string strKey, HDC hdc)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight, alpha);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, destWidth, destHeight, currentFrameX, currentFrameY);
}

void ImageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

