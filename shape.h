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

	void setHDC(HDC hdc);                                       // ����HDC
	void setState(StateType state) { m_state = state; }         // ���õ�ǰ״̬
	void setShape(ShapeType shape) { m_shapeType = shape; }     // ��ǰ��״
 
	virtual Shape* checkState(const Point& checkPoint) = 0;     // ����Լ��Ƿ�ѡ��
	virtual void moveFunction(const Point& sPoint, const Point& dPoint) = 0;  // �ƶ�����
	virtual void zoomFunction(const Point& sPoint, const Point& dPoint) = 0;  // �Ŵ���С����
	virtual void draw() = 0;                                    // ���Լ�������


private:
	HDC m_hdc;                                  // HDC����
	Painter* m_painter;                         // ��ͼ����
	StateType m_state;                          // ��ǰ״̬
	ShapeType m_shapeType;                      // ��ǰ��״
};