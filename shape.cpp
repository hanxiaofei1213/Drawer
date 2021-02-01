
#include "shape.h"

// 构造函数
Shape::Shape(HDC hdc) {
	m_hdc = hdc;
	m_painter = new Painter(m_hdc);
	m_state = StateType::NOMAL;
	m_shapeType = ShapeType::NODEFINE;
}

// 析构函数
Shape::~Shape() {
	delete m_painter;
}

void Shape::setHDC(HDC hdc) {
	m_hdc = hdc;
	m_painter->setHDC(hdc);
}
