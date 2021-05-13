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
class WindowLessMenu;

class Drawer : public Widget{
public:
	Drawer();
	virtual ~Drawer();
	 
	void init();                                                       // 一些初始化
	void initContextMenu(); 
	virtual void drawAll();                                            // 将所有shape画到内存画板，一次性显示

	/**
	 * @brief 处理鼠标右键点击事件
	 */
	void dealRightBtnEvent(MouseEvent* event);     

protected:
	virtual void mousePressEvent(MouseEvent* event) override;          // 处理鼠标按下的事件
	virtual void mouseMoveEvent(MouseEvent* event) override;           // 处理鼠标移动的事件
	virtual void mouseReleaseEvent(MouseEvent* event) override;        // 处理鼠标按下的事件
	virtual void paintEvent(PaintEvent* event) override;               // 处理重绘事件
	virtual Shape* checkAllShapeState(const Point& point);             // 检查所有shape的状态

	/**
	 * @brief 处理右键菜单中action事件
	 */
	void dealContextMenuAction(MouseEvent* event);

private:
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
	WindowLessMenu* m_pContextMenu = nullptr;                          // 右键菜单
};
