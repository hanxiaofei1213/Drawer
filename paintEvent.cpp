#include "paintEvent.h"

PaintEvent::PaintEvent(HWND a_hwnd, PAINTSTRUCT *a_ps)
{
	m_hwnd = a_hwnd;
	m_ps = a_ps;
	m_hdc = BeginPaint(m_hwnd, m_ps);
}


PaintEvent::~PaintEvent()
{
	EndPaint(m_hwnd, m_ps);
}
