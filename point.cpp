#include "point.h"

// 移动构造函数
Point::Point(Point&& a_point) noexcept
{
	m_nx = a_point.x();
	m_ny = a_point.y();

	a_point.setX(0);
	a_point.setY(0);

}

// 移动运算符
Point& Point::operator=(Point&& a_point) noexcept
{
	m_nx = a_point.x();
	m_ny = a_point.y();

	a_point.setX(0);
	a_point.setY(0);
	return *this;
}

/**
 * @brief 两点相加
 * @param a_point 另一个点
 */
Point Point::addPoint(const Point& a_point) const
{
	Point p;
	p.setX(m_nx + a_point.x());
	p.setY(m_ny + a_point.y());
	return p;
}

/**
 * @brief 两点相减
 * @param a_point 另一个点
 */
Point Point::minusPoint(const Point& a_point) const
{
	Point p;
	p.setX(m_nx - a_point.x());
	p.setY(m_ny - a_point.y());
	return p;
}

/**
 * @brief 两点相等
 * @param a_point 另一个点
 * @return true相等，false不相等
 */
bool Point::equalPoint(const Point& a_point) const
{
	if (this->m_nx == a_point.m_nx && this->m_ny == a_point.m_ny)
		return true;
	return false;
}


/**
 * @brief 判断两个点是否接近
 * @param a_p1 要比的点
 * @param a_level 近的程度，这里就是两点之间的距离
 * @return true表示接近，false则相反
 */
bool Point::pointAroundPoint(const Point& a_p1, int a_level) const
{
	Point diffPoint = this->minusPoint(a_p1);

	// 如果两点之差在a_level容忍之间，则表示接近
	if (std::abs(diffPoint.x()) < a_level && std::abs(diffPoint.y()) < a_level)
		return true;
	return false;
}


/**
 * @brief 判断一个点是否靠近一条线，根据点到直线的方程来算
 * @param a_lineBegin 线的起点
 * @param a_lineEnd 线的终点
 * @param a_level 近的程度，这里就是点到直线的距离
 * @return true表示接近，false则相反
 */
bool Point::pointAroundLine(const Point& a_lineBegin, const Point& a_lineEnd, int a_level) const
{
	// 计算两点之差
	Point diffPoint = a_lineEnd.minusPoint(a_lineBegin);

	// 计算斜率和截距，注意除数为0的情况
	double k = 0;
	if (diffPoint.x() != 0)
		k = (double)diffPoint.y() / diffPoint.x();
	double b = a_lineBegin.y() - k * a_lineBegin.x();

	// 点到直线距离
	double distance = std::abs(k * this->x() - this->y() + b) / std::sqrt(k * k + 1);

	// 距离太大
	if (distance > a_level)
		return false;
	// 距离合适，但是在延长线上
	else if (this->x() < a_lineBegin.x() && this->x() < a_lineEnd.x())
		return false;
	else if (this->x() > a_lineBegin.x() && this->x() > a_lineEnd.x())
		return false;

	// 距离合适，并且不在延长线上
	return true;
}
