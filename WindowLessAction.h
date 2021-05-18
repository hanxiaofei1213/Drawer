#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : WindowLessAction.h
// Creator : 王文喜
// Data : 2021/04/29
// Comment : 无句柄action，提供文字和图片action
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





