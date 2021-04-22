#include "wndProc.h"

#include "eventLoop.h"
#include "event.h"

/**
 * @brief 开启消息循环
 */
void BeginMessageLoop() {
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

/**
 * @brief 窗口过程函数
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// 事件循环对象
	static EventLoop eventloop;    
	PAINTSTRUCT ps;

	Event* tosendEvent = eventloop.packageMessage(hwnd, message, wParam, lParam, &ps);

	// 如果自己处理了，那就不需要调用系统默认窗口处理函数
	if (eventloop.event(tosendEvent))
		return 0;
	delete tosendEvent;                     // Todo: 这里味道怪怪的，虽然确实这样可以，但是改一下吧

	return DefWindowProc(hwnd, message, wParam, lParam);
}

