#include "painter.h"

#include "WindowLessAction.h"


WindowLessAction::WindowLessAction(WindowLessWidget* parent) : WindowLessWidget(parent)
{

}

WindowLessAction::~WindowLessAction()
{
}

void WindowLessAction::show()
{
	WindowLessWidget::show();


	// only for test
	RECT r = { 0, 0, 100, 100 };
	getPainter()->drawText(m_pText, r);
}

void WindowLessAction::setText(LPCTSTR text)
{
	m_pText = text;
}
