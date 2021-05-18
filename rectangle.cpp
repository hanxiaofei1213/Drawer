
#include "rectangle.h"

Rect::Rect(HDC a_hdc) : Shape(a_hdc) {
	setShape(Shape::ShapeType::RECT);
}

Rect::~Rect() {
	
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
	Point* beginPoint = getBegin();
	Point* endPoint = getEnd();

	
	// ����ھ��ε����Ͻǻ����½ǣ�����Ҫ�Ŵ���С
	if (checkPoint.pointAroundPoint(*beginPoint, m_nNearLevel) || checkPoint.pointAroundPoint(*endPoint, m_nNearLevel)) {
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// ����ھ����ڲ�����Ҫ�ƶ�
	else if (x >= beginPoint->x() && x <= endPoint->x() && y >= beginPoint->y() && y <= endPoint->y()) {
		setState(Shape::StateType::TOMOVE);
		return this;
	}
	else if (x <= beginPoint->x() && x >= endPoint->x() && y <= beginPoint->y() && y >= endPoint->y()) {
		setState(Shape::StateType::TOMOVE);
		return this;
	}
	return nullptr;
}

/**
 * @brief ���Լ�������
 */
void Rect::draw() {
	getPainter()->drawRect(getBegin()->x(), getBegin()->y(), getEnd()->x(), getEnd()->y());
}




