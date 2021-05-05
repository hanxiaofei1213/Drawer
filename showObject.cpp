#include "buttonEvent.h"
#include "mouseEvent.h"
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
 * @brief ������ӵ�չʾ�б��У���һֱ����׷���һ����showlist
 * @param toAddObject Ҫ��ӵĶ���
 */
void ShowObject::addShowList(ShowObject* toAddObject) {
	if (this->getParent())
	{
		ShowObject* grandParent = static_cast<ShowObject*>(this->getParent());
		grandParent->addShowList(toAddObject);
	}
	else
	{
		m_showChildList.push_back(toAddObject);
	}	
}

/**
 * @brief ����չʾ�б�
 * @return չʾ�б�����
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

