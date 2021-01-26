#include "showObject.h"

#include "mouseEvent.h"
#include "buttonEvent.h"

/**
 * @brief ���캯��
 * @param a_parent ������ΪNULL��ǰΪ�������ڣ���Ϊ�գ���ǰ�������Ӵ���
 * @param a_className ����������ƣ�����ϵͳע��õģ�Ҳ�����Զ����
 */
ShowObject::ShowObject(ShowObject* a_parent, LPCTSTR a_className) : Object(a_parent)
{
	// TODO: ÿ�ζ�Ҫ�Լ�CreateWindow������취�������ˣ��鷳����
    // TODO: ����ÿ�ζ�Ҫ�Լ�Ū��ǰ�����������ॸ��㣿�����װ��
	
	// ��������
	m_className = a_className;
	m_windowName = NULL;
	m_location = new Point(300, 200);
	m_width = 500;
	m_height = 500;
	m_hwnd = NULL;

	// �����Ƿ��и�����ȷ��m_style��m_hwndParent��ֵ
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


// TODO:��һ���ͷ�ʲô��Դ
ShowObject::~ShowObject()
{
	delete m_location;
}


/**
 * @brief �趨�ı������
 */
void ShowObject::setText(LPCTSTR a_text)
{
	m_windowName = a_text;
	SetWindowTextW(m_hwnd, a_text);
}
		

/**
 * @brief �ƶ�������
 * @param a_loc Ŀ��λ�ã�point����
 */
void ShowObject::move(Point* a_loc)
{
	m_location = a_loc;
	MoveWindow(m_hwnd, a_loc->x(), a_loc->y(), m_width, m_height, TRUE);
}

/**
 * @brief �ƶ������ڣ�����
 * @param a_x x����
 * @param a_y y����
 */
void ShowObject::move(int a_x, int a_y)
{
	
	m_location->setX(a_x);
	m_location->setY(a_y);
	
	MoveWindow(m_hwnd, a_x, a_y, m_width, m_height, TRUE);  
}


/**
 * @brief �����趨���ڴ�С
 * @param a_width ���
 * @param a_height �߶�
 */
void ShowObject::resize(int a_width, int a_height)
{
	m_width = a_width;
	m_height = a_height;
	MoveWindow(m_hwnd, m_location->x(), m_location->y(), a_width, a_height, TRUE);
}


/**
 * @brief ���õ�ǰ���ھ��
 * @param a_hwnd ���ھ��
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
void ShowObject::addShowList(ShowObject* a_toAddObject)
{
	m_showChildList.push_back(a_toAddObject);
}


/**
 * @brief �������չʾ�б���ɾ��
 * @param a_showObject Ҫɾ���Ķ���
 */
void ShowObject::removeShowList(ShowObject*)
{
	// TODO: ʵ�����
	printf("δʵ��\n");
}


/**
 * @brief չʾ�Լ���չʾ�б����������Ԫ��
 */
void ShowObject::show()               
{
	for (auto i : m_showChildList)
	{
		i->show(); 
	}
	ShowWindow(getHwnd(), TRUE);
	UpdateWindow(getHwnd());
}

/**
 * @brief ��д������¼�ѭ��
 * @param a_event Ҫ������¼�
 */
bool ShowObject::eventLoop(Event* a_event) 
{

	return Object::eventLoop(a_event);
}
