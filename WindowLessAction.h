#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : WindowLessAction.h
// Creator : ����ϲ
// Data : 2021/04/29
// Comment : �޾��action���ṩ���ֺ�ͼƬaction
//////////////////////////////////////////////////////////////////////////
#include "point.h"
#include "windowLessWidget.h"

class Shape;
class Rect;

class WindowLessAction : public WindowLessWidget
{

public:
	WindowLessAction(WindowLessWidget* parent = nullptr);
	virtual ~WindowLessAction();
	virtual void show() override;

	Shape* getShape() { return m_shape; }

	void setText(LPCTSTR text) { m_pText = text; }
	void setShape(Shape* rect) { m_shape = rect; }

protected:
	void checkShapeSize();
	void checkShapeLoc();

private:
	LPCTSTR m_pText = nullptr;
	Shape* m_shape = nullptr;
};





