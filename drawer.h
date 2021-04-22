#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : drawer.h
// Creator : ����ϲ
// Data : 2021/1/22
// Comment : ��ͼ���������
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
	 
	void init();                                                       // һЩ��ʼ��
	virtual void drawAll();                                            // ������shape�����ڴ滭�壬һ������ʾ

protected:
	virtual void mousePressEvent(MouseEvent* event) override;          // ������갴�µ��¼�
	virtual void mouseMoveEvent(MouseEvent* event) override;           // ��������ƶ����¼�
	virtual void mouseReleaseEvent(MouseEvent* event) override;        // ������갴�µ��¼�
	virtual void paintEvent(PaintEvent* event) override;               // �����ػ��¼�
	virtual void buttonPressEvent(ButtonEvent* event) override;        // ����ť���µ��¼��ַ�������İ�ť
	virtual Shape* checkAllShapeState(const Point& point);             // �������shape��״̬

private:
	ToolBar* m_toolbar = nullptr;                                      // ������
	ToolbarBtn* m_arrowBBtn = nullptr;                                 // ����ͷ״̬
	ToolbarBtn* m_lineTBBtn = nullptr;                                 // ���ߵĹ�������ť
	ToolbarBtn* m_rectTBBtn = nullptr;                                 // �����εĹ�������ť
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
};
