#include "painter.h"


// only for test
#include <Windows.h>

Painter::Painter(HDC hdc) {
	m_hdc = hdc;
	m_pen = CreatePen(m_penStyle, m_nPenWidth, m_penColor);
}

Painter::~Painter() {
	DeleteObject(m_pen);
}

void Painter::drawLine(int x1, int y1, int x2, int y2) {
	HPEN oldPen = (HPEN)SelectObject(m_hdc, m_pen);
	MoveToEx(m_hdc, x1, y1, NULL);
	LineTo(m_hdc, x2, y2);
	SelectObject(m_hdc, oldPen);
}

void Painter::drawRect(int x1, int y1, int x2, int y2) {
	HPEN oldPen = (HPEN)SelectObject(m_hdc, m_pen);
	Rectangle(m_hdc, x1, y1, x2, y2);
	SelectObject(m_hdc, oldPen);
}

void Painter::drawText(LPCTSTR text, RECT rect, UINT format /*= DT_CENTER*/)
{
	HPEN oldPen = (HPEN)SelectObject(m_hdc, m_pen);
	DrawText(m_hdc, text, -1, &rect, format);
	SelectObject(m_hdc, oldPen);
}

void Painter::changePen(int style, int width, COLORREF color)
{
	DeleteObject(m_pen);
	m_pen = CreatePen(style, width, color);
}
