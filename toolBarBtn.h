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
	ToolbarBtn(ToolBar* parent);
	virtual ~ToolbarBtn();

	TBBUTTON& getTBButton() { return m_tbbutton; }
	
	void setText(LPCTSTR text);               // 设置工具栏按钮的文本

private:
	int m_bitmap = I_IMAGENONE;               // 按钮的位图
	BYTE m_state = TBSTATE_ENABLED;           // 位图的状态
	BYTE m_style = BTNS_AUTOSIZE;             // 位图风格
	INT_PTR m_string = (INT_PTR)L"tbb";       // 按钮的文字
	TBBUTTON  m_tbbutton = { m_bitmap, getObjectId(), m_state, m_style, {0}, 0, m_string };  // 保存工具栏按钮
	ToolBar* m_toolbar = nullptr;             // 保存存放自己的工具栏
};

