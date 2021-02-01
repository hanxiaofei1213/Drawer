
#include "rectangle.h"

Rect::Rect(HDC a_hdc) : Shape(a_hdc) {
	setShape(Shape::ShapeType::RECT);
	m_begin = new Point;
	m_end = new Point;
}

Rect::~Rect() {
	delete m_end;
	delete m_begin;
}

/**
 * @brief ���þ��ο�ʼ�ĵ�
 * @param a_point ��ʼ�ĵ�
 */
void Rect::setBegin(const Point& begin) {
	m_begin->setX(begin.x());
	m_begin->setY(begin.y());
}

/**
 * @brief ���þ��ν����ĵ�
 * @param a_point �����ĵ�
 */
void Rect::setEnd(const Point& end) {
	m_end->setX(end.x());
	m_end->setY(end.y());
}


// TODO:�ǵ����������ʽ
/**
 * @brief �鿴���λ���Ƿ�ѡ���Լ�
 * @param a_checkPoint ��Ҫ�����жϵ��������
 * @return ��Ϊ�������򷵻�nullptr�����򷵻�this
 */
Shape* Rect::checkState(const Point& checkPoint) {
	int x = checkPoint.x();
	int y = checkPoint.y();

	
	// ����ھ��ε����Ͻǻ����½ǣ�����Ҫ�Ŵ���С
	if (checkPoint.pointAroundPoint(*m_begin, m_nNearLevel) || checkPoint.pointAroundPoint(*m_end, m_nNearLevel)) {
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// ����ھ����ڲ�����Ҫ�ƶ�
	else if (x >= m_begin->x() && x <= m_end->x() && y >= m_begin->y() && y <= m_end->y()) {
		setState(Shape::StateType::TOMOVE);
		return this;
	}
	else if (x <= m_begin->x() && x >= m_end->x() && y <= m_begin->y() && y >= m_end->y()) {
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
void Rect::moveFunction(const Point& sPoint, const Point& dPoint) {
	Point diffPoint = dPoint.minusPoint(sPoint);
	*m_begin = m_begin->addPoint(diffPoint);
	*m_end = m_end->addPoint(diffPoint);
}


/**
 * @brief ���Լ����ŵĺ���
 * @param a_sPoint ԭ����λ��
 * @param a_dPoint �ƶ����λ��
 */
void Rect::zoomFunction(const Point& sPoint, const Point& dPoint) {
	// ���������㣬�������Ϊ���
	if (sPoint.pointAroundPoint(*m_begin, m_nNearLevel)) {
		setBegin(dPoint);
	}
	// ��������յ㣬���ص���Ϊ���
	else if (sPoint.pointAroundPoint(*m_end, m_nNearLevel)) {
		setEnd(dPoint);
	}
}


/**
 * @brief ���Լ�������
 */
void Rect::draw() {
	getPainter()->drawRect(m_begin->x(), m_begin->y(), m_end->x(), m_end->y());
}




