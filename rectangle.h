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

	Rect(HDC hdc);
	virtual ~Rect();

	Point* getBegin() { return m_begin; }
	Point* getEnd() { return m_end; }

	void setBegin(const Point& begin);
	void setEnd(const Point& end);

	virtual Shape* checkState(const Point& checkPoint) override;                    // �жϵ�ǰ��״̬
	virtual void moveFunction(const Point& sPoint, const Point& dPoint) override;   // �ƶ�����
	virtual void zoomFunction(const Point& sPoint, const Point& dPoint) override;   // �Ŵ���С����
	virtual void draw() override;                                                   // ���Լ�������



private:
	Point* m_begin = nullptr;
	Point* m_end = nullptr;
};


