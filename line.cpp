#include "line.h"

Line::Line(HDC hdc) : Shape(hdc) {
	setShape(Shape::ShapeType::LINE);
}


Line::~Line() {
	
}



// TODO: 记得添加鼠标样式
/**
 * @brief 查看鼠标位置是否选中自己
 * @param a_checkPoint 鼠标的坐标
 * @return 返回nullptr，则未被选中，否则返回this
 */
Shape* Line::checkState(const Point& checkPoint) {
	int x = checkPoint.x();
	int y = checkPoint.y();
	Point* beginPoint = getBegin();
	Point* endPoint = getEnd();

	// 如果在线的两个端点附近，则放大缩小
	if (checkPoint.pointAroundPoint(*beginPoint, m_nNearLevel) || checkPoint.pointAroundPoint(*endPoint, m_nNearLevel)) {
		setState(Shape::StateType::TOZOOM);
		return this;
	}
	// 如果在线附近，则移动
	else if (checkPoint.pointAroundLine(*beginPoint, *endPoint, m_nNearLevel)) {
		setState(Shape::StateType::TOMOVE);
		return this;
	} 

	return nullptr;
}

/**
 * @brief 将自己画出来
 */
void Line::draw() {
	getPainter()->drawLine(getBegin()->x(), getBegin()->y(), getEnd()->x(), getEnd()->y());
}