#include <vector>
#include "painter.h"
#include "WindowLessAction.h"
#include "WindowLessMenu.h"

#include "test.h"

Test::Test(WindowWidget* parent) : Widget(parent)
{
	resize(1000, 600);
	WindowLessMenu* menu = new WindowLessMenu(this);
	menu->move(100, 0);
	
	WindowLessAction* action1 = new WindowLessAction(menu);
	action1->setText(L"1231");
	WindowLessAction* action2 = new WindowLessAction(menu);
	action2->setText(L"5656");

	std::vector<WindowLessAction*> actions = { action1, action2 };
	
	menu->addActions(actions);
}

Test::~Test()
{
}


