#pragma once

#include "showObject.h"

class ToolbarBtn;


class ToolBar : public ShowObject {
public:
	ToolBar(ShowObject* parent);
	virtual ~ToolBar() {}

	void addTBButton(ToolbarBtn* boolbarBtn);       // ����������ť��ӵ�������
};


