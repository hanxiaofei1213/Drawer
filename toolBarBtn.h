#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : tbButton.h
// Creator : ����ϲ
// Data : 2021/1/22
// Comment : ��������ť�ְ࣬��ֻ�Ǳ���ӵ���������������չʾ���ܣ�Ҳ����ͨ��CreateWindow����
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
	
	void setText(LPCTSTR text);               // ���ù�������ť���ı�

private:
	int m_bitmap = I_IMAGENONE;               // ��ť��λͼ
	BYTE m_state = TBSTATE_ENABLED;           // λͼ��״̬
	BYTE m_style = BTNS_AUTOSIZE;             // λͼ���
	INT_PTR m_string = (INT_PTR)L"tbb";       // ��ť������
	TBBUTTON  m_tbbutton = { m_bitmap, getObjectId(), m_state, m_style, {0}, 0, m_string };  // ���湤������ť
	ToolBar* m_toolbar = nullptr;             // �������Լ��Ĺ�����
};

