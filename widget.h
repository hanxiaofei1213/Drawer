#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : widget.h
// Creator : ����ϲ
// Data : 2021/1/18
// Comment : ����ؼ�����WNDCLASS�Ȳ�����װ������ӵ�г�Ϊ�����ؼ����ؼ�������
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
