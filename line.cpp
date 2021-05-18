#include "line.h"

Line::Line(HDC hdc) : Shape(hdc) {
	setShape(Shape::ShapeType::LINE);
}


Line::~Line() {
	
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
	Point* beginPoint = getBegin();
	Point* endPoint = getEnd();

	// ������ߵ������˵㸽������Ŵ���С
	if (checkPoint.pointAroundPoint(*beginPoint, m_nNearLevel) || checkPoint.pointAroundPoint(*endPoint, m_nNearLevel)) {
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// ������߸��������ƶ�
	else if (checkPoint.pointAroundLine(*beginPoint, *endPoint, m_nNearLevel)) {
		setState(Shape::StateType::TOMOVE);
		return this;
	} 

	return nullptr;
}

/**
 * @brief ���Լ�������
 */
void Line::draw() {
	getPainter()->drawLine(getBegin()->x(), getBegin()->y(), getEnd()->x(), getEnd()->y());
}