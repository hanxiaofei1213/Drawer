#include "buttonEvent.h"
#include "mouseEvent.h"
#include "paintEvent.h"
#include "point.h"

#include "showObject.h"


ShowObject::ShowObject(ShowObject* parent) : Object(parent)
{
	if (parent)
		parent->addShowList(this);
}

ShowObject::~ShowObject()
{
}

/**
 * @brief 将对象加到展示列表中，最后show函数将会展示所有此列表控件
 * @param a_toAddObject 要添加的对象
 */
void ShowObject::addShowList(ShowObject* toAddObject) {
	m_showChildList.push_back(toAddObject);
}

/**
 * @brief 返回展示列表
 * @return 展示列表引用
 */
std::vector<ShowObject*>& ShowObject::getShowList() {
	return m_showChildList;
}

bool ShowObject::eventLoop(Event* event)
{
	switch (event->getType()) {
	case Event::EventType::LBUTTONDOWN:
	case Event::EventType::RBUTTONDOWN:
		mousePressEvent(static_cast<MouseEvent*>(event));  
		break;
	case Event::EventType::LBUTTONUP:
	case Event::EventType::RBUTTONUP:
		mouseReleaseEvent(static_cast<MouseEvent*>(event));
		break;
	case Event::EventType::MOUSEMOVE:
		mouseMoveEvent(static_cast<MouseEvent*>(event));
		break;
	case Event::EventType::BUTTON_CLICK:
	case Event::EventType::BUTTON_DBLCLK:
		buttonPressEvent(static_cast<ButtonEvent*>(event)); 
	case Event::EventType::PAINTEVENT:
		paintEvent(static_cast<PaintEvent*>(event));
	}

	return Object::eventLoop(event);
}

void ShowObject::showChildren()
{
	for (auto x : m_showChildList)
		x->show();
}

void ShowObject::mousePressEvent(MouseEvent* event)
{

}

void ShowObject::mouseMoveEvent(MouseEvent* event)
{

}

void ShowObject::mouseReleaseEvent(MouseEvent* event)
{

}

void ShowObject::paintEvent(PaintEvent* event)
{

}

void ShowObject::buttonPressEvent(ButtonEvent* event)
{

}

