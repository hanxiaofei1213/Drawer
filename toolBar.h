#pragma once

#include "showObject.h"

class ToolbarBtn;


class ToolBar : public ShowObject {
public:
	ToolBar(ShowObject*);
	virtual ~ToolBar() {}

	void addTBButton(ToolbarBtn*);          // ����������ť��ӵ�������
};


