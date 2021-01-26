#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : eventLoop.h
// Creator : 王文喜
// Data : 2021/1/19
// Comment : 事件循环，负责消息打包和事件分发
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "object.h"

class Event;
class MouseEvent;
class ButtonEvent;
class PaintEvent;

class EventLoop {
public:
	EventLoop();
	virtual ~EventLoop();

	Event* packageMessage(HWND, UINT, WPARAM, LPARAM, PAINTSTRUCT*);       // 将过程函数的消息打包成事件
	bool event();                                            // 分发事件

protected:
	Object* calculateDestObject(HWND);                       // 获得目的对象的this指针
	MouseEvent* packageMouseMsg(HWND, UINT, WPARAM, LPARAM); // 将鼠标消息打包成事件
	ButtonEvent* packageBtnMsg(HWND, UINT, WPARAM, LPARAM);  // 将按钮消息打包成事件
	PaintEvent* packagePaintMsg(HWND, PAINTSTRUCT*);         // 将绘画消息打包成事件

private:
	Event* m_event;                                          // 要处理的事件
	
};
