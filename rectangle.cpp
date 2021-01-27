
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
 * @brief ���þ��ο�ʼ�ĵ�
 * @param a_point ��ʼ�ĵ�
 */
void Rect::setBegin(const Point& a_point)
{
	m_begin->setX(a_point.x());
	m_begin->setY(a_point.y());
}

/**
 * @brief ���þ��ν����ĵ�
 * @param a_point �����ĵ�
 */
void Rect::setEnd(const Point& a_point)
{
	m_end->setX(a_point.x());
	m_end->setY(a_point.y());
}


// TODO:�ǵ����������ʽ
/**
 * @brief �鿴���λ���Ƿ�ѡ���Լ�
 * @param a_checkPoint ��Ҫ�����жϵ��������
 * @return ��Ϊ�������򷵻�nullptr�����򷵻�this
 */
Shape* Rect::checkState(const Point& a_checkPoint)
{
	int x = a_checkPoint.x();
	int y = a_checkPoint.y();

	
	// ����ھ��ε����Ͻǻ����½ǣ�����Ҫ�Ŵ���С
	if (a_checkPoint.pointAroundPoint(*m_begin, m_nNearLevel) || a_checkPoint.pointAroundPoint(*m_end, m_nNearLevel))
	{
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// ����ھ����ڲ�����Ҫ�ƶ�
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
 * @brief ���Լ��ƶ��ĺ���
 * @param a_sPoint ԭ����λ��
 * @param a_dPoint �ƶ����λ��
 */
void Rect::moveFunction(const Point& a_sPoint, const Point& a_dPoint)
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
void Rect::zoomFunction(const Point& a_sPoint, const Point& a_dPoint)
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
void Rect::draw()
{
	getPainter()->drawRect(m_begin->x(), m_begin->y(), m_end->x(), m_end->y());
}




