#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : rectangle.h
// Creator : ����ϲ
// Data : 2021/1/21
// Comment : ���滭���Σ��̳�shape
//////////////////////////////////////////////////////////////////////////


#include "shape.h"


class Rect : public Shape {
public:
	const int m_nNearLevel = 10;    // ����̶�

	Rect(HDC);
	virtual ~Rect();

	Point* getBegin() { return m_begin; }
	Point* getEnd() { return m_end; }

	void setBegin(const Point&);
	void setEnd(const Point&);

	virtual Shape* checkState(const Point&) override;                 // �жϵ�ǰ��״̬
	virtual void moveFunction(const Point&, const Point&) override;   // �ƶ�����
	virtual void zoomFunction(const Point&, const Point&) override;   // �Ŵ���С����
	virtual void draw() override;                                     // ���Լ�������



private:
	Point* m_begin;
	Point* m_end;
};


