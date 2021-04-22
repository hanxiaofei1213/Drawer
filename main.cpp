# include <windows.h>

#include "drawer.h"

// only for test
#include "test.h"


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE , _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	Drawer drawer;
	drawer.show();

	//Test test;
	//test.show();

	BeginMessageLoop();
	return 0;
}


