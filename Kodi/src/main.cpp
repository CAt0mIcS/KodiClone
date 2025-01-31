#include "pch.h"

#include "Application.h"


int APIENTRY wWinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ PWSTR /*nCmdLine*/, _In_ int /*nCmdShow*/)
{
	try
	{
		return Application{}.Run();
	}
	catch (KodiException& e)
	{
		MessageBoxA(NULL, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(NULL, "Unknown Exception", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}

