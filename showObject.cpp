#include "showObject.h"

#include "mouseEvent.h"
#include "buttonEvent.h"

/**
 * @brief ���캯��
 * @param a_parent ������ΪNULL��ǰΪ�������ڣ���Ϊ�գ���ǰ�������Ӵ���
 * @param a_className ����������ƣ�����ϵͳע��õģ�Ҳ�����Զ����
 */
ShowObject::ShowObject(ShowObject* parent, LPCTSTR className) : Object(parent)
{
	// TODO: ÿ�ζ�Ҫ�Լ�CreateWindow������취�������ˣ��鷳����
    // TODO: ����ÿ�ζ�Ҫ�Լ�Ū��ǰ�����������ॸ��㣿�����װ��
	
	// ��������
	m_className = className;
	m_windowName = NULL;
	m_location = new Point(300, 200);
	m_width = 500;
	m_height = 500;
	m_hwnd = NULL;

	// �����Ƿ��и�����ȷ��m_style��m_hwndParent��ֵ
	if (parent != NULL)
	{
        m_style = WS_CHILD;
		m_parentHwnd = parent->getHwnd();
		parent->addShowList(this);
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
 * @brief �趨�ı������
 */
void ShowObject::setText(LPCTSTR text)
{
	m_windowName = text;
	SetWindowTextW(m_hwnd, text);
}
		

/**
 * @brief �ƶ�������
 * @param a_loc Ŀ��λ�ã�point����
 */
void ShowObject::move(Point* loc)
{
	m_location = loc;
	MoveWindow(m_hwnd, loc->x(), loc->y(), m_width, m_height, TRUE);
}

/**
 * @brief �ƶ������ڣ�����
 * @param a_x x����
 * @param a_y y����
 */
void ShowObject::move(int x, int y)
{
	
	m_location->setX(x);
	m_location->setY(y);
	
	MoveWindow(m_hwnd, x, y, m_width, m_height, TRUE);  
}


/**
 * @brief �����趨���ڴ�С
 * @param a_width ���
 * @param a_height �߶�
 */
void ShowObject::resize(int width, int height)
{
	m_width = width;
	m_height = height;
	MoveWindow(m_hwnd, m_location->x(), m_location->y(), width, height, TRUE);
}


/**
 * @brief ���õ�ǰ���ھ��
 * @param a_hwnd ���ھ��
 */
void ShowObject::setNowHwnd(HWND hwnd)
{
	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("ShowObject::setNowHwnd HWND == NULL"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}
	m_hwnd = hwnd;
}


/**
 * @brief ����չʾ�б�
 * @return չʾ�б�����
 */
std::vector<ShowObject*>& ShowObject::getShowList()
{
	return m_showChildList;
}

/**
 * @brief ������ӵ�չʾ�б��У����show��������չʾ���д��б�ؼ�
 * @param a_toAddObject Ҫ��ӵĶ���
 */
void ShowObject::addShowList(ShowObject* toAddObject)
{
	m_showChildList.push_back(toAddObject);
}


/**
 * @brief չʾ�Լ���չʾ�б����������Ԫ��
 */
void ShowObject::show()               
{
	for (auto i : m_showChildList)
		i->show(); 
	ShowWindow(getHwnd(), TRUE);
	UpdateWindow(getHwnd());
}

/**
 * @brief ��д������¼�ѭ��
 * @param a_event Ҫ������¼�
 */
bool ShowObject::eventLoop(Event* event) 
{
	return Object::eventLoop(event);
}
