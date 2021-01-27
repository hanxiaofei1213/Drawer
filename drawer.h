#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : drawer.h
// Creator : ����ϲ
// Data : 2021/1/22
// Comment : ��ͼ���������
//////////////////////////////////////////////////////////////////////////
#include "widget.h"

#include <vector>

#include "shape.h"

class ToolBar;
class ToolbarBtn;

class Drawer : public Widget{
public:

	Drawer();
	virtual ~Drawer();
	 
	void init();                                                 // һЩ��ʼ��
	virtual void drawAll();                                      // ������shape�����ڴ滭�壬һ������ʾ

protected:
	virtual void mousePressEvent(MouseEvent*) override;          // ������갴�µ��¼�
	virtual void mouseMoveEvent(MouseEvent*) override;           // ��������ƶ����¼�
	virtual void mouseReleaseEvent(MouseEvent*) override;        // ������갴�µ��¼�
	virtual void paintEvent(PaintEvent*) override;               // �����ػ��¼�
	virtual void buttonPressEvent(ButtonEvent*) override;        // ����ť���µ��¼��ַ�������İ�ť
	virtual Shape* checkAllShapeState(const Point&);             // �������shape��״̬

private:
	ToolBar* m_toolbar;                     // ������
	ToolbarBtn* m_arrowBBtn;                // ����ͷ״̬
	ToolbarBtn* m_lineTBBtn;                // ���ߵĹ�������ť
	ToolbarBtn* m_rectTBBtn;                // �����εĹ�������ť
	std::vector<Shape*> m_shapeList;        // ���shape������
	Shape::ShapeType m_shapeType;           // �����ʱ��״����
	Shape* m_tempShape;                     // ��ʱ��״
	Point* m_beginPoint;                    // ��ʼʱ�ĵ�
	HDC m_hdc;                              // ��ǰ����HDC
	RECT m_rc;                              // ��ǰ��������
	RECT m_toolbarRC;                       // ����������
	RECT m_flashArea;                       // Ҫˢ�µ�����
	HDC m_memHdc;                           // �ڴ�HDC
	HBITMAP m_memBitMap;                    // �ڴ滭��
	int m_nBitmapWidth;                     // �ڴ滭�����
	int m_nBitmapHeight;                    // �ڴ滭�����
};
