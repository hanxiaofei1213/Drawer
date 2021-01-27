#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : painter.h
// Creator : ����ϲ
// Data : 2021/1/21
// Comment : ��GDI��ͼ�ĺ�����װ����
//////////////////////////////////////////////////////////////////////////

#include <windows.h>


class Painter {
public:
	Painter(HDC a_hdc);
	virtual ~Painter() {}

	void setHDC(HDC a_hdc) { m_hdc = a_hdc; }

	void drawLine(int, int, int, int);
	void drawRect(int, int, int, int);

private:
	HDC m_hdc;
};






