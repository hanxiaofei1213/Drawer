#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : widget.h
// Creator : 王文喜
// Data : 2021/1/18
// Comment : 窗体控件，将WNDCLASS等操作封装起来，拥有成为其他控件父控件的能力
//////////////////////////////////////////////////////////////////////////

#include <windows.h>

#include "WindowWidget.h"

class MouseEvent;
class ButtonEvent;
class PaintEvent;

class Widget : public WindowWidget {
public:
	Widget(WindowWidget* parent = nullptr);
	virtual ~Widget();

};
