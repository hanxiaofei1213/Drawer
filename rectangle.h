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


	virtual Shape* checkState(const Point& checkPoint) override;                    // �жϵ�ǰ��״̬
	virtual void draw() override;                                                   // ���Լ�������


};


