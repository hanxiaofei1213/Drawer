#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : shape.h
// Creator : ����ϲ
// Data : 2021/1/21
// Comment : ��껭ͼ��ͼ�εĻ��࣬ӵ�м���Լ��Ƿ�ѡ�е���������֧���ƶ����Ŵ���С
//////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "painter.h"
#include "point.h"
#include "size.h"

class Shape {
public:
	enum class StateType {NOMAL, TOMOVE, TOZOOM};
	enum class ShapeType {NODEFINE, LINE, RECT};

	Shape(HDC);
	virtual ~Shape();

	Painter* getPainter() { return m_painter; }                               // ��û�ͼ
	StateType getState() { return m_state; }                                  // ��ȡ��ǰ״̬
	ShapeType getShape() { return m_shapeType; }                              // ��ȡ��ǰ��״
	Point* getBegin() { return m_beginPoint; }
	Point* getEnd() { return m_endPoint; }
	Size getSize() { return { m_endPoint->x() - m_beginPoint->x(), m_endPoint->y() - m_beginPoint->y() }; }

	void setHDC(HDC hdc);                                                     // ����HDC
	void setState(StateType state) { m_state = state; }                       // ���õ�ǰ״̬
	void setShape(ShapeType shape) { m_shapeType = shape; }                   // ��ǰ��״
	void setBegin(const Point& beginPoint);
	void setEnd(const Point& endPoint);
 
	virtual Shape* checkState(const Point& checkPoint) = 0;                   // ����Լ��Ƿ�ѡ��
	virtual void resize(int width, int height);                               
	virtual void moveFunction(const Point& sPoint, const Point& dPoint);      // �ƶ�����
	virtual void zoomFunction(const Point& sPoint, const Point& dPoint);      // �Ŵ���С����
	virtual void draw() = 0;                                                  // ���Լ�������


private:
	HDC m_hdc = nullptr;                                  // HDC����
	Painter* m_painter = nullptr;                         // ��ͼ����
	StateType m_state = StateType::NOMAL;                 // ��ǰ״̬
	ShapeType m_shapeType = ShapeType::NODEFINE;          // ��ǰ��״
	Point* m_beginPoint = nullptr;
	Point* m_endPoint = nullptr;
};