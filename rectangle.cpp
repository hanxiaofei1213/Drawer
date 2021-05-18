
#include "rectangle.h"

Rect::Rect(HDC a_hdc) : Shape(a_hdc) {
	setShape(Shape::ShapeType::RECT);
}

Rect::~Rect() {
	
}

// TODO:记得设置鼠标样式
/**
 * @brief 查看鼠标位置是否选中自己
 * @param a_checkPoint 需要进行判断的鼠标坐标
 * @return 若为正常，则返回nullptr，否则返回this
 */
Shape* Rect::checkState(const Point& checkPoint) {
	int x = checkPoint.x();
	int y = checkPoint.y();
	Point* beginPoint = getBegin();
	Point* endPoint = getEnd();

	
	// 如果在矩形的左上角或右下角，则需要放大缩小
	if (checkPoint.pointAroundPoint(*beginPoint, m_nNearLevel) || checkPoint.pointAroundPoint(*endPoint, m_nNearLevel)) {
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// 如果在矩形内部则需要移动
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
 * @brief 将自己画出来
 */
void Rect::draw() {
	getPainter()->drawRect(getBegin()->x(), getBegin()->y(), getEnd()->x(), getEnd()->y());
}




