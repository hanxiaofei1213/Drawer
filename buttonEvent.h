#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : buttonEvent.h
// Creator : ����ϲ
// Data : 2021/1/21
// Comment : ����ť��Ϣ��װ���¼��������ṩ���úͻ�ȡ��ťΨһid
//////////////////////////////////////////////////////////////////////////

#include "event.h"

class ButtonEvent : public Event {
public:
	ButtonEvent() : m_btnId(0) {}
	~ButtonEvent() {}


	int getBtnId() { return m_btnId; }           // ��ȡ��ťΨһid
	void setBtnId(int id) { m_btnId = id; }      // ���ð�ťΨһid

private:
	int m_btnId;                                 // ��ť��Ψһid
};
