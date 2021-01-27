#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : shape.h
// Creator : ����ϲ
// Data : 2021/1/21
// Comment : ��껭ͼ��ͼ�εĻ��࣬ӵ�м���Լ��Ƿ�ѡ�е���������֧���ƶ����Ŵ���С
//////////////////////////////////////////////////////////////////////////
#include "painter.h"

#include <windows.h>

#include "point.h"

class Shape {
public:
	enum class StateType {NOMAL, TOMOVE, TOZOOM};
	enum class ShapeType {NODEFINE, LINE, RECT};

	Shape(HDC);
	virtual ~Shape();


	Painter* getPainter() { return m_painter; }                 // ��û�ͼ
	StateType getState() { return m_state; }                    // ��ȡ��ǰ״̬
	ShapeType getShape() { return m_shapeType; }                // ��ȡ��ǰ��״

	void setHDC(HDC a_hdc);                                     // ����HDC
	void setState(StateType a_state) { m_state = a_state; }     // ���õ�ǰ״̬
	void setShape(ShapeType a_shape) { m_shapeType = a_shape; } // ��ǰ��״
 
	virtual Shape* checkState(const Point&) = 0;                // ����Լ��Ƿ�ѡ��
	virtual void moveFunction(const Point&, const Point&) = 0;  // �ƶ�����
	virtual void zoomFunction(const Point&, const Point&) = 0;  // �Ŵ���С����

	virtual void draw() = 0;                                    // ���Լ�������


private:
	HDC m_hdc;                                  // HDC����
	Painter* m_painter;                         // ��ͼ����
	StateType m_state;                          // ��ǰ״̬
	ShapeType m_shapeType;                      // ��ǰ��״
};