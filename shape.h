#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : shape.h
// Creator : 王文喜
// Data : 2021/1/21
// Comment : 鼠标画图的图形的基类，拥有检测自己是否被选中的能力，并支持移动，放大缩小
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


	Painter* getPainter() { return m_painter; }                               // 获得画图
	StateType getState() { return m_state; }                                  // 获取当前状态
	ShapeType getShape() { return m_shapeType; }                              // 获取当前形状

	void setHDC(HDC hdc);                                                     // 设置HDC
	void setState(StateType state) { m_state = state; }                       // 设置当前状态
	void setShape(ShapeType shape) { m_shapeType = shape; }                   // 当前形状
 
	virtual Shape* checkState(const Point& checkPoint) = 0;                   // 检查自己是否被选中
	virtual void moveFunction(const Point& sPoint, const Point& dPoint) = 0;  // 移动函数
	virtual void zoomFunction(const Point& sPoint, const Point& dPoint) = 0;  // 放大缩小函数
	virtual void draw() = 0;                                                  // 将自己画出来


private:
	HDC m_hdc = nullptr;                                  // HDC对象
	Painter* m_painter = nullptr;                         // 画图对象
	StateType m_state = StateType::NOMAL;                 // 当前状态
	ShapeType m_shapeType = ShapeType::NODEFINE;          // 当前形状
};