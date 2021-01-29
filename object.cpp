
#include "object.h"

#include "event.h"

Object::Object(Object* a_parent) : m_instance(GetModuleHandle(NULL)), m_objectId(0)
{
	setParent(a_parent);
}

/**
 * @brief 释放内存
 */
Object::~Object()
{
	
}


/**
 * @brief 添加子对象
 * @param 子对象
 * @return 返回子对象的唯一id
 */
int Object::addChild(Object* a_child)
{
	m_children.push_back(a_child);
	return m_children.size();
}

/**
 * @brief 设置自己的父对象，同时把自己添加到父对象的列表中，并且设置好自己的唯一id
 * @param 父对象的指针
 * @remark B的父对象是A，若C将父对象设为B，则此函数自动将C的父对象转为A
 */
void Object::setParent(Object* a_parent)      
{         
	m_parent = a_parent;                        // 指定父对象
	if (a_parent == NULL)                       // 如果父对象为NULL，则什么也不做，m_parent是默认值NULL
		return;
	else if (a_parent->getParent() != NULL)     // 如果此窗口有父对象，此父对象也有父对象
	{
		setParent(a_parent->getParent());
	}
	else {
		m_objectId = a_parent->addChild(this);  // 将自己添加到父对象的列表中，并设置唯一id
	}
}

/**
 * @brief 开启事件循环，负责把事件分发给不同的函数
 */
bool Object::eventLoop(Event* a_event)
{
	return true;
}

