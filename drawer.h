#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : drawer.h
// Creator : 王文喜
// Data : 2021/1/22
// Comment : 画图工具入口类
//////////////////////////////////////////////////////////////////////////
#include "widget.h"

#include <vector>

#include "shape.h"

class ToolBar;
class ToolbarBtn;
class Shape;

class Drawer : public Widget{
public:

	Drawer();
	virtual ~Drawer();

protected:
	virtual void mousePressEvent(MouseEvent*) override;          // 处理鼠标按下的事件
	virtual void mouseMoveEvent(MouseEvent*) override;           // 处理鼠标移动的事件
	virtual void mouseReleaseEvent(MouseEvent*) override;        // 处理鼠标按下的事件
	virtual void paintEvent(PaintEvent*) override;               // 处理重绘事件
	virtual void buttonPressEvent(ButtonEvent*) override;        // 将按钮按下的事件分发到具体的按钮
	virtual Shape* checkAllShapeState(const Point&);             // 检查所有shape的状态

private:
	ToolBar* m_toolbar;                     // 工具栏
	ToolbarBtn* m_arrowBBtn;                // 鼠标箭头状态
	ToolbarBtn* m_lineTBBtn;                // 画线的工具栏按钮
	ToolbarBtn* m_rectTBBtn;                // 画矩形的工具栏按钮
	std::vector<Shape*> m_shapeList;        // 存放shape的容器
	Shape::ShapeType m_shapeType;           // 存放临时形状类型
	Shape* m_tempShape;                     // 临时形状
	Point* m_beginPoint;                    // 开始时的点
};
