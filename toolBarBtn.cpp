#include "toolBarBtn.h"

#include "toolBar.h"

ToolbarBtn::ToolbarBtn(ToolBar* parent) : Object(parent)
{
	m_bitmap = I_IMAGENONE;
	m_state = TBSTATE_ENABLED;
	m_style = BTNS_AUTOSIZE;
	m_string = (INT_PTR)L"tbb";
	m_tbbutton = { m_bitmap, getObjectId(), m_state, m_style, {0}, 0, m_string };

	// �ڹ�����������Լ�
	m_toolbar = parent;
	parent->addTBButton(this);
}


ToolbarBtn::~ToolbarBtn()
{
}

/**
 * @brief ���ù�������ť�ı�
 * @param a_text ����
 * @param a_toolbarHwnd �����˹�������ť�Ĵ��ھ��
 */
void ToolbarBtn::setText(LPCTSTR text)
{
	TBBUTTONINFO info = { sizeof(TBBUTTONINFO), TBIF_TEXT, 0, 0, 0, 0, 0, 0, (LPTSTR)text, sizeof(text) };
	SendMessage(m_toolbar->getHwnd(), TB_SETBUTTONINFO, getObjectId(), (LPARAM)&info);
}
