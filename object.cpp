
#include "object.h"

#include "event.h"

Object::Object(Object* a_parent) : m_instance(GetModuleHandle(NULL)), m_objectId(0)
{
	setParent(a_parent);
}

/**
 * @brief �ͷ��ڴ�
 */
Object::~Object()
{
	
}


/**
 * @brief ����Ӷ���
 * @param �Ӷ���
 * @return �����Ӷ����Ψһid
 */
int Object::addChild(Object* a_child)
{
	m_children.push_back(a_child);
	return m_children.size();
}

/**
 * @brief �����Լ��ĸ�����ͬʱ���Լ���ӵ���������б��У��������ú��Լ���Ψһid
 * @param �������ָ��
 * @remark B�ĸ�������A����C����������ΪB����˺����Զ���C�ĸ�����תΪA
 */
void Object::setParent(Object* a_parent)      
{         
	m_parent = a_parent;                        // ָ��������
	if (a_parent == NULL)                       // ���������ΪNULL����ʲôҲ������m_parent��Ĭ��ֵNULL
		return;
	else if (a_parent->getParent() != NULL)     // ����˴����и����󣬴˸�����Ҳ�и�����
	{
		setParent(a_parent->getParent());
	}
	else {
		m_objectId = a_parent->addChild(this);  // ���Լ���ӵ���������б��У�������Ψһid
	}
}

/**
 * @brief �����¼�ѭ����������¼��ַ�����ͬ�ĺ���
 */
bool Object::eventLoop(Event* a_event)
{
	return true;
}

