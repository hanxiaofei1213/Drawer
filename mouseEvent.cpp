
#include "mouseEvent.h"


MouseEvent::~MouseEvent() {
	delete m_mosPos;
}


/**
 * @brief 设置鼠标的坐标
 * @param a_nx 鼠标x坐标
 * @param a_ny 鼠标y坐标
 */
void MouseEvent::setPos(int nx, int ny) {
	m_mosPos->setX(nx);
	m_mosPos->setY(ny);
}
