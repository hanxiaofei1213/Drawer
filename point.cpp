#include "point.h"

// �ƶ����캯��
Point::Point(Point&& point) noexcept {
	m_nx = point.x();
	m_ny = point.y();

	point.setX(0);
	point.setY(0);
}

std::tuple<bool, bool> Point::isHorizontalLeft(Point* point1, Point* point2, int nearLevel)
{
	std::tuple<bool, bool> answer;
	bool isHorizatal = false;
	bool isLeftSide = false;

	if (std::abs(point2->y() - point1->y()) < nearLevel)
	{
		isHorizatal = true;
		if (point1->x() < point2->x())
			isLeftSide = true;
	}
	
	answer = { isHorizatal, isLeftSide };
	return answer;
}

std::tuple<bool, bool> Point::isVerticalUp(Point* point1, Point* point2, int nearLevel /*= 10*/)
{
	std::tuple<bool, bool> answer;
	bool isVertical = false;
	bool isUpSide = false;

	if (std::abs(point2->x() - point1->x()) < nearLevel)
	{
		isVertical = true;
		if (point1->y() < point2->y())
			isUpSide = true;
	}

	answer = { isVertical, isUpSide };
	return answer;
}

// �ƶ������
Point& Point::operator=(Point&& point) noexcept {
	m_nx = point.x();
	m_ny = point.y();

	point.setX(0);
	point.setY(0);
	return *this;
}

/**
 * @brief �������
 * @param a_point ��һ����
 */
Point Point::addPoint(const Point& point) const {
	Point p;
	p.setX(m_nx + point.x());
	p.setY(m_ny + point.y());
	return p;   // �ƶ�����
}

/**
 * @brief �������
 * @param a_point ��һ����
 */
Point Point::minusPoint(const Point& point) const {
	Point p;
	p.setX(m_nx - point.x());
	p.setY(m_ny - point.y());
	return p;   // �ƶ�����
}

/**
 * @brief �������
 * @param a_point ��һ����
 * @return true��ȣ�false�����
 */
bool Point::equalPoint(const Point& point) const {
	if (this->m_nx == point.m_nx && this->m_ny == point.m_ny)
		return true;
	return false;
}


/**
 * @brief �ж��������Ƿ�ӽ�
 * @param a_p1 Ҫ�ȵĵ�
 * @param a_level ���ĳ̶ȣ������������֮��ľ���
 * @return true��ʾ�ӽ���false���෴
 */
bool Point::pointAroundPoint(const Point& p1, int level) const {
	Point diffPoint = this->minusPoint(p1);

	// �������֮����a_level����֮�䣬���ʾ�ӽ�
	if (std::abs(diffPoint.x()) < level && std::abs(diffPoint.y()) < level)
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
bool Point::pointAroundLine(const Point& lineBegin, const Point& lineEnd, int level) const {

	// ��������֮��
	Point diffPoint = lineEnd.minusPoint(lineBegin);

	// ����б�ʺͽؾ࣬ע�����Ϊ0�����
	double k = 0;
	if (diffPoint.x() != 0)
		k = (double)diffPoint.y() / diffPoint.x();
	double b = lineBegin.y() - k * lineBegin.x();

	// �㵽ֱ�߾���
	double distance = std::abs(k * this->x() - this->y() + b) / std::sqrt(k * k + 1);

	// ����̫��
	if (distance > level)
		return false;

	// ������ʣ��������ӳ�����
	else if (this->x() < lineBegin.x() && this->x() < lineEnd.x())
		return false;
	else if (this->x() > lineBegin.x() && this->x() > lineEnd.x())
		return false;

	// ������ʣ����Ҳ����ӳ�����
	return true;
}
