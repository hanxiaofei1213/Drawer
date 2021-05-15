#pragma once

#include "event.h"


class MouseWheelEvent : public Event
{
public:
	MouseWheelEvent();
	virtual ~MouseWheelEvent();

	void setWheelDistance(int num) { m_wheelDistance = num / 100; }
	int getWheelDistance() { return m_wheelDistance; }

private:
	int m_wheelDistance = 0;
};


