#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : rectangle.h
// Creator : 王文喜
// Data : 2021/1/21
// Comment : 鼠标绘画矩形，继承shape
//////////////////////////////////////////////////////////////////////////

#include "shape.h"

class Rect : public Shape {
public:
	const int m_nNearLevel = 10;    // 相近程度

	Rect(HDC hdc);
	virtual ~Rect();

	Point* getBegin() { return m_begin; }
	Point* getEnd() { return m_end; }

	void setBegin(const Point& begin);
	void setEnd(const Point& end);

	virtual Shape* checkState(const Point& checkPoint) override;                    // 判断当前的状态
	virtual void moveFunction(const Point& sPoint, const Point& dPoint) override;   // 移动函数
	virtual void zoomFunction(const Point& sPoint, const Point& dPoint) override;   // 放大缩小函数
	virtual void draw() override;                                                   // 将自己画出来



private:
	Point* m_begin = nullptr;
	Point* m_end = nullptr;
};


