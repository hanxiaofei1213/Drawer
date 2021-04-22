#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : showObject.h
// Creator : ����ϲ
// Data : 2021/1/15
// Comment : �̳�object�������ṩ��ʾ�ȷ������Ƿ�װwindows�ṩ�ؼ�����ĸ���
//////////////////////////////////////////////////////////////////////////

#include "showObject.h"
#include "point.h"

class Event;
class MouseEvent;
class ButtonEvent;

class WindowWidget : public ShowObject{

public:
	WindowWidget(WindowWidget* parent, LPCTSTR className);
	virtual ~WindowWidget();

	void setText(LPCTSTR a_text);                                  // ���ñ�����ı� 
	void setNowHwnd(HWND hwnd);                                    // ���õ�ǰ�ľ��
	virtual void move(Point a_loc) override;
	virtual void move(int x, int y) override;
	virtual void resize(int width, int height) override;
	DWORD getStyle() { return m_style; }
	Point& getLoc() { return m_location; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	HWND getHwnd() { return m_hwnd; }
	LPCTSTR getWindowName() { return m_windowName; }               // ���ر�����ı�����
	HWND getParentHwnd() { return m_parentHwnd; }                  // ���ظ�������
	virtual void show() override;

private:
	LPCTSTR m_className = nullptr;                 // ����������ƣ��Զ����ϵͳע��õ�
	LPCTSTR	m_windowName = nullptr;                // ������ı�����
	Point m_location;                              // λ��
	int m_width = 500;                             // ��
	int m_height = 500;                            // ��
	DWORD m_style = 0;                             // ���ڷ��
	HWND m_hwnd = nullptr;                         // ��ǰ�Ĵ��ھ��
	HWND m_parentHwnd = nullptr;                   // ������ľ��
};


