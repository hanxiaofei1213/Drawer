# include <windows.h>

#include "drawer.h"

// only for test
#include "test.h"
#include "rectangle.h"


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE , _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	//Drawer drawer;
	//drawer.show();

	Test test;
	test.show();

	Rect r(GetDC(test.getHwnd()));
	r.setBegin({ 100, 100 });
	r.setEnd({ 300, 200 });
	r.draw();

	BeginMessageLoop();
	return 0;
}


