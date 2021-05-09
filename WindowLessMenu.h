#pragma once

#include "windowLessWidget.h"

class ShowObject;
class WindowLessAction;

class WindowLessMenu : public WindowLessWidget
{
public:
	WindowLessMenu(ShowObject* parent = nullptr);
	virtual ~WindowLessMenu();

	void addAction(WindowLessAction* action);

private:
	int m_nActionNum = 0;
};



