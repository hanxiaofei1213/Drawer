#include "toolBarBtn.h"

#include "toolBar.h"

ToolbarBtn::ToolbarBtn(ToolBar* parent) : Object(parent) {
	// �ڸ�����������Լ�
	m_toolbar = parent;
	parent->addTBButton(this);
}


ToolbarBtn::~ToolbarBtn() {

}

/**
 * @brief ���ù�������ť�ı�
 * @param text ����
 * @param toolbarHwnd �����˹�������ť�Ĵ��ھ��
 */
void ToolbarBtn::setText(LPCTSTR text) {
	TBBUTTONINFO info = { sizeof(TBBUTTONINFO), TBIF_TEXT, 0, 0, 0, 0, 0, 0, (LPTSTR)text, sizeof(text) };
	SendMessage(m_toolbar->getHwnd(), TB_SETBUTTONINFO, getObjectId(), (LPARAM)&info);
}
