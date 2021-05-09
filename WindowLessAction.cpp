#include "painter.h"

#include "WindowLessAction.h"

class WindowWidget;

WindowLessAction::WindowLessAction(WindowLessWidget* parent) : WindowLessWidget(parent)
{

}

WindowLessAction::~WindowLessAction()
{
}

void WindowLessAction::show()
{
	WindowLessWidget::show();

	getPainter()->drawText(m_pText, getRect());
}

void WindowLessAction::setText(LPCTSTR text)
{
	m_pText = text;
}
