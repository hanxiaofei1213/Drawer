
#include "Widget.h"

#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"



Widget::Widget(ShowObject* a_parent) : ShowObject(a_parent, TEXT("Widget"))
{
	WNDCLASS wndClass;

	// 构造窗口结构体
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 2 * sizeof(size_t);        // 分配空间，准备把this指针传入
	wndClass.hInstance = getInstance();
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszClassName = TEXT("Widget");
	wndClass.lpszMenuName = NULL;

	// 注册窗口
	RegisterClass(&wndClass);

	// 创建窗口
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
 * @brief 重写父类的事件循环
 * @param a_event 要处理的事件
 */
bool Widget::eventLoop(Event* a_event)
{
	switch (a_event->getType())
	{
	case Event::EventType::LBUTTONDOWN:
	case Event::EventType::RBUTTONDOWN:
		mousePressEvent(static_cast<MouseEvent*>(a_event));  
		break;
	case Event::EventType::LBUTTONUP:
	case Event::EventType::RBUTTONUP:
		mouseReleaseEvent(static_cast<MouseEvent*>(a_event));
		break;
	case Event::EventType::MOUSEMOVE:
		mouseMoveEvent(static_cast<MouseEvent*>(a_event));
		break;
	case Event::EventType::BUTTON_CLICK:
	case Event::EventType::BUTTON_DBLCLK:
		buttonPressEvent(static_cast<ButtonEvent*>(a_event)); 
	case Event::EventType::PAINTEVENT:
		paintEvent(static_cast<PaintEvent*>(a_event));
	}


	return Object::eventLoop(a_event);
}


/**
 * @brief 用来处理鼠标按下的事件
 * @a_event 要处理的事件
 */
void Widget::mousePressEvent(MouseEvent* a_event)
{
	
}

/**
 * @brief 用来处理鼠标移动的事件
 * @a_event 要处理的事件
 */
void Widget::mouseMoveEvent(MouseEvent*)
{
}

/**
 * @brief 用来处理鼠标放开的事件
 * @a_event 要处理的事件
 */
void Widget::mouseReleaseEvent(MouseEvent* a_event)
{
	//MessageBox(NULL, TEXT("mouseReleaseEvent"), TEXT("test"), MB_OK);
}


/**
 * @brief 用来处理画图的事件
 * @a_event 要处理的事件
 */
void Widget::paintEvent(PaintEvent* a_event)
{
}

/**
 * @brief 处理按钮按下的事件
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



