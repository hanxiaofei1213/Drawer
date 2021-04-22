#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : showObject.h
// Creator : 王文喜
// Data : 2021/1/15
// Comment : 继承object，额外提供显示等方法，是封装windows提供控件的类的父类
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

	void setText(LPCTSTR a_text);                                  // 设置标题或文本 
	void setNowHwnd(HWND hwnd);                                    // 设置当前的句柄
	virtual void move(Point a_loc) override;
	virtual void move(int x, int y) override;
	virtual void resize(int width, int height) override;
	DWORD getStyle() { return m_style; }
	Point& getLoc() { return m_location; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	HWND getHwnd() { return m_hwnd; }
	LPCTSTR getWindowName() { return m_windowName; }               // 返回标题或文本内容
	HWND getParentHwnd() { return m_parentHwnd; }                  // 返回父对象句柄
	virtual void show() override;

private:
	LPCTSTR m_className = nullptr;                 // 窗口类的名称，自定义或系统注册好的
	LPCTSTR	m_windowName = nullptr;                // 标题或文本内容
	Point m_location;                              // 位置
	int m_width = 500;                             // 宽
	int m_height = 500;                            // 高
	DWORD m_style = 0;                             // 窗口风格
	HWND m_hwnd = nullptr;                         // 当前的窗口句柄
	HWND m_parentHwnd = nullptr;                   // 父对象的句柄
};


