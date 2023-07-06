#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT font = CreateFontA
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0, fontName
	);
	auto oldFont = (HFONT)SelectObject(hdc, font);

	SetTextColor(hdc, color);
	if (sizeof(TEXT("a")) == 2)
	{
		TextOutA(hdc, destX, destY, printString, length);
	}
	else
	{
		wchar_t charBuffer[256];
		size_t tcnt;

		ZeroMemory(charBuffer, sizeof(charBuffer));
		mbstowcs_s(&tcnt, charBuffer, printString, length);
		TextOutW(hdc, destX, destY, charBuffer, tcnt);
	}
	SelectObject(hdc, oldFont);
	DeleteObject(font);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	// 문자크기, 문자폭, 기울기(전체), 문자방향, 문자 굵기, 기울기(t / f), 밑줄(t / f), 취소선, 문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
	HFONT font = CreateFontA
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0, fontName
	);
	auto oldFont = (HFONT)SelectObject(hdc, font);

	SetTextColor(hdc, color);

	if (sizeof(TEXT("a")) == 2)
	{
		char charBuffer[256];
		size_t tcnt;

		ZeroMemory(charBuffer, sizeof(charBuffer));
		wcstombs_s(&tcnt, charBuffer, printString, length * 2);
		TextOutA(hdc, destX, destY, charBuffer, tcnt);
	}
	else
	{
		SetTextColor(hdc, RGB(255, 0, 0));
		TextOutW(hdc, destX, destY, printString, length);
	}
	SelectObject(hdc, oldFont);
	DeleteObject(font);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR* printStringArr, int arrSize, int lineHeight, COLORREF color)
{
	int lineCount = 0;
	int height = lineHeight;
	if (lineHeight == NULL)
	{
		height = fontSize;
	}
	SetBkMode(hdc, TRANSPARENT);
	HFONT font = CreateFontA
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0, fontName
	);
	auto oldFont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, color);
	wchar_t charBuffer[256];
	MoveToEx(hdc, destX, destY, NULL);
	SetTextAlign(hdc, TA_UPDATECP);
	for (int i = 0; i < arrSize; i++)
	{
		int bufferIndex = 0;
		// 개행문자가 들어오면 개행한다.
		for (int j = 0; j < wcslen(printStringArr[i]); j++)
		{
			if (printStringArr[i][j] == L'\n')
			{
				charBuffer[bufferIndex] = L'\0';
				drawText(hdc, destX, destY, fontName, fontSize, fontWeight, charBuffer, wcslen(charBuffer), color);
				bufferIndex = 0;
				lineCount++;
				MoveToEx(hdc, destX, destY + lineCount * height, NULL);
			}
			else
			{
				charBuffer[bufferIndex] = printStringArr[i][j];
				bufferIndex++;
			}
		}
		if (bufferIndex != 0 && charBuffer[bufferIndex - 1] != '\0')
		{
			charBuffer[bufferIndex] = L'\0';
		}
		drawText(hdc, destX, destY, fontName, fontSize, fontWeight, charBuffer, wcslen(charBuffer), color);
	}
	SetTextAlign(hdc, TA_NOUPDATECP);
	SelectObject(hdc, oldFont);
	DeleteObject(font);
}
