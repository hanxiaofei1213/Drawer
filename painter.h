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
	Painter(HDC a_hdc);
	virtual ~Painter() {}

	void drawLine(int, int, int, int);
	void drawRect(int, int, int, int);

private:
	HDC m_hdc;
};






