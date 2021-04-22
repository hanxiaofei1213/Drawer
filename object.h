#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : object.h
// Creator : 王文喜
// Data : 2021/1/15
// Comment : 所有封装好的控件的基类，负责父子对象之间的控制与事件分发
//////////////////////////////////////////////////////////////////////////

// Todo: 怎么移除子对象还欠考虑！
// Todo: 移除子对象

#include <windows.h>
#include <vector>

#include "wndProc.h"

class Event;

class Object {
public:
	Object(Object* parent);
	virtual ~Object();

	HINSTANCE getInstance() { return m_instance; }      // 返回当前实例
	int getObjectId() { return m_objectId; }            // 返回唯一id 
	Object* getParent() { return m_parent; }            // 获得父对象
	void setParent(Object* a_parent);                   // 设置父对象
	virtual void dispatchEvent(Event* event);           // 将事件派发到每一个子对象的eventLoop之中
	virtual bool eventLoop(Event* event);               // 事件循环，负责派发事件

protected:
	virtual int addChild(Object* child);                // 添加子对象

private:
	Object* m_parent = nullptr;                         // 父控件
	std::vector<Object*> m_children;                    // 子控件列表，用来管理内存释放和提供唯一id
	HINSTANCE m_instance = GetModuleHandle(NULL);       // 当前的进程实例
	// Todo: id定的方式是不是要变一变？
	int m_objectId = 0;                                 // 每个控件的唯一id，注意每个id由m_chidren大小来定
};

