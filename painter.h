#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : painter.h
// Creator : 王文喜
// Data : 2021/1/21
// Comment : 将GDI绘图的函数封装起来
//////////////////////////////////////////////////////////////////////////

#include <windows.h>


class Painter {
public:
	Painter(HDC hdc);
	virtual ~Painter() {}

	void setHDC(HDC hdc) { m_hdc = hdc; }

	void drawLine(int x1, int y1, int x2, int y2);
	void drawRect(int x1, int y1, int x2, int y2);

private:
	HDC m_hdc = nullptr;
};






