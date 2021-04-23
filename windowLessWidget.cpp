#include "event.h"
#include "mouseEvent.h"
#include "size.h"
#include "WindowWidget.h"


#include "windowLessWidget.h"

// only for test
#include "rectangle.h"
#include <wingdi.h>

WindowLessWidget::WindowLessWidget(ShowObject* parent) : ShowObject(parent)
{
	m_windowParent = static_cast<WindowWidget*>(getParent());
	m_HDC = GetDC(m_windowParent->getHwnd());
	initMemBitMap();
}

WindowLessWidget::~WindowLessWidget()
{
}

// Todo: 支持展示刷新
void WindowLessWidget::move(Point loc)
{
	m_location = std::move(loc);
}

void WindowLessWidget::move(int x, int y)
{
	m_location = { x, y };
}

void WindowLessWidget::resize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
}

void WindowLessWidget::show()
{
	// only for test
	Rect rect(m_memHDC);
	rect.setBegin(m_location);
	rect.setEnd({ m_location.x() + m_nWidth, m_location.y() + m_nHeight });
	rect.draw();

	BitBlt(m_HDC, m_location.x(), m_location.y(), m_nWidth, m_nHeight, m_memHDC, 0, 0, SRCCOPY);
}

void WindowLessWidget::hide()
{
	RECT r = { m_location.x(), m_location.y(), m_location.x() + m_nWidth, m_location.y() + m_nHeight };
	InvalidateRect(m_windowParent->getHwnd(), &r, TRUE);
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

void WindowLessWidget::initMemBitMap()
{
	m_memHDC = CreateCompatibleDC(m_HDC);
	m_memBitmap = CreateCompatibleBitmap(m_HDC, m_nWidth, m_nHeight);

	SelectObject(m_memHDC, m_memBitmap);
	SelectObject(m_memHDC, m_hBursh);
}

