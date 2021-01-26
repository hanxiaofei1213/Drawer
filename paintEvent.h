#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : paintEvent.h
// Creator : ����ϲ
// Data : 2021/1/21
// Comment : �ѻ�����Ϣ��װ�ɻ����¼��������ṩhdc����
//////////////////////////////////////////////////////////////////////////


#include <windows.h>

#include "event.h"


class PaintEvent : public Event {
public:
	PaintEvent(HWND, PAINTSTRUCT*);
	virtual ~PaintEvent();

	HDC getHDC() { return m_hdc; }                       // ��ȡ��ͼHDC

private:
	HDC m_hdc;                                           // ��ͼ��HDC
	HWND m_hwnd;                                         // ���
	PAINTSTRUCT* m_ps;                                    // �ṹ��
};




