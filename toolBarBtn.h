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
	int m_bitmap;                             // ��ť��λͼ
	BYTE m_state;                             // λͼ��״̬
	BYTE m_style;                             // λͼ���
	INT_PTR m_string;                         // ��ť������
	TBBUTTON  m_tbbutton;                     // ���湤������ť
	ToolBar* m_toolbar;                       // �������Լ��Ĺ�����
};

