#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : showObject.h
// Creator : ����ϲ
// Data : 2021/1/15
// Comment : �̳�object�������ṩ��ʾ�ȷ����������п�չʾ�Ķ���ĸ��࣬��Ҫͨ��CreateWindow��������
//////////////////////////////////////////////////////////////////////////

#include "object.h"
#include "point.h"

class Event;
class MouseEvent;
class ButtonEvent;

class ShowObject : public Object{

public:
	ShowObject(ShowObject* parent, LPCTSTR className);
	virtual ~ShowObject();

	// set����
	void setText(LPCTSTR a_text);                                  // ���ñ�����ı� 
	void move(Point* a_loc);                                       // �ƶ�����λ��
	void move(int a_x, int a_y);                                   // �ƶ�����λ��
	void resize(int a_width, int a_height);                        // ���ô�С
	void setNowHwnd(HWND hwnd);                                    // ���õ�ǰ�ľ��

	// get����
	HWND getHwnd() { return m_hwnd; }                              // ���ص�ǰ���ڴ��ھ��	
	Point* getLoc() { return m_location; }                         // ���ص�ǰλ��
	int getWidth() { return m_width; }                             // ���ؿ�
	int getHeight() { return m_height; }                           // ���ظ�
	DWORD getStyle() { return m_style; }                           // ���ص�ǰstyle
	LPCTSTR getWindowName() { return m_windowName; }               // ���ر�����ı�����
	HWND getParentHwnd() { return m_parentHwnd; }                  // ���ظ�������

	std::vector<ShowObject*>& getShowList();                       // ����չʾ�б�
	void addShowList(ShowObject* object);                          // ��ӵ�չʾ�б���

	virtual void show();                                           // ��ʾ�������

	virtual bool eventLoop(Event* event) override;                 // ��дObject���¼�ѭ��

private:
	LPCTSTR m_className = nullptr;                 // ����������ƣ��Զ����ϵͳע��õ�
	LPCTSTR	m_windowName = nullptr;                // ������ı�����
	Point* m_location = nullptr;                   // λ��
	int m_width = 500;                             // ��
	int m_height = 500;                            // ��
	DWORD m_style = 0;                             // ���ڷ��
	HWND m_hwnd = nullptr;                         // ��ǰ�Ĵ��ھ��
	HWND m_parentHwnd = nullptr;                   // ������ľ��
	std::vector<ShowObject*> m_showChildList;      // ��������չʾ�ؼ���������show()�����У�չʾ����
};


