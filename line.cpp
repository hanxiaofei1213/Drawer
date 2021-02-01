#include "line.h"

Line::Line(HDC hdc) : Shape(hdc) {
	setShape(Shape::ShapeType::LINE);
	m_begin = new Point;
	m_end = new Point;
}


Line::~Line() {
	delete m_end;
	delete m_begin;
}

/**
 * @brief ������ʼ��
 */
void Line::setBegin(const Point& begin) {
	m_begin->setX(begin.x());
	m_begin->setY(begin.y());
}

void Line::setEnd(const Point& end) {
	m_end->setX(end.x());
	m_end->setY(end.y());
}


// TODO: �ǵ���������ʽ
/**
 * @brief �鿴���λ���Ƿ�ѡ���Լ�
 * @param a_checkPoint ��������
 * @return ����nullptr����δ��ѡ�У����򷵻�this
 */
Shape* Line::checkState(const Point& checkPoint) {
	int x = checkPoint.x();
	int y = checkPoint.y();

	// ������ߵ������˵㸽������Ŵ���С
	if (checkPoint.pointAroundPoint(*m_begin, m_nNearLevel) || checkPoint.pointAroundPoint(*m_end, m_nNearLevel)) {
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// ������߸��������ƶ�
	else if (checkPoint.pointAroundLine(*m_begin, *m_end, m_nNearLevel)) {
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
void Line::moveFunction(const Point& sPoint, const Point& dPoint) {
	Point diffPoint = dPoint.minusPoint(sPoint);
	*m_begin = m_begin->addPoint(diffPoint);
	*m_end = m_end->addPoint(diffPoint);
}


/**
 * @brief ���Լ����ŵĺ���
 * @param a_sPoint ԭ����λ��
 * @param a_dPoint �ƶ����λ��
 */
void Line::zoomFunction(const Point& sPoint, const Point& dPoint) {
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
void Line::draw() {

	getPainter()->drawLine(m_begin->x(), m_begin->y(), m_end->x(), m_end->y());
}