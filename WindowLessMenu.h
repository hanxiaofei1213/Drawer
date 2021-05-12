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

	void addAction(WindowLessAction* action);

	virtual void show() override;

	/**
	 * @brief ���ص�ǰ���ѡ���action
	 */
	int chooseAction(MouseEvent* event);

protected:
	virtual void mousePressEvent(MouseEvent* event) override;

	

private:
	int m_nActionNum = 0;
	std::vector<WindowLessAction*> m_vecAction;
};



