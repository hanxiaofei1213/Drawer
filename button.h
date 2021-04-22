#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : button.h
// Creator : 王文喜
// Data : 2021/1/18
// Comment : 按钮控件，将创建按钮操作封装起来
//////////////////////////////////////////////////////////////////////////

#include "WindowWidget.h"

class Button : public WindowWidget
{
public:
	Button(WindowWidget* parent);
	virtual ~Button();
};

