#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : tbButton.h
// Creator : 王文喜
// Data : 2021/1/22
// Comment : 工具栏按钮类，职责只是被添加到工具栏，不具有展示功能，也并不通过CreateWindow创建
//////////////////////////////////////////////////////////////////////////


#include "object.h"

#include <commctrl.h>
#include <windows.h>

class ToolBar;

class ToolbarBtn : public Object {
public:
	ToolbarBtn(ToolBar*);
	virtual ~ToolbarBtn();

	TBBUTTON& getTBButton() { return m_tbbutton; }
	
	void setText(LPCTSTR);              // 设置工具栏按钮的文本

private:
	int m_bitmap;                             // 按钮的位图
	BYTE m_state;                             // 位图的状态
	BYTE m_style;                             // 位图风格
	INT_PTR m_string;                         // 按钮的文字
	TBBUTTON  m_tbbutton;                     // 保存工具栏按钮
	ToolBar* m_toolbar;                       // 保存存放自己的工具栏
};

