#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : object.h
// Creator : ����ϲ
// Data : 2021/1/15
// Comment : ���з�װ�õĿؼ��Ļ��࣬�����Ӷ���֮��Ŀ������¼��ַ�
//////////////////////////////////////////////////////////////////////////

// Todo: ��ô�Ƴ��Ӷ���Ƿ���ǣ�
// Todo: �Ƴ��Ӷ���

#include <windows.h>
#include <vector>

#include "wndProc.h"

class Event;

class Object {
public:
	Object(Object* parent);
	virtual ~Object();

	HINSTANCE getInstance() { return m_instance; }      // ���ص�ǰʵ��
	int getObjectId() { return m_objectId; }            // ����Ψһid 
	Object* getParent() { return m_windowParent; }      // ��ø�����
	virtual void setParent(Object* a_parent);           // ���ø�����
	virtual void dispatchEvent(Event* event);           // ���¼��ɷ���ÿһ���Ӷ����eventLoop֮��
	virtual bool eventLoop(Event* event);               // �¼�ѭ���������ɷ��¼�

protected:
	virtual int addChild(Object* child);                // ����Ӷ���

private:
	Object* m_windowParent = nullptr;                   // ���ؼ�
	std::vector<Object*> m_children;                    // �ӿؼ��б����������ڴ��ͷź��ṩΨһid
	HINSTANCE m_instance = GetModuleHandle(NULL);       // ��ǰ�Ľ���ʵ��
	// Todo: id���ķ�ʽ�ǲ���Ҫ��һ�䣿
	int m_objectId = 0;                                 // ÿ���ؼ���Ψһid��ע��ÿ��id��m_chidren��С����
};

