#include "toolBarBtn.h"

#include "toolBar.h"

ToolbarBtn::ToolbarBtn(ToolBar* parent) : Object(parent) {
	// 在父容器中添加自己
	m_toolbar = parent;
	parent->addTBButton(this);
}


ToolbarBtn::~ToolbarBtn() {

}

/**
 * @brief 设置工具栏按钮文本
 * @param text 名字
 * @param toolbarHwnd 包含此工具栏按钮的窗口句柄
 */
void ToolbarBtn::setText(LPCTSTR text) {
	TBBUTTONINFO info = { sizeof(TBBUTTONINFO), TBIF_TEXT, 0, 0, 0, 0, 0, 0, (LPTSTR)text, sizeof(text) };
	SendMessage(m_toolbar->getHwnd(), TB_SETBUTTONINFO, getObjectId(), (LPARAM)&info);
}
