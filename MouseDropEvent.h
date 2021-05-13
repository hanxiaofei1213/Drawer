//////////////////////////////////////////////////////////////////////////
// FileName : MouseDropEvent.h
// Creator : 王文喜
// Data : 2021/05/13
// Comment : 鼠标拖拽事件
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "event.h"

class MouseDropEvent : public Event
{
public:
	enum class DropType
	{
		NODEFINE,
		RIGHT2LEFT,
		LEFT2RIGHT,
		TOP2BOTTOM,
		BOTTOM2TOP
	};

	MouseDropEvent();
	virtual ~MouseDropEvent();

	void setDropType(DropType type) { m_dropType = type; }
	DropType getDropType() { return m_dropType; }

private:
	DropType m_dropType = DropType::NODEFINE;

};





