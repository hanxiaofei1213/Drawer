#include "mouseEvent.h"
#include "WindowLessAction.h"

#include "WindowLessMenu.h"

namespace
{
	const int MENU_WIDTH = 200;
	const int MENU_HEIGHT = 400;
	const int ACTION_HEIGHT = 50;
}


WindowLessMenu::WindowLessMenu(ShowObject* parent) : WindowLessWidget(parent)
{
	resize(MENU_WIDTH, MENU_HEIGHT);
}

WindowLessMenu::~WindowLessMenu()
{
}

void WindowLessMenu::addAction(WindowLessAction* action)
{
	m_nActionNum++;
	m_vecAction.push_back(action);
	resize(MENU_WIDTH, m_nActionNum * ACTION_HEIGHT);
}

void WindowLessMenu::show()
{
	WindowLessWidget::show();
	int countAction = 0;

	for (auto x : m_vecAction)
	{
		if (!x->isShow())
			continue;

		Point& loc = getLoc();
		x->move(loc.x(), loc.y() + countAction * ACTION_HEIGHT);
		x->resize(MENU_WIDTH, ACTION_HEIGHT);
		
		x->show();
		countAction++;
	}
		
}

void WindowLessMenu::mousePressEvent(MouseEvent* event)
{
	if (isShow()) 
	{
		hide();
		return;
	}

	if (event->getButtonType() == MouseEvent::ButtonType::RIGHTBUTTON)
		show();
}

