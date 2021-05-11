#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : showObject.h
// Creator : ����ϲ
// Data : 2021/04/19
// Comment : �̳�object�������ṩ��ʾ�����Լ������С���ԣ������п�չʾ��Ļ���
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include "event.h"
#include "object.h"
#include "point.h"

class ButtonEvent;
class MouseEvent;
class PaintEvent;


class ShowObject :public Object
{
public:
	ShowObject(ShowObject* parent = nullptr);
	virtual ~ShowObject();

	virtual void addShowList(ShowObject* object);                            // ��ӵ�չʾ�б���
	std::vector<ShowObject*>& getShowList();                                 // ����չʾ�б�
	virtual bool eventLoop(Event* event) override;
	void showChildren();

	virtual void move(Point loc) = 0;                                        // �ƶ�����λ��
	virtual void move(int x, int y) = 0;                                     // �ƶ�����λ��
	virtual void resize(int width, int height) = 0;                          // ���ô�С
	virtual void show() = 0;                                                 // ��ʾ�������
	virtual void hide() = 0;
	bool isShow() { return m_bShow; }
	void setVisiable(bool bShow) { m_bShow = bShow; }

protected:
	virtual void mousePressEvent(MouseEvent* event);                     // ������갴�µ��¼�
	virtual void mouseMoveEvent(MouseEvent* event);                      // ��������ƶ����¼�
	virtual void mouseReleaseEvent(MouseEvent* event);                   // ������갴�µ��¼�
	virtual void paintEvent(PaintEvent* event);                          // �����ػ��¼�
	virtual void buttonPressEvent(ButtonEvent* event);                   // ����ť���µ��¼��ַ�������İ�ť

private:
	std::vector<ShowObject*> m_showChildList;                            // ��������չʾ�ؼ���������show()�����У�չʾ����
	bool m_bShow = true;  
};







