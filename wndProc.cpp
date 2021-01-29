#include "wndProc.h"

#include "eventLoop.h"
#include "event.h"

/**
 * @brief ������Ϣѭ��
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
 * @brief ���ڹ��̺���
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// �¼�ѭ������
	static EventLoop eventloop;    
	PAINTSTRUCT ps;

	Event* tosendEvent = eventloop.packageMessage(hwnd, message, wParam, lParam, &ps);

	// ����Լ������ˣ��ǾͲ���Ҫ����ϵͳĬ�ϴ��ڴ�����
	if (eventloop.event(tosendEvent))
		return 0;
	delete tosendEvent;

	return DefWindowProc(hwnd, message, wParam, lParam);
}

