#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : WindowLessAction.h
// Creator : 王文喜
// Data : 2021/04/29
// Comment : 无句柄action，提供文字和图片action
//////////////////////////////////////////////////////////////////////////

#include "windowLessWidget.h"


class WindowLessAction : public WindowLessWidget
{

public:
	WindowLessAction(WindowLessWidget* parent = nullptr);
	virtual ~WindowLessAction();
	virtual void show() override;

	void setText(LPCTSTR text);

private:
	LPCTSTR m_pText = nullptr;

};





