
#include "Widget.h"

#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"



Widget::Widget(ShowObject* a_parent) : ShowObject(a_parent, TEXT("Widget"))
{
	WNDCLASS wndClass;

	// ���촰�ڽṹ��
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 2 * sizeof(size_t);      // ����ռ䣬׼����thisָ�봫��
	wndClass.hInstance = getInstance();
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszClassName = TEXT("Widget");
	wndClass.lpszMenuName = NULL;

	// ע�ᴰ��
	RegisterClass(&wndClass);

	// ��������
	HWND nowHwnd = CreateWindow(
		TEXT("Widget"),
		getWindowName(),
		getStyle(),
		getLoc()->x(), getLoc()->y(), getWidth(), getHeight(),
		getParentHwnd(),
		(HMENU)getObjectId(),
		getInstance(),
		NULL
	);

	setNowHwnd(nowHwnd);

	SetWindowLongPtr(nowHwnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

Widget::~Widget()
{

}


/**
 * @brief ��д������¼�ѭ��
 * @param a_event Ҫ������¼�
 */
bool Widget::eventLoop(Event* a_event)
{
	switch (a_event->getType())
	{
	case Event::EventType::LBUTTONDOWN:
	case Event::EventType::RBUTTONDOWN:
		mousePressEvent((MouseEvent*)a_event);    // Fixme: ����ת�����б�İ취���Ҽǵ�
		break;
	case Event::EventType::LBUTTONUP:
	case Event::EventType::RBUTTONUP:
		mouseReleaseEvent((MouseEvent*)a_event);
		break;
	case Event::EventType::MOUSEMOVE:
		mouseMoveEvent((MouseEvent*)a_event);
		break;
	case Event::EventType::BUTTON_CLICK:
	case Event::EventType::BUTTON_DBLCLK:
		buttonPressEvent((ButtonEvent*)a_event);
	case Event::EventType::PAINTEVENT:
		paintEvent((PaintEvent*)a_event);
	}


	return Object::eventLoop(a_event);
}


/**
 * @brief ����������갴�µ��¼�
 * @a_event Ҫ������¼�
 */
void Widget::mousePressEvent(MouseEvent* a_event)
{
	//MessageBox(NULL, TEXT("mousePressEvent"), TEXT("test"), MB_OK);
}

/**
 * @brief ������������ƶ����¼�
 * @a_event Ҫ������¼�
 */
void Widget::mouseMoveEvent(MouseEvent*)
{
}

/**
 * @brief �����������ſ����¼�
 * @a_event Ҫ������¼�
 */
void Widget::mouseReleaseEvent(MouseEvent* a_event)
{
	//MessageBox(NULL, TEXT("mouseReleaseEvent"), TEXT("test"), MB_OK);
}


/**
 * @brief ��������ͼ���¼�
 * @a_event Ҫ������¼�
 */
void Widget::paintEvent(PaintEvent* a_event)
{
}

/**
 * @brief ����ť���µ��¼�
 */
void Widget::buttonPressEvent(ButtonEvent* a_event)
{
	switch (a_event->getType())
	{
	case Event::EventType::BUTTON_CLICK:

		break;
	default:
		break;
	}
}



