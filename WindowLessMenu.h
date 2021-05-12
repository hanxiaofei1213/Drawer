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

	void addAction(WindowLessAction* action);

	virtual void show() override;

	/**
	 * @brief 返回当前鼠标选择的action
	 */
	int chooseAction(MouseEvent* event);

protected:
	virtual void mousePressEvent(MouseEvent* event) override;

	

private:
	int m_nActionNum = 0;
	std::vector<WindowLessAction*> m_vecAction;
};



