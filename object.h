#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : object.h
// Creator : ����ϲ
// Data : 2021/1/15
// Comment : ���з�װ�õĿؼ��Ļ��࣬�ṩ�¼��ַ��Ͷ�����ά��
//////////////////////////////////////////////////////////////////////////


// TODO: ��ô�Ƴ��Ӷ���Ƿ���ǣ�

#include <windows.h>
#include <vector>

#include "wndProc.h"

class Event;

class Object {
public:
	Object(Object*);
	virtual ~Object();

	virtual int addChild(Object*);                      // ����Ӷ���
	HINSTANCE getInstance() { return m_instance; }      // ���ص�ǰʵ��
	int getObjectId() { return m_objectId; }            // ����Ψһid 
	Object* getParent() { return m_parent; }            // ��ø�����
	void setParent(Object* a_parent);                   // ���ø�����

	virtual bool eventLoop(Event*);                     // �¼�ѭ���������ɷ��¼�

private:
	Object* m_parent;                                   // ���ؼ�
	std::vector<Object*> m_children;                    // �ӿؼ��б����������ڴ��ͷź��ṩΨһid������
	HINSTANCE m_instance;                               // ��ǰ�Ľ���ʵ��
	int m_objectId;                                     // ÿ���ؼ���Ψһid
};

