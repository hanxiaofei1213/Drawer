#include "eventLoop.h"

#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"


#include <CommCtrl.h>

/**
 * @brief 初始化属性
 */
EventLoop::EventLoop() {
	
}

/**
 * @brief 释放资源
 */
EventLoop::~EventLoop() {
	
}

/**
 * @brief 将消息打包成事件
 */
Event* EventLoop::packageMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* ps) {
	// 将要发送的事件
	Event* toSendEvent = nullptr;

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
	return destObj->eventLoop(toSendEvent);
}

/**
 * @brief 使用SetWindowLongPtr和GetWindowLongPtr获得目的对象的this指针
 * @param a_hwnd 窗口过程函数中的窗口句柄
 * @return 目的对象
 */
Object* EventLoop::calculateDestObject(HWND hwnd) {
	Object* obj = (Object*)GetWindowLongPtr(hwnd, GWL_USERDATA);
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
		// TODO: 这个多个鼠标同时按下，难顶哎
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

	// FixMe: 那个菜单和快捷键好像和这个冲突，怎么回事？
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







