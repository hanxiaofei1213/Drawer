#pragma once


//////////////////////////////////////////////////////////////////////////
// FileName : windowLessWidget.h
// Creator : ����ϲ
// Data : 2021/4/18
// Comment : �̳�object���������޾���ؼ��ĸ��࣬�ṩ�����Ŀؼ�������ע�⣬�޾���������޷������Ϣ�ģ�Ҫ�봦����Ϣ������о���Ĵ�������ȡ
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include <windows.h>

#include "point.h"
#include "showObject.h"

class Event;
class Size;
class WindowWidget;

class WindowLessWidget : public ShowObject
{
public:
	WindowLessWidget(ShowObject* parent = nullptr);
	virtual ~WindowLessWidget();

	virtual void move(Point loc) override;
	virtual void move(int x, int y) override;
	virtual void resize(int width, int height) override;
	virtual void show() override;

	// Todo: ��Ҫ֪���Ƿ񱻵��ѡ�е�
	virtual bool eventLoop(Event* event) override;

protected:
	void updataUI();

private:
	Point m_location;
	int m_nWidth = 100;
	int m_nHeight = 60;
	WindowWidget* m_parent = nullptr;
};


