#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : object.h
// Creator : 王文喜
// Data : 2021/1/15
// Comment : 所有封装好的控件的基类，提供事件分发和对象树维护
//////////////////////////////////////////////////////////////////////////


// TODO: 怎么移除子对象还欠考虑！

#include <windows.h>
#include <vector>

#include "wndProc.h"

class Event;

class Object {
public:
	Object(Object*);
	virtual ~Object();

	virtual int addChild(Object*);                      // 添加子对象
	HINSTANCE getInstance() { return m_instance; }      // 返回当前实例
	int getObjectId() { return m_objectId; }            // 返回唯一id 
	Object* getParent() { return m_parent; }            // 获得父对象
	void setParent(Object* a_parent);                   // 设置父对象

	virtual bool eventLoop(Event*);                     // 事件循环，负责派发事件

private:
	Object* m_parent;                                   // 父控件
	std::vector<Object*> m_children;                    // 子控件列表，用来管理内存释放和提供唯一id！！！
	HINSTANCE m_instance;                               // 当前的进程实例
	int m_objectId;                                     // 每个控件的唯一id
};

