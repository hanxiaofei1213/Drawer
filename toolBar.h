#pragma once

#include "showObject.h"

class ToolbarBtn;


class ToolBar : public ShowObject {
public:
	ToolBar(ShowObject* parent);
	virtual ~ToolBar() {}

	void addTBButton(ToolbarBtn* boolbarBtn);       // 将工具栏按钮添加到工具栏
};


