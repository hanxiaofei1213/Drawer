#include "Drawer.h"

#include "toolBar.h"
#include "toolBarBtn.h"
#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"
#include "line.h"
#include "rectangle.h"

// 构造函数
Drawer::Drawer() : Widget(NULL), m_shapeType(Shape::ShapeType::NODEFINE), m_tempShape(nullptr)
{
	m_beginPoint = new Point;

	// 设置自己的一些属性
	setText(TEXT("Drawer"));
	resize(800, 600);

	// 绘制自己的界面
	m_toolbar = new ToolBar(this);
	m_arrowBBtn = new ToolbarBtn(m_toolbar);
	m_lineTBBtn = new ToolbarBtn(m_toolbar);
	m_rectTBBtn = new ToolbarBtn(m_toolbar);
	
	m_arrowBBtn->setText(TEXT("Arrow"));
	m_lineTBBtn->setText(TEXT("Line"));
	m_rectTBBtn->setText(TEXT("Rect"));
}

// 析构函数
Drawer::~Drawer()
{
	delete m_beginPoint;
	for (auto i : m_shapeList)
		delete i;
}

/**
 * @brief 处理按钮按下事件
 * @param a_event 事件
 * @remark 这里创建的对象
 */
void Drawer::mousePressEvent(MouseEvent* a_event)
{
	if (a_event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;
	
	// FixMe: 为什么这里加上就对了？
	InvalidateRect(getHwnd(), NULL, TRUE);     

	// 获取鼠标开始的点
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
 * @brief 处理按钮移动事件
 */
void Drawer::mouseMoveEvent(MouseEvent* a_event)
{
	// 如果不是鼠标左键按下，不处理
	if (a_event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;

	// 如果没选择任何shape，则不处理
	if (!m_tempShape)
		return;

	Point endPoint;
	endPoint.setX(a_event->getPos()->x());
	endPoint.setY(a_event->getPos()->y());
	switch (m_shapeType)
	{
	// 工具栏为arrow模式
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
 * @brief 处理按钮放开事件
 */
void Drawer::mouseReleaseEvent(MouseEvent* a_event)
{
	if (a_event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;


	// 如果当前shape为空，则不处理
	if (!m_tempShape)
		return;

	// 如果当前形状为NORMAL，则为新创建的shape，添加到list中
	if (m_tempShape->getState() == Shape::StateType::NOMAL)
		m_shapeList.push_back(m_tempShape);
	else 
		m_tempShape->setState(Shape::StateType::NOMAL);

	m_tempShape = nullptr;

	// 强制重绘，擦除临时形状，只显示paintEvent中的形状
	InvalidateRect(getHwnd(), NULL, TRUE);
	//SendMessage(getHwnd(), WM_PAINT, 0, 0);
}



/**
 * @brief 处理重绘事件
 */
void Drawer::paintEvent(PaintEvent* a_event)
{
	for (auto i : m_shapeList)
		i->draw();	
}

/**
 * @brief 处理按钮按下事件
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


// TODO: 这个函数返回值是不是可以改一下？
/**
 * @brief 检查当前所有shape的状态
 * @param a_point 鼠标点击的位置
 * @return 如果有shape被选中，返回其指针
 * @remark 可能会有很多图形都会被选中，但只选择最后一个，因为最后一个往往在最上面
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

