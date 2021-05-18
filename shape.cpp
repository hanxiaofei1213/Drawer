
#include "shape.h"


namespace {
	const int NEAR_LEVEL = 10;
}


Shape::Shape(HDC hdc) {
	m_hdc = hdc;
	m_painter = new Painter(m_hdc);
	m_state = StateType::NOMAL;
	m_shapeType = ShapeType::NODEFINE;
	m_beginPoint = new Point;
	m_endPoint = new Point;
}

Shape::~Shape() {
	delete m_painter;
	delete m_beginPoint;
	delete m_endPoint;
}

void Shape::setHDC(HDC hdc) {
	if (!hdc)
		return;

	m_hdc = hdc;
	m_painter->setHDC(hdc);
}

void Shape::setBegin(const Point& beginPoint)
{
	m_beginPoint->setX(beginPoint.x());
	m_beginPoint->setY(beginPoint.y());
}

void Shape::setEnd(const Point& endPoint)
{
	m_endPoint->setX(endPoint.x());
	m_endPoint->setY(endPoint.y());
}

void Shape::resize(int width, int height)
{
	m_endPoint->setX(m_beginPoint->x() + width);
	m_endPoint->setY(m_beginPoint->y() + height);
}

void Shape::moveFunction(const Point& sPoint, const Point& dPoint)
{
	Point diffPoint = dPoint.minusPoint(sPoint);
	*m_beginPoint = m_beginPoint->addPoint(diffPoint);
	*m_endPoint = m_endPoint->addPoint(diffPoint);
}

void Shape::zoomFunction(const Point& sPoint, const Point& dPoint)
{
	// 如果靠近起点，将起点设为这个
	if (sPoint.pointAroundPoint(*m_beginPoint, NEAR_LEVEL)) {
		setBegin(dPoint);
	}
	// 如果靠近终点，把重点设为这个
	else if (sPoint.pointAroundPoint(*m_endPoint, NEAR_LEVEL)) {
		setEnd(dPoint);
	}
}
