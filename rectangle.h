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


	virtual Shape* checkState(const Point& checkPoint) override;                    // 判断当前的状态
	virtual void draw() override;                                                   // 将自己画出来


};


