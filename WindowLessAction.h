#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : WindowLessAction.h
// Creator : ����ϲ
// Data : 2021/04/29
// Comment : �޾��action���ṩ���ֺ�ͼƬaction
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





