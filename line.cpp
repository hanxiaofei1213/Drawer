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
 * @brief ������ʼ��
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


// TODO: �ǵ���������ʽ
/**
 * @brief �鿴���λ���Ƿ�ѡ���Լ�
 * @param a_checkPoint ��������
 * @return ����nullptr����δ��ѡ�У����򷵻�this
 */
Shape* Line::checkState(const Point& a_checkPoint)
{
	int x = a_checkPoint.x();
	int y = a_checkPoint.y();

	// ������ߵ������˵㸽������Ŵ���С
	if (a_checkPoint.pointAroundPoint(*m_begin, m_nNearLevel) || a_checkPoint.pointAroundPoint(*m_end, m_nNearLevel))
	{
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// ������߸��������ƶ�
	else if (a_checkPoint.pointAroundLine(*m_begin, *m_end, m_nNearLevel)) {
		setState(Shape::StateType::TOMOVE);
		return this;
	} 

	return nullptr;
}


/**
 * @brief ���Լ��ƶ��ĺ���
 * @param a_sPoint ԭ����λ��
 * @param a_dPoint �ƶ����λ��
 */
void Line::moveFunction(const Point& a_sPoint, const Point& a_dPoint)
{
	Point diffPoint = a_dPoint.minusPoint(a_sPoint);
	*m_begin = m_begin->addPoint(diffPoint);
	*m_end = m_end->addPoint(diffPoint);
}


/**
 * @brief ���Լ����ŵĺ���
 * @param a_sPoint ԭ����λ��
 * @param a_dPoint �ƶ����λ��
 */
void Line::zoomFunction(const Point& a_sPoint, const Point& a_dPoint)
{
	// ���������㣬�������Ϊ���
	if (a_sPoint.pointAroundPoint(*m_begin, m_nNearLevel))
	{
		setBegin(a_dPoint);
	}
	// ��������յ㣬���ص���Ϊ���
	else if (a_sPoint.pointAroundPoint(*m_end, m_nNearLevel)) {
		setEnd(a_dPoint);
	}
}

/**
 * @brief ���Լ�������
 */
void Line::draw()
{

	getPainter()->drawLine(m_begin->x(), m_begin->y(), m_end->x(), m_end->y());
}