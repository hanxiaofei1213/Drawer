#include "buttonEvent.h"
#include "line.h"
#include "MouseDropEvent.h"
#include "mouseEvent.h"
#include "paintEvent.h"
#include "rectangle.h"
#include "toolBar.h"
#include "toolBarBtn.h"
#include "WindowLessAction.h"
#include "WindowLessMenu.h"

#include "Drawer.h"

// only for test
#include <iostream>

// ���캯��
Drawer::Drawer() : Widget(NULL) {
	// �����Լ���һЩ����
	setText(TEXT("Drawer"));
	resize(800, 600);

	m_beginPoint = new Point;

	init();
	initContextMenu();
}

// ��������
Drawer::~Drawer() {
	if (m_memHdc)
		DeleteDC(m_memHdc);
	if (m_memBitMap)
		DeleteObject(m_memBitMap);
	ReleaseDC(getHwnd(), m_hdc);
	if (m_tempShape)
		delete m_tempShape;
	for (auto i : m_shapeList)
		delete i;

	delete m_beginPoint;
}


/**
 * @brief һЩ������ĳ�ʼ��
 */
void Drawer::init() {
	// ��ȡ���������ܴ��ڵ�λ�ô�С
	GetWindowRect(getHwnd(), &m_rc);

	// ���㻭����С
	int nleftUpX = m_toolbarRC.left;
	int nleftUpY = m_toolbarRC.top;

	m_nBitmapWidth = 800;
	m_nBitmapHeight = 600;
	m_flashArea.left = 0;
	m_flashArea.top = 0;
	m_flashArea.right = 800;
	m_flashArea.bottom = 600;
}

void Drawer::initContextMenu()
{
	m_pContextMenu = new WindowLessMenu(this);
	WindowLessAction* arrAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* lineAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* rectAction = new WindowLessAction(m_pContextMenu);

	arrAction->setText(L"arr");
	lineAction->setText(L"line");
	rectAction->setText(L"rect");

	m_pContextMenu->addAction(arrAction);
	m_pContextMenu->addAction(lineAction);
	m_pContextMenu->addAction(rectAction);
	m_pContextMenu->setVisiable(false);
}

/**
 * @brief ������ͼ�λ��Ƶ��ڴ滭����һ��չʾȫ��
 */
void Drawer::drawAll() {
	m_memHdc = CreateCompatibleDC(m_hdc);
	m_memBitMap = CreateCompatibleBitmap(m_hdc, m_nBitmapWidth, m_nBitmapHeight);
	static HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(m_memHdc, m_memBitMap);
	SelectObject(m_memHdc, hbrush);
	Rectangle(m_memHdc, 0, 0, m_nBitmapWidth, m_nBitmapHeight);

	// ���ڴ滭���ϻ�
	for (auto shape : m_shapeList) {
		shape->setHDC(m_memHdc);
		shape->draw();
	}
	// �����ʱshapeҲ��
	if (m_tempShape) {
		m_tempShape->setHDC(m_memHdc);
		m_tempShape->draw();
	}

	// �ᵽ��ʵ����
	int loc = m_toolbarRC.bottom - m_toolbarRC.top;
	BitBlt(m_hdc, 0, loc, m_nBitmapWidth, m_nBitmapHeight, m_memHdc, 0, loc, SRCCOPY);

	// �ָ�ԭ����HDC
	for (auto shape : m_shapeList)
		shape->setHDC(m_hdc);
	if (m_tempShape)
		m_tempShape->setHDC(m_hdc);

	// �ͷŶ���
	DeleteObject(m_memBitMap);
	DeleteDC(m_memHdc);
}

void Drawer::dealRightBtnEvent(MouseEvent* event)
{
	Point* loc = event->getPos();
	m_pContextMenu->move(loc->x(), loc->y());
}


/**
 * @brief ����ť�����¼�
 * @param event �¼�
 * @remark ���ﴴ���Ķ���
 */
