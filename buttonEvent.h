#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : buttonEvent.h
// Creator : 王文喜
// Data : 2021/1/21
// Comment : 将按钮消息封装成事件，向外提供设置和获取按钮唯一id
//////////////////////////////////////////////////////////////////////////

#include "event.h"

class ButtonEvent : public Event {
public:
	ButtonEvent() : m_btnId(0) {}
	~ButtonEvent() {}


	int getBtnId() { return m_btnId; }                // 获取按钮唯一id
	void setBtnId(int id) { m_btnId = id; }           // 设置按钮唯一id

private:
	int m_btnId = 0;                                  // 按钮的唯一id
};
