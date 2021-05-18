#include "buttonEvent.h"
#include "line.h"
#include "MouseDropEvent.h"
#include "mouseEvent.h"
#include "mouseWheelEvent.h"
#include "paintEvent.h"
#include "rectangle.h"
#include "toolBar.h"
#include "toolBarBtn.h"
#include "WindowLessAction.h"
#include "WindowLessMenu.h"

#include "Drawer.h"

namespace {
	const int verPenStyle[] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT };
	const COLORREF rgbArr[] = { RGB(255, 255, 255), 
								RGB(135, 206, 235), 
								RGB(50, 205, 50), 
								RGB(255, 215, 0), 
								RGB(255, 0, 0), };
}



// ���캯��
Drawer::Drawer() : Widget(NULL) {
	// �����Լ���һЩ����
	setText(TEXT("Drawer"));
	resize(800, 600);

	m_beginPoint = new Point;

	init();
	initContextMenu();
	initGDI();
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
 * @brief ������ͼ�λ��Ƶ��ڴ滭����һ��չʾȫ��
 */
void Drawer::drawAll() {

	Rectangle(m_memHdc, 0, 0, m_nBitmapWidth, m_nBitmapHeight);
	
	// ���ڴ滭���ϻ�
	for (auto shape : m_shapeList) {
		shape->draw();
	}
	// �����ʱshapeҲ��
	if (m_tempShape) {
		m_tempShape->draw();
	}

	// �ᵽ��ʵ����
	int loc = m_toolbarRC.bottom - m_toolbarRC.top;
	BitBlt(m_hdc, 0, loc, m_nBitmapWidth, m_nBitmapHeight, m_memHdc, 0, loc, SRCCOPY);
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

	// �����״ѡ��
	initContextMenuShapeAction();

	// ���shapeѡ��
	initContextMenuStyleAction();

	// �����ɫѡ��
	initContextMenuColorAction();
	

	m_pContextMenu->setVisiable(false);
}

void Drawer::initGDI()
{
	m_memHdc = CreateCompatibleDC(m_hdc);
	m_memBitMap = CreateCompatibleBitmap(m_hdc, m_nBitmapWidth, m_nBitmapHeight);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(m_memHdc, hPen);
	SelectObject(m_memHdc, hbrush);
	SelectObject(m_memHdc, m_memBitMap);
}


void Drawer::initContextMenuShapeAction()
{
	WindowLessAction* arrAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* lineAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* rectAction = new WindowLessAction(m_pContextMenu);

	arrAction->setText(L"arr");
	lineAction->setText(L"line");
	rectAction->setText(L"rect");

	std::vector<WindowLessAction*> actions = { arrAction, lineAction, rectAction };
	m_pContextMenu->addActions(actions);
}

void Drawer::initContextMenuStyleAction()
{
	int lineWidth = 200;
	WindowLessAction* action = nullptr;
	Line* line = nullptr;

	for (int i = 0; i < 5; ++i)
	{
		action = new WindowLessAction(m_pContextMenu);
		line = new Line(m_hdc);
		line->resize(lineWidth, 0);
		line->getPainter()->setPenStyle(verPenStyle[i]);
		line->getPainter()->setPenWidth(1);
		action->setShape(line);
		m_pContextMenu->addAction(action);
	}
}

void Drawer::initContextMenuColorAction()
{
	std::vector<WindowLessAction*> vecColorAction;
	for (int i = 0; i < 5; ++i)
	{
		WindowLessAction* action = new WindowLessAction(m_pContextMenu);
		Rect* rect = new Rect(m_hdc);
		rect->resize(30, 30);
		rect->getPainter()->setBrushColor(rgbArr[i]);
		action->setShape(rect);
		vecColorAction.push_back(action);
	}

	m_pContextMenu->addActions(vecColorAction);
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
		line->setHDC(m_memHdc);
		setShapePenState(line);
		line->setBegin(*m_beginPoint);
		line->setEnd(*m_beginPoint);
		m_tempShape = (Shape*)line;
		break;
	}
	case Shape::ShapeType::RECT: 
	{
		Rect* rect = new Rect(m_hdc);
		rect->setHDC(m_memHdc);
		setShapePenState(rect);
		rect->setBegin(*m_beginPoint);
		rect->setEnd(*m_beginPoint);
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

void Drawer::mouseWheelEvent(MouseWheelEvent* event)
{
	int distance = event->getWheelDistance();
	m_nPenWidth += distance;
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
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		resetPenStyle(actionId);
		break;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		resetPenColor(actionId);
		break;
	default:
		break;
	}

}

void Drawer::dealRightBtnEvent(MouseEvent* event)
{
	Point* loc = event->getPos();
	m_pContextMenu->move(loc->x(), loc->y());
}

void Drawer::resetPenStyle(int actionId)
{
	m_penStyle = verPenStyle[actionId - 3];
	m_nPenWidth = 1;                // ������Ϊ1�Ż��в�ͬ����ʽ
}

void Drawer::resetPenColor(int actionId)
{
	m_penColor = rgbArr[actionId - 8];
}

void Drawer::setShapePenState(Shape* shape)
{
	Painter* shapePainter = shape->getPainter();
	shapePainter->setPenWidth(m_nPenWidth);
	shapePainter->setPenStyle(m_penStyle);
	shapePainter->setPenColor(m_penColor);
}
