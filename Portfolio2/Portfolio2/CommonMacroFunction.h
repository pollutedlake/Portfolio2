#pragma once

// POINT 생성
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

// 두 POINT가 같은지 확인
inline bool SamePoint(POINT pt1, POINT pt2)
{
	if (pt1.x == pt2.x)
	{
		if (pt1.y == pt2.y)
		{
			return true;
		}
	}
	return false;
}

// 선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

// left, top으로 RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

// 중앙을 기준으로 RECT 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// left, top으로 타원 만들기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// 중점으로 타원 만들기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void MyTextOut(HDC hdc, int x, int y, LPCTSTR Text)
{
	TextOut(hdc, x, y, Text, lstrlen(Text));
}