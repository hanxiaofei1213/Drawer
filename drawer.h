#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : drawer.h
// Creator : ����ϲ
// Data : 2021/1/22
// Comment : ��ͼ���������
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include <Windows.h>
#include "shape.h"

#include "widget.h"

class MouseWheelEvent;
class ToolBar;
class ToolbarBtn;
class WindowLessMenu;


class Drawer : public Widget{
public:
	Drawer();
	virtual ~Drawer();
	 
	void init();                                                       // һЩ��ʼ��
	void initContextMenu(); 
	void initGDI();
	virtual void drawAll();                                            // ������shape�����ڴ滭�壬һ������ʾ

	/**
	 * @brief ��������Ҽ�����¼�
	 */
	void dealRightBtnEvent(MouseEvent* event);     

protected:
	virtual void mousePressEvent(MouseEvent* event) override;          // ������갴�µ��¼�
	virtual void mouseMoveEvent(MouseEvent* event) override;           // ��������ƶ����¼�
	virtual void mouseReleaseEvent(MouseEvent* event) override;        // ������갴�µ��¼�
	virtual void paintEvent(PaintEvent* event) override;               // �����ػ��¼�
	virtual void mouseDropEvent(MouseDropEvent* event) override;
	virtual void mouseWheelEvent(MouseWheelEvent* event) override;
	virtual Shape* checkAllShapeState(const Point& point);             // �������shape��״̬

	/**
	 * @brief �����Ҽ��˵���action�¼�
	 */
	void dealContextMenuAction(MouseEvent* event);

private:
	std::vector<Shape*> m_shapeList;                                   // ���shape������
	Shape::ShapeType m_shapeType = Shape::ShapeType::NODEFINE;         // �����ʱ��״����
	Shape* m_tempShape = nullptr;                                      // ��ʱ��״
	Point* m_beginPoint = nullptr;                                     // ��ʼʱ�ĵ�
	HDC m_hdc = GetDC(getHwnd());                                      // ��ǰ����HDC
	RECT m_rc = { 0 };                                                 // ��ǰ��������
	RECT m_toolbarRC = { 0 };                                          // ����������
	RECT m_flashArea = { 0 };                                          // Ҫˢ�µ�����
	HDC m_memHdc = nullptr;                                            // �ڴ�HDC
	HBITMAP m_memBitMap = nullptr;                                     // �ڴ滭��
	int m_nBitmapWidth = 0;                                            // �ڴ滭�����
	int m_nBitmapHeight = 0;                                           // �ڴ滭�����
	WindowLessMenu* m_pContextMenu = nullptr;                          // �Ҽ��˵�
	HPEN m_pen;
	int m_nPenWidth = 1;
};
