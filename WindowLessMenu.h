//////////////////////////////////////////////////////////////////////////
// FileName : WindowLessMenu.h
// Creator : 王文喜
// Data : 2021/05/10
// Comment : 无句柄菜单类
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>

#include "windowLessWidget.h"

class MouseEvent;
class ShowObject;
class WindowLessAction;

class WindowLessMenu : public WindowLessWidget
{
public:
	WindowLessMenu(ShowObject* parent = nullptr);
	virtual ~WindowLessMenu();

	virtual void move(Point loc) override;
	virtual void move(int x, int y) override;

	void addAction(WindowLessAction* action);

	/**
	 * @brief 添加一系列action，这些action会被均匀分配在一行中
	 */
	void addActions(std::vector<WindowLessAction*> actions);

	virtual void show() override;

	/**
	 * @brief 返回当前鼠标选择的action
	 */
	int chooseAction(MouseEvent* event);

protected:
	void updateActionLoc(Point& oldLoc, Point& newLoc);
	virtual void mousePressEvent(MouseEvent* event) override;

private:
	int m_nMenuLine = 0;
	int m_nActionNum = 0;
	std::vector<WindowLessAction*> m_vecAction;
};



