//////////////////////////////////////////////////////////////////////////
// FileName : WindowLessMenu.h
// Creator : ����ϲ
// Data : 2021/05/10
// Comment : �޾���˵���
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
	 * @brief ���һϵ��action����Щaction�ᱻ���ȷ�����һ����
	 */
	void addActions(std::vector<WindowLessAction*> actions);

	virtual void show() override;

	/**
	 * @brief ���ص�ǰ���ѡ���action
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



