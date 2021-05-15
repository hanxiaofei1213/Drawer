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

void WindowLessMenu::move(Point loc)
{
	updateActionLoc(getLoc(), loc);
	WindowLessWidget::move(loc.x(), loc.y());	
}

void WindowLessMenu::move(int x, int y)
{
	Point newPoint = { x, y };
	updateActionLoc(getLoc(), newPoint);
	WindowLessWidget::move(x, y);
}

void WindowLessMenu::addAction(WindowLessAction* action)
{
	Point& menuLoc = getLoc();
	action->move(menuLoc.x(), menuLoc.y() + m_nActionNum * ACTION_HEIGHT);
	action->resize(MENU_WIDTH, ACTION_HEIGHT);

	m_nActionNum++;
	m_nMenuLine++;
	m_vecAction.push_back(action);
	resize(MENU_WIDTH, m_nMenuLine * ACTION_HEIGHT);
}

void WindowLessMenu::addActions(std::vector<WindowLessAction*> actions)
{
	if (actions.empty())
		return;

	Point& menuLoc = getLoc();
	int actionX = menuLoc.x();
	int actionY = menuLoc.y() + m_nActionNum * ACTION_HEIGHT;
	int signleActionWidth = MENU_WIDTH / actions.size();

	for (int i = 0; i < actions.size(); ++i)
	{
		actions[i]->move(actionX + i * signleActionWidth, actionY);
		actions[i]->resize(signleActionWidth, ACTION_HEIGHT);
		m_nActionNum++;
		m_vecAction.push_back(actions[i]);
	}
	m_nMenuLine++;
	resize(MENU_WIDTH, m_nMenuLine * ACTION_HEIGHT);
}

void WindowLessMenu::show()
{
	WindowLessWidget::show();

	for (auto x : m_vecAction)
	{
		if (!x->isShow())
			continue;

		x->show();
	}	
}

int WindowLessMenu::chooseAction(MouseEvent* event)
{
	int count = 0;
	Point* mousePressPoint = event->getPos();
	int x = mousePressPoint->x();
	int y = mousePressPoint->y();

	RECT menuRect = getRect();
	if (!isShow() || x < menuRect.left || x > menuRect.right || y < menuRect.top || y > menuRect.bottom)
		return -1;

	for (auto action : m_vecAction)
	{
		RECT actionRect = action->getRect();
		if (x > actionRect.left && x < actionRect.right && y > actionRect.top && y < actionRect.bottom)
			return count;

		count++;
	}

	return -1;
}

void WindowLessMenu::updateActionLoc(Point& oldLoc, Point& newLoc)
{
	Point diffPoint = newLoc.minusPoint(oldLoc);
	
	for (auto action : m_vecAction)
	{
		Point actionNewLoc = action->getLoc().addPoint(diffPoint);
		action->move(actionNewLoc.x(), actionNewLoc.y());
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

	if (event->getButtonType() == MouseEvent::ButtonType::LEFTBUTTON)
		chooseAction(event);
}



