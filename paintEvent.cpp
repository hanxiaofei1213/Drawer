#include "paintEvent.h"

PaintEvent::PaintEvent(HWND hwnd, PAINTSTRUCT *ps) {
	m_hwnd = hwnd;
	m_ps = ps;
	m_hdc = BeginPaint(m_hwnd, m_ps);
}


PaintEvent::~PaintEvent() {
	EndPaint(m_hwnd, m_ps);
}
