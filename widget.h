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
	Widget(ShowObject* a_parent);
	virtual ~Widget();

	virtual bool eventLoop(Event*) override;                       // ��дObject���¼�ѭ��
	
protected:
	virtual void mousePressEvent(MouseEvent*);                     // ������갴�µ��¼�
	virtual void mouseMoveEvent(MouseEvent*);                      // ��������ƶ����¼�
	virtual void mouseReleaseEvent(MouseEvent*);                   // ������갴�µ��¼�
	virtual void paintEvent(PaintEvent*);                          // �����ػ��¼�
	virtual void buttonPressEvent(ButtonEvent*);                   // ����ť���µ��¼��ַ�������İ�ť

};
