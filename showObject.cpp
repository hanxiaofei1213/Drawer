#include "buttonEvent.h"
#include "MouseDropEvent.h"
#include "mouseEvent.h"
#include "mouseWheelEvent.h"
#include "paintEvent.h"

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
 * @brief 将对象加到展示列表中，会一直向上追到最父一级的showlist
 * @param toAddObject 要添加的对象
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
		break;
	case Event::EventType::PAINTEVENT:
		paintEvent(static_cast<PaintEvent*>(event));
		break;
	case Event::EventType::MOUSEDROP:
		mouseDropEvent(static_cast<MouseDropEvent*>(event));
		break;
	case Event::EventType::MOUSE_WHEEL:
		mouseWheelEvent(static_cast<MouseWheelEvent*>(event));
		break;
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

void ShowObject::mouseDropEvent(MouseDropEvent* event)
{

}

void ShowObject::mouseWheelEvent(MouseWheelEvent* event)
{

}

