
#include "object.h"

#include "event.h"

Object::Object(Object* parent) {
	setParent(parent);
}

/**
 * @brief �ͷ��ڴ�
 */
Object::~Object() {
	
}


/**
 * @brief ����Ӷ���
 * @param �Ӷ���
 * @return �����Ӷ����Ψһid
 */
int Object::addChild(Object* child) {
	m_children.push_back(child);
	return m_children.size();
}

/**
 * @brief �����Լ��ĸ�����ͬʱ���Լ���ӵ���������б��У��������ú��Լ���Ψһid
 * @param �������ָ��
 * @remark B�ĸ�������A����C����������ΪB����˺����Զ���C�ĸ�����תΪA
 */
void Object::setParent(Object* parent) {         
	m_parent = parent;                        // ָ��������
	if (parent == NULL)                       // ���������ΪNULL����ʲôҲ������m_parent��Ĭ��ֵNULL
		return;
	else if (parent->getParent() != NULL) {   // ����˴����и����󣬴˸�����Ҳ�и�����
		setParent(parent->getParent());
	}
	else {
		m_objectId = parent->addChild(this);  // ���Լ���ӵ���������б��У�������Ψһid
	}
}

/**
 * @brief �����¼�ѭ����������¼��ַ�����ͬ�ĺ���
 */
bool Object::eventLoop(Event* event) {
	return true;
}

