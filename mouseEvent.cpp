
#include "mouseEvent.h"


MouseEvent::MouseEvent()
{
	m_mosPos = new Point;
	m_buttonType = MouseEvent::ButtonType::NOBUTTON;
}


MouseEvent::~MouseEvent()
{
	delete m_mosPos;
}


/**
 * @brief ������������
 * @param a_nx ���x����
 * @param a_ny ���y����
 */
void MouseEvent::setPos(int a_nx, int a_ny)
{
	m_mosPos->setX(a_nx);
	m_mosPos->setY(a_ny);
}
