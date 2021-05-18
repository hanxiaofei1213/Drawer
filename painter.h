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
	explicit Painter(HDC hdc);
	virtual ~Painter();

	void setHDC(HDC hdc) { m_hdc = hdc; }

	void setPenWidth(int width) { m_nPenWidth = width; changePen(m_penStyle, m_nPenWidth, m_penColor); }
	void setPenStyle(int style) { m_penStyle = style; changePen(m_penStyle, m_nPenWidth, m_penColor); }
	void setPenColor(COLORREF color) { m_penColor = color; changePen(m_penStyle, m_nPenWidth, m_penColor); }

	void setBrushColor(COLORREF color) { m_brushColor = color; changeBursh(m_brushColor); }

	void drawLine(int x1, int y1, int x2, int y2);
	void drawRect(int x1, int y1, int x2, int y2);
	void drawText(LPCTSTR text, RECT rect, UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE);

protected:
	void changePen(int style, int width, COLORREF color);
	void changeBursh(COLORREF color);

private:
	HDC m_hdc = nullptr;
	HPEN m_pen = nullptr;
	int m_nPenWidth = 2;
	int m_penStyle = PS_SOLID;
	COLORREF m_penColor = RGB(50, 50, 50);
	HBRUSH m_brush = nullptr;
	COLORREF m_brushColor = RGB(255, 255, 255);
};






