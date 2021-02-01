
#include "painter.h"

Painter::Painter(HDC hdc) {
	m_hdc = hdc;
}

/**
 * @brief 画一条直线
 */
void Painter::drawLine(int x1, int y1, int x2, int y2) {
	MoveToEx(m_hdc, x1, y1, NULL);
	LineTo(m_hdc, x2, y2);
}


/**
 * @brief 画一个矩形
 */
void Painter::drawRect(int x1, int y1, int x2, int y2) {
	Rectangle(m_hdc, x1, y1, x2, y2);
}
