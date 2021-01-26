
#include "painter.h"

Painter::Painter(HDC a_hdc)
{
	m_hdc = a_hdc;
}

/**
 * @brief 画一条直线
 */
void Painter::drawLine(int a_x1, int a_y1, int a_x2, int a_y2)
{
	MoveToEx(m_hdc, a_x1, a_y1, NULL);
	LineTo(m_hdc, a_x2, a_y2);
}


/**
 * @brief 画一个矩形
 */
void Painter::drawRect(int a_x1, int a_y1, int a_x2, int a_y2)
{
	Rectangle(m_hdc, a_x1, a_y1, a_x2, a_y2);
}
