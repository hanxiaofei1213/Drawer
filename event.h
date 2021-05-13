#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : event.h
// Creator : 王文喜
// Data : 2021/1/19
// Comment : 事件类，仅作为数据的载体
//////////////////////////////////////////////////////////////////////////


class Object;

class Event {
public:
	// 事件类型的枚举
	enum class EventType {
		EVENT = 0, LBUTTONDOWN, LBUTTONUP, 
		RBUTTONDOWN, RBUTTONUP, MOUSEMOVE, 
		PAINTEVENT, MENU_COMMAND, 
		BUTTON_CLICK, BUTTON_DBLCLK, MOUSEDROP
	};

	Event();                                                      
	virtual ~Event() {}                                           
	
	Object* getDestObject() { return m_destObject; }                // 获得目的对象
	EventType getType() { return m_type; }                          // 获得事件的类型

	void setDestObject(Object* destObj) { m_destObject = destObj; }  // 设置目的
	void setEventType(EventType type) { m_type = type; }             // 设置事件类型

private:
	EventType m_type = EventType::EVENT;                             // 事件的类型
	Object* m_destObject = nullptr;                                  // 要把事件送到这个目的对象
};
