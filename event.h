#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : event.h
// Creator : ����ϲ
// Data : 2021/1/19
// Comment : �¼��࣬����Ϊ���ݵ�����
//////////////////////////////////////////////////////////////////////////


class Object;

class Event {
public:
	// �¼����͵�ö��
	enum class EventType {
		EVENT = 0, LBUTTONDOWN, LBUTTONUP, 
		RBUTTONDOWN, RBUTTONUP, MOUSEMOVE, 
		MOUSE_WHEEL, PAINTEVENT, MENU_COMMAND, 
		BUTTON_CLICK, BUTTON_DBLCLK, MOUSEDROP
	};

	Event();                                                      
	virtual ~Event() {}                                           
	
	Object* getDestObject() { return m_destObject; }                // ���Ŀ�Ķ���
	EventType getType() { return m_type; }                          // ����¼�������

	void setDestObject(Object* destObj) { m_destObject = destObj; }  // ����Ŀ��
	void setEventType(EventType type) { m_type = type; }             // �����¼�����

private:
	EventType m_type = EventType::EVENT;                             // �¼�������
	Object* m_destObject = nullptr;                                  // Ҫ���¼��͵����Ŀ�Ķ���
};
