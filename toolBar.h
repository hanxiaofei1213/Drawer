#pragma once

#include "WindowWidget.h"

class ToolbarBtn;


class ToolBar : public WindowWidget {
public:
	ToolBar(WindowWidget* parent);
	virtual ~ToolBar() {}

	void addTBButton(ToolbarBtn* boolbarBtn);       // ����������ť��ӵ�������
};


