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
	Painter(HDC hdc);
	virtual ~Painter() {}

	void setHDC(HDC hdc) { m_hdc = hdc; }

	void drawLine(int x1, int y1, int x2, int y2);
	void drawRect(int x1, int y1, int x2, int y2);

private:
	HDC m_hdc;
};






