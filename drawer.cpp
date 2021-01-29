#include "Drawer.h"

#include "toolBar.h"
#include "toolBarBtn.h"
#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"
#include "line.h"
#include "rectangle.h"


// ���캯��
Drawer::Drawer() : Widget(NULL), m_shapeType(Shape::ShapeType::NODEFINE), m_tempShape(nullptr)
{
	// �����Լ���һЩ����
	setText(TEXT("Drawer"));
	resize(800, 600);
	m_beginPoint = new Point;
	m_hdc = GetDC(getHwnd());
	m_memHdc = NULL;
	m_memBitMap = NULL;

	// �����Լ��Ľ���
	m_toolbar = new ToolBar(this);
	m_arrowBBtn = new ToolbarBtn(m_toolbar);
	m_lineTBBtn = new ToolbarBtn(m_toolbar);
	m_rectTBBtn = new ToolbarBtn(m_toolbar);

	m_arrowBBtn->setText(TEXT("Arrow"));
	m_lineTBBtn->setText(TEXT("Line"));
	m_rectTBBtn->setText(TEXT("Rect"));

	init();
}

// ��������
Drawer::~Drawer()
{
	if (m_memHdc)
		DeleteDC(m_memHdc);
	if (m_memBitMap)
		DeleteObject(m_memBitMap);
	ReleaseDC(getHwnd(), m_hdc);
	if (m_tempShape)
		delete m_tempShape;
	for (auto i : m_shapeList)
		delete i;
	delete m_rectTBBtn;
	delete m_lineTBBtn;
	delete m_arrowBBtn;
	delete m_toolbar;
	delete m_beginPoint;
}


/**
 * @brief һЩ������ĳ�ʼ��
 */
void Drawer::init()
{
	// ��ȡ���������ܴ��ڵ�λ�ô�С
	GetWindowRect(getHwnd(), &m_rc);
	GetWindowRect(m_toolbar->getHwnd(), &m_toolbarRC);

	// ���㻭����С
	int nleftUpX = m_toolbarRC.left;
	int nleftUpY = m_toolbarRC.top;
	m_nBitmapWidth = m_toolbarRC.right - m_toolbarRC.left;
	m_nBitmapHeight = m_rc.bottom - m_toolbarRC.top;
	m_flashArea.left = m_toolbarRC.left;
	m_flashArea.top = m_toolbarRC.bottom;
	m_flashArea.right = m_toolbarRC.right;
	m_flashArea.bottom = m_rc.bottom;
}


/**
 * @brief ������ͼ�λ��Ƶ��ڴ滭����һ��չʾȫ��
 */
void Drawer::drawAll()
{
	m_memHdc = CreateCompatibleDC(m_hdc);
	m_memBitMap = CreateCompatibleBitmap(m_hdc, m_nBitmapWidth, m_nBitmapHeight);
	static HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(m_memHdc, m_memBitMap);
	SelectObject(m_memHdc, hbrush);
	Rectangle(m_memHdc, 0, 0, m_nBitmapWidth, m_nBitmapHeight);

	// ���ڴ滭���ϻ�
	for (auto shape : m_shapeList)
	{
		shape->setHDC(m_memHdc);
		shape->draw();
	}
	// �����ʱshapeҲ��
	if (m_tempShape)
	{
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

/**
 * @brief ����ť�����¼�
 * @param a_event �¼�
 * @remark ���ﴴ���Ķ���
 */
void Drawer::mousePressEvent(MouseEvent* a_event)
{
	if (a_event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;  

	// ��ȡ��꿪ʼ�ĵ�
	m_beginPoint->setX(a_event->getPos()->x());
	m_beginPoint->setY(a_event->getPos()->y());

	switch (m_shapeType)
	{
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
void Drawer::mouseMoveEvent(MouseEvent* a_event)
{
	// ����������������£�������
	if (a_event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;

	// ���ûѡ���κ�shape���򲻴���
	if (!m_tempShape)
		return;
	
	Point endPoint(a_event->getPos()->x(), a_event->getPos()->y());
	switch (m_shapeType)
	{
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
void Drawer::mouseReleaseEvent(MouseEvent* a_event)
{
	if (a_event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
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
void Drawer::paintEvent(PaintEvent* a_event)
{
	drawAll();
}

/**
 * @brief ����ť�����¼�
 */
void Drawer::buttonPressEvent(ButtonEvent* a_event)
{
	int eventBtnId = a_event->getBtnId();

	if (m_arrowBBtn->getObjectId() == eventBtnId)
	{
		m_shapeType = Shape::ShapeType::NODEFINE;
	}
	else if (m_lineTBBtn->getObjectId() == eventBtnId)
	{
		m_shapeType = Shape::ShapeType::LINE;
	}
	else if (m_rectTBBtn->getObjectId() == eventBtnId)
	{
		m_shapeType = Shape::ShapeType::RECT;
	}
}


/**
 * @brief ��鵱ǰ����shape��״̬
 * @param a_point �������λ��
 * @return �����shape��ѡ�У�������ָ��
 * @remark ���ܻ��кܶ�ͼ�ζ��ᱻѡ�У���ֻѡ�����һ������Ϊ���һ��������������
 */
Shape* Drawer::checkAllShapeState(const Point& a_point)
{
	Shape* shape = nullptr;
	for (int i = m_shapeList.size() - 1; i >= 0; --i)
	{
		shape = m_shapeList[i]->checkState(a_point);
		if (shape)
			return shape;
	}
	return nullptr;
}

