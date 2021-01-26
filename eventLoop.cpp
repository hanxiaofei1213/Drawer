#include "eventLoop.h"

#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"


#include <CommCtrl.h>

/**
 * @brief 初始化属性
 */
EventLoop::EventLoop()
{
	m_event = nullptr;
}

/**
 * @brief 释放资源
 */
EventLoop::~EventLoop()
{
	if (m_event)
		delete m_event;
}

/**
 * @brief 将消息打包成事件
 */
Event* EventLoop::packageMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* ps)
{
	// 将m_event内存释放掉
	if (m_event)
	{
		delete m_event;
		m_event = nullptr;
	}

	// 分配消息
	switch (message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		m_event = packageMouseMsg(hwnd, message, wParam, lParam);
		break;
	case WM_COMMAND:
		m_event = packageBtnMsg(hwnd, message, wParam, lParam);
		break;
	case WM_PAINT:
		m_event = packagePaintMsg(hwnd, ps);
		break;
	case TB_SETBUTTONINFO:
		MessageBox(NULL, TEXT("TB_SETBUTTONINFO"), TEXT("test"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return m_event;
}

/**
 * @brief 将事件分发出去
 */
bool EventLoop::event()
{
	// 如果m_event为空，则说明这个消息不是我们要处理的，交给系统即可
	if (!m_event)
		return false;

	// 把事件交给目的对象的eventLoop函数
	Object* destObj = m_event->getDestObject();
	return destObj->eventLoop(m_event);
}

/**
 * @brief 使用SetWindowLongPtr和GetWindowLongPtr获得目的对象的this指针
 * @param a_hwnd 窗口过程函数中的窗口句柄
 * @return 目的对象
 */
Object* EventLoop::calculateDestObject(HWND a_hwnd)
{
	Object* obj = (Object*)GetWindowLongPtr(a_hwnd, GWL_USERDATA);
	if (obj == NULL)
	{
		MessageBox(NULL, TEXT("EventLoop::calculateDestObject fail!"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}
	return obj;
}


/**
 * @brief 将鼠标消息打包成事件
 * 
 */
MouseEvent* EventLoop::packageMouseMsg(HWND a_hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	MouseEvent* event = new MouseEvent;

	switch (message)
	{
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
		switch (wParam)
		{
		case MK_LBUTTON:
			event->setButtonType(MouseEvent::ButtonType::LEFTBUTTON);
			break;
		case MK_RBUTTON:
			event->setButtonType(MouseEvent::ButtonType::RIGHTBUTTON);
			break;
		default:
			DefWindowProc(a_hwnd, message, wParam, lParam);
			break;
		}
		break;
	}

	event->setPos(LOWORD(lParam), HIWORD(lParam));
	event->setDestObject(calculateDestObject(a_hwnd));
	return event;
}


/**
 * @brief 将按钮消息打包成事件
 */
ButtonEvent* EventLoop::packageBtnMsg(HWND a_hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ButtonEvent* event = new ButtonEvent;
	int type = HIWORD(wParam);
	int id = LOWORD(wParam);

	// FixMe: 那个菜单和快捷键好像和这个冲突，怎么回事？
	switch (type)
	{
	case BN_CLICKED:  // 单击事件
		event->setEventType(Event::EventType::BUTTON_CLICK);
		break;
	case BN_DBLCLK:  // 双击事件
		event->setEventType(Event::EventType::BUTTON_DBLCLK);
		break;
	default:    
		DefWindowProc(a_hwnd, message, wParam, lParam);
		break;
	}
	event->setBtnId(id);
	event->setDestObject(calculateDestObject(a_hwnd));
	return event;
}


/**
 * @brief 将重绘消息打包成事件
 */
PaintEvent* EventLoop::packagePaintMsg(HWND a_hwnd, PAINTSTRUCT* a_ps)
{
	PaintEvent* event = new PaintEvent(a_hwnd, a_ps);
	event->setEventType(Event::EventType::PAINTEVENT);
	event->setDestObject(calculateDestObject(a_hwnd));
	return event;
}







