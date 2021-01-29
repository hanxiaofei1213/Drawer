#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : widget.h
// Creator : ����ϲ
// Data : 2021/1/18
// Comment : ����ؼ�����WNDCLASS�Ȳ�����װ������ӵ�д����¼���������Ҳӵ�г�Ϊ�����ؼ����ؼ�������
//////////////////////////////////////////////////////////////////////////

#include <windows.h>

#include "showObject.h"

class MouseEvent;
class ButtonEvent;
class PaintEvent;

class Widget : public ShowObject {
public:
	Widget(ShowObject* parent);
	virtual ~Widget();

	virtual bool eventLoop(Event* event) override;                       // ��дObject���¼�ѭ��
	
protected:
	virtual void mousePressEvent(MouseEvent* event);                     // ������갴�µ��¼�
	virtual void mouseMoveEvent(MouseEvent* event);                      // ��������ƶ����¼�
	virtual void mouseReleaseEvent(MouseEvent* event);                   // ������갴�µ��¼�
	virtual void paintEvent(PaintEvent* event);                          // �����ػ��¼�
	virtual void buttonPressEvent(ButtonEvent* event);                   // ����ť���µ��¼��ַ�������İ�ť

};
