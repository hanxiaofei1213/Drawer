#include "event.h"
#include "mouseEvent.h"
#include "size.h"
#include "WindowWidget.h"


#include "windowLessWidget.h"

// only for test
#include "rectangle.h"

#include "point.h"

WindowLessWidget::WindowLessWidget(ShowObject* parent) : ShowObject(parent)
{
	m_parent = static_cast<WindowWidget*>(getParent());

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
	HDC hdc = GetDC(m_parent->getHwnd());
	Rect rect(hdc);
	rect.setBegin(m_location);
	rect.setEnd({ m_location.x() + m_nWidth, m_location.y() + m_nHeight });
	rect.draw();
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

void WindowLessWidget::updataUI()
{
	UpdateWindow(m_parent->getHwnd());
}

