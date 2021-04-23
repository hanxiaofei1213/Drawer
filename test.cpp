
#include "rectangle.h"

#include "test.h"

Test::Test(WindowWidget* parent) : Widget(parent)
{
	m_btn = new Button(this);
	m_btn->setText(L"click");
	m_btn->move(100, 0);

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
		static int temp = 1;
		if (temp++ % 2)
			m_widget->hide();
		else
			m_widget->show();

	}
}

