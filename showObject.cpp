#include "showObject.h"

#include "mouseEvent.h"
#include "buttonEvent.h"

/**
 * @brief 构造函数
 * @param a_parent 父对象，为NULL则当前为单独窗口，不为空，则当前对象是子窗口
 * @param a_className 窗口类的名称，可以系统注册好的，也可以自定义的
 */
ShowObject::ShowObject(ShowObject* a_parent, LPCTSTR a_className) : Object(a_parent)
{
	// TODO: 每次都要自己CreateWindow，想想办法给他整了，麻烦死了
    // TODO: 还有每次都要自己弄当前句柄，忘记了啷个搞？必须封装了
	
	// 设置属性
	m_className = a_className;
	m_windowName = NULL;
	m_location = new Point(300, 200);
	m_width = 500;
	m_height = 500;
	m_hwnd = NULL;

	// 根据是否有父对象，确认m_style和m_hwndParent的值
	if (a_parent != NULL)
	{
        m_style = WS_CHILD;
		m_parentHwnd = a_parent->getHwnd();
		a_parent->addShowList(this);
	}
	else {
		m_style = WS_OVERLAPPEDWINDOW;
		m_parentHwnd = NULL;
	}

	
}


ShowObject::~ShowObject()
{
	if (m_hwnd)
		DestroyWindow(m_hwnd);
	delete m_location;
}


/**
 * @brief 设定文本或标题
 */
void ShowObject::setText(LPCTSTR a_text)
{
	m_windowName = a_text;
	SetWindowTextW(m_hwnd, a_text);
}
		

/**
 * @brief 移动本窗口
 * @param a_loc 目标位置，point对象
 */
void ShowObject::move(Point* a_loc)
{
	m_location = a_loc;
	MoveWindow(m_hwnd, a_loc->x(), a_loc->y(), m_width, m_height, TRUE);
}

/**
 * @brief 移动本窗口（重载
 * @param a_x x坐标
 * @param a_y y坐标
 */
void ShowObject::move(int a_x, int a_y)
{
	
	m_location->setX(a_x);
	m_location->setY(a_y);
	
	MoveWindow(m_hwnd, a_x, a_y, m_width, m_height, TRUE);  
}


/**
 * @brief 重新设定窗口大小
 * @param a_width 宽度
 * @param a_height 高度
 */
void ShowObject::resize(int a_width, int a_height)
{
	m_width = a_width;
	m_height = a_height;
	MoveWindow(m_hwnd, m_location->x(), m_location->y(), a_width, a_height, TRUE);
}


/**
 * @brief 设置当前窗口句柄
 * @param a_hwnd 窗口句柄
 */
void ShowObject::setNowHwnd(HWND a_hwnd)
{
	if (a_hwnd == NULL)
	{
		MessageBox(NULL, TEXT("ShowObject::setNowHwnd HWND == NULL"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}
	m_hwnd = a_hwnd;
}


/**
 * @brief 返回展示列表
 * @return 展示列表引用
 */
std::vector<ShowObject*>& ShowObject::getShowList()
{
	return m_showChildList;
}

/**
 * @brief 将对象加到展示列表中，最后show函数将会展示所有此列表控件
 * @param a_toAddObject 要添加的对象
 */
void ShowObject::addShowList(ShowObject* a_toAddObject)
{
	m_showChildList.push_back(a_toAddObject);
}


/**
 * @brief 展示自己和展示列表里面的所有元素
 */
void ShowObject::show()               
{
	for (auto i : m_showChildList)
		i->show(); 
	ShowWindow(getHwnd(), TRUE);
	UpdateWindow(getHwnd());
}

/**
 * @brief 重写父类的事件循环
 * @param a_event 要处理的事件
 */
bool ShowObject::eventLoop(Event* a_event) 
{
	return Object::eventLoop(a_event);
}
