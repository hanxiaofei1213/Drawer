#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : mouseEvent.h
// Creator : 王文喜
// Data : 2021/1/19
// Comment : 鼠标事件，保存触发事件的鼠标按钮和触发时位置
//////////////////////////////////////////////////////////////////////////

#include "event.h"
#include "point.h"

class MouseEvent : public Event {
public:
	enum class ButtonType {NOBUTTON, LEFTBUTTON, RIGHTBUTTON, MIDBUTTON};

	MouseEvent();
	virtual ~MouseEvent();

	Point* getPos() { return m_mosPos; }                      // 返回鼠标相对位置
	ButtonType getButtonType() { return m_buttonType; }       // 返回鼠标按钮类型
	 
	void setPos(int nx, int ny);                              // 设置鼠标坐标
	void setButtonType(ButtonType type) { m_buttonType = type; }  // 设置按钮类型

private:
	Point* m_mosPos;                                         // 鼠标点击位置的相对坐标
	ButtonType m_buttonType;                                 // 鼠标按键
};

