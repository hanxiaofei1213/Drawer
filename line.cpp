#include "line.h"

Line::Line(HDC a_hdc) : Shape(a_hdc)
{
	setShape(Shape::ShapeType::LINE);
	m_begin = new Point;
	m_end = new Point;
}


Line::~Line()
{
	delete m_end;
	delete m_begin;
}

/**
 * @brief 设置起始点
 */
void Line::setBegin(const Point& a_point)
{
	m_begin->setX(a_point.x());
	m_begin->setY(a_point.y());
}

void Line::setEnd(const Point& a_point)
{
	m_end->setX(a_point.x());
	m_end->setY(a_point.y());
}


// TODO: 记得添加鼠标样式
/**
 * @brief 查看鼠标位置是否选中自己
 * @param a_checkPoint 鼠标的坐标
 * @return 返回nullptr，则未被选中，否则返回this
 */
Shape* Line::checkState(const Point& a_checkPoint)
{
	int x = a_checkPoint.x();
	int y = a_checkPoint.y();

	// 如果在线的两个端点附近，则放大缩小
	if (a_checkPoint.pointAroundPoint(*m_begin, m_nNearLevel) || a_checkPoint.pointAroundPoint(*m_end, m_nNearLevel))
	{
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// 如果在线附近，则移动
	else if (a_checkPoint.pointAroundLine(*m_begin, *m_end, m_nNearLevel)) {
		setState(Shape::StateType::TOMOVE);
		return this;
	} 

	return nullptr;
}


/**
 * @brief 将自己移动的函数
 * @param a_sPoint 原来的位置
 * @param a_dPoint 移动后的位置
 */
void Line::moveFunction(const Point& a_sPoint, const Point& a_dPoint)
{
	Point diffPoint = a_dPoint.minusPoint(a_sPoint);
	*m_begin = m_begin->addPoint(diffPoint);
	*m_end = m_end->addPoint(diffPoint);
}


/**
 * @brief 将自己缩放的函数
 * @param a_sPoint 原来的位置
 * @param a_dPoint 移动后的位置
 */
void Line::zoomFunction(const Point& a_sPoint, const Point& a_dPoint)
{
	// 如果靠近起点，将起点设为这个
	if (a_sPoint.pointAroundPoint(*m_begin, m_nNearLevel))
	{
		setBegin(a_dPoint);
	}
	// 如果靠近终点，把重点设为这个
	else if (a_sPoint.pointAroundPoint(*m_end, m_nNearLevel)) {
		setEnd(a_dPoint);
	}
}

/**
 * @brief 将自己画出来
 */
void Line::draw()
{

	getPainter()->drawLine(m_begin->x(), m_begin->y(), m_end->x(), m_end->y());
}