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

protected:
	virtual void mousePressEvent(MouseEvent* event) override;

private:
	int m_nActionNum = 0;
	std::vector<WindowLessAction*> m_vecAction;
};



