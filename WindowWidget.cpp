#include "WindowWidget.h"

#include "mouseEvent.h"
#include "buttonEvent.h"

/**
 * @brief 构造函数
 * @param parent 父对象，为NULL则当前为单独窗口，不为空，则当前对象是子窗口
 * @param className 窗口类的名称，可以系统注册好的，也可以自定义的
 */
WindowWidget::WindowWidget(WindowWidget* parent, LPCTSTR className) : ShowObject(parent), m_location(300,200) {
	// TODO: 每次都要自己CreateWindow，想想办法给他整了，麻烦死了
    // TODO: 还有每次都要自己弄当前句柄，忘记了啷个搞？必须封装了
	
	// 设置属性
	m_className = className;

	// 根据是否有父对象，确认m_style和m_hwndParent的值
	if (parent != NULL) {
        m_style = WS_CHILD;
		m_parentHwnd = parent->getHwnd();
		parent->addShowList(this);
	}
	else {
		m_style = WS_OVERLAPPEDWINDOW;
		m_parentHwnd = NULL;
	}
}


WindowWidget::~WindowWidget() {
	if (m_hwnd)
		DestroyWindow(m_hwnd);
}


/**
 * @brief 设定文本或标题
 */
void WindowWidget::setText(LPCTSTR text) {
	m_windowName = text;
	SetWindowTextW(m_hwnd, text);
}
		

/**
 * @brief 移动本窗口
 * @param a_loc 目标位置，point对象
 */
void WindowWidget::move(Point loc) {
	m_location = std::move(loc);
	MoveWindow(m_hwnd, loc.x(), loc.y(), m_width, m_height, TRUE);
}

/**
 * @brief 移动本窗口（重载
 * @param a_x x坐标
 * @param a_y y坐标
 */
void WindowWidget::move(int x, int y) {
	m_location.setX(x);
	m_location.setY(y);
	MoveWindow(m_hwnd, x, y, m_width, m_height, TRUE);  
}


/**
 * @brief 重新设定窗口大小
 * @param width 宽度
 * @param height 高度
 */
void WindowWidget::resize(int width, int height) {
	m_width = width;
	m_height = height;
	MoveWindow(m_hwnd, m_location.x(), m_location.y(), width, height, TRUE);
}


/**
 * @brief 设置当前窗口句柄
 * @param hwnd 窗口句柄
 */
void WindowWidget::setNowHwnd(HWND hwnd) {
	if (hwnd == NULL) {
		MessageBox(NULL, TEXT("ShowObject::setNowHwnd HWND == NULL"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}
	m_hwnd = hwnd;
}


/**
 * @brief 展示自己和展示列表里面的所有元素
 */
void WindowWidget::show() {
	ShowWindow(m_hwnd, TRUE);
	UpdateWindow(m_hwnd);

	for (auto showItem : getShowList())
	{
		if (!showItem->isShow())
			continue;

		showItem->show();
		auto childVec = showItem->getShowList();
		if (childVec.empty())
			continue;
		for (auto x : childVec)
			x->show();
	}
		
	setShowState(true);
}

void WindowWidget::hide()
{
	setShowState(false);
	// Todo: 具体实现还没写

}

