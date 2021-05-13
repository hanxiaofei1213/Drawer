#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : eventLoop.h
// Creator : 王文喜
// Data : 2021/1/19
// Comment : 事件循环，负责消息打包成事件并把事件分发给对应的widget
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "object.h"

class ButtonEvent;
class Event;
class MouseDropEvent;
class MouseEvent;
class PaintEvent;
class Point;

class EventLoop {
public:
	EventLoop();
	virtual ~EventLoop();

	Event* packageMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* ps); // 将过程函数的消息打包成事件
	bool event(Event* toSendEvent);                                                     // 分发事件

protected:
	Object* calculateDestObject(HWND hwnd);                                             // 获得目的对象的this指针
	MouseEvent* packageMouseMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); // 将鼠标消息打包成事件
	ButtonEvent* packageBtnMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  // 将按钮消息打包成事件
	PaintEvent* packagePaintMsg(HWND hwnd, PAINTSTRUCT* ps);                            // 将绘画消息打包成事件

	/**
	 * @brief 打包鼠标拖动消息成事件
	 */
	MouseDropEvent* packageMouseDropMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	/**
	 * @brief 检查鼠标拖动的方向
	 */
	bool checkMouseDropType(Point* begin, Point* end, MouseDropEvent* event);
};
