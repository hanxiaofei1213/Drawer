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
	m_beginPoint = new Point;

	// �����Լ���һЩ����
	setText(TEXT("Drawer"));
	resize(800, 600);

	// �����Լ��Ľ���
	m_toolbar = new ToolBar(this);
	m_arrowBBtn = new ToolbarBtn(m_toolbar);
	m_lineTBBtn = new ToolbarBtn(m_toolbar);
	m_rectTBBtn = new ToolbarBtn(m_toolbar);
	
	m_arrowBBtn->setText(TEXT("Arrow"));
	m_lineTBBtn->setText(TEXT("Line"));
	m_rectTBBtn->setText(TEXT("Rect"));
}

// ��������
Drawer::~Drawer()
{
	delete m_beginPoint;
	for (auto i : m_shapeList)
		delete i;
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
	
	// FixMe: Ϊʲô������ϾͶ��ˣ�
	InvalidateRect(getHwnd(), NULL, TRUE);     

	// ��ȡ��꿪ʼ�ĵ�
	m_beginPoint->setX(a_event->getPos()->x());
	m_beginPoint->setY(a_event->getPos()->y());
	HDC hdc = GetDC(getHwnd());

	switch (m_shapeType)
	{
	case Shape::ShapeType::NODEFINE:
		m_tempShape = checkAllShapeState(*m_beginPoint);
		break;
	case Shape::ShapeType::LINE:
	{
		Line* line = new Line(hdc);
		line->setBegin(*m_beginPoint);
		m_tempShape = (Shape*)line;
		break;
	}
	case Shape::ShapeType::RECT:
	{
		Rect* rect = new Rect(hdc);
		rect->setBegin(*m_beginPoint);
		m_tempShape = (Shape*)rect;
		break;
	}
	}
	
	ReleaseDC(getHwnd(), hdc);
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

	Point endPoint;
	endPoint.setX(a_event->getPos()->x());
	endPoint.setY(a_event->getPos()->y());
	switch (m_shapeType)
	{
	// ������Ϊarrowģʽ
	case Shape::ShapeType::NODEFINE:
		if (m_tempShape->getState() == Shape::StateType::TOMOVE)
			m_tempShape->moveFunction(*m_beginPoint, endPoint);
		else if (m_tempShape->getState() == Shape::StateType::TOZOOM)
			m_tempShape->zoomFunction(*m_beginPoint, endPoint);
			
		m_tempShape->draw();
		m_beginPoint->setX(endPoint.x());
		m_beginPoint->setY(endPoint.y());
		break;
	case Shape::ShapeType::LINE:
	{
		Line* line = (Line*)m_tempShape;
		line->setEnd(endPoint);
		line->draw();
		break;
	}
	case Shape::ShapeType::RECT:
	{
		Rect* rect = (Rect*)m_tempShape;
		rect->setEnd(endPoint);
		rect->draw();
		break;
	}
	}
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
	InvalidateRect(getHwnd(), NULL, TRUE);
	//SendMessage(getHwnd(), WM_PAINT, 0, 0);
}



/**
 * @brief �����ػ��¼�
 */
void Drawer::paintEvent(PaintEvent* a_event)
{
	for (auto i : m_shapeList)
		i->draw();	
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


// TODO: �����������ֵ�ǲ��ǿ��Ը�һ�£�
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

