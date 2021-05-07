#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName : showObject.h
// Creator : 王文喜
// Data : 2021/04/19
// Comment : 继承object，额外提供显示方法以及坐标大小属性，是所有可展示类的基类
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

	virtual void addShowList(ShowObject* object);                            // 添加到展示列表中
	std::vector<ShowObject*>& getShowList();                                 // 返回展示列表
	virtual bool eventLoop(Event* event) override;
	void showChildren();

	virtual void move(Point loc) = 0;                                        // 移动窗口位置
	virtual void move(int x, int y) = 0;                                     // 移动窗口位置
	virtual void resize(int width, int height) = 0;                          // 设置大小
	virtual void show() = 0;                                                 // 显示这个窗口
	virtual void hide() = 0;
	bool isShow() { return m_bShow; }

protected:
	void setShowState(bool bShow) { m_bShow = bShow; }
	virtual void mousePressEvent(MouseEvent* event);                     // 处理鼠标按下的事件
	virtual void mouseMoveEvent(MouseEvent* event);                      // 处理鼠标移动的事件
	virtual void mouseReleaseEvent(MouseEvent* event);                   // 处理鼠标按下的事件
	virtual void paintEvent(PaintEvent* event);                          // 处理重绘事件
	virtual void buttonPressEvent(ButtonEvent* event);                   // 将按钮按下的事件分发到具体的按钮

private:
	std::vector<ShowObject*> m_showChildList;                            // 保存所有展示控件，用于在show()函数中，展示所有
	bool m_bShow = true;  
};







