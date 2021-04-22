#pragma once


//////////////////////////////////////////////////////////////////////////
// FileName : windowLessWidget.h
// Creator : 王文喜
// Data : 2021/4/18
// Comment : 继承object，是所有无句柄控件的父类，提供基础的控件方法，注意，无句柄窗口是无法获得消息的，要想处理消息必须从有句柄的窗口中拿取
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include <windows.h>

#include "point.h"
#include "showObject.h"

class Event;
class Size;
class WindowWidget;

class WindowLessWidget : public ShowObject
{
public:
	WindowLessWidget(ShowObject* parent = nullptr);
	virtual ~WindowLessWidget();

	virtual void move(Point loc) override;
	virtual void move(int x, int y) override;
	virtual void resize(int width, int height) override;
	virtual void show() override;

	// Todo: 需要知道是否被点击选中等
	virtual bool eventLoop(Event* event) override;

protected:
	void updataUI();

private:
	Point m_location;
	int m_nWidth = 100;
	int m_nHeight = 60;
	WindowWidget* m_parent = nullptr;
};


