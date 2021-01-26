#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : line.h
// Creator : ����ϲ
// Data : 2021/1/22
// Comment : ��ֱ�ߵ��࣬�̳�shape
//////////////////////////////////////////////////////////////////////////


#include "shape.h"

class Line : public Shape {
public:
	const int m_nNearLevel = 10;

	Line(HDC);
	virtual ~Line();

	Point* getBegin() { return m_begin; }
	Point* getEnd() { return m_end; }

	void setBegin(const Point&);
	void setEnd(const Point&);

	virtual Shape* checkState(const Point&) override;                 // ��鵱ǰ״̬
	virtual void moveFunction(const Point&, const Point&) override;   // �ƶ�����
	virtual void zoomFunction(const Point&, const Point&) override;   // ���ź���
	virtual void draw() override;                                     // �����Լ�

private:
	Point* m_begin;
	Point* m_end;

};
