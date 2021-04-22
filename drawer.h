#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : drawer.h
// Creator : 王文喜
// Data : 2021/1/22
// Comment : 画图工具入口类
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include "shape.h"

#include "widget.h"

class ToolBar;
class ToolbarBtn;

class Drawer : public Widget{
public:
	Drawer();
	virtual ~Drawer();
	 
	void init();                                                       // 一些初始化
	virtual void drawAll();                                            // 将所有shape画到内存画板，一次性显示

protected:
	virtual void mousePressEvent(MouseEvent* event) override;          // 处理鼠标按下的事件
	virtual void mouseMoveEvent(MouseEvent* event) override;           // 处理鼠标移动的事件
	virtual void mouseReleaseEvent(MouseEvent* event) override;        // 处理鼠标按下的事件
	virtual void paintEvent(PaintEvent* event) override;               // 处理重绘事件
	virtual void buttonPressEvent(ButtonEvent* event) override;        // 将按钮按下的事件分发到具体的按钮
	virtual Shape* checkAllShapeState(const Point& point);             // 检查所有shape的状态

private:
	ToolBar* m_toolbar = nullptr;                                      // 工具栏
	ToolbarBtn* m_arrowBBtn = nullptr;                                 // 鼠标箭头状态
	ToolbarBtn* m_lineTBBtn = nullptr;                                 // 画线的工具栏按钮
	ToolbarBtn* m_rectTBBtn = nullptr;                                 // 画矩形的工具栏按钮
	std::vector<Shape*> m_shapeList;                                   // 存放shape的容器
	Shape::ShapeType m_shapeType = Shape::ShapeType::NODEFINE;         // 存放临时形状类型
	Shape* m_tempShape = nullptr;                                      // 临时形状
	Point* m_beginPoint = nullptr;                                     // 开始时的点
	HDC m_hdc = GetDC(getHwnd());                                      // 当前窗口HDC
	RECT m_rc = { 0 };                                                 // 当前窗口区域
	RECT m_toolbarRC = { 0 };                                          // 工具栏区域
	RECT m_flashArea = { 0 };                                          // 要刷新的区域
	HDC m_memHdc = nullptr;                                            // 内存HDC
	HBITMAP m_memBitMap = nullptr;                                     // 内存画布
	int m_nBitmapWidth = 0;                                            // 内存画布宽度
	int m_nBitmapHeight = 0;                                           // 内存画布宽度
};
