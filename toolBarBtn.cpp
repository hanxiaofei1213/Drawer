#include "toolBarBtn.h"

#include "toolBar.h"

ToolbarBtn::ToolbarBtn(ToolBar* parent) : Object(parent)
{
	m_bitmap = I_IMAGENONE;
	m_state = TBSTATE_ENABLED;
	m_style = BTNS_AUTOSIZE;
	m_string = (INT_PTR)L"tbb";
	m_tbbutton = { m_bitmap, getObjectId(), m_state, m_style, {0}, 0, m_string };

	// 在工具栏中添加自己
	m_toolbar = parent;
	parent->addTBButton(this);
}


ToolbarBtn::~ToolbarBtn()
{
}

/**
 * @brief 设置工具栏按钮文本
 * @param a_text 名字
 * @param a_toolbarHwnd 包含此工具栏按钮的窗口句柄
 */
void ToolbarBtn::setText(LPCTSTR text)
{
	TBBUTTONINFO info = { sizeof(TBBUTTONINFO), TBIF_TEXT, 0, 0, 0, 0, 0, 0, (LPTSTR)text, sizeof(text) };
	SendMessage(m_toolbar->getHwnd(), TB_SETBUTTONINFO, getObjectId(), (LPARAM)&info);
}
