
#include "rectangle.h"

Rect::Rect(HDC a_hdc) : Shape(a_hdc)
{
	setShape(Shape::ShapeType::RECT);
	m_begin = new Point;
	m_end = new Point;
}

Rect::~Rect()
{
	delete m_end;
	delete m_begin;
}

/**
 * @brief 设置矩形开始的点
 * @param a_point 开始的点
 */
void Rect::setBegin(const Point& a_point)
{
	m_begin->setX(a_point.x());
	m_begin->setY(a_point.y());
}

/**
 * @brief 设置矩形结束的点
 * @param a_point 结束的点
 */
void Rect::setEnd(const Point& a_point)
{
	m_end->setX(a_point.x());
	m_end->setY(a_point.y());
}


// TODO:记得设置鼠标样式，可能需要改成const
/**
 * @brief 查看鼠标位置是否选中自己
 * @param a_checkPoint 需要进行判断的鼠标坐标
 * @return 若为正常，则返回nullptr，否则返回this
 */
Shape* Rect::checkState(const Point& a_checkPoint)
{
	int x = a_checkPoint.x();
	int y = a_checkPoint.y();

	
	// 如果在矩形的左上角或右下角，则需要放大缩小
	if (a_checkPoint.pointAroundPoint(*m_begin, m_nNearLevel) || a_checkPoint.pointAroundPoint(*m_end, m_nNearLevel))
	{
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// 如果在矩形内部则需要移动
	else if (x >= m_begin->x() && x <= m_end->x() && y >= m_begin->y() && y <= m_end->y())
	{
		setState(Shape::StateType::TOMOVE);
		return this;
	}
	else if (x <= m_begin->x() && x >= m_end->x() && y <= m_begin->y() && y >= m_end->y())
	{
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
void Rect::moveFunction(const Point& a_sPoint, const Point& a_dPoint)
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
void Rect::zoomFunction(const Point& a_sPoint, const Point& a_dPoint)
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
void Rect::draw()
{
	getPainter()->drawRect(m_begin->x(), m_begin->y(), m_end->x(), m_end->y());
}




