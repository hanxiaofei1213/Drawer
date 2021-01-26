#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : wndProc.h
// Creator : 王文喜
// Data : 2021/1/14
// Comment : 1. 将窗口过程函数放在其中。2. 创建事件循环的全局变量，放入窗口过程函数中。3. 开启消息循环。
//////////////////////////////////////////////////////////////////////////
#include <windows.h>

// 开启消息循环
void BeginMessageLoop();

// 窗口过程函数，用来派发消息
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

