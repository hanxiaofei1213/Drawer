

#include "test.h"

Test::Test(WindowWidget* parent) : Widget(parent)
{
	m_btn = new Button(this);
	m_btn->setText(L"click");

	m_widget = new WindowLessWidget(this);
}

Test::~Test()
{
}

void Test::buttonPressEvent(ButtonEvent* event)
{
	int btnId = event->getBtnId();

	if (m_btn->getObjectId() == btnId)
	{
		static int temp = 10;
		m_widget->move(0, temp++);
	}
}