void Drawer::mousePressEvent(MouseEvent* event) {	
	if (event->getButtonType() == MouseEvent::ButtonType::RIGHTBUTTON)
		dealRightBtnEvent(event);

	if (event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;  

	// �����Ҽ��˵��¼�
	dealContextMenuAction(event);

	// ��ȡ��꿪ʼ�ĵ�
	m_beginPoint->setX(event->getPos()->x());
	m_beginPoint->setY(event->getPos()->y());

	switch (m_shapeType) {
	case Shape::ShapeType::NODEFINE:
		m_tempShape = checkAllShapeState(*m_beginPoint);
		break;
	case Shape::ShapeType::LINE: 
	{
		Line* line = new Line(m_hdc);
		line->setBegin(*m_beginPoint);
		line->setEnd(*m_beginPoint);
		m_tempShape = (Shape*)line;
		break;
	}
	case Shape::ShapeType::RECT: 
	{
		Rect* rect = new Rect(m_hdc);
		rect->setBegin(*m_beginPoint);
		rect->setBegin(*m_beginPoint);
		m_tempShape = (Shape*)rect;
		break;
	}
	}
}

/**
 * @brief ����ť�ƶ��¼�
 */
void Drawer::mouseMoveEvent(MouseEvent* event) {
	// ����������������£�������
	if (event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;

	// ���ûѡ���κ�shape���򲻴���
	if (!m_tempShape)
		return;
	
	Point endPoint(event->getPos()->x(), event->getPos()->y());
	switch (m_shapeType) {
	// ������Ϊarrowģʽ
	case Shape::ShapeType::NODEFINE:
		if (m_tempShape->getState() == Shape::StateType::TOMOVE)
			m_tempShape->moveFunction(*m_beginPoint, endPoint);
		else if (m_tempShape->getState() == Shape::StateType::TOZOOM)
			m_tempShape->zoomFunction(*m_beginPoint, endPoint);
		m_beginPoint->setX(endPoint.x());
		m_beginPoint->setY(endPoint.y());
		break;
	case Shape::ShapeType::LINE: 
	{
		Line* line = (Line*)m_tempShape;
		line->setEnd(endPoint);
		break;
	}
	case Shape::ShapeType::RECT: 
	{
		Rect* rect = (Rect*)m_tempShape;
		rect->setEnd(endPoint);
		break;
	}
	}

	// �����е�չʾ����������������������ǰtempShape
	drawAll();
}


/**
 * @brief ����ť�ſ��¼�
 */
void Drawer::mouseReleaseEvent(MouseEvent* event) {
	if (event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;

	// �����ǰshapeΪ�գ��򲻴���
	if (!m_tempShape)
		return;

	// �����ǰ��״ΪNORMAL����Ϊ�´�����shape����ӵ�list��
	if (m_tempShape->getState() == Shape::StateType::NOMAL)
		m_shapeList.push_back(m_tempShape);
	else 
		m_tempShape->setState(Shape::StateType::NOMAL);

	m_tempShape = nullptr;

	// ǿ���ػ棬������ʱ��״��ֻ��ʾpaintEvent�е���״
	InvalidateRect(getHwnd(), &m_flashArea, TRUE);
}

/**
 * @brief �����ػ��¼�
 */
void Drawer::paintEvent(PaintEvent* event) {
	drawAll();
}

void Drawer::mouseDropEvent(MouseDropEvent* event)
{
	switch (event->getDropType())
	{
	case MouseDropEvent::DropType::LEFT2RIGHT:
		// Todo: ���������л�
		break;
	case MouseDropEvent::DropType::RIGHT2LEFT:
		break;
	case MouseDropEvent::DropType::TOP2BOTTOM:
		DestroyWindow(getHwnd());
		break;
	case MouseDropEvent::DropType::BOTTOM2TOP:
		// Todo: ����ͼƬ

		break;
	default:
		break;
	}
}

/**
 * @brief ��鵱ǰ����shape��״̬
 * @param point �������λ��
 * @return �����shape��ѡ�У�������ָ��
 * @remark ���ܻ��кܶ�ͼ�ζ��ᱻѡ�У���ֻѡ�����һ������Ϊ���һ��������������
 */
Shape* Drawer::checkAllShapeState(const Point& point)
{
	Shape* shape = nullptr;
	for (int i = m_shapeList.size() - 1; i >= 0; --i) {
		shape = m_shapeList[i]->checkState(point);
		if (shape)
			return shape;
	}
	return nullptr;
}

void Drawer::dealContextMenuAction(MouseEvent* event)
{
	int actionId = m_pContextMenu->chooseAction(event);

	switch (actionId)
	{
	case 0:
		m_shapeType = Shape::ShapeType::NODEFINE;
		break;
	case 1:
		m_shapeType = Shape::ShapeType::LINE;
		break;
	case 2:
		m_shapeType = Shape::ShapeType::RECT;
		break;
	default:
		break;
	}

}

