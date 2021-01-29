#include "eventLoop.h"

#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"


#include <CommCtrl.h>

/**
 * @brief ��ʼ������
 */
EventLoop::EventLoop()
{
	
}

/**
 * @brief �ͷ���Դ
 */
EventLoop::~EventLoop()
{
	
}

/**
 * @brief ����Ϣ������¼�
 */
Event* EventLoop::packageMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* ps)
{
	// ��Ҫ���͵��¼�
	Event* toSendEvent = nullptr;

	// ������Ϣ
	switch (message)
	{
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
 * @brief ���¼��ַ���ȥ
 */
bool EventLoop::event(Event* toSendEvent)
{
	// ���toSendEventΪ�գ���˵�������Ϣ��������Ҫ����ģ�����ϵͳ����
	if (!toSendEvent)
		return false;

	// ���¼�����Ŀ�Ķ����eventLoop����
	Object* destObj = toSendEvent->getDestObject();
	return destObj->eventLoop(toSendEvent);
}

/**
 * @brief ʹ��SetWindowLongPtr��GetWindowLongPtr���Ŀ�Ķ����thisָ��
 * @param a_hwnd ���ڹ��̺����еĴ��ھ��
 * @return Ŀ�Ķ���
 */
Object* EventLoop::calculateDestObject(HWND hwnd)
{
	Object* obj = (Object*)GetWindowLongPtr(hwnd, GWL_USERDATA);
	if (obj == NULL)
	{
		MessageBox(NULL, TEXT("EventLoop::calculateDestObject fail!"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}
	return obj;
}


/**
 * @brief �������Ϣ������¼�
 * 
 */
MouseEvent* EventLoop::packageMouseMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		// TODO: ���������ͬʱ���£��Ѷ���
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
 * @brief ����ť��Ϣ������¼�
 */
ButtonEvent* EventLoop::packageBtnMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ButtonEvent* event = new ButtonEvent;
	int type = HIWORD(wParam);
	int id = LOWORD(wParam);

	// FixMe: �Ǹ��˵��Ϳ�ݼ�����������ͻ����ô���£�
	switch (type)
	{
	case BN_CLICKED:  // �����¼�
		event->setEventType(Event::EventType::BUTTON_CLICK);
		break;
	case BN_DBLCLK:  // ˫���¼�
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
 * @brief ���ػ���Ϣ������¼�
 */
PaintEvent* EventLoop::packagePaintMsg(HWND hwnd, PAINTSTRUCT* ps)
{
	PaintEvent* event = new PaintEvent(hwnd, ps);
	event->setEventType(Event::EventType::PAINTEVENT);
	event->setDestObject(calculateDestObject(hwnd));
	return event;
}







