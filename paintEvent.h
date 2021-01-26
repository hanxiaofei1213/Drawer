#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : paintEvent.h
// Creator : 王文喜
// Data : 2021/1/21
// Comment : 把绘制消息封装成绘制事件，向外提供hdc属性
//////////////////////////////////////////////////////////////////////////


#include <windows.h>

#include "event.h"


class PaintEvent : public Event {
public:
	PaintEvent(HWND, PAINTSTRUCT*);
	virtual ~PaintEvent();

	HDC getHDC() { return m_hdc; }                       // 获取绘图HDC

private:
	HDC m_hdc;                                           // 绘图用HDC
	HWND m_hwnd;                                         // 句柄
	PAINTSTRUCT* m_ps;                                    // 结构体
};




