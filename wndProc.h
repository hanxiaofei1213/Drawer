#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : wndProc.h
// Creator : ����ϲ
// Data : 2021/1/14
// Comment : 1. �����ڹ��̺����������С�2. �����¼�ѭ����ȫ�ֱ��������봰�ڹ��̺����С�3. ������Ϣѭ����
//////////////////////////////////////////////////////////////////////////
#include <windows.h>

// ������Ϣѭ��
void BeginMessageLoop();

// ���ڹ��̺����������ɷ���Ϣ
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

