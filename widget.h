#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : widget.h
// Creator : 王文喜
// Data : 2021/1/18
// Comment : 窗体控件，将WNDCLASS等操作封装起来，拥有处理事件的能力，也拥有成为其他控件父控件的能力
//////////////////////////////////////////////////////////////////////////


#include <windows.h>

#include "showObject.h"

class MouseEvent;
class ButtonEvent;
class PaintEvent;

class Widget : public ShowObject {
public:
	Widget(ShowObject* a_parent);
	~Widget();

	virtual bool eventLoop(Event*) override;                       // 重写Object的事件循环
	
protected:
	virtual void mousePressEvent(MouseEvent*);                     // 处理鼠标按下的事件
	virtual void mouseMoveEvent(MouseEvent*);                      // 处理鼠标移动的事件
	virtual void mouseReleaseEvent(MouseEvent*);                   // 处理鼠标按下的事件
	virtual void paintEvent(PaintEvent*);                          // 处理重绘事件
	virtual void buttonPressEvent(ButtonEvent*);                   // 将按钮按下的事件分发到具体的按钮



private:
	
};
