#include "buttonEvent.h"
#include "eventLoop.h"
#include "MouseDropEvent.h"
#include "mouseEvent.h"

#include "paintEvent.h"

#include <CommCtrl.h>
#include <tuple>

EventLoop::EventLoop() {
	
}

EventLoop::~EventLoop() {
	
}

/**
 * @brief 将消息打包成事件
 */
Event* EventLoop::packageMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* ps) {
	// 将要发送的事件
	Event* toSendEvent = nullptr;

	// 检查是否有鼠标拖动
	toSendEvent = packageMouseDropMsg(hwnd, message, wParam, lParam);
	if (toSendEvent)
		return toSendEvent;

	// 分配消息
	switch (message) {
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		toSendEvent = packageMouseMsg(hwnd, message, wParam, lParam);
		break;
	case WM_COMMAND:
		toSendEvent = packageBtnMsg(hwnd, message, wParam, lParam);
		break;
	case WM_PAINT:
		toSendEvent = packagePaintMsg(hwnd, ps);
		break;
	case TB_SETBUTTONINFO:
		MessageBox(NULL, TEXT("TB_SETBUTTONINFO"), TEXT("test"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return toSendEvent;
}

/**
 * @brief 将事件分发出去
 */
bool EventLoop::event(Event* toSendEvent) {
	// 如果toSendEvent为空，则说明这个消息不是我们要处理的，交给系统即可
	if (!toSendEvent)
		return false;

	// 把事件交给目的对象的eventLoop函数
	Object* destObj = toSendEvent->getDestObject();
	destObj->dispatchEvent(toSendEvent);
	return true;
}

/**
 * @brief 使用SetWindowLongPtr和GetWindowLongPtr获得目的对象的this指针
 * @param a_hwnd 窗口过程函数中的窗口句柄
 * @return 目的对象
 */
Object* EventLoop::calculateDestObject(HWND hwnd) {
	Object* obj = (Object*)GetWindowLongPtr(hwnd, -21);
	if (obj == NULL) {
		MessageBox(NULL, TEXT("EventLoop::calculateDestObject fail!"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}
	return obj;
}

/**
 * @brief 将鼠标消息打包成事件
 * 
 */
MouseEvent* EventLoop::packageMouseMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	MouseEvent* event = new MouseEvent;

	switch (message) {
	case WM_LBUTTONDOWN:
		event->setEventType(Event::EventType::LBUTTONDOWN);
		event->setButtonType(MouseEvent::ButtonType::LEFTBUTTON);
		break;
	case WM_LBUTTONUP:
		event->setEventType(Event::EventType::LBUTTONUP);
		event->setButtonType(MouseEvent::ButtonType::LEFTBUTTON);
		break;
	case WM_RBUTTONDOWN:
		event->setEventType(Event::EventType::RBUTTONDOWN);
		event->setButtonType(MouseEvent::ButtonType::RIGHTBUTTON);
		break;
	case WM_RBUTTONUP:
		event->setEventType(Event::EventType::RBUTTONUP);
		event->setButtonType(MouseEvent::ButtonType::RIGHTBUTTON);
		break;
	case WM_MOUSEMOVE:
		event->setEventType(Event::EventType::MOUSEMOVE);
		switch (wParam) {
		case MK_LBUTTON:
			event->setButtonType(MouseEvent::ButtonType::LEFTBUTTON);
			break;
		case MK_RBUTTON:
			event->setButtonType(MouseEvent::ButtonType::RIGHTBUTTON);
			break;
		default:
			DefWindowProc(hwnd, message, wParam, lParam);
			break;
		}
		break;
	}

	event->setPos(LOWORD(lParam), HIWORD(lParam));
	event->setDestObject(calculateDestObject(hwnd));
	return event;
}


/**
 * @brief 将按钮消息打包成事件
 */
ButtonEvent* EventLoop::packageBtnMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	ButtonEvent* event = new ButtonEvent;
	int type = HIWORD(wParam);
	int id = LOWORD(wParam);

	switch (type) {
	case BN_CLICKED:  // 单击事件
		event->setEventType(Event::EventType::BUTTON_CLICK);
		break;
	case BN_DBLCLK:  // 双击事件
		event->setEventType(Event::EventType::BUTTON_DBLCLK);
		break;
	default:    
		DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
	event->setBtnId(id);
	event->setDestObject(calculateDestObject(hwnd));
	return event;
}

/**
 * @brief 将重绘消息打包成事件
 */
PaintEvent* EventLoop::packagePaintMsg(HWND hwnd, PAINTSTRUCT* ps) {
	PaintEvent* event = new PaintEvent(hwnd, ps);
	event->setEventType(Event::EventType::PAINTEVENT);
	event->setDestObject(calculateDestObject(hwnd));
	return event;
}

MouseDropEvent* EventLoop::packageMouseDropMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MouseDropEvent* toSendEvent = nullptr;
	static bool beginDrop = false;
	static Point beginPoint;
	static Point endPoint;

	switch (message)
	{
	case WM_MBUTTONDOWN:
		beginDrop = true;
		beginPoint = { LOWORD(lParam), HIWORD(lParam) };
		break;
	case WM_MBUTTONUP:
		if (beginDrop)
		{
			endPoint = { LOWORD(lParam), HIWORD(lParam) };
			toSendEvent = new MouseDropEvent;
			bool isMouseDrop = checkMouseDropType(&beginPoint, &endPoint, toSendEvent);
			if (!isMouseDrop)
			{
				delete toSendEvent;
				toSendEvent = nullptr;
			}
			else
			{
				toSendEvent->setDestObject(calculateDestObject(hwnd));
				toSendEvent->setEventType(Event::EventType::MOUSEDROP);
			}
			beginDrop = false;
		}
		break;
	default:
		break;
	}

	return toSendEvent;
}

bool EventLoop::checkMouseDropType(Point* begin, Point* end, MouseDropEvent* event)
{
	if (!event)
		return false;

	auto answer = Point::isHorizontalLeft(begin, end);
	if (std::get<0>(answer))
	{
		if (std::get<1>(answer))
			event->setDropType(MouseDropEvent::DropType::LEFT2RIGHT);
		else
			event->setDropType(MouseDropEvent::DropType::RIGHT2LEFT);

		return true;
	}

	answer = Point::isVerticalUp(begin, end);
	if (std::get<0>(answer))
	{
		if (std::get<1>(answer))
			event->setDropType(MouseDropEvent::DropType::TOP2BOTTOM);
		else
			event->setDropType(MouseDropEvent::DropType::BOTTOM2TOP);

		return true;
	}

	return false;
}





