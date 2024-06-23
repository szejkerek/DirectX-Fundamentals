#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	System system;
	if (system.Initialize(1920, 1080, true))
	{
		system.Run();
	}

	system.Shutdown();
	return 0;
}
