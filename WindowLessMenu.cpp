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

	Point& loc = getLoc();
	action->move(loc.x(), (m_nActionNum - 1) * ACTION_HEIGHT);
	action->resize(MENU_WIDTH, ACTION_HEIGHT);

	resize(MENU_WIDTH, m_nActionNum * ACTION_HEIGHT);
}
