# include <windows.h>

#include "drawer.h"




int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE , _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	Drawer drawer;

	drawer.show();

	BeginMessageLoop();
	return 0;
}


