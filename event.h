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
		PAINTEVENT, MENU_COMMAND, 
		BUTTON_CLICK, BUTTON_DBLCLK
	};

	Event();                                            // ���캯��
	virtual ~Event() {}                                 // ��������
	
	Object* getDestObject() { return m_destObject; }    // ���Ŀ�Ķ���
	EventType getType() { return m_type; }              // ����¼�������

	void setDestObject(Object* a_destObj) { m_destObject = a_destObj; }  // ����Ŀ��
	void setEventType(EventType a_type) { m_type = a_type; }             // �����¼�����

private:
	EventType m_type;                                   // �¼�������
	Object* m_destObject;                               // Ҫ���¼��͵����Ŀ�Ķ���
};
