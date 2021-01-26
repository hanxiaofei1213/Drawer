
#include "toolBar.h"

#include <CommCtrl.h>

#include "toolBarBtn.h"

ToolBar::ToolBar(ShowObject* a_parent) : ShowObject(a_parent, TOOLBARCLASSNAME)
{
	// ����������
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

	DWORD d2 = GetLastError();      // FixMe: ����Ϊʲô˵����6�أ�
	// ���õ�ǰ���ھ��
	setNowHwnd(nowhwnd);
}


/**
 * @brief ����������ť��ӵ�������
 * @param Ҫ��ӵĹ�������ť
 */
void ToolBar::addTBButton(ToolbarBtn* a_tbb)
{
	HWND hwnd = getHwnd();
	SendMessage(hwnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hwnd, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&a_tbb->getTBButton());
}


