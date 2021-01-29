
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
void MouseEvent::setPos(int nx, int ny)
{
	m_mosPos->setX(nx);
	m_mosPos->setY(ny);
}
