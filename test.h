#pragma once

#include "widget.h"
#include "buttonEvent.h"
#include "button.h"
#include "windowLessWidget.h"

class Test : public Widget
{
public:
	Test(WindowWidget* parent = nullptr);
	~Test();

protected:
	virtual void buttonPressEvent(ButtonEvent* event) override;

private:
	Button* m_btn = nullptr;
	WindowLessWidget* m_widget = nullptr;
};


