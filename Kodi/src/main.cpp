#include "pch.h"


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR nCmdLine, _In_ int nCmdShow)
{
	WNDCLASS wc{};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"MAINWINDOW";
	RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(0, L"MAINWINDOW", L"Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(35, 38, 40)));
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		break; 
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return TRUE;
}
