
#include "object.h"

#include "event.h"

Object::Object(Object* parent) {
	setParent(parent);
}

/**
 * @brief 释放内存
 */
Object::~Object() {
	
}


/**
 * @brief 添加子对象
 * @param 子对象
 * @return 返回子对象的唯一id
 */
int Object::addChild(Object* child) {
	m_children.push_back(child);
	return m_children.size();
}

/**
 * @brief 设置自己的父对象，同时把自己添加到父对象的列表中，并且设置好自己的唯一id
 * @param 父对象的指针
 * @remark B的父对象是A，若C将父对象设为B，则此函数自动将C的父对象转为A
 */
void Object::setParent(Object* parent) {         
	m_parent = parent;                        // 指定父对象
	if (parent == NULL)                       // 如果父对象为NULL，则什么也不做，m_parent是默认值NULL
		return;
	else if (parent->getParent() != NULL) {   // 如果此窗口有父对象，此父对象也有父对象
		setParent(parent->getParent());
	}
	else {
		m_objectId = parent->addChild(this);  // 将自己添加到父对象的列表中，并设置唯一id
	}
}

/**
 * @brief 开启事件循环，负责把事件分发给不同的函数
 */
bool Object::eventLoop(Event* event) {
	return true;
}

