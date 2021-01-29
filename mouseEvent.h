#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : mouseEvent.h
// Creator : ����ϲ
// Data : 2021/1/19
// Comment : ����¼������津���¼�����갴ť�ʹ���ʱλ��
//////////////////////////////////////////////////////////////////////////

#include "event.h"
#include "point.h"

class MouseEvent : public Event {
public:
	enum class ButtonType {NOBUTTON, LEFTBUTTON, RIGHTBUTTON, MIDBUTTON};

	MouseEvent();
	virtual ~MouseEvent();

	Point* getPos() { return m_mosPos; }                      // ����������λ��
	ButtonType getButtonType() { return m_buttonType; }       // ������갴ť����
	 
	void setPos(int nx, int ny);                              // �����������
	void setButtonType(ButtonType type) { m_buttonType = type; }  // ���ð�ť����

private:
	Point* m_mosPos;                                         // �����λ�õ��������
	ButtonType m_buttonType;                                 // ��갴��
};

