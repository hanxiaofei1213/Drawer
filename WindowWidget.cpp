#include "WindowWidget.h"

#include "mouseEvent.h"
#include "buttonEvent.h"

/**
 * @brief ���캯��
 * @param parent ������ΪNULL��ǰΪ�������ڣ���Ϊ�գ���ǰ�������Ӵ���
 * @param className ����������ƣ�����ϵͳע��õģ�Ҳ�����Զ����
 */
WindowWidget::WindowWidget(WindowWidget* parent, LPCTSTR className) : ShowObject(parent), m_location(300,200) {
	// TODO: ÿ�ζ�Ҫ�Լ�CreateWindow������취�������ˣ��鷳����
    // TODO: ����ÿ�ζ�Ҫ�Լ�Ū��ǰ�����������ॸ��㣿�����װ��
	
	// ��������
	m_className = className;

	// �����Ƿ��и�����ȷ��m_style��m_hwndParent��ֵ
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
 * @brief �趨�ı������
 */
void WindowWidget::setText(LPCTSTR text) {
	m_windowName = text;
	SetWindowTextW(m_hwnd, text);
}
		

/**
 * @brief �ƶ�������
 * @param a_loc Ŀ��λ�ã�point����
 */
void WindowWidget::move(Point loc) {
	m_location = std::move(loc);
	MoveWindow(m_hwnd, loc.x(), loc.y(), m_width, m_height, TRUE);
}

/**
 * @brief �ƶ������ڣ�����
 * @param a_x x����
 * @param a_y y����
 */
void WindowWidget::move(int x, int y) {
	m_location.setX(x);
	m_location.setY(y);
	MoveWindow(m_hwnd, x, y, m_width, m_height, TRUE);  
}


/**
 * @brief �����趨���ڴ�С
 * @param width ���
 * @param height �߶�
 */
void WindowWidget::resize(int width, int height) {
	m_width = width;
	m_height = height;
	MoveWindow(m_hwnd, m_location.x(), m_location.y(), width, height, TRUE);
}


/**
 * @brief ���õ�ǰ���ھ��
 * @param hwnd ���ھ��
 */
void WindowWidget::setNowHwnd(HWND hwnd) {
	if (hwnd == NULL) {
		MessageBox(NULL, TEXT("ShowObject::setNowHwnd HWND == NULL"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}
	m_hwnd = hwnd;
}


/**
 * @brief չʾ�Լ���չʾ�б����������Ԫ��
 */
void WindowWidget::show() {
	ShowWindow(m_hwnd, TRUE);
	UpdateWindow(m_hwnd);

	for (auto i : getShowList())
		i->show(); 
}

