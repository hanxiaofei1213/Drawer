#include "wndProc.h"

#include "eventLoop.h"

/**
 * @brief 开启消息循环
 */
void BeginMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

/**
 * @brief 窗口过程函数
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 事件循环对象
	static EventLoop eventloop;    
	PAINTSTRUCT ps;

	eventloop.packageMessage(hwnd, message, wParam, lParam, &ps);

	// 如果自己处理了，那就不需要调用系统默认窗口处理函数
	if (eventloop.event())
		return 0;
	return DefWindowProc(hwnd, message, wParam, lParam);
}

