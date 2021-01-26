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
	m_event = nullptr;
}

/**
 * @brief �ͷ���Դ
 */
EventLoop::~EventLoop()
{
	if (m_event)
		delete m_event;
}

/**
 * @brief ����Ϣ������¼�
 */
Event* EventLoop::packageMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* ps)
{
	// ��m_event�ڴ��ͷŵ�
	if (m_event)
	{
		delete m_event;
		m_event = nullptr;
	}

	// ������Ϣ
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
 * @brief ���¼��ַ���ȥ
 */
bool EventLoop::event()
{
	// ���m_eventΪ�գ���˵�������Ϣ��������Ҫ����ģ�����ϵͳ����
	if (!m_event)
		return false;

	// ���¼�����Ŀ�Ķ����eventLoop����
	Object* destObj = m_event->getDestObject();
	return destObj->eventLoop(m_event);
}

/**
 * @brief ʹ��SetWindowLongPtr��GetWindowLongPtr���Ŀ�Ķ����thisָ��
 * @param a_hwnd ���ڹ��̺����еĴ��ھ��
 * @return Ŀ�Ķ���
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
 * @brief �������Ϣ������¼�
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
 * @brief ����ť��Ϣ������¼�
 */
ButtonEvent* EventLoop::packageBtnMsg(HWND a_hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		DefWindowProc(a_hwnd, message, wParam, lParam);
		break;
	}
	event->setBtnId(id);
	event->setDestObject(calculateDestObject(a_hwnd));
	return event;
}


/**
 * @brief ���ػ���Ϣ������¼�
 */
PaintEvent* EventLoop::packagePaintMsg(HWND a_hwnd, PAINTSTRUCT* a_ps)
{
	PaintEvent* event = new PaintEvent(a_hwnd, a_ps);
	event->setEventType(Event::EventType::PAINTEVENT);
	event->setDestObject(calculateDestObject(a_hwnd));
	return event;
}







