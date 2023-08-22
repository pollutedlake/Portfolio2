#pragma once
#include "../FrameWork/DesignPattern/SingletonBase.h"

class FontManager : public SingletonBase<FontManager>
{
public:
	void textOut(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color);
	void textOut(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color);
	void textOut(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR* printStringArr, int arrSize, int length, COLORREF color);
	
	void drawText(HDC hdc, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color, LPRECT rc);
	void drawText(HDC hdc, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color, LPRECT rc);
	void drawText(HDC hdc, char* fontName, int fontSize, int fontWeight, LPCWSTR* printStringArr, int arrSize, int lineHeight, COLORREF color, LPRECT rc, int length);

	FontManager() {}
	~FontManager() {}
};

