#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : showObject.h
// Creator : 王文喜
// Data : 2021/1/15
// Comment : 继承object，额外提供显示等方法，是所有可展示的对象的父类，主要通过CreateWindow创建对象
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

	// set方法
	void setText(LPCTSTR a_text);                                  // 设置标题或文本 
	void move(Point* a_loc);                                       // 移动窗口位置
	void move(int a_x, int a_y);                                   // 移动窗口位置
	void resize(int a_width, int a_height);                        // 设置大小
	void setNowHwnd(HWND hwnd);                                    // 设置当前的句柄

	// get方法
	HWND getHwnd() { return m_hwnd; }                              // 返回当前窗口窗口句柄	
	Point* getLoc() { return m_location; }                         // 返回当前位置
	int getWidth() { return m_width; }                             // 返回宽
	int getHeight() { return m_height; }                           // 返回高
	DWORD getStyle() { return m_style; }                           // 返回当前style
	LPCTSTR getWindowName() { return m_windowName; }               // 返回标题或文本内容
	HWND getParentHwnd() { return m_parentHwnd; }                  // 返回父对象句柄

	std::vector<ShowObject*>& getShowList();                       // 返回展示列表
	void addShowList(ShowObject* object);                          // 添加到展示列表中

	virtual void show();                                           // 显示这个窗口

	virtual bool eventLoop(Event* event) override;                 // 重写Object的事件循环

private:
	LPCTSTR m_className = nullptr;                 // 窗口类的名称，自定义或系统注册好的
	LPCTSTR	m_windowName = nullptr;                // 标题或文本内容
	Point* m_location = nullptr;                   // 位置
	int m_width = 500;                             // 宽
	int m_height = 500;                            // 高
	DWORD m_style = 0;                             // 窗口风格
	HWND m_hwnd = nullptr;                         // 当前的窗口句柄
	HWND m_parentHwnd = nullptr;                   // 父对象的句柄
	std::vector<ShowObject*> m_showChildList;      // 保存所有展示控件，用于在show()函数中，展示所有
};


