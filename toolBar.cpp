
#include "toolBar.h"

#include <CommCtrl.h>

#include "toolBarBtn.h"

ToolBar::ToolBar(ShowObject* parent) : ShowObject(parent, TOOLBARCLASSNAME) {
	// 创建工具栏
	HWND nowhwnd = CreateWindowEx(
		0,
		TOOLBARCLASSNAME,
		NULL,
		WS_CHILD | TBSTYLE_WRAPABLE,
		0, 0, 0, 0,
		getParentHwnd(),
		NULL,
		getInstance(),   
		NULL
	);

	DWORD d2 = GetLastError();      // FixMe: 这里为什么说返回6呢？
	// 设置当前窗口句柄
	setNowHwnd(nowhwnd);
}


/**
 * @brief 将工具栏按钮添加到工具栏
 * @param 要添加的工具栏按钮
 */
void ToolBar::addTBButton(ToolbarBtn* boolbarBtn) {
	HWND hwnd = getHwnd();
	SendMessage(hwnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hwnd, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&boolbarBtn->getTBButton());
}


