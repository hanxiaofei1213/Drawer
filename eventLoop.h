#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : eventLoop.h
// Creator : ����ϲ
// Data : 2021/1/19
// Comment : �¼�ѭ����������Ϣ������¼������¼��ַ�����Ӧ��widget
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "object.h"

class ButtonEvent;
class Event;
class MouseDropEvent;
class MouseEvent;
class PaintEvent;
class Point;

class EventLoop {
public:
	EventLoop();
	virtual ~EventLoop();

	Event* packageMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* ps); // �����̺�������Ϣ������¼�
	bool event(Event* toSendEvent);                                                     // �ַ��¼�

protected:
	Object* calculateDestObject(HWND hwnd);                                             // ���Ŀ�Ķ����thisָ��
	MouseEvent* packageMouseMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); // �������Ϣ������¼�
	ButtonEvent* packageBtnMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  // ����ť��Ϣ������¼�
	PaintEvent* packagePaintMsg(HWND hwnd, PAINTSTRUCT* ps);                            // ���滭��Ϣ������¼�

	/**
	 * @brief �������϶���Ϣ���¼�
	 */
	MouseDropEvent* packageMouseDropMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	/**
	 * @brief �������϶��ķ���
	 */
	bool checkMouseDropType(Point* begin, Point* end, MouseDropEvent* event);
};
