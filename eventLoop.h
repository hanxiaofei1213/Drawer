#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : eventLoop.h
// Creator : ����ϲ
// Data : 2021/1/19
// Comment : �¼�ѭ����������Ϣ������¼��ַ�
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "object.h"

class Event;
class MouseEvent;
class ButtonEvent;
class PaintEvent;

class EventLoop {
public:
	EventLoop();
	virtual ~EventLoop();

	Event* packageMessage(HWND, UINT, WPARAM, LPARAM, PAINTSTRUCT*);       // �����̺�������Ϣ������¼�
	bool event();                                            // �ַ��¼�

protected:
	Object* calculateDestObject(HWND);                       // ���Ŀ�Ķ����thisָ��
	MouseEvent* packageMouseMsg(HWND, UINT, WPARAM, LPARAM); // �������Ϣ������¼�
	ButtonEvent* packageBtnMsg(HWND, UINT, WPARAM, LPARAM);  // ����ť��Ϣ������¼�
	PaintEvent* packagePaintMsg(HWND, PAINTSTRUCT*);         // ���滭��Ϣ������¼�

private:
	Event* m_event;                                          // Ҫ������¼�
	
};
