
#include "Widget.h"

#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"



Widget::Widget(ShowObject* parent) : ShowObject(parent, TEXT("Widget"))
{
	WNDCLASS wndClass;

	// ���촰�ڽṹ��
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 2 * sizeof(size_t);        // ����ռ䣬׼����thisָ�봫��
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
bool Widget::eventLoop(Event* event)
{
	switch (event->getType())
	{
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


/**
 * @brief ����������갴�µ��¼�
 * @a_event Ҫ������¼�
 */
void Widget::mousePressEvent(MouseEvent* event)
{
	
}

/**
 * @brief ������������ƶ����¼�
 * @a_event Ҫ������¼�
 */
void Widget::mouseMoveEvent(MouseEvent* event)
{
}

/**
 * @brief �����������ſ����¼�
 * @a_event Ҫ������¼�
 */
void Widget::mouseReleaseEvent(MouseEvent* event)
{
	//MessageBox(NULL, TEXT("mouseReleaseEvent"), TEXT("test"), MB_OK);
}


/**
 * @brief ��������ͼ���¼�
 * @a_event Ҫ������¼�
 */
void Widget::paintEvent(PaintEvent* event)
{
}

/**
 * @brief ����ť���µ��¼�
 */
void Widget::buttonPressEvent(ButtonEvent* event)
{
	switch (event->getType())
	{
	case Event::EventType::BUTTON_CLICK:

		break;
	default:
		break;
	}
}



