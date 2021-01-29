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

	Line(HDC hdc);
	virtual ~Line();

	Point* getBegin() { return m_begin; }
	Point* getEnd() { return m_end; }

	void setBegin(const Point& begin);
	void setEnd(const Point& end);
	   
	virtual Shape* checkState(const Point& checkPoint) override;                    // ��鵱ǰ״̬
	virtual void moveFunction(const Point& sPoint, const Point& dPoint) override;   // �ƶ�����
	virtual void zoomFunction(const Point& sPoint, const Point& dPoint) override;   // ���ź���
	virtual void draw() override;                                                   // �����Լ�

private:
	Point* m_begin;
	Point* m_end;

};
