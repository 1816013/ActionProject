#include <Windows.h>
#include "System/Application.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_  HINSTANCE,_In_ LPSTR, _In_ int)
{
	auto& app = Application::Instance();
	if (!app.Initialize())
	{
		return -1;
	}
	app.Run();
	app.Terminate();
	return 0;
}