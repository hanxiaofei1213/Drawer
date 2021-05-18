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
	   
	virtual Shape* checkState(const Point& checkPoint) override;                    // ��鵱ǰ״̬
	virtual void draw() override;                                                   // �����Լ�

};
