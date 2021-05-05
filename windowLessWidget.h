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
class Painter;
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
	virtual void hide() override;

	// Todo: ��Ҫ֪���Ƿ񱻵��ѡ�е�
	virtual bool eventLoop(Event* event) override;

	RECT getRect() { return m_rect; }

protected:
	void init();
	void initMemBitMap();
	void releaseMemBitMap();
	Painter* getPainter() { return m_painter; }
	/**
	 * @brief ����location��width height����rect����
	 */
	void updateRect();

private:
	Point m_location;
	int m_nWidth = 100;
	int m_nHeight = 60;
	RECT m_rect = { 0 };
	WindowWidget* m_windowParent = nullptr; 	
	Painter* m_painter = nullptr;
	Painter* m_memPainter = nullptr;
	HDC m_HDC = nullptr;
	HDC m_memHDC = nullptr;
	HBITMAP m_memBitmap = nullptr;
	HBRUSH m_hBursh = CreateSolidBrush(RGB(255, 255, 255));
};


