
#include "painter.h"
#include "WindowLessAction.h"

#include "test.h"

Test::Test(WindowWidget* parent) : Widget(parent)
{
	m_widget = new WindowLessWidget(this);
	WindowLessAction* action = new WindowLessAction(m_widget);

	m_widget->resize(300, 200);
	action->resize(200, 100);
	action->setText(L"123");

	
}

Test::~Test()
{
}

void Test::buttonPressEvent(ButtonEvent* event)
{
	int btnId = event->getBtnId();

	if (m_btn->getObjectId() == btnId)
	{
		static int temp = 1;
		if (temp++ % 2)
			m_widget->hide();
		else
			m_widget->show();

	}
}

