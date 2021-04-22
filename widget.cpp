
#include "Widget.h"

#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"

Widget::Widget(WindowWidget* parent) : WindowWidget(parent, TEXT("Widget")) {
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
		getLoc().x(), getLoc().y(), getWidth(), getHeight(),
		getParentHwnd(),
		(HMENU)getObjectId(),
		getInstance(),
		NULL
	);

	setNowHwnd(nowHwnd);

	SetWindowLongPtr(nowHwnd, -21, reinterpret_cast<LONG_PTR>(this));
}

Widget::~Widget() {
	
}




