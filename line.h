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

	Line(HDC hdc);
	virtual ~Line();
	   
	virtual Shape* checkState(const Point& checkPoint) override;                    // 检查当前状态
	virtual void draw() override;                                                   // 画出自己

};
