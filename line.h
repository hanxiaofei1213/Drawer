#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : line.h
// Creator : 王文喜
// Data : 2021/1/22
// Comment : 画直线的类，继承shape
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

	virtual Shape* checkState(const Point&) override;                 // 检查当前状态
	virtual void moveFunction(const Point&, const Point&) override;   // 移动函数
	virtual void zoomFunction(const Point&, const Point&) override;   // 缩放函数
	virtual void draw() override;                                     // 画出自己

private:
	Point* m_begin;
	Point* m_end;

};
