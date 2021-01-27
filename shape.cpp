
#include "shape.h"

// ���캯��
Shape::Shape(HDC a_hdc)
{
	m_hdc = a_hdc;
	m_painter = new Painter(m_hdc);
	m_state = StateType::NOMAL;
	m_shapeType = ShapeType::NODEFINE;
}

// ��������
Shape::~Shape()
{
	delete m_painter;
}

void Shape::setHDC(HDC a_hdc)
{
	m_hdc = a_hdc;
	m_painter->setHDC(a_hdc);
}
