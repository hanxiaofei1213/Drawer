#include "point.h"

// �ƶ����캯��
Point::Point(Point&& a_point) noexcept
{
	m_nx = a_point.x();
	m_ny = a_point.y();

	a_point.setX(0);
	a_point.setY(0);

}

// �ƶ������
Point& Point::operator=(Point&& a_point) noexcept
{
	m_nx = a_point.x();
	m_ny = a_point.y();

	a_point.setX(0);
	a_point.setY(0);
	return *this;
}

/**
 * @brief �������
 * @param a_point ��һ����
 */
Point Point::addPoint(const Point& a_point) const
{
	Point p;
	p.setX(m_nx + a_point.x());
	p.setY(m_ny + a_point.y());
	return p;
}

/**
 * @brief �������
 * @param a_point ��һ����
 */
Point Point::minusPoint(const Point& a_point) const
{
	Point p;
	p.setX(m_nx - a_point.x());
	p.setY(m_ny - a_point.y());
	return p;
}

/**
 * @brief �������
 * @param a_point ��һ����
 * @return true��ȣ�false�����
 */
bool Point::equalPoint(const Point& a_point) const
{
	if (this->m_nx == a_point.m_nx && this->m_ny == a_point.m_ny)
		return true;
	return false;
}


/**
 * @brief �ж��������Ƿ�ӽ�
 * @param a_p1 Ҫ�ȵĵ�
 * @param a_level ���ĳ̶ȣ������������֮��ľ���
 * @return true��ʾ�ӽ���false���෴
 */
bool Point::pointAroundPoint(const Point& a_p1, int a_level) const
{
	Point diffPoint = this->minusPoint(a_p1);

	// �������֮����a_level����֮�䣬���ʾ�ӽ�
	if (std::abs(diffPoint.x()) < a_level && std::abs(diffPoint.y()) < a_level)
		return true;
	return false;
}


/**
 * @brief �ж�һ�����Ƿ񿿽�һ���ߣ����ݵ㵽ֱ�ߵķ�������
 * @param a_lineBegin �ߵ����
 * @param a_lineEnd �ߵ��յ�
 * @param a_level ���ĳ̶ȣ�������ǵ㵽ֱ�ߵľ���
 * @return true��ʾ�ӽ���false���෴
 */
bool Point::pointAroundLine(const Point& a_lineBegin, const Point& a_lineEnd, int a_level) const
{
	// ��������֮��
	Point diffPoint = a_lineEnd.minusPoint(a_lineBegin);

	// ����б�ʺͽؾ࣬ע�����Ϊ0�����
	double k = 0;
	if (diffPoint.x() != 0)
		k = (double)diffPoint.y() / diffPoint.x();
	double b = a_lineBegin.y() - k * a_lineBegin.x();

	// �㵽ֱ�߾���
	double distance = std::abs(k * this->x() - this->y() + b) / std::sqrt(k * k + 1);

	// ����̫��
	if (distance > a_level)
		return false;
	// ������ʣ��������ӳ�����
	else if (this->x() < a_lineBegin.x() && this->x() < a_lineEnd.x())
		return false;
	else if (this->x() > a_lineBegin.x() && this->x() > a_lineEnd.x())
		return false;

	// ������ʣ����Ҳ����ӳ�����
	return true;
}
