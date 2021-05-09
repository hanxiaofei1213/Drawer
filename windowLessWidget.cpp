#include "event.h"
#include "mouseEvent.h"
#include "painter.h"
#include "size.h"
#include "WindowWidget.h"

#include "windowLessWidget.h"

// only for test
#include "rectangle.h"
#include <wingdi.h>

WindowLessWidget::WindowLessWidget(ShowObject* parent) : ShowObject(parent)
{
	m_windowParent = static_cast<WindowWidget*>(getParent());
	init();
}

WindowLessWidget::~WindowLessWidget()
{
	releaseMemBitMap();
	ReleaseDC(m_windowParent->getHwnd(), m_HDC);
	delete m_painter;
}

void WindowLessWidget::move(Point loc)
{
	m_location = {loc.x(), loc.y()};
	updateRect();
}

void WindowLessWidget::move(int x, int y)
{
	m_location = { x, y };
	updateRect();
}

void WindowLessWidget::resize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;

	// 每次改变大小之后都需要改一下内存画布
	releaseMemBitMap();
	initMemBitMap();              // Todo: 这里可以优化一下

	updateRect();
}

void WindowLessWidget::show()
{
	Rectangle(m_memHDC, 0, 0, m_nWidth, m_nHeight);
	m_memPainter->drawRect(0, 0, m_nWidth, m_nHeight);
	BitBlt(m_HDC, m_location.x(), m_location.y(), m_nWidth, m_nHeight, m_memHDC, 0, 0, SRCCOPY);
	setShowState(true);
}

void WindowLessWidget::hide()
{
	RECT r = { m_location.x(), m_location.y(), m_location.x() + m_nWidth, m_location.y() + m_nHeight };
	InvalidateRect(m_windowParent->getHwnd(), &r, TRUE);
	setShowState(false);
}

bool WindowLessWidget::eventLoop(Event* event)
{
	switch (event->getType())
	{
	case Event::EventType::PAINTEVENT:
		

		break;
	default:
		ShowObject::eventLoop(event);
		break;
	}
	return true;
}

void WindowLessWidget::init()
{
	m_HDC = GetDC(m_windowParent->getHwnd());
	m_painter = new Painter(m_HDC);
	initMemBitMap();
	updateRect();
}

void WindowLessWidget::initMemBitMap()
{
	
	m_memHDC = CreateCompatibleDC(m_HDC);
	m_memBitmap = CreateCompatibleBitmap(m_HDC, m_nWidth, m_nHeight);
	m_memPainter = new Painter(m_memHDC);

	SelectObject(m_memHDC, m_memBitmap);
	SelectObject(m_memHDC, m_hBursh);
	
}

void WindowLessWidget::releaseMemBitMap()
{
	DeleteDC(m_memHDC);
	DeleteObject(m_memBitmap);
}

void WindowLessWidget::updateRect()
{
	m_rect = { m_location.x(), m_location.y(), m_location.x() + m_nWidth, m_location.y() + m_nHeight };
}

